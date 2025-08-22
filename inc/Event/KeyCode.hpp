#pragma once

namespace AMB {

/// @brief Enumeration of the keys
enum KeyCode {
    KEY_CODE_UNKNOWN = 0,

    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
    /* @{ */

    KEY_CODE_A = 4,
    KEY_CODE_B = 5,
    KEY_CODE_C = 6,
    KEY_CODE_D = 7,
    KEY_CODE_E = 8,
    KEY_CODE_F = 9,
    KEY_CODE_G = 10,
    KEY_CODE_H = 11,
    KEY_CODE_I = 12,
    KEY_CODE_J = 13,
    KEY_CODE_K = 14,
    KEY_CODE_L = 15,
    KEY_CODE_M = 16,
    KEY_CODE_N = 17,
    KEY_CODE_O = 18,
    KEY_CODE_P = 19,
    KEY_CODE_Q = 20,
    KEY_CODE_R = 21,
    KEY_CODE_S = 22,
    KEY_CODE_T = 23,
    KEY_CODE_U = 24,
    KEY_CODE_V = 25,
    KEY_CODE_W = 26,
    KEY_CODE_X = 27,
    KEY_CODE_Y = 28,
    KEY_CODE_Z = 29,

    KEY_CODE_1 = 30,
    KEY_CODE_2 = 31,
    KEY_CODE_3 = 32,
    KEY_CODE_4 = 33,
    KEY_CODE_5 = 34,
    KEY_CODE_6 = 35,
    KEY_CODE_7 = 36,
    KEY_CODE_8 = 37,
    KEY_CODE_9 = 38,
    KEY_CODE_0 = 39,

    KEY_CODE_RETURN = 40,
    KEY_CODE_ESCAPE = 41,
    KEY_CODE_BACKSPACE = 42,
    KEY_CODE_TAB = 43,
    KEY_CODE_SPACE = 44,

    KEY_CODE_MINUS = 45,
    KEY_CODE_EQUALS = 46,
    KEY_CODE_LEFTBRACKET = 47,
    KEY_CODE_RIGHTBRACKET = 48,
    KEY_CODE_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    KEY_CODE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate KEY_CODE_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    KEY_CODE_SEMICOLON = 51,
    KEY_CODE_APOSTROPHE = 52,
    KEY_CODE_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    KEY_CODE_COMMA = 54,
    KEY_CODE_PERIOD = 55,
    KEY_CODE_SLASH = 56,

    KEY_CODE_CAPSLOCK = 57,

    KEY_CODE_F1 = 58,
    KEY_CODE_F2 = 59,
    KEY_CODE_F3 = 60,
    KEY_CODE_F4 = 61,
    KEY_CODE_F5 = 62,
    KEY_CODE_F6 = 63,
    KEY_CODE_F7 = 64,
    KEY_CODE_F8 = 65,
    KEY_CODE_F9 = 66,
    KEY_CODE_F10 = 67,
    KEY_CODE_F11 = 68,
    KEY_CODE_F12 = 69,

    KEY_CODE_PRINTSCREEN = 70,
    KEY_CODE_SCROLLLOCK = 71,
    KEY_CODE_PAUSE = 72,
    KEY_CODE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    KEY_CODE_HOME = 74,
    KEY_CODE_PAGEUP = 75,
    KEY_CODE_DELETE = 76,
    KEY_CODE_END = 77,
    KEY_CODE_PAGEDOWN = 78,
    KEY_CODE_RIGHT = 79,
    KEY_CODE_LEFT = 80,
    KEY_CODE_DOWN = 81,
    KEY_CODE_UP = 82,

    KEY_CODE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    KEY_CODE_KP_DIVIDE = 84,
    KEY_CODE_KP_MULTIPLY = 85,
    KEY_CODE_KP_MINUS = 86,
    KEY_CODE_KP_PLUS = 87,
    KEY_CODE_KP_ENTER = 88,
    KEY_CODE_KP_1 = 89,
    KEY_CODE_KP_2 = 90,
    KEY_CODE_KP_3 = 91,
    KEY_CODE_KP_4 = 92,
    KEY_CODE_KP_5 = 93,
    KEY_CODE_KP_6 = 94,
    KEY_CODE_KP_7 = 95,
    KEY_CODE_KP_8 = 96,
    KEY_CODE_KP_9 = 97,
    KEY_CODE_KP_0 = 98,
    KEY_CODE_KP_PERIOD = 99,

