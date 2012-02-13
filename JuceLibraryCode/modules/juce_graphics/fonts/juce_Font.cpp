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


namespace FontValues
{
    float limitFontHeight (const float height) noexcept
    {
        return jlimit (0.1f, 10000.0f, height);
    }

    const float defaultFontHeight = 14.0f;
    String fallbackFontFamily;
    String fallbackFontStyle;
}

typedef Typeface::Ptr (*GetTypefaceForFont) (const Font&);
GetTypefaceForFont juce_getTypefaceForFont = nullptr;

//==============================================================================
class TypefaceCache  : public DeletedAtShutdown
{
public:
    TypefaceCache()
        : counter (0)
    {
        setSize (10);
    }

    ~TypefaceCache()
    {
        clearSingletonInstance();
    }

    juce_DeclareSingleton_SingleThreaded_Minimal (TypefaceCache);

    void setSize (const int numToCache)
    {
        faces.clear();
        faces.insertMultiple (-1, CachedFace(), numToCache);
    }

    Typeface::Ptr findTypefaceFor (const Font& font)
    {
        const String faceFamily (font.getTypefaceFamily());
        const String faceStyle (font.getTypefaceStyle());

        int i;
        for (i = faces.size(); --i >= 0;)
        {
            CachedFace& face = faces.getReference(i);

            if (face.typefaceFamily == faceFamily
                 && face.typefaceStyle == faceStyle
                 && face.typeface->isSuitableForFont (font))
            {
                face.lastUsageCount = ++counter;
                return face.typeface;
            }
        }

        int replaceIndex = 0;
        int bestLastUsageCount = std::numeric_limits<int>::max();

        for (i = faces.size(); --i >= 0;)
        {
            const int lu = faces.getReference(i).lastUsageCount;

            if (bestLastUsageCount > lu)
            {
                bestLastUsageCount = lu;
                replaceIndex = i;
            }
        }

        CachedFace& face = faces.getReference (replaceIndex);
        face.typefaceFamily = faceFamily;
        face.typefaceStyle = faceStyle;
        face.lastUsageCount = ++counter;

        if (juce_getTypefaceForFont == nullptr)
            face.typeface = Font::getDefaultTypefaceForFont (font);
        else
            face.typeface = juce_getTypefaceForFont (font);

        jassert (face.typeface != nullptr); // the look and feel must return a typeface!

        if (defaultFace == nullptr && font == Font())
            defaultFace = face.typeface;

        return face.typeface;
    }

    Typeface::Ptr getDefaultTypeface() const noexcept
    {
        return defaultFace;
    }

private:
    struct CachedFace
    {
        CachedFace() noexcept
            : lastUsageCount (0)
        {
        }

        // Although it seems a bit wacky to store the name here, it's because it may be a
        // placeholder rather than a real one, e.g. "<Sans-Serif>" vs the actual typeface name.
        // Since the typeface itself doesn't know that it may have this alias, the name under
        // which it was fetched needs to be stored separately.
        String typefaceFamily;
        String typefaceStyle;
        int lastUsageCount;
        Typeface::Ptr typeface;
    };

    Array <CachedFace> faces;
    Typeface::Ptr defaultFace;
    int counter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TypefaceCache);
};

juce_ImplementSingleton_SingleThreaded (TypefaceCache)

void Typeface::setTypefaceCacheSize (int numFontsToCache)
{
    TypefaceCache::getInstance()->setSize (numFontsToCache);
}

//==============================================================================
Font::SharedFontInternal::SharedFontInternal (const float height_, const String& typefaceStyle_) noexcept
    : typefaceFamily (Font::getDefaultSansSerifFamily()),
      typefaceStyle (typefaceStyle_),
      height (height_),
      horizontalScale (1.0f),
      kerning (0),
      ascent (0),
      underline (false),
      typeface (typefaceStyle_ == Font::getDefaultStyle()
                    ? TypefaceCache::getInstance()->getDefaultTypeface() : nullptr)
{
}

Font::SharedFontInternal::SharedFontInternal (const float height_, const String& typefaceFamily_, const String& typefaceStyle_) noexcept
    : typefaceFamily (typefaceFamily_),
      typefaceStyle (typefaceStyle_),
      height (height_),
      horizontalScale (1.0f),
      kerning (0),
      ascent (0),
      underline (false),
      typeface (nullptr)
{
}

