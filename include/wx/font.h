/////////////////////////////////////////////////////////////////////////////
// Name:        wx/font.h
// Purpose:     wxFontBase class: the interface of wxFont
// Author:      Vadim Zeitlin
// Modified by:
// Created:     20.09.99
// RCS-ID:      $Id$
// Copyright:   (c) wxWindows team
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_FONT_H_BASE_
#define _WX_FONT_H_BASE_

#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma interface "fontbase.h"
#endif

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "wx/defs.h"        // for wxDEFAULT &c
#include "wx/fontenc.h"     // the font encoding constants
#include "wx/gdiobj.h"      // the base class

// ----------------------------------------------------------------------------
// forward declarations
// ----------------------------------------------------------------------------

class WXDLLEXPORT wxFontData;
class WXDLLEXPORT wxFontBase;
class WXDLLEXPORT wxFont;

// ----------------------------------------------------------------------------
// font constants
// ----------------------------------------------------------------------------

// standard font families: these may be used only for the font creation, it
// doesn't make sense to query an existing font for its font family as,
// especially if the font had been created from a native font description, it
// may be unknown
enum wxFontFamily
{
    wxFONTFAMILY_DEFAULT = wxDEFAULT,
    wxFONTFAMILY_DECORATIVE = wxDECORATIVE,
    wxFONTFAMILY_ROMAN = wxROMAN,
    wxFONTFAMILY_SCRIPT = wxSCRIPT,
    wxFONTFAMILY_SWISS = wxSWISS,
    wxFONTFAMILY_MODERN = wxMODERN,
    wxFONTFAMILY_TELETYPE = wxTELETYPE,
    wxFONTFAMILY_MAX,
    wxFONTFAMILY_UNKNOWN = wxFONTFAMILY_MAX
};

// font styles
enum wxFontStyle
{
    wxFONTSTYLE_NORMAL = wxNORMAL,
    wxFONTSTYLE_ITALIC = wxITALIC,
    wxFONTSTYLE_SLANT = wxSLANT,
    wxFONTSTYLE_MAX
};

// font weights
enum wxFontWeight
{
    wxFONTWEIGHT_NORMAL = wxNORMAL,
    wxFONTWEIGHT_LIGHT = wxLIGHT,
    wxFONTWEIGHT_BOLD = wxBOLD,
    wxFONTWEIGHT_MAX
};

// the font flag bits for the new font ctor accepting one combined flags word
enum
{
    // no special flags: font with default weight/slant/anti-aliasing
    wxFONTFLAG_DEFAULT          = 0,

    // slant flags (default: no slant)
    wxFONTFLAG_ITALIC           = 1 << 0,
    wxFONTFLAG_SLANT            = 1 << 1,

    // weight flags (default: medium)
    wxFONTFLAG_LIGHT            = 1 << 2,
    wxFONTFLAG_BOLD             = 1 << 3,

    // anti-aliasing flag: force on or off (default: the current system default)
    wxFONTFLAG_ANTIALIASED      = 1 << 4,
    wxFONTFLAG_NOT_ANTIALIASED  = 1 << 5,

    // underlined/strikethrough flags (default: no lines)
    wxFONTFLAG_UNDERLINED       = 1 << 6,
    wxFONTFLAG_STRIKETHROUGH    = 1 << 7,

    // the mask of all currently used flags
    wxFONTFLAG_MASK = wxFONTFLAG_ITALIC             |
                      wxFONTFLAG_SLANT              |
                      wxFONTFLAG_LIGHT              |
                      wxFONTFLAG_BOLD               |
                      wxFONTFLAG_ANTIALIASED        |
                      wxFONTFLAG_NOT_ANTIALIASED    |
                      wxFONTFLAG_UNDERLINED         |
                      wxFONTFLAG_STRIKETHROUGH
};

// ----------------------------------------------------------------------------
// wxFontBase represents a font object
// ----------------------------------------------------------------------------

class WXDLLEXPORT wxFontRefData;
struct WXDLLEXPORT wxNativeFontInfo;

class WXDLLEXPORT wxFontBase : public wxGDIObject
{
public:
    // creator function
    virtual ~wxFontBase();

