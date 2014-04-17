/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "dsp-utility.h"
#include "GonioPoints.h"
#include "PluginState.h"
#include <vector>
#include <stack>
//==============================================================================
/**
*/

#define TOMATL_PLUGIN_SET_PROPERTY(name, value) mState. name = value; makeCurrentStateEffective()

class AdmvAudioProcessor  : public AudioProcessor
{
public:
	tomatl::dsp::SpectrumBlock* mSpectroSegments;
	GonioPoints<double>* mGonioSegments;
	//==============================================================================
	AdmvAudioProcessor();
	~AdmvAudioProcessor();

	//==============================================================================
	void prepareToPlay (double sampleRate, int samplesPerBlock);
	void releaseResources();

	void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

	//==============================================================================
	AudioProcessorEditor* createEditor();
	bool hasEditor() const;

	//==============================================================================
	const String getName() const;

	int getNumParameters();

	float getParameter (int index);
	void setParameter (int index, float newValue);

	const String getParameterName (int index);
	const String getParameterText (int index);

	const String getInputChannelName (int channelIndex) const;
	const String getOutputChannelName (int channelIndex) const;
	bool isInputChannelStereoPair (int index) const;
	bool isOutputChannelStereoPair (int index) const;

	bool acceptsMidi() const;
	bool producesMidi() const;
	bool silenceInProducesSilenceOut() const;
	double getTailLengthSeconds() const;

	//==============================================================================
	int getNumPrograms();
	int getCurrentProgram();
	void setCurrentProgram (int index);
	const String getProgramName (int index);
	void changeProgramName (int index, const String& newName);

	const AdmvPluginState& getState() { return mState; }

	void setManualGonioScaleEnabled(bool value) { TOMATL_PLUGIN_SET_PROPERTY(mManualGoniometerScale, value); }
	void setManualGonioScaleValue(double value) { TOMATL_PLUGIN_SET_PROPERTY(mManualGoniometerScaleValue, value); }
	void setSpectroMagnitudeScale(std::pair<double, double> value) { TOMATL_PLUGIN_SET_PROPERTY(mSpectrometerMagnitudeScale, value); }
	void setSpectroFrequencyScale(std::pair<double, double> value) { TOMATL_PLUGIN_SET_PROPERTY(mSpectrometerFrequencyScale, value); }

	//==============================================================================
	void getStateInformation (MemoryBlock& destData);
	void setStateInformation (const void* data, int sizeInBytes);
	virtual void numChannelsChanged();

	size_t getCurrentInputCount() { return mCurrentInputCount; }

	Colour getStereoPairColor(int index) 
	{ 
		/*0x4ae329,
			0x3192e7,
			0xc628e7,
			0x5218f7,
			0xc6ff18,
			0xf72021*/
		// TODO: store collection and return const references
		if (index == 0)
		{
			return Colour::fromString("ff4ae329");
		}
		else if (index == 1)
		{
			return Colour::fromString("ff3192e7");
		}
		else if (index = 2)
		{
			return Colour::fromString("ffc628e7");
		}
		else if (index = 3)
		{
			return Colour::fromString("ff5218f7");
		}
		else
		{
			return Colour::fromString("ffc6ff18");
		}
	}
	size_t getMaxStereoPairCount() { return mMaxStereoPairCount; }

	double mLastGonioScale;

private:
	std::vector<tomatl::dsp::GonioCalculator<double>*> mGonioCalcs;
	std::vector<tomatl::dsp::SpectroCalculator<double>*> mSpectroCalcs;
	size_t mMaxStereoPairCount;
	size_t mCurrentInputCount;
	AdmvPluginState mState;
	
	void makeCurrentStateEffective();

	uint8 getStateVersion()
	{
		return 3;
	}

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdmvAudioProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
