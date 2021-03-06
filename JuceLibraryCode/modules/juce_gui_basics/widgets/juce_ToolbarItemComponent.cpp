/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/


ToolbarItemFactory::ToolbarItemFactory()
{
}

ToolbarItemFactory::~ToolbarItemFactory()
{
}

//==============================================================================
class ItemDragAndDropOverlayComponent    : public Component
{
public:
    ItemDragAndDropOverlayComponent()
        : isDragging (false)
    {
        setAlwaysOnTop (true);
        setRepaintsOnMouseActivity (true);
        setMouseCursor (MouseCursor::DraggingHandCursor);
    }

    void paint (Graphics& g)
    {
        ToolbarItemComponent* const tc = dynamic_cast <ToolbarItemComponent*> (getParentComponent());

        if (isMouseOverOrDragging()
              && tc != nullptr
              && tc->getEditingMode() == ToolbarItemComponent::editableOnToolbar)
        {
            g.setColour (findColour (Toolbar::editingModeOutlineColourId, true));
            g.drawRect (0, 0, getWidth(), getHeight(),
                        jmin (2, (getWidth() - 1) / 2, (getHeight() - 1) / 2));
        }
    }

    void mouseDown (const MouseEvent& e)
    {
        isDragging = false;
        ToolbarItemComponent* const tc = dynamic_cast <ToolbarItemComponent*> (getParentComponent());

        if (tc != nullptr)
        {
            tc->dragOffsetX = e.x;
            tc->dragOffsetY = e.y;
        }
    }

    void mouseDrag (const MouseEvent& e)
    {
        if (! (isDragging || e.mouseWasClicked()))
        {
            isDragging = true;
            DragAndDropContainer* const dnd = DragAndDropContainer::findParentDragContainerFor (this);

            if (dnd != nullptr)
            {
                dnd->startDragging (Toolbar::toolbarDragDescriptor, getParentComponent(), Image::null, true);

                ToolbarItemComponent* const tc = dynamic_cast <ToolbarItemComponent*> (getParentComponent());

                if (tc != nullptr)
                {
                    tc->isBeingDragged = true;

                    if (tc->getEditingMode() == ToolbarItemComponent::editableOnToolbar)
                        tc->setVisible (false);
                }
            }
        }
    }

    void mouseUp (const MouseEvent&)
    {
        isDragging = false;
        ToolbarItemComponent* const tc = dynamic_cast <ToolbarItemComponent*> (getParentComponent());

        if (tc != nullptr)
        {
            tc->isBeingDragged = false;

            Toolbar* const tb = tc->getToolbar();

            if (tb != nullptr)
                tb->updateAllItemPositions (true);
            else if (tc->getEditingMode() == ToolbarItemComponent::editableOnToolbar)
                delete tc;
        }
    }

    void parentSizeChanged()
    {
        setBounds (0, 0, getParentWidth(), getParentHeight());
    }

private:
    //==============================================================================
    bool isDragging;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ItemDragAndDropOverlayComponent);
};


//==============================================================================
ToolbarItemComponent::ToolbarItemComponent (const int itemId_,
                                            const String& labelText,
                                            const bool isBeingUsedAsAButton_)
    : Button (labelText),
      itemId (itemId_),
      mode (normalMode),
      toolbarStyle (Toolbar::iconsOnly),
      dragOffsetX (0),
      dragOffsetY (0),
      isActive (true),
      isBeingDragged (false),
      isBeingUsedAsAButton (isBeingUsedAsAButton_)
{
    // Your item ID can't be 0!
    jassert (itemId_ != 0);
}

ToolbarItemComponent::~ToolbarItemComponent()
{
    overlayComp = nullptr;
}

Toolbar* ToolbarItemComponent::getToolbar() const
{
    return dynamic_cast <Toolbar*> (getParentComponent());
}

bool ToolbarItemComponent::isToolbarVertical() const
{
    const Toolbar* const t = getToolbar();
    return t != nullptr && t->isVertical();
}

void ToolbarItemComponent::setStyle (const Toolbar::ToolbarItemStyle& newStyle)
{
    if (toolbarStyle != newStyle)
    {
        toolbarStyle = newStyle;
        repaint();
        resized();
    }
}

void ToolbarItemComponent::paintButton (Graphics& g, const bool over, const bool down)
{
    if (isBeingUsedAsAButton)
        getLookAndFeel().paintToolbarButtonBackground (g, getWidth(), getHeight(),
                                                       over, down, *this);

    if (toolbarStyle != Toolbar::iconsOnly)
    {
        const int indent = contentArea.getX();
        int y = indent;
        int h = getHeight() - indent * 2;

        if (toolbarStyle == Toolbar::iconsWithText)
        {
            y = contentArea.getBottom() + indent / 2;
            h -= contentArea.getHeight();
        }

        getLookAndFeel().paintToolbarButtonLabel (g, indent, y, getWidth() - indent * 2, h,
                                                  getButtonText(), *this);
    }

    if (! contentArea.isEmpty())
    {
        Graphics::ScopedSaveState ss (g);

        g.reduceClipRegion (contentArea);
        g.setOrigin (contentArea.getX(), contentArea.getY());

        paintButtonArea (g, contentArea.getWidth(), contentArea.getHeight(), over, down);
    }
}

void ToolbarItemComponent::resized()
{
    if (toolbarStyle != Toolbar::textOnly)
    {
        const int indent = jmin (proportionOfWidth (0.08f),
                                 proportionOfHeight (0.08f));

        contentArea = Rectangle<int> (indent, indent,
                                      getWidth() - indent * 2,
                                      toolbarStyle == Toolbar::iconsWithText ? proportionOfHeight (0.55f)
                                                                             : (getHeight() - indent * 2));
    }
    else
    {
        contentArea = Rectangle<int>();
    }

    contentAreaChanged (contentArea);
}

void ToolbarItemComponent::setEditingMode (const ToolbarEditingMode newMode)
{
    if (mode != newMode)
    {
        mode = newMode;
        repaint();

        if (mode == normalMode)
        {
            overlayComp = nullptr;
        }
        else if (overlayComp == nullptr)
        {
            addAndMakeVisible (overlayComp = new ItemDragAndDropOverlayComponent());
            overlayComp->parentSizeChanged();
        }

        resized();
    }
}