    // from the font components
    static wxFont *New(
        int pointSize,              // size of the font in points
        int family,                 // see wxFontFamily enum
        int style,                  // see wxFontStyle enum
        int weight,                 // see wxFontWeight enum
        bool underlined = FALSE,    // not underlined by default
        const wxString& face = wxEmptyString,              // facename
        wxFontEncoding encoding = wxFONTENCODING_DEFAULT); // ISO8859-X, ...

    // from the font components but using the font flags instead of separate
    // parameters for each flag
    static wxFont *New(int pointSize,
                       wxFontFamily family,
                       int flags = wxFONTFLAG_DEFAULT,
                       const wxString& face = wxEmptyString,
                       wxFontEncoding encoding = wxFONTENCODING_DEFAULT);

    // from the (opaque) native font description object
    static wxFont *New(const wxNativeFontInfo& nativeFontDesc);

    // from the string representation of wxNativeFontInfo
    static wxFont *New(const wxString& strNativeFontDesc);

    // was the font successfully created?
    bool Ok() const { return m_refData != NULL; }

    // comparison
    bool operator == (const wxFont& font) const;
    bool operator != (const wxFont& font) const;

    // accessors: get the font characteristics
    virtual int GetPointSize() const = 0;
    virtual int GetFamily() const = 0;
    virtual int GetStyle() const = 0;
    virtual int GetWeight() const = 0;
    virtual bool GetUnderlined() const = 0;
    virtual wxString GetFaceName() const = 0;
    virtual wxFontEncoding GetEncoding() const = 0;
    virtual wxNativeFontInfo *GetNativeFontInfo() const;

    virtual bool IsFixedWidth() const;

    wxString GetNativeFontInfoDesc() const;
    wxString GetNativeFontInfoUserDesc() const;

    // change the font characteristics
    virtual void SetPointSize( int pointSize ) = 0;
    virtual void SetFamily( int family ) = 0;
    virtual void SetStyle( int style ) = 0;
    virtual void SetWeight( int weight ) = 0;
    virtual void SetFaceName( const wxString& faceName ) = 0;
    virtual void SetUnderlined( bool underlined ) = 0;
    virtual void SetEncoding(wxFontEncoding encoding) = 0;
    void SetNativeFontInfo(const wxNativeFontInfo& info)
        { DoSetNativeFontInfo(info); }

    void SetNativeFontInfo(const wxString& info);
    void SetNativeFontInfoUserDesc(const wxString& info);

    // translate the fonts into human-readable string (i.e. GetStyleString()
    // will return "wxITALIC" for an italic font, ...)
    wxString GetFamilyString() const;
    wxString GetStyleString() const;
    wxString GetWeightString() const;

    // Unofficial API, don't use
    virtual void SetNoAntiAliasing( bool WXUNUSED(no) = TRUE ) {  }
    virtual bool GetNoAntiAliasing() { return FALSE; }

    // the default encoding is used for creating all fonts with default
    // encoding parameter
    static wxFontEncoding GetDefaultEncoding() { return ms_encodingDefault; }
    static void SetDefaultEncoding(wxFontEncoding encoding);

protected:
    // get the internal data
    wxFontRefData *GetFontData() const
        { return (wxFontRefData *)m_refData; }

    // the function called by both overloads of SetNativeFontInfo()
    virtual void DoSetNativeFontInfo(const wxNativeFontInfo& info);

private:
    // the currently default encoding: by default, it's the default system
    // encoding, but may be changed by the application using
    // SetDefaultEncoding() to make all subsequent fonts created without
    // specifing encoding parameter using this encoding
    static wxFontEncoding ms_encodingDefault;
};

// include the real class declaration
#if defined(__WXMSW__)
    #include "wx/msw/font.h"
#elif defined(__WXMOTIF__)
    #include "wx/motif/font.h"
#elif defined(__WXGTK__)
    #include "wx/gtk/font.h"
#elif defined(__WXX11__)
    #include "wx/x11/font.h"
#elif defined(__WXMGL__)
    #include "wx/mgl/font.h"
#elif defined(__WXMAC__)
    #include "wx/mac/font.h"
#elif defined(__WXPM__)
    #include "wx/os2/font.h"
#endif

// ----------------------------------------------------------------------------
// macros
// ----------------------------------------------------------------------------

#define M_FONTDATA GetFontData()

#endif
    // _WX_FONT_H_BASE_
