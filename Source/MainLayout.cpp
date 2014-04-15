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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainLayout.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "PluginProcessor.h"
//[/MiscUserDefs]

//==============================================================================
MainLayout::MainLayout (AdmvAudioProcessor* plugin)
{
    addAndMakeVisible (mInputChannels = new Label ("Input Channels",
                                                   TRANS("0")));
    mInputChannels->setFont (Font (15.00f, Font::plain));
    mInputChannels->setJustificationType (Justification::centredLeft);
    mInputChannels->setEditable (false, false, false);
    mInputChannels->setColour (TextEditor::textColourId, Colours::black);
    mInputChannels->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (mGonioManualScale = new ToggleButton ("Goniometer Manual Scale"));
    mGonioManualScale->setButtonText (TRANS("Custom scale"));
    mGonioManualScale->addListener (this);

    addAndMakeVisible (mGonioScaleValue = new Slider ("Gonio Scale Value"));
    mGonioScaleValue->setRange (-72, 0, 0);
    mGonioScaleValue->setSliderStyle (Slider::LinearVertical);
    mGonioScaleValue->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    mGonioScaleValue->addListener (this);

    addAndMakeVisible (mSpectroMagnitudeScale = new Slider ("Spectrum Magnitude Scale"));
    mSpectroMagnitudeScale->setRange (-72, 0, 0);
    mSpectroMagnitudeScale->setSliderStyle (Slider::TwoValueVertical);
    mSpectroMagnitudeScale->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    mSpectroMagnitudeScale->addListener (this);

    addAndMakeVisible (mGonioPlaceholder = new Label ("Goniometer",
                                                      TRANS("Goniometer\n")));
    mGonioPlaceholder->setFont (Font (15.00f, Font::plain));
    mGonioPlaceholder->setJustificationType (Justification::centred);
    mGonioPlaceholder->setEditable (false, false, false);
    mGonioPlaceholder->setColour (Label::backgroundColourId, Colours::cadetblue);
    mGonioPlaceholder->setColour (TextEditor::textColourId, Colours::black);
    mGonioPlaceholder->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (mSpectroPlaceholder = new Label ("Spectrometer",
                                                        TRANS("Spectrometer\n")));
    mSpectroPlaceholder->setFont (Font (15.00f, Font::plain));
    mSpectroPlaceholder->setJustificationType (Justification::centred);
    mSpectroPlaceholder->setEditable (false, false, false);
    mSpectroPlaceholder->setColour (Label::backgroundColourId, Colours::grey);
    mSpectroPlaceholder->setColour (TextEditor::textColourId, Colours::black);
    mSpectroPlaceholder->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (mChcLabel = new Label ("Channel Count",
                                              TRANS("Channel Count:")));
    mChcLabel->setFont (Font (15.00f, Font::plain));
    mChcLabel->setJustificationType (Justification::centredLeft);
    mChcLabel->setEditable (false, true, false);
    mChcLabel->setColour (TextEditor::textColourId, Colours::black);
    mChcLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    mChcLabel->addListener (this);

    addAndMakeVisible (mDoNothing = new TextButton ("Do Nothing"));
    mDoNothing->addListener (this);


    //[UserPreSize]
	mParentProcessor = plugin;

	// This hack unsets label colours assigned by Introjucer, as there is no way to avoid these colors automatic generation
	for (int i = 0; i < getNumChildComponents(); ++i)
	{
		Component* comp = getChildComponent(i);

		Label* label = NULL;
		label = dynamic_cast<Label*>(comp);

		if (label != NULL)
		{
			label->removeColour(TextEditor::textColourId);
			label->removeColour(TextEditor::backgroundColourId);
		}
	}
    //[/UserPreSize]

    setSize (991, 450);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainLayout::~MainLayout()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    mInputChannels = nullptr;
    mGonioManualScale = nullptr;
    mGonioScaleValue = nullptr;
    mSpectroMagnitudeScale = nullptr;
    mGonioPlaceholder = nullptr;
    mSpectroPlaceholder = nullptr;
    mChcLabel = nullptr;
    mDoNothing = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainLayout::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff1e1e1e));

    //[UserPaint] Add your own custom painting code here..
	g.fillAll(LookAndFeel::getDefaultLookAndFeel().findColour(TomatlLookAndFeel::defaultBackground));
    //[/UserPaint]
}

