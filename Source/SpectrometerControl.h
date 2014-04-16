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
public:
	SpectrometerControl(AdmvAudioProcessor* parent) : mFreqGrid(tomatl::dsp::Bound2D<double>(20., 30000., -72., 0.))
	{
		mParentProcessor = parent;
	}

	virtual void init(juce::Rectangle<int> bounds)
	{
		setSize(bounds.getWidth(), bounds.getHeight());
		mBuffer = Image(Image::PixelFormat::RGB, getWidth(), getHeight(), true, TomatlImageType());
		
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
		
		// Zoom viewport if requested
		tomatl::dsp::Bound2D<double> bounds;
		fillBoundsFromState(mParentProcessor->getState(), bounds);
		mFreqGrid.updateBounds(bounds);

		Graphics buffer(mBuffer);

		std::vector<std::pair<Path, int>> paths;

		LowLevelGraphicsSoftwareRenderer& c = dynamic_cast<LowLevelGraphicsSoftwareRenderer&>(g.getInternalContext());
		
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

			Path p;
			p.startNewSubPath(0, mFreqGrid.getHeight() - 1);

			bool firstSignificantPointAdded = false;
			
			for (int i = 0; i < block.mLength - 1; i += 2)
			{
				double f0 = mFreqGrid.binNumberToFrequency(block.mData[i + 0].first);
				int x0 = mFreqGrid.freqToX(f0);
				int y0 = mFreqGrid.dbToY(TOMATL_TO_DB(block.mData[i + 0].second));

				double f1 = mFreqGrid.binNumberToFrequency(block.mData[i + 1].first);
				int x1 = mFreqGrid.freqToX(f1);
				int y1 = mFreqGrid.dbToY(TOMATL_TO_DB(block.mData[i + 1].second));

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
					p.quadraticTo(x0, y0, x1, y1);

					lastX = x1;
					lastY = y1;
				}
				else if (x0 - lastX > 1)
				{
					p.lineTo(x0, y0);
					p.lineTo(x1, y1);
					
					lastX = x1;
					lastY = y1;
				}
			}

			p.lineTo(mFreqGrid.getWidth(), p.getCurrentPosition().getY());
			p.lineTo(mFreqGrid.getWidth(), mFreqGrid.getHeight() - 1);
			p.lineTo(0, mFreqGrid.getHeight() - 1);

			paths.push_back(std::pair<Path, int>(p, block.mIndex));
		}

		Image::BitmapData pixels(mBuffer, Image::BitmapData::ReadWriteMode::readWrite);

		buffer.fillAll(Colour::fromString("FF101010"));

		for (int i = 0; i < paths.size(); ++i)
		{
			Path p = paths[i].first;

			buffer.setColour(mParentProcessor->getStereoPairColor(paths[i].second));
			buffer.strokePath(p, PathStrokeType(1.f));
			
			buffer.setColour(mParentProcessor->getStereoPairColor(paths[i].second).withAlpha((float)0.1));
			buffer.fillPath(p);
		}
		
		g.drawImageAt(mBuffer, 0, 0, false);
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

	void resized()
	{
		// This method is where you should set the bounds of any child
		// components that your component contains..
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrometerControl)
};


#endif  // SPECTROMETERCONTROL_H_INCLUDED