    KEY_CODE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    KEY_CODE_APPLICATION = 101, /**< windows contextual menu, compose */
    KEY_CODE_POWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    KEY_CODE_KP_EQUALS = 103,
    KEY_CODE_F13 = 104,
    KEY_CODE_F14 = 105,
    KEY_CODE_F15 = 106,
    KEY_CODE_F16 = 107,
    KEY_CODE_F17 = 108,
    KEY_CODE_F18 = 109,
    KEY_CODE_F19 = 110,
    KEY_CODE_F20 = 111,
    KEY_CODE_F21 = 112,
    KEY_CODE_F22 = 113,
    KEY_CODE_F23 = 114,
    KEY_CODE_F24 = 115,
    KEY_CODE_EXECUTE = 116,
    KEY_CODE_HELP = 117,
    KEY_CODE_MENU = 118,
    KEY_CODE_SELECT = 119,
    KEY_CODE_STOP = 120,
    KEY_CODE_AGAIN = 121,   /**< redo */
    KEY_CODE_UNDO = 122,
    KEY_CODE_CUT = 123,
    KEY_CODE_COPY = 124,
    KEY_CODE_PASTE = 125,
    KEY_CODE_FIND = 126,
    KEY_CODE_MUTE = 127,
    KEY_CODE_VOLUMEUP = 128,
    KEY_CODE_VOLUMEDOWN = 129,
/* not sure whether there's a reason to enable these */
/*     KEY_CODE_LOCKINGCAPSLOCK = 130,  */
/*     KEY_CODE_LOCKINGNUMLOCK = 131, */
/*     KEY_CODE_LOCKINGSCROLLLOCK = 132, */
    KEY_CODE_KP_COMMA = 133,
    KEY_CODE_KP_EQUALSAS400 = 134,

    KEY_CODE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    KEY_CODE_INTERNATIONAL2 = 136,
    KEY_CODE_INTERNATIONAL3 = 137, /**< Yen */
    KEY_CODE_INTERNATIONAL4 = 138,
    KEY_CODE_INTERNATIONAL5 = 139,
    KEY_CODE_INTERNATIONAL6 = 140,
    KEY_CODE_INTERNATIONAL7 = 141,
    KEY_CODE_INTERNATIONAL8 = 142,
    KEY_CODE_INTERNATIONAL9 = 143,
    KEY_CODE_LANG1 = 144, /**< Hangul/English toggle */
    KEY_CODE_LANG2 = 145, /**< Hanja conversion */
    KEY_CODE_LANG3 = 146, /**< Katakana */
    KEY_CODE_LANG4 = 147, /**< Hiragana */
    KEY_CODE_LANG5 = 148, /**< Zenkaku/Hankaku */
    KEY_CODE_LANG6 = 149, /**< reserved */
    KEY_CODE_LANG7 = 150, /**< reserved */
    KEY_CODE_LANG8 = 151, /**< reserved */
    KEY_CODE_LANG9 = 152, /**< reserved */

    KEY_CODE_ALTERASE = 153, /**< Erase-Eaze */
    KEY_CODE_SYSREQ = 154,
    KEY_CODE_CANCEL = 155,
    KEY_CODE_CLEAR = 156,
    KEY_CODE_PRIOR = 157,
    KEY_CODE_RETURN2 = 158,
    KEY_CODE_SEPARATOR = 159,
    KEY_CODE_OUT = 160,
    KEY_CODE_OPER = 161,
    KEY_CODE_CLEARAGAIN = 162,
    KEY_CODE_CRSEL = 163,
    KEY_CODE_EXSEL = 164,