void MainLayout::resized()
{
    mInputChannels->setBounds (112, 424, 32, 24);
    mGonioManualScale->setBounds (9, 368, 112, 24);
    mGonioScaleValue->setBounds (351, 0, 32, 360);
    mSpectroMagnitudeScale->setBounds (955, 0, 32, 360);
    mGonioPlaceholder->setBounds (9, 9, 342, 342);
    mSpectroPlaceholder->setBounds (383, 9, 568, 342);
    mChcLabel->setBounds (9, 424, 112, 24);
    mDoNothing->setBounds (210, 368, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainLayout::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == mGonioManualScale)
    {
        //[UserButtonCode_mGonioManualScale] -- add your button handler code here..
		mParentProcessor->setManualGonioScaleEnabled(buttonThatWasClicked->getToggleState());
        //[/UserButtonCode_mGonioManualScale]
    }
    else if (buttonThatWasClicked == mDoNothing)
    {
        //[UserButtonCode_mDoNothing] -- add your button handler code here..
        //[/UserButtonCode_mDoNothing]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void MainLayout::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == mGonioScaleValue)
    {
        //[UserSliderCode_mGonioScaleValue] -- add your slider handling code here..
		mParentProcessor->setManualGonioScaleValue(TOMATL_FROM_DB(sliderThatWasMoved->getValue()));
        //[/UserSliderCode_mGonioScaleValue]
    }
    else if (sliderThatWasMoved == mSpectroMagnitudeScale)
    {
        //[UserSliderCode_mSpectroMagnitudeScale] -- add your slider handling code here..
		mParentProcessor->setSpectroMagnitudeScale(std::pair<double, double>(sliderThatWasMoved->getMinValue(), sliderThatWasMoved->getMaxValue()));
        //[/UserSliderCode_mSpectroMagnitudeScale]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void MainLayout::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == mChcLabel)
    {
        //[UserLabelCode_mChcLabel] -- add your label text handling code here..
        //[/UserLabelCode_mChcLabel]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainLayout" componentName=""
                 parentClasses="public Component" constructorParams="AdmvAudioProcessor* plugin"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="991" initialHeight="450">
  <BACKGROUND backgroundColour="ff1e1e1e"/>
  <LABEL name="Input Channels" id="7b8ac8bacb5bd100" memberName="mInputChannels"
         virtualName="" explicitFocusOrder="0" pos="112 424 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="Goniometer Manual Scale" id="5481fd838f81a9d7" memberName="mGonioManualScale"
                virtualName="" explicitFocusOrder="0" pos="9 368 112 24" buttonText="Custom scale"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="Gonio Scale Value" id="759c99b88517019b" memberName="mGonioScaleValue"
          virtualName="" explicitFocusOrder="0" pos="351 0 32 360" min="-72"
          max="0" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Spectrum Magnitude Scale" id="c469fe133993978c" memberName="mSpectroMagnitudeScale"
          virtualName="" explicitFocusOrder="0" pos="955 0 32 360" min="-72"
          max="0" int="0" style="TwoValueVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Goniometer" id="cc50c59b667e6fe0" memberName="mGonioPlaceholder"
         virtualName="" explicitFocusOrder="0" pos="9 9 342 342" bkgCol="ff5f9ea0"
         edTextCol="ff000000" edBkgCol="0" labelText="Goniometer&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="Spectrometer" id="ec29c7cd27f78cb9" memberName="mSpectroPlaceholder"
         virtualName="" explicitFocusOrder="0" pos="383 9 568 342" bkgCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="Spectrometer&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="Channel Count" id="b9537e4c0c585d02" memberName="mChcLabel"
         virtualName="" explicitFocusOrder="0" pos="9 424 112 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Channel Count:" editableSingleClick="0"
         editableDoubleClick="1" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Do Nothing" id="3fdb35449265341e" memberName="mDoNothing"
              virtualName="" explicitFocusOrder="0" pos="210 368 150 24" buttonText="Do Nothing"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
