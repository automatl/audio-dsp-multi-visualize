/*
  ==============================================================================

	SpectrometerControl.h
	Created: 7 Apr 2014 3:46:06pm
	Author:  Kykc

  ==============================================================================
*/

#ifndef SPECTROMETERCONTROL_H_INCLUDED
#define SPECTROMETERCONTROL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "TomatlImageType.h"
#include "ILateInitComponent.h"

//==============================================================================
/*
*/

class SpectrometerControl : public ILateInitComponent
{
private:
	AdmvAudioProcessor* mParentProcessor;
	tomatl::dsp::FrequencyDomainGrid mFreqGrid;
	size_t mRightBorder = 10;
	size_t mBottomBorder = 16;
	Image mBuffer;
	Image mBackground;
	Image mSurface;

	void redrawBackground()
	{
		Graphics g(mBackground);

		g.fillAll(LookAndFeel::getDefaultLookAndFeel().findColour(TomatlLookAndFeel::controlBackground));

		g.setColour(Colours::darkgrey);
		g.drawRect(getLocalBounds(), 2.f);

		g.setColour(Colours::darkgrey.withAlpha(0.3f));
		for (int i = 0; i < mFreqGrid.getFreqLineCount(); ++i)
		{
			auto line = mFreqGrid.getFreqLine(i);

			g.setColour(Colours::darkgrey.withAlpha(0.3f));
			g.drawLine(line.mLocation, 0, line.mLocation, mFreqGrid.getHeight());

			if (line.mLocation > 0)
			{
				g.setColour(LookAndFeel::getDefaultLookAndFeel().findColour(TomatlLookAndFeel::alternativeText1).withAlpha(0.6f));
				g.drawText(juce::String(line.mCaption.c_str()), juce::Rectangle<float>(line.mLocation - 12, mFreqGrid.getHeight(), 24, mBottomBorder), Justification::centred, false);
			}
		}

		for (int i = 0; i < mFreqGrid.getAmplLineCount(); ++i)
		{
			auto line = mFreqGrid.getAmplLine(i);

			g.setColour(Colours::darkgrey.withAlpha(0.3f));
			g.drawLine(juce::Line<float>(0, line.mLocation, mFreqGrid.getWidth(), line.mLocation));

			if (line.mLocation + 1 < mFreqGrid.getHeight())
			{
				g.setColour(LookAndFeel::getDefaultLookAndFeel().findColour(TomatlLookAndFeel::alternativeText1).withAlpha(0.6f));
				g.drawText(juce::String(line.mCaption.c_str()), juce::Rectangle<float>(mFreqGrid.getWidth() - 14, line.mLocation - 8, 30, 14), Justification::centredLeft, false);
			}
		}

		g.setColour(Colours::black);
		g.drawRect(getLocalBounds().expanded(-1.), 1.f);
	}

	void clearArgbImage(Image& subject)
	{
		Image::BitmapData pixels(subject, Image::BitmapData::readWrite);

		for (int i = 0; i < pixels.height; ++i)
		{
			memset(pixels.getLinePointer(i), 0x0, pixels.width * pixels.pixelStride);
		}
	}

public:
	SpectrometerControl(AdmvAudioProcessor* parent) : mFreqGrid(tomatl::dsp::Bound2D<double>(20., 30000., -72., 0.))
	{
		mParentProcessor = parent;
	}

	virtual void init(juce::Rectangle<int> bounds)
	{
		setSize(bounds.getWidth(), bounds.getHeight());
		mBuffer = Image(Image::ARGB, getWidth(), getHeight(), true, TomatlImageType());
		mBackground = Image(Image::RGB, getWidth(), getHeight(), true, TomatlImageType());
		mSurface = Image(Image::RGB, getWidth(), getHeight(), true, TomatlImageType());

		setOpaque(true);
		setPaintingIsUnclipped(true);

		mFreqGrid.updateSize(getWidth() - mRightBorder, getHeight() - mBottomBorder);
	}

	~SpectrometerControl()
	{
	}

	forcedinline void fillBoundsFromState(const AdmvPluginState& state, tomatl::dsp::Bound2D<double>& subject)
	{
		subject.X.mLow = mFreqGrid.fullScaleXToFreq(mFreqGrid.getWidth() / 100. * state.mSpectrometerFrequencyScale.first);
		subject.X.mHigh = mFreqGrid.fullScaleXToFreq(mFreqGrid.getWidth() / 100. * state.mSpectrometerFrequencyScale.second);

		subject.Y.mLow = mFreqGrid.fullScaleYToDb(mFreqGrid.getHeight() - mFreqGrid.getHeight() / 100. * state.mSpectrometerMagnitudeScale.first);
		subject.Y.mHigh = mFreqGrid.fullScaleYToDb(mFreqGrid.getHeight() - mFreqGrid.getHeight() / 100. * state.mSpectrometerMagnitudeScale.second);
	}