Font::SharedFontInternal::SharedFontInternal (const Typeface::Ptr& typeface_) noexcept
    : typefaceFamily (typeface_->getFamily()),
      typefaceStyle (typeface_->getStyle()),
      height (FontValues::defaultFontHeight),
      horizontalScale (1.0f),
      kerning (0),
      ascent (0),
      underline (false),
      typeface (typeface_)
{
}

Font::SharedFontInternal::SharedFontInternal (const SharedFontInternal& other) noexcept
    : typefaceFamily (other.typefaceFamily),
      typefaceStyle (other.typefaceStyle),
      height (other.height),
      horizontalScale (other.horizontalScale),
      kerning (other.kerning),
      ascent (other.ascent),
      underline (false),
      typeface (other.typeface)
{
}

bool Font::SharedFontInternal::operator== (const SharedFontInternal& other) const noexcept
{
    return height == other.height
            && horizontalScale == other.horizontalScale
            && kerning == other.kerning
            && typefaceFamily == other.typefaceFamily
            && typefaceStyle == other.typefaceStyle;
}

//==============================================================================
Font::Font()
    : font (new SharedFontInternal (FontValues::defaultFontHeight, Font::getDefaultStyle()))
{
}

Font::Font (const float fontHeight, const String& typefaceStyle_)
    : font (new SharedFontInternal (FontValues::limitFontHeight (fontHeight), typefaceStyle_))
{
}

Font::Font (const float fontHeight, const String& typefaceName_, const String& typefaceStyle_)
    : font (new SharedFontInternal (FontValues::limitFontHeight (fontHeight), typefaceName_, typefaceStyle_))
{
}

Font::Font (const Typeface::Ptr& typeface)
    : font (new SharedFontInternal (typeface))
{
}

Font::Font (const Font& other) noexcept
    : font (other.font)
{
}

Font& Font::operator= (const Font& other) noexcept
{
    font = other.font;
    return *this;
}

#if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
Font::Font (Font&& other) noexcept
    : font (static_cast <ReferenceCountedObjectPtr <SharedFontInternal>&&> (other.font))
{
}

Font& Font::operator= (Font&& other) noexcept
{
    font = static_cast <ReferenceCountedObjectPtr <SharedFontInternal>&&> (other.font);
    return *this;
}
#endif

Font::~Font() noexcept
{
}

bool Font::operator== (const Font& other) const noexcept
{
    return font == other.font
            || *font == *other.font;
}

bool Font::operator!= (const Font& other) const noexcept
{
    return ! operator== (other);
}

void Font::dupeInternalIfShared()
{
    if (font->getReferenceCount() > 1)
        font = new SharedFontInternal (*font);
}

//==============================================================================
const String& Font::getDefaultSansSerifFamily()
{
    static const String family ("<Sans-Serif>");
    return family;
}

const String& Font::getDefaultSerifFamily()
{
    static const String family ("<Serif>");
    return family;
}

const String& Font::getDefaultMonospacedFamily()
{
    static const String family ("<Monospaced>");
    return family;
}

const String& Font::getDefaultStyle()
{
    static const String style ("<Style>");
    return style;
}

void Font::setTypefaceFamily (const String& family)
{
    if (family != font->typefaceFamily)
    {
        dupeInternalIfShared();
        font->typefaceFamily = family;
        font->typeface = nullptr;
        font->ascent = 0;
    }
}

void Font::setTypefaceStyle (const String& style)
{
    if (style != font->typefaceStyle)
    {
        dupeInternalIfShared();
        font->typefaceStyle = style;
        font->typeface = nullptr;
        font->ascent = 0;
    }
}

//==============================================================================
const String& Font::getFallbackFontFamily()
{
    return FontValues::fallbackFontFamily;
}

void Font::setFallbackFontFamily (const String& family)
{
    FontValues::fallbackFontFamily = family;

   #if JUCE_MAC || JUCE_IOS
    jassertfalse; // Note that use of a fallback font isn't currently implemented in OSX..
   #endif
}

const String& Font::getFallbackFontStyle()
{
    return FontValues::fallbackFontStyle;
}

