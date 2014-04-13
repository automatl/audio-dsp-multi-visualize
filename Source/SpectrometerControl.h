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

//==============================================================================
/*
*/
class SpectrometerControl    : public Component
{
private:
	AdmvAudioProcessor* mParentProcessor;
	tomatl::dsp::OctaveScale mFreqScale;
	tomatl::dsp::LinearScale mMagnitudeScale;
	tomatl::dsp::Bound2D<double> mBounds;
	double* mFreqCache;

	Image mBuffer;
public:
	SpectrometerControl(AdmvAudioProcessor* parent)
	{
		setSize(600, 400);
		mBuffer = Image(Image::PixelFormat::RGB, getWidth(), getHeight(), true, TomatlImageType());
		mParentProcessor = parent;
		setOpaque(true);
		this->setPaintingIsUnclipped(true);
		mBounds.X.mLow = 20.;
		mBounds.X.mHigh = 22000.;

		mBounds.Y.mLow = -72.;
		mBounds.Y.mHigh = 0.;

		// TODO: fix possible crashes for sample rates > 96000
		mFreqCache = new double[48000];

		memset(mFreqCache, 0x0, sizeof(double) * 48000);
	}

	~SpectrometerControl()
	{
		delete mFreqCache;
	}

	int scaleX(double value, size_t binCount, size_t sampleRate)
	{
		int index = value;

		if (mFreqCache[index] == 0)
		{
			value = value * sampleRate / (binCount * 2);
			mFreqCache[index] = mFreqScale.scale(getWidth(), mBounds.X, value, true);
		}
		
		return mFreqCache[index];
	}

	// TODO: optimize somehow. maybe get dB values here, and just linearly scale them
	int scaleY(double value)
	{
		return getHeight() - mMagnitudeScale.scale(getHeight(), mBounds.Y, 20 * log10(value), true) - 1;
	}

	void paint(Graphics& g)
	{
		Graphics buffer(mBuffer);

		std::vector<std::pair<Path, int>> paths;

		LowLevelGraphicsSoftwareRenderer& c = dynamic_cast<LowLevelGraphicsSoftwareRenderer&>(g.getInternalContext());
		//Image* img = c.getImage();
		
		for (int pn = 0; pn < mParentProcessor->getMaxStereoPairCount(); ++pn)
		{
			tomatl::dsp::SpectrumBlock block = mParentProcessor->mSpectroSegments[pn];

			if (block.mLength <= 0)
			{
				continue;
			}

			int lastX = -10;
			Path p;
			p.startNewSubPath(0, getHeight() - 1);
			
			for (int i = 0; i < block.mLength - 1; i += 2)
			{
				int x0 = scaleX(block.mData[i + 0].first, block.mLength, block.mSampleRate);
				int y0 = scaleY(block.mData[i + 0].second);

				int x1 = scaleX(block.mData[i + 1].first, block.mLength, block.mSampleRate);
				int y1 = scaleY(block.mData[i + 1].second);

				if (x0 - lastX > 5)
				{
					p.quadraticTo(x0, y0, x1, y1);

					lastX = x1;
				}
				else if (x0 - lastX > 1)
				{
					p.lineTo(x0, y0);
					p.lineTo(x1, y1);
					
					lastX = x1;
				}
			}

			p.lineTo(getWidth(), getHeight() - 1);
			p.lineTo(0, getHeight() - 1);

			paths.push_back(std::pair<Path, int>(p, block.mIndex));
		}

		Image::BitmapData pixels(mBuffer, Image::BitmapData::ReadWriteMode::readWrite);

		// This is buffer.fillAll(Colours::black);
		for (int i = 0; i < pixels.height; ++i)
		{
			uint8* src = pixels.getLinePointer(i);
			memset(src, 0x0, pixels.width * pixels.pixelStride);
		}

		for (int i = 0; i < paths.size(); ++i)
		{
			Path p = paths[i].first;

			buffer.setColour(mParentProcessor->getStereoPairColor(paths[i].second));
			buffer.strokePath(p, PathStrokeType(1.f));
			
			buffer.setColour(mParentProcessor->getStereoPairColor(paths[i].second).withAlpha((float)0.1));
			buffer.fillPath(p);
		}
		
		g.drawImageAt(mBuffer, 0, 0, false);
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
