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
//[/MiscUserDefs]

//==============================================================================
MainLayout::MainLayout ()
{
    addAndMakeVisible (mTestBtn = new TextButton ("Test"));
    mTestBtn->setButtonText (TRANS("new button"));
    mTestBtn->addListener (this);


    //[UserPreSize]
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
    mTestBtn->setBounds (8, 440, 150, 24);
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

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
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
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="1000" initialHeight="500">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 0 400 400" fill="solid: ff8a2aa5" hasStroke="0"/>
    <RECT pos="400 0 600 400" fill="solid: ffa52a4c" hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="Test" id="feb5c2e1366974ac" memberName="mTestBtn" virtualName=""
              explicitFocusOrder="0" pos="8 440 150 24" buttonText="new button"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
