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

#ifndef __JUCE_FONT_JUCEHEADER__
#define __JUCE_FONT_JUCEHEADER__

#include "juce_Typeface.h"
class LowLevelGraphicsContext;


//==============================================================================
/**
    Represents a particular font, including its size, style, etc.

    Apart from the typeface to be used, a Font object also dictates whether
    the font is bold, italic, underlined, how big it is, and its kerning and
    horizontal scale factor.

    @see Typeface
*/
class JUCE_API  Font
{
public:

    //==============================================================================
    /** Creates a sans-serif font in a given size.

        @param fontHeight    the height in pixels (can be fractional)
        @param typefaceStyle the style of the typeface to use
    */
    Font (float fontHeight, const String& typefaceStyle = Font::getDefaultStyle());

    /** Creates a font with a given typeface and parameters.

        @param fontHeight     the height in pixels (can be fractional)
        @param typefaceFamily the name of the typeface to use
        @param typefaceStyle  the style of the typeface to use
    */
    Font (float fontHeight, const String& typefaceFamily, const String& typefaceStyle);

    /** Creates a copy of another Font object. */
    Font (const Font& other) noexcept;

    /** Creates a font for a typeface. */
    Font (const Typeface::Ptr& typeface);

    /** Creates a basic sans-serif font at a default height.

        You should use one of the other constructors for creating a font that you're planning
        on drawing with - this constructor is here to help initialise objects before changing
        the font's settings later.
    */
    Font();

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
    Font (Font&& other) noexcept;
    Font& operator= (Font&& other) noexcept;
   #endif

    /** Copies this font from another one. */
    Font& operator= (const Font& other) noexcept;

    bool operator== (const Font& other) const noexcept;
    bool operator!= (const Font& other) const noexcept;

    /** Destructor. */
    ~Font() noexcept;

    //==============================================================================
    /** Changes the family of the typeface

        e.g. "Arial", "Courier", etc.

        This may also be set to Font::getDefaultSansSerifFamily(), Font::getDefaultSerifFamily(),
        or Font::getDefaultMonospacedFamily(), which are not actual platform-specific family names,
        but are generic names that are used to represent the various default font families.
        If you need to know the exact typeface name being used, you can call
        Font::getTypeface()->getTypefaceFamily(), which will give you the platform-specific name.

        If a suitable font isn't found on the machine, it'll just use a default instead.
    */
    void setTypefaceFamily (const String& family);

    /** Returns the name of the typeface family that this font uses.

        e.g. "Arial", "Courier", etc.

        This may also be set to Font::getDefaultSansSerifFamily(), Font::getDefaultSerifFamily(),
        or Font::getDefaultMonospacedFontName(), which are not actual platform-specific family names,
        but are generic names that are used to represent the various default font families.

        If you need to know the exact typeface name being used, you can call
        Font::getTypeface()->getTypefaceName(), which will give you the platform-specific name.
    */
    const String& getTypefaceFamily() const noexcept              { return font->typefaceFamily; }

    //==============================================================================
    /** Changes the style of the typeface

        e.g. "Regular", "Italic", etc.

    */
    void setTypefaceStyle (const String& style);

    /** Returns the name of the typeface style that this font uses.

        e.g. "Regular", "Italic", etc.

    */
    const String& getTypefaceStyle() const noexcept              { return font->typefaceStyle; }

    //==============================================================================
    /** Returns a typeface family that represents the default sans-serif font.

        This is also the typeface that will be used when a font is created without
        specifying any typeface details.

        Note that this method just returns a generic placeholder string that means "the default
        sans-serif font" - it's not the actual family of this font.

        @see setTypefaceFamily, getDefaultSerifFamily, getDefaultMonospacedFamily
    */
    static const String& getDefaultSansSerifFamily();

    /** Returns a typeface family that represents the default sans-serif font.

        Note that this method just returns a generic placeholder string that means "the default
        serif font" - it's not the actual family of this font.

        @see setTypefaceFamily, getDefaultSansSerifFamily, getDefaultMonospacedFamily
    */
    static const String& getDefaultSerifFamily();

    /** Returns a typeface family that represents the default sans-serif font.

        Note that this method just returns a generic placeholder string that means "the default
        monospaced font" - it's not the actual family of this font.

        @see setTypefaceFamily, getDefaultSansSerifFamily, getDefaultSerifFamily
    */
    static const String& getDefaultMonospacedFamily();

    /** Returns a typeface style that represents the default style.

        Note that this method just returns a generic placeholder string that means "the default
        font style" - it's not the actual style of this font.

        @see setTypefaceStyle
    */
    static const String& Font::getDefaultStyle();

    /** Returns the default system typeface for the given font. */
    static Typeface::Ptr getDefaultTypefaceForFont (const Font& font);

    //==============================================================================
    /** Returns the total height of this font.

        This is the maximum height, from the top of the ascent to the bottom of the
        descenders.

        @see setHeight, setHeightWithoutChangingWidth, getAscent
    */
    float getHeight() const noexcept                            { return font->height; }

    /** Changes the font's height.

        @see getHeight, setHeightWithoutChangingWidth
    */
    void setHeight (float newHeight);

    /** Changes the font's height without changing its width.

        This alters the horizontal scale to compensate for the change in height.
    */
    void setHeightWithoutChangingWidth (float newHeight);

