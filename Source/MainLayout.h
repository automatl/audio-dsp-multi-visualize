/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_4057432C47622D16__
#define __JUCE_HEADER_4057432C47622D16__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainLayout  : public Component,
                    public ButtonListener,
                    public SliderListener
{
public:
    //==============================================================================
    MainLayout (AdmvAudioProcessor* plugin);
    ~MainLayout();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void updateInputChannels(size_t value) { mInputChannels.get()->setText(String(value), NotificationType::dontSendNotification); }

	void updateFromState(const AdmvPluginState& state)
	{
		mGonioManualScale.get()->setToggleState(state.mManualGoniometerScale, NotificationType::dontSendNotification);
		mGonioScaleValue.get()->setValue(TOMATL_TO_DB(state.mManualGoniometerScaleValue), NotificationType::dontSendNotification);
		mGonioScaleValue.get()->setEnabled(state.mManualGoniometerScale);
	}
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	AdmvAudioProcessor* mParentProcessor = NULL;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> mTestBtn;
    ScopedPointer<Label> mInputChannels;
    ScopedPointer<ToggleButton> mGonioManualScale;
    ScopedPointer<Slider> mGonioScaleValue;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainLayout)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_4057432C47622D16__