void Font::setFallbackFontStyle (const String& style)
{
    FontValues::fallbackFontStyle = style;

   #if JUCE_MAC || JUCE_IOS
    jassertfalse; // Note that use of a fallback font isn't currently implemented in OSX..
   #endif
}

//==============================================================================
void Font::setHeight (float newHeight)
{
    newHeight = FontValues::limitFontHeight (newHeight);

    if (font->height != newHeight)
    {
        dupeInternalIfShared();
        font->height = newHeight;
    }
}

void Font::setHeightWithoutChangingWidth (float newHeight)
{
    newHeight = FontValues::limitFontHeight (newHeight);

    if (font->height != newHeight)
    {
        dupeInternalIfShared();
        font->horizontalScale *= (font->height / newHeight);
        font->height = newHeight;
    }
}

void Font::setSizeAndStyle (float newHeight,
                            const float newHorizontalScale,
                            const float newKerningAmount)
{
    newHeight = FontValues::limitFontHeight (newHeight);

    if (font->height != newHeight
         || font->horizontalScale != newHorizontalScale
         || font->kerning != newKerningAmount)
    {
        dupeInternalIfShared();
        font->height = newHeight;
        font->horizontalScale = newHorizontalScale;
        font->kerning = newKerningAmount;
    }

}

void Font::setHorizontalScale (const float scaleFactor)
{
    dupeInternalIfShared();
    font->horizontalScale = scaleFactor;
}

void Font::setExtraKerningFactor (const float extraKerning)
{
    dupeInternalIfShared();
    font->kerning = extraKerning;
}

void Font::setUnderline (const bool shouldBeUnderlined)
{
    font->underline = shouldBeUnderlined;
}

float Font::getAscent() const
{
    if (font->ascent == 0)
        font->ascent = getTypeface()->getAscent();

    return font->height * font->ascent;
}

float Font::getDescent() const
{
    return font->height - getAscent();
}

int Font::getStringWidth (const String& text) const
{
    return roundToInt (getStringWidthFloat (text));
}

float Font::getStringWidthFloat (const String& text) const
{
    float w = getTypeface()->getStringWidth (text);

    if (font->kerning != 0)
        w += font->kerning * text.length();

    return w * font->height * font->horizontalScale;
}

void Font::getGlyphPositions (const String& text, Array <int>& glyphs, Array <float>& xOffsets) const
{
    getTypeface()->getGlyphPositions (text, glyphs, xOffsets);

    const float scale = font->height * font->horizontalScale;
    const int num = xOffsets.size();

    if (num > 0)
    {
        float* const x = &(xOffsets.getReference(0));

        if (font->kerning != 0)
        {
            for (int i = 0; i < num; ++i)
                x[i] = (x[i] + i * font->kerning) * scale;
        }
        else
        {
            for (int i = 0; i < num; ++i)
                x[i] *= scale;
        }
    }
}

void Font::findFonts (Array<Font>& destArray)
{
    const StringArray families (findAllTypefaceFamilies());

    for (int i = 0; i < families.size(); ++i)
    {
        const StringArray styles (findAllTypefaceStyles (families[i]));
        for (int j = 0; j < styles.size(); ++j)
            destArray.add (Font (FontValues::defaultFontHeight, families[i],  styles[j]));
    }
}

//==============================================================================
String Font::toString() const
{
    String s (getTypefaceFamily());
    s += "; " + getTypefaceStyle() + "; ";
    s += String (getHeight(), 1);

    return s;
}

Font Font::fromString (const String& fontDescription)
{
    int start = 0;
    int separator = fontDescription.indexOfChar (';');

    String family = fontDescription.substring (start, separator).trim();
    start = separator + 1;
    separator = fontDescription.indexOfChar (start, ';');
    String style = fontDescription.substring (start, separator).trim();
    String sizeAndStyle (fontDescription.substring (separator + 1));

    float height = sizeAndStyle.getFloatValue();
    if (height <= 0)
        height = 10.0f;

    return Font (height, family, style);
}

//==============================================================================
Typeface* Font::getTypeface() const
{
    if (font->typeface == 0)
        font->typeface = TypefaceCache::getInstance()->findTypefaceFor (*this);

    return font->typeface;
}
