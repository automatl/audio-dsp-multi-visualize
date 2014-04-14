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
    addAndMakeVisible (mTestBtn = new TextButton ("Test"));
    mTestBtn->addListener (this);

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
    mGonioScaleValue->setSliderStyle (Slider::LinearHorizontal);
    mGonioScaleValue->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    mGonioScaleValue->addListener (this);


    //[UserPreSize]
	mParentProcessor = plugin;
    //[/UserPreSize]

    setSize (1000, 500);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainLayout::~MainLayout()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    mTestBtn = nullptr;
    mInputChannels = nullptr;
    mGonioManualScale = nullptr;
    mGonioScaleValue = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainLayout::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colour (0xff8a2aa5));
    g.fillRect (0, 0, 400, 400);

    g.setColour (Colour (0xffa52a4c));
    g.fillRect (400, 0, 600, 400);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainLayout::resized()
{
    mTestBtn->setBounds (480, 448, 72, 24);
    mInputChannels->setBounds (480, 416, 150, 24);
    mGonioManualScale->setBounds (0, 400, 112, 24);
    mGonioScaleValue->setBounds (112, 400, 288, 23);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainLayout::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == mTestBtn)
    {
        //[UserButtonCode_mTestBtn] -- add your button handler code here..
        //[/UserButtonCode_mTestBtn]
    }
    else if (buttonThatWasClicked == mGonioManualScale)
    {
        //[UserButtonCode_mGonioManualScale] -- add your button handler code here..
		mParentProcessor->setManualGonioScaleEnabled(buttonThatWasClicked->getToggleState());
        //[/UserButtonCode_mGonioManualScale]
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

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
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
                 overlayOpacity="0.330" fixedSize="1" initialWidth="1000" initialHeight="500">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 0 400 400" fill="solid: ff8a2aa5" hasStroke="0"/>
    <RECT pos="400 0 600 400" fill="solid: ffa52a4c" hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="Test" id="feb5c2e1366974ac" memberName="mTestBtn" virtualName=""
              explicitFocusOrder="0" pos="480 448 72 24" buttonText="Test"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="Input Channels" id="7b8ac8bacb5bd100" memberName="mInputChannels"
         virtualName="" explicitFocusOrder="0" pos="480 416 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="Goniometer Manual Scale" id="5481fd838f81a9d7" memberName="mGonioManualScale"
                virtualName="" explicitFocusOrder="0" pos="0 400 112 24" buttonText="Custom scale"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="Gonio Scale Value" id="759c99b88517019b" memberName="mGonioScaleValue"
          virtualName="" explicitFocusOrder="0" pos="112 400 288 23" min="-72"
          max="0" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