	void paint(Graphics& g)
	{
		if (mParentProcessor->mSpectroSegments == NULL)
		{
			return;
		}

		clearArgbImage(mBuffer);
		bool backgroundRedraw = false;
		tomatl::dsp::Bound2D<double> bounds;
		fillBoundsFromState(mParentProcessor->getState(), bounds);

		backgroundRedraw = backgroundRedraw || mFreqGrid.updateBounds(bounds);

		Graphics buffer(mBuffer);

		std::vector<std::pair<Path, int>> paths;

		LowLevelGraphicsSoftwareRenderer& c = dynamic_cast<LowLevelGraphicsSoftwareRenderer&>(g.getInternalContext());

		if (backgroundRedraw)
		{
			redrawBackground();
		}
		
		for (int pn = 0; pn < mParentProcessor->getMaxStereoPairCount(); ++pn)
		{
			tomatl::dsp::SpectrumBlock block = mParentProcessor->mSpectroSegments[pn];

			if (block.mLength <= 0)
			{
				continue;
			}

			mFreqGrid.updateSampleRate(block.mSampleRate);
			mFreqGrid.updateBinCount(block.mLength);

			int lastX = 0;
			int lastY = 0;
			int lastDx = 0;

			int y0, y1;
			y0 = y1 = mFreqGrid.minusInfToY();

			Path p;
			p.startNewSubPath(0, mFreqGrid.minusInfToY());

			bool firstSignificantPointAdded = false;
			
			// TODO: omit DC offset (f0 == 0)
			for (int i = 0; i < block.mLength - 1; i += 2)
			{
				double f0 = mFreqGrid.binNumberToFrequency(block.mData[i + 0].first);
				int x0 = mFreqGrid.freqToX(f0 > 0 ? f0 : 0.000001);
				y0 = std::min(y0, mFreqGrid.dbToY(TOMATL_TO_DB(block.mData[i + 0].second)));

				double f1 = mFreqGrid.binNumberToFrequency(block.mData[i + 1].first);
				int x1 = mFreqGrid.freqToX(f1);
				y1 = std::min(y1, mFreqGrid.dbToY(TOMATL_TO_DB(block.mData[i + 1].second)));

				if (!mFreqGrid.isFrequencyVisible(f0) && !mFreqGrid.isFrequencyVisible(f1))
				{
					continue;
				}

				if (!firstSignificantPointAdded)
				{
					p.lineTo(mFreqGrid.freqToX(mFreqGrid.binNumberToFrequency(0)), y0);

					firstSignificantPointAdded = true;
				}

				if (x0 - lastX > 5)
				{
					lastDx = x0 - lastX;

					p.quadraticTo(x0, y0, x1, y1);

					lastX = x1;
					lastY = y1;

					y0 = y1 = mFreqGrid.minusInfToY();
				}
				else if (x0 - lastX > 1)
				{
					lastDx = x0 - lastX;

					p.lineTo(x0, y0);
					p.lineTo(x1, y1);
					
					lastX = x1;
					lastY = y1;

					y0 = y1 = mFreqGrid.minusInfToY();
				}
			}

			// Our behaviour on how to approximate curve where we have no data is dependent on frequency -
			// on high frequencies we momentarily decay to zero,
			// on low frequencies we're drawing horizontal line till the end
			// This is kind of logical thing to do, as our frequency resolution decreases with the frequency and
			// each next bin becomes wider
			if (lastDx < 5)
			{
				p.lineTo(p.getCurrentPosition().getX(), mFreqGrid.dbToY(-1000.));
			}
			else
			{
				p.lineTo(mFreqGrid.getWidth(), p.getCurrentPosition().getY());
			}

			p.lineTo(mFreqGrid.getWidth(), mFreqGrid.getHeight() - 1);
			p.lineTo(0, mFreqGrid.getHeight() - 1);

			paths.push_back(std::pair<Path, int>(p, block.mIndex));
		}

		for (int i = 0; i < paths.size(); ++i)
		{
			Path p = paths[i].first;

			buffer.setColour(mParentProcessor->getStereoPairColor(paths[i].second));
			buffer.strokePath(p, PathStrokeType(1.f));
			
			buffer.setColour(mParentProcessor->getStereoPairColor(paths[i].second).withAlpha((float)0.1));
			buffer.fillPath(p);
		}
		
#if TOMATL_CUSTOM_BLENDING
		tomatl::draw::Util::blend(mBackground, mBuffer, mSurface);
		g.drawImageAt(mSurface, 0, 0, false);
#else
		g.drawImageAt(mBackground, 0, 0, false);
		g.drawImageAt(mBuffer, 0, 0, false);
#endif
	}

	void resized()
	{
		// This method is where you should set the bounds of any child
		// components that your component contains..
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrometerControl)
};


#endif  // SPECTROMETERCONTROL_H_INCLUDED
