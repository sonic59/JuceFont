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

#ifndef __JUCER_HEADER_WINDOWCOMPONENT_WINDOWCOMPONENT_3F16D2AB__
#define __JUCER_HEADER_WINDOWCOMPONENT_WINDOWCOMPONENT_3F16D2AB__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class WindowComponent  : public Component,
                         public ComboBoxListener,
                         public SliderListener
{
public:
    //==============================================================================
    WindowComponent ();
    ~WindowComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void sliderValueChanged (Slider* sliderThatWasMoved);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    Label* lblFamily;
    ComboBox* cmbFamily;
    Label* lblStyle;
    ComboBox* cmbStyle;
    Label* lblHeight;
    GroupComponent* grpSample;
    Label* lblSample;
    TextEditor* txtSample;
    Slider* slHeight;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    WindowComponent (const WindowComponent&);
    const WindowComponent& operator= (const WindowComponent&);
};


#endif   // __JUCER_HEADER_WINDOWCOMPONENT_WINDOWCOMPONENT_3F16D2AB__
