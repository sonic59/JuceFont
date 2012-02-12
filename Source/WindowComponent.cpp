/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  12 Feb 2012 10:08:44am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "WindowComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
WindowComponent::WindowComponent ()
    : lblFamily (0),
      cmbFamily (0),
      lblStyle (0),
      cmbStyle (0),
      lblHeight (0),
      grpSample (0),
      lblSample (0),
      txtSample (0),
      slHeight (0)
{
    addAndMakeVisible (lblFamily = new Label (L"lblFamily",
                                              L"Font Family"));
    lblFamily->setFont (Font (15.0000f, Font::plain));
    lblFamily->setJustificationType (Justification::centredLeft);
    lblFamily->setEditable (false, false, false);
    lblFamily->setColour (TextEditor::textColourId, Colours::black);
    lblFamily->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (cmbFamily = new ComboBox (L"cmbFamily"));
    cmbFamily->setEditableText (false);
    cmbFamily->setJustificationType (Justification::centredLeft);
    cmbFamily->setTextWhenNothingSelected (String::empty);
    cmbFamily->setTextWhenNoChoicesAvailable (L"(no choices)");
    cmbFamily->addListener (this);

    addAndMakeVisible (lblStyle = new Label (L"lblStyle",
                                             L"Font Style"));
    lblStyle->setFont (Font (15.0000f, Font::plain));
    lblStyle->setJustificationType (Justification::centredLeft);
    lblStyle->setEditable (false, false, false);
    lblStyle->setColour (TextEditor::textColourId, Colours::black);
    lblStyle->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (cmbStyle = new ComboBox (L"cmbStyle"));
    cmbStyle->setEditableText (false);
    cmbStyle->setJustificationType (Justification::centredLeft);
    cmbStyle->setTextWhenNothingSelected (String::empty);
    cmbStyle->setTextWhenNoChoicesAvailable (L"(no choices)");
    cmbStyle->addListener (this);

    addAndMakeVisible (lblHeight = new Label (L"lblHeight",
                                              L"Font Height"));
    lblHeight->setFont (Font (15.0000f, Font::plain));
    lblHeight->setJustificationType (Justification::centredLeft);
    lblHeight->setEditable (false, false, false);
    lblHeight->setColour (TextEditor::textColourId, Colours::black);
    lblHeight->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (grpSample = new GroupComponent (L"grpSample",
                                                       L"Sample Text"));

    addAndMakeVisible (lblSample = new Label (L"lblSample",
                                              L"The quick brown fox jumps over the lazy dog"));
    lblSample->setFont (Font (15.0000f, Font::plain));
    lblSample->setJustificationType (Justification::centredLeft);
    lblSample->setEditable (false, false, false);
    lblSample->setColour (TextEditor::textColourId, Colours::black);
    lblSample->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (txtSample = new TextEditor (L"txtSample"));
    txtSample->setMultiLine (true);
    txtSample->setReturnKeyStartsNewLine (true);
    txtSample->setReadOnly (false);
    txtSample->setScrollbarsShown (true);
    txtSample->setCaretVisible (true);
    txtSample->setPopupMenuEnabled (true);
    txtSample->setText (L"The quick brown fox jumps over the lazy dog and feels as if he were in the seventh heaven of typography together with Hermann Zapf\n");

    addAndMakeVisible (slHeight = new Slider (L"slHeight"));
    slHeight->setRange (0, 250, 0.1);
    slHeight->setSliderStyle (Slider::LinearBar);
    slHeight->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    slHeight->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

WindowComponent::~WindowComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (lblFamily);
    deleteAndZero (cmbFamily);
    deleteAndZero (lblStyle);
    deleteAndZero (cmbStyle);
    deleteAndZero (lblHeight);
    deleteAndZero (grpSample);
    deleteAndZero (lblSample);
    deleteAndZero (txtSample);
    deleteAndZero (slHeight);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void WindowComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void WindowComponent::resized()
{
    lblFamily->setBounds (8, 8, 88, 24);
    cmbFamily->setBounds (168, 8, 304, 24);
    lblStyle->setBounds (8, 40, 88, 24);
    cmbStyle->setBounds (168, 40, 304, 24);
    lblHeight->setBounds (8, 72, 88, 24);
    grpSample->setBounds (8, 104, 464, 160);
    lblSample->setBounds (24, 128, 432, 48);
    txtSample->setBounds (24, 184, 432, 64);
    slHeight->setBounds (168, 72, 304, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void WindowComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cmbFamily)
    {
        //[UserComboBoxCode_cmbFamily] -- add your combo box handling code here..
        //[/UserComboBoxCode_cmbFamily]
    }
    else if (comboBoxThatHasChanged == cmbStyle)
    {
        //[UserComboBoxCode_cmbStyle] -- add your combo box handling code here..
        //[/UserComboBoxCode_cmbStyle]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void WindowComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slHeight)
    {
        //[UserSliderCode_slHeight] -- add your slider handling code here..
        //[/UserSliderCode_slHeight]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="WindowComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="lblFamily" id="ef44ab56ce3a952c" memberName="lblFamily"
         virtualName="" explicitFocusOrder="0" pos="8 8 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Font Family" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="cmbFamily" id="d9bf7cf961bb5d45" memberName="cmbFamily"
            virtualName="" explicitFocusOrder="0" pos="168 8 304 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="lblStyle" id="ba91e733cb7cade1" memberName="lblStyle" virtualName=""
         explicitFocusOrder="0" pos="8 40 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Font Style" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="cmbStyle" id="d9caf95e3b441235" memberName="cmbStyle" virtualName=""
            explicitFocusOrder="0" pos="168 40 304 24" editable="0" layout="33"
            items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="lblHeight" id="9d22f1efd65b86c3" memberName="lblHeight"
         virtualName="" explicitFocusOrder="0" pos="8 72 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Font Height" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <GROUPCOMPONENT name="grpSample" id="80d002a77331c5e7" memberName="grpSample"
                  virtualName="" explicitFocusOrder="0" pos="8 104 464 160" title="Sample Text"/>
  <LABEL name="lblSample" id="98bdda0d3fdaa30" memberName="lblSample"
         virtualName="" explicitFocusOrder="0" pos="24 128 432 48" edTextCol="ff000000"
         edBkgCol="0" labelText="The quick brown fox jumps over the lazy dog"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="txtSample" id="d38f7cdef6830b4a" memberName="txtSample"
              virtualName="" explicitFocusOrder="0" pos="24 184 432 64" initialText="The quick brown fox jumps over the lazy dog and feels as if he were in the seventh heaven of typography together with Hermann Zapf&#10;"
              multiline="1" retKeyStartsLine="1" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <SLIDER name="slHeight" id="2f1d9d3fade56757" memberName="slHeight" virtualName=""
          explicitFocusOrder="0" pos="168 72 304 24" min="0" max="250"
          int="0.1" style="LinearBar" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