    /** Returns the height of the font above its baseline.

        This is the maximum height from the baseline to the top.

        @see getHeight, getDescent
    */
    float getAscent() const;

    /** Returns the amount that the font descends below its baseline.

        This is calculated as (getHeight() - getAscent()).

        @see getAscent, getHeight
    */
    float getDescent() const;

    //==============================================================================
    /** Makes the font underlined or non-underlined. */
    void setUnderline (bool shouldBeUnderlined);
    /** Returns true if the font is underlined. */
    bool isUnderlined() const noexcept                       { return font->underline; }

    //==============================================================================
    /** Changes the font's horizontal scale factor.

        @param scaleFactor  a value of 1.0 is the normal scale, less than this will be
                            narrower, greater than 1.0 will be stretched out.
    */
    void setHorizontalScale (float scaleFactor);

    /** Returns the font's horizontal scale.

        A value of 1.0 is the normal scale, less than this will be narrower, greater
        than 1.0 will be stretched out.

        @see setHorizontalScale
    */
    float getHorizontalScale() const noexcept               { return font->horizontalScale; }

    /** Changes the font's kerning.

        @param extraKerning     a multiple of the font's height that will be added
                                to space between the characters. So a value of zero is
                                normal spacing, positive values spread the letters out,
                                negative values make them closer together.
    */
    void setExtraKerningFactor (float extraKerning);

    /** Returns the font's kerning.

        This is the extra space added between adjacent characters, as a proportion
        of the font's height.

        A value of zero is normal spacing, positive values will spread the letters
        out more, and negative values make them closer together.
    */
    float getExtraKerningFactor() const noexcept            { return font->kerning; }


    //==============================================================================
    /** Changes all the font's characteristics with one call. */
    void setSizeAndStyle (float newHeight,
                          float newHorizontalScale,
                          float newKerningAmount);

    //==============================================================================
    /** Returns the total width of a string as it would be drawn using this font.

        For a more accurate floating-point result, use getStringWidthFloat().
    */
    int getStringWidth (const String& text) const;

    /** Returns the total width of a string as it would be drawn using this font.

        @see getStringWidth
    */
    float getStringWidthFloat (const String& text) const;

    /** Returns the series of glyph numbers and their x offsets needed to represent a string.

        An extra x offset is added at the end of the run, to indicate where the right hand
        edge of the last character is.
    */
    void getGlyphPositions (const String& text, Array <int>& glyphs, Array <float>& xOffsets) const;

    //==============================================================================
    /** Returns the typeface used by this font.

        Note that the object returned may go out of scope if this font is deleted
        or has its style changed.
    */
    Typeface* getTypeface() const;

    /** Creates an array of Font objects to represent all the fonts on the system.

        If you just need the family names of the typefaces, you can also use
        findAllTypefaceFamilies() instead.

        @param results  the array to which new Font objects will be added.
    */
    static void findFonts (Array<Font>& results);

    /** Returns a list of all the available typeface families.

        The names returned can be passed into setTypefaceFamily().

        You can use this instead of findFonts() if you only need their families, and not
        font objects.
    */
    static StringArray findAllTypefaceFamilies();

    /** Returns a list of all the available typeface styles.

        The names returned can be passed into setTypefaceStyle().

        You can use this instead of findFonts() if you only need their styles, and not
        font objects.
    */
    static StringArray findAllTypefaceStyles (const String& family);

    //==============================================================================
    /** Returns the family name of the typeface to be used for rendering glyphs that aren't found
        in the requested typeface.
    */
    static const String& getFallbackFontFamily();

    /** Sets the (platform-specific) family name of the typeface to use to find glyphs that aren't
        available in whatever font you're trying to use.
    */
    static void setFallbackFontFamily (const String& family);

    /** Returns the style name of the typeface to be used for rendering glyphs that aren't found
        in the requested typeface.
    */
    static const String& getFallbackFontStyle();

    /** Sets the (platform-specific) style name of the typeface to use to find glyphs that aren't
        available in whatever font you're trying to use.
    */
    static void setFallbackFontStyle (const String& style);

    //==============================================================================
    /** Creates a string to describe this font.
        The string will contain information to describe the font's typeface, size, and
        style. To recreate the font from this string, use fromString().
    */
    String toString() const;

    /** Recreates a font from its stringified encoding.
        This method takes a string that was created by toString(), and recreates the
        original font.
    */
    static Font fromString (const String& fontDescription);


private:
    //==============================================================================
    friend class FontGlyphAlphaMap;
    friend class TypefaceCache;

    class SharedFontInternal  : public SingleThreadedReferenceCountedObject
    {
    public:
        SharedFontInternal (float height, const String& typefaceStyle) noexcept;
        SharedFontInternal (float height, const String& typefaceFamily, const String& typefaceStyle) noexcept;
        SharedFontInternal (const Typeface::Ptr& typeface) noexcept;
        SharedFontInternal (const SharedFontInternal& other) noexcept;

        bool operator== (const SharedFontInternal&) const noexcept;

        String typefaceFamily;
        String typefaceStyle;
        float height, horizontalScale, kerning, ascent;
        bool underline;
        Typeface::Ptr typeface;
    };

    ReferenceCountedObjectPtr <SharedFontInternal> font;
    void dupeInternalIfShared();

    JUCE_LEAK_DETECTOR (Font);
};

#endif   // __JUCE_FONT_JUCEHEADER__