    KEY_CODE_KP_00 = 176,
    KEY_CODE_KP_000 = 177,
    KEY_CODE_THOUSANDSSEPARATOR = 178,
    KEY_CODE_DECIMALSEPARATOR = 179,
    KEY_CODE_CURRENCYUNIT = 180,
    KEY_CODE_CURRENCYSUBUNIT = 181,
    KEY_CODE_KP_LEFTPAREN = 182,
    KEY_CODE_KP_RIGHTPAREN = 183,
    KEY_CODE_KP_LEFTBRACE = 184,
    KEY_CODE_KP_RIGHTBRACE = 185,
    KEY_CODE_KP_TAB = 186,
    KEY_CODE_KP_BACKSPACE = 187,
    KEY_CODE_KP_A = 188,
    KEY_CODE_KP_B = 189,
    KEY_CODE_KP_C = 190,
    KEY_CODE_KP_D = 191,
    KEY_CODE_KP_E = 192,
    KEY_CODE_KP_F = 193,
    KEY_CODE_KP_XOR = 194,
    KEY_CODE_KP_POWER = 195,
    KEY_CODE_KP_PERCENT = 196,
    KEY_CODE_KP_LESS = 197,
    KEY_CODE_KP_GREATER = 198,
    KEY_CODE_KP_AMPERSAND = 199,
    KEY_CODE_KP_DBLAMPERSAND = 200,
    KEY_CODE_KP_VERTICALBAR = 201,
    KEY_CODE_KP_DBLVERTICALBAR = 202,
    KEY_CODE_KP_COLON = 203,
    KEY_CODE_KP_HASH = 204,
    KEY_CODE_KP_SPACE = 205,
    KEY_CODE_KP_AT = 206,
    KEY_CODE_KP_EXCLAM = 207,
    KEY_CODE_KP_MEMSTORE = 208,
    KEY_CODE_KP_MEMRECALL = 209,
    KEY_CODE_KP_MEMCLEAR = 210,
    KEY_CODE_KP_MEMADD = 211,
    KEY_CODE_KP_MEMSUBTRACT = 212,
    KEY_CODE_KP_MEMMULTIPLY = 213,
    KEY_CODE_KP_MEMDIVIDE = 214,
    KEY_CODE_KP_PLUSMINUS = 215,
    KEY_CODE_KP_CLEAR = 216,
    KEY_CODE_KP_CLEARENTRY = 217,
    KEY_CODE_KP_BINARY = 218,
    KEY_CODE_KP_OCTAL = 219,
    KEY_CODE_KP_DECIMAL = 220,
    KEY_CODE_KP_HEXADECIMAL = 221,

    KEY_CODE_LCTRL = 224,
    KEY_CODE_LSHIFT = 225,
    KEY_CODE_LALT = 226, /**< alt, option */
    KEY_CODE_LGUI = 227, /**< windows, command (apple), meta */
    KEY_CODE_RCTRL = 228,
    KEY_CODE_RSHIFT = 229,
    KEY_CODE_RALT = 230, /**< alt gr, option */
    KEY_CODE_RGUI = 231, /**< windows, command (apple), meta */

    KEY_CODE_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special KMOD_MODE for it I'm adding it here
                                 */

    /* @} *//* Usage page 0x07 */

    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    KEY_CODE_AUDIONEXT = 258,
    KEY_CODE_AUDIOPREV = 259,
    KEY_CODE_AUDIOSTOP = 260,
    KEY_CODE_AUDIOPLAY = 261,
    KEY_CODE_AUDIOMUTE = 262,
    KEY_CODE_MEDIASELECT = 263,
    KEY_CODE_WWW = 264,
    KEY_CODE_MAIL = 265,
    KEY_CODE_CALCULATOR = 266,
    KEY_CODE_COMPUTER = 267,
    KEY_CODE_AC_SEARCH = 268,
    KEY_CODE_AC_HOME = 269,
    KEY_CODE_AC_BACK = 270,
    KEY_CODE_AC_FORWARD = 271,
    KEY_CODE_AC_STOP = 272,
    KEY_CODE_AC_REFRESH = 273,
    KEY_CODE_AC_BOOKMARKS = 274,

    /* @} *//* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /* @{ */

    KEY_CODE_BRIGHTNESSDOWN = 275,
    KEY_CODE_BRIGHTNESSUP = 276,
    KEY_CODE_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                           switch, video mode switch */
    KEY_CODE_KBDILLUMTOGGLE = 278,
    KEY_CODE_KBDILLUMDOWN = 279,
    KEY_CODE_KBDILLUMUP = 280,
    KEY_CODE_EJECT = 281,
    KEY_CODE_SLEEP = 282,

    KEY_CODE_APP1 = 283,
    KEY_CODE_APP2 = 284,

    /* @} *//* Walther keys */

    /**
     *  \name Usage page 0x0C (additional media keys)
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    KEY_CODE_AUDIOREWIND = 285,
    KEY_CODE_AUDIOFASTFORWARD = 286,

    /* @} *//* Usage page 0x0C (additional media keys) */

    /* Add any other keys here. */

    KEY_NUM_CODES = 512 /**< not a key, just marks the number of scancodes
                                 for array bounds */
};

}