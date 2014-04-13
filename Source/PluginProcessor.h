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
#include <vector>
#include <stack>
//==============================================================================
/**
*/
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

	//==============================================================================
	void getStateInformation (MemoryBlock& destData);
	void setStateInformation (const void* data, int sizeInBytes);
	virtual void numChannelsChanged();

	Colour getStereoPairColor(int index) { return Colour::fromString("aa4ae329"); }
	size_t getMaxStereoPairCount() { return mMaxStereoPairCount; }
private:
	std::vector<tomatl::dsp::GonioCalculator<double>*> mGonioCalcs;
	std::vector<tomatl::dsp::SpectroCalculator<double>*> mSpectroCalcs;
	size_t mMaxStereoPairCount;
	
	
	
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdmvAudioProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
