#pragma once
#include "Event.h"

namespace Simulacra
{
    enum class VKEY : int32_t;
    enum class SCANCODE : int32_t;

    class KeyPressedDownEvent : public Event
    {
    public:
        explicit KeyPressedDownEvent(VKEY key)
            : Event(EventType::KEY_PRESSED, "Key Pressed"), m_Key(key)
        {
            std::cout << m_Name << std::endl;
        }
        virtual ~KeyPressedDownEvent() = default;

        VKEY KeyCode() const { return m_Key; }

        static EventType StaticType()
        {
           return EventType::KEY_PRESSED;
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << std::to_string((int32_t)m_Key);
            return ss.str();
        }

        virtual EventType Type() const override
        {
            return StaticType();
        }
    private: 
        VKEY m_Key;
    };

    class KeyPressedUpEvent : public Event
    {
    public:
        explicit KeyPressedUpEvent(VKEY key)
            : Event(EventType::KEY_RELEASED, "Key Released"), m_Key(key)
        {
            std::cout << m_Name << std::endl;
        }
        virtual ~KeyPressedUpEvent() = default;

        VKEY KeyCode() const { return m_Key; }

        static EventType StaticType()
        {
           return EventType::KEY_RELEASED;
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << std::to_string((int32_t)m_Key);
            return ss.str();
        }

        virtual EventType Type() const override
        {
            return StaticType();
        }
    private: 
        VKEY m_Key;
    };

    enum class SCANCODE : int32_t
    {
        SCANCODE_UNKNOWN = 0,
        /**
         *  \name Usage page 0x07
         *
         *  These values are from usage page 0x07 (USB keyboard page).
         */
        /* @{ */

        SCANCODE_A = 4,
        SCANCODE_B = 5,
        SCANCODE_C = 6,
        SCANCODE_D = 7,
        SCANCODE_E = 8,
        SCANCODE_F = 9,
        SCANCODE_G = 10,
        SCANCODE_H = 11,
        SCANCODE_I = 12,
        SCANCODE_J = 13,
        SCANCODE_K = 14,
        SCANCODE_L = 15,
        SCANCODE_M = 16,
        SCANCODE_N = 17,
        SCANCODE_O = 18,
        SCANCODE_P = 19,
        SCANCODE_Q = 20,
        SCANCODE_R = 21,
        SCANCODE_S = 22,
        SCANCODE_T = 23,
        SCANCODE_U = 24,
        SCANCODE_V = 25,
        SCANCODE_W = 26,
        SCANCODE_X = 27,
        SCANCODE_Y = 28,
        SCANCODE_Z = 29,

        SCANCODE_1 = 30,
        SCANCODE_2 = 31,
        SCANCODE_3 = 32,
        SCANCODE_4 = 33,
        SCANCODE_5 = 34,
        SCANCODE_6 = 35,
        SCANCODE_7 = 36,
        SCANCODE_8 = 37,
        SCANCODE_9 = 38,
        SCANCODE_0 = 39,

        SCANCODE_RETURN = 40,
        SCANCODE_ESCAPE = 41,
        SCANCODE_BACKSPACE = 42,
        SCANCODE_TAB = 43,
        SCANCODE_SPACE = 44,

        SCANCODE_MINUS = 45,
        SCANCODE_EQUALS = 46,
        SCANCODE_LEFTBRACKET = 47,
        SCANCODE_RIGHTBRACKET = 48,
        SCANCODE_BACKSLASH = 49, /**< Located at the lower left of the return
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
        SCANCODE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                    *   instead of 49 for the same key, but all
                                    *   OSes I've seen treat the two codes
                                    *   identically. So, as an implementor, unless
                                    *   your keyboard generates both of those
                                    *   codes and your OS treats them differently,
                                    *   you should generate SCANCODE_BACKSLASH
                                    *   instead of this code. As a user, you
                                    *   should not rely on this code because SDL
                                    *   will never generate it with most (all?)
                                    *   keyboards.
                                    */
        SCANCODE_SEMICOLON = 51,
        SCANCODE_APOSTROPHE = 52,
        SCANCODE_GRAVE = 53, /**< Located in the top left corner (on both ANSI
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
        SCANCODE_COMMA = 54,
        SCANCODE_PERIOD = 55,
        SCANCODE_SLASH = 56,

        SCANCODE_CAPSLOCK = 57,

        SCANCODE_F1 = 58,
        SCANCODE_F2 = 59,
        SCANCODE_F3 = 60,
        SCANCODE_F4 = 61,
        SCANCODE_F5 = 62,
        SCANCODE_F6 = 63,
        SCANCODE_F7 = 64,
        SCANCODE_F8 = 65,
        SCANCODE_F9 = 66,
        SCANCODE_F10 = 67,
        SCANCODE_F11 = 68,
        SCANCODE_F12 = 69,

        SCANCODE_PRINTSCREEN = 70,
        SCANCODE_SCROLLLOCK = 71,
        SCANCODE_PAUSE = 72,
        SCANCODE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                    does send code 73, not 117) */
        SCANCODE_HOME = 74,
        SCANCODE_PAGEUP = 75,
        SCANCODE_DELETE = 76,
        SCANCODE_END = 77,
        SCANCODE_PAGEDOWN = 78,
        SCANCODE_RIGHT = 79,
        SCANCODE_LEFT = 80,
        SCANCODE_DOWN = 81,
        SCANCODE_UP = 82,

        SCANCODE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                        */
        SCANCODE_KP_DIVIDE = 84,
        SCANCODE_KP_MULTIPLY = 85,
        SCANCODE_KP_MINUS = 86,
        SCANCODE_KP_PLUS = 87,
        SCANCODE_KP_ENTER = 88,
        SCANCODE_KP_1 = 89,
        SCANCODE_KP_2 = 90,
        SCANCODE_KP_3 = 91,
        SCANCODE_KP_4 = 92,
        SCANCODE_KP_5 = 93,
        SCANCODE_KP_6 = 94,
        SCANCODE_KP_7 = 95,
        SCANCODE_KP_8 = 96,
        SCANCODE_KP_9 = 97,
        SCANCODE_KP_0 = 98,
        SCANCODE_KP_PERIOD = 99,

        SCANCODE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                            *   keyboards have over ANSI ones,
                                            *   located between left shift and Y.
                                            *   Produces GRAVE ACCENT and TILDE in a
                                            *   US or UK Mac layout, REVERSE SOLIDUS
                                            *   (backslash) and VERTICAL LINE in a
                                            *   US or UK Windows layout, and
                                            *   LESS-THAN SIGN and GREATER-THAN SIGN
                                            *   in a Swiss German, German, or French
                                            *   layout. */
        SCANCODE_APPLICATION = 101, /**< windows contextual menu, compose */
        SCANCODE_POWER = 102, /**< The USB document says this is a status flag,
                                *   not a physical key - but some Mac keyboards
                                *   do have a power key. */
        SCANCODE_KP_EQUALS = 103,
        SCANCODE_F13 = 104,
        SCANCODE_F14 = 105,
        SCANCODE_F15 = 106,
        SCANCODE_F16 = 107,
        SCANCODE_F17 = 108,
        SCANCODE_F18 = 109,
        SCANCODE_F19 = 110,
        SCANCODE_F20 = 111,
        SCANCODE_F21 = 112,
        SCANCODE_F22 = 113,
        SCANCODE_F23 = 114,
        SCANCODE_F24 = 115,
        SCANCODE_EXECUTE = 116,
        SCANCODE_HELP = 117,    /**< AL Integrated Help Center */
        SCANCODE_MENU = 118,    /**< Menu (show menu) */
        SCANCODE_SELECT = 119,
        SCANCODE_STOP = 120,    /**< AC Stop */
        SCANCODE_AGAIN = 121,   /**< AC Redo/Repeat */
        SCANCODE_UNDO = 122,    /**< AC Undo */
        SCANCODE_CUT = 123,     /**< AC Cut */
        SCANCODE_COPY = 124,    /**< AC Copy */
        SCANCODE_PASTE = 125,   /**< AC Paste */
        SCANCODE_FIND = 126,    /**< AC Find */
        SCANCODE_MUTE = 127,
        SCANCODE_VOLUMEUP = 128,
        SCANCODE_VOLUMEDOWN = 129,
    /* not sure whether there's a reason to enable these */
    /*     SCANCODE_LOCKINGCAPSLOCK = 130,  */
    /*     SCANCODE_LOCKINGNUMLOCK = 131, */
    /*     SCANCODE_LOCKINGSCROLLLOCK = 132, */
        SCANCODE_KP_COMMA = 133,
        SCANCODE_KP_EQUALSAS400 = 134,

        SCANCODE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                                footnotes in USB doc */
        SCANCODE_INTERNATIONAL2 = 136,
        SCANCODE_INTERNATIONAL3 = 137, /**< Yen */
        SCANCODE_INTERNATIONAL4 = 138,
        SCANCODE_INTERNATIONAL5 = 139,
        SCANCODE_INTERNATIONAL6 = 140,
        SCANCODE_INTERNATIONAL7 = 141,
        SCANCODE_INTERNATIONAL8 = 142,
        SCANCODE_INTERNATIONAL9 = 143,
        SCANCODE_LANG1 = 144, /**< Hangul/English toggle */
        SCANCODE_LANG2 = 145, /**< Hanja conversion */
        SCANCODE_LANG3 = 146, /**< Katakana */
        SCANCODE_LANG4 = 147, /**< Hiragana */
        SCANCODE_LANG5 = 148, /**< Zenkaku/Hankaku */
        SCANCODE_LANG6 = 149, /**< reserved */
        SCANCODE_LANG7 = 150, /**< reserved */
        SCANCODE_LANG8 = 151, /**< reserved */
        SCANCODE_LANG9 = 152, /**< reserved */

        SCANCODE_ALTERASE = 153,    /**< Erase-Eaze */
        SCANCODE_SYSREQ = 154,
        SCANCODE_CANCEL = 155,      /**< AC Cancel */
        SCANCODE_CLEAR = 156,
        SCANCODE_PRIOR = 157,
        SCANCODE_RETURN2 = 158,
        SCANCODE_SEPARATOR = 159,
        SCANCODE_OUT = 160,
        SCANCODE_OPER = 161,
        SCANCODE_CLEARAGAIN = 162,
        SCANCODE_CRSEL = 163,
        SCANCODE_EXSEL = 164,

        SCANCODE_KP_00 = 176,
        SCANCODE_KP_000 = 177,
        SCANCODE_THOUSANDSSEPARATOR = 178,
        SCANCODE_DECIMALSEPARATOR = 179,
        SCANCODE_CURRENCYUNIT = 180,
        SCANCODE_CURRENCYSUBUNIT = 181,
        SCANCODE_KP_LEFTPAREN = 182,
        SCANCODE_KP_RIGHTPAREN = 183,
        SCANCODE_KP_LEFTBRACE = 184,
        SCANCODE_KP_RIGHTBRACE = 185,
        SCANCODE_KP_TAB = 186,
        SCANCODE_KP_BACKSPACE = 187,
        SCANCODE_KP_A = 188,
        SCANCODE_KP_B = 189,
        SCANCODE_KP_C = 190,
        SCANCODE_KP_D = 191,
        SCANCODE_KP_E = 192,
        SCANCODE_KP_F = 193,
        SCANCODE_KP_XOR = 194,
        SCANCODE_KP_POWER = 195,
        SCANCODE_KP_PERCENT = 196,
        SCANCODE_KP_LESS = 197,
        SCANCODE_KP_GREATER = 198,
        SCANCODE_KP_AMPERSAND = 199,
        SCANCODE_KP_DBLAMPERSAND = 200,
        SCANCODE_KP_VERTICALBAR = 201,
        SCANCODE_KP_DBLVERTICALBAR = 202,
        SCANCODE_KP_COLON = 203,
        SCANCODE_KP_HASH = 204,
        SCANCODE_KP_SPACE = 205,
        SCANCODE_KP_AT = 206,
        SCANCODE_KP_EXCLAM = 207,
        SCANCODE_KP_MEMSTORE = 208,
        SCANCODE_KP_MEMRECALL = 209,
        SCANCODE_KP_MEMCLEAR = 210,
        SCANCODE_KP_MEMADD = 211,
        SCANCODE_KP_MEMSUBTRACT = 212,
        SCANCODE_KP_MEMMULTIPLY = 213,
        SCANCODE_KP_MEMDIVIDE = 214,
        SCANCODE_KP_PLUSMINUS = 215,
        SCANCODE_KP_CLEAR = 216,
        SCANCODE_KP_CLEARENTRY = 217,
        SCANCODE_KP_BINARY = 218,
        SCANCODE_KP_OCTAL = 219,
        SCANCODE_KP_DECIMAL = 220,
        SCANCODE_KP_HEXADECIMAL = 221,

        SCANCODE_LCTRL = 224,
        SCANCODE_LSHIFT = 225,
        SCANCODE_LALT = 226, /**< alt, option */
        SCANCODE_LGUI = 227, /**< windows, command (apple), meta */
        SCANCODE_RCTRL = 228,
        SCANCODE_RSHIFT = 229,
        SCANCODE_RALT = 230, /**< alt gr, option */
        SCANCODE_RGUI = 231, /**< windows, command (apple), meta */

        SCANCODE_MODE = 257,    /**< I'm not sure if this is really not covered
                                    *   by any of the above, but since there's a
                                    *   special KMOD_MODE for it I'm adding it here
                                    */

        /* @} *//* Usage page 0x07 */

        /**
         *  \name Usage page 0x0C
         *
         *  These values are mapped from usage page 0x0C (USB consumer page).
         *  See https://usb.org/sites/default/files/hut1_2.pdf
         *
         *  There are way more keys in the spec than we can represent in the
         *  current scancode range, so pick the ones that commonly come up in
         *  real world usage.
         */
        /* @{ */

        SCANCODE_AUDIONEXT = 258,
        SCANCODE_AUDIOPREV = 259,
        SCANCODE_AUDIOSTOP = 260,
        SCANCODE_AUDIOPLAY = 261,
        SCANCODE_AUDIOMUTE = 262,
        SCANCODE_MEDIASELECT = 263,
        SCANCODE_WWW = 264,             /**< AL Internet Browser */
        SCANCODE_MAIL = 265,
        SCANCODE_CALCULATOR = 266,      /**< AL Calculator */
        SCANCODE_COMPUTER = 267,
        SCANCODE_AC_SEARCH = 268,       /**< AC Search */
        SCANCODE_AC_HOME = 269,         /**< AC Home */
        SCANCODE_AC_BACK = 270,         /**< AC Back */
        SCANCODE_AC_FORWARD = 271,      /**< AC Forward */
        SCANCODE_AC_STOP = 272,         /**< AC Stop */
        SCANCODE_AC_REFRESH = 273,      /**< AC Refresh */
        SCANCODE_AC_BOOKMARKS = 274,    /**< AC Bookmarks */

        /* @} *//* Usage page 0x0C */

        /**
         *  \name Walther keys
         *
         *  These are values that Christian Walther added (for mac keyboard?).
         */
        /* @{ */

        SCANCODE_BRIGHTNESSDOWN = 275,
        SCANCODE_BRIGHTNESSUP = 276,
        SCANCODE_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                            switch, video mode switch */
        SCANCODE_KBDILLUMTOGGLE = 278,
        SCANCODE_KBDILLUMDOWN = 279,
        SCANCODE_KBDILLUMUP = 280,
        SCANCODE_EJECT = 281,
        SCANCODE_SLEEP = 282,           /**< SC System Sleep */

        SCANCODE_APP1 = 283,
        SCANCODE_APP2 = 284,

        /* @} *//* Walther keys */

        /**
         *  \name Usage page 0x0C (additional media keys)
         *
         *  These values are mapped from usage page 0x0C (USB consumer page).
         */
        /* @{ */

        SCANCODE_AUDIOREWIND = 285,
        SCANCODE_AUDIOFASTFORWARD = 286,

        /* @} *//* Usage page 0x0C (additional media keys) */

        /**
         *  \name Mobile keys
         *
         *  These are values that are often used on mobile phones.
         */
        /* @{ */

        SCANCODE_SOFTLEFT = 287, /**< Usually situated below the display on phones and
                                        used as a multi-function feature key for selecting
                                        a software defined function shown on the bottom left
                                        of the display. */
        SCANCODE_SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                        used as a multi-function feature key for selecting
                                        a software defined function shown on the bottom right
                                        of the display. */
        SCANCODE_CALL = 289, /**< Used for accepting phone calls. */
        SCANCODE_ENDCALL = 290, /**< Used for rejecting phone calls. */

        /* @} *//* Mobile keys */

        /* Add any other keys here. */

        NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes
                                    for array bounds */
    };

    #define SIMULACRA_SCANCODE_MASK (1<<30)
    #define SIMULACRA_SCANCODE_TO_KEYCODE(X)  ((int32_t)X | SIMULACRA_SCANCODE_MASK)

    enum class VKEY : int32_t
    {
        KEYCODE_UNKNOWN = 0,

        KEYCODE_RETURN = '\r',
        KEYCODE_ESCAPE = '\x1B',
        KEYCODE_BACKSPACE = '\b',
        KEYCODE_TAB = '\t',
        KEYCODE_SPACE = ' ',
        KEYCODE_EXCLAIM = '!',
        KEYCODE_QUOTEDBL = '"',
        KEYCODE_HASH = '#',
        KEYCODE_PERCENT = '%',
        KEYCODE_DOLLAR = '$',
        KEYCODE_AMPERSAND = '&',
        KEYCODE_QUOTE = '\'',
        KEYCODE_LEFTPAREN = '(',
        KEYCODE_RIGHTPAREN = ')',
        KEYCODE_ASTERISK = '*',
        KEYCODE_PLUS = '+',
        KEYCODE_COMMA = ',',
        KEYCODE_MINUS = '-',
        KEYCODE_PERIOD = '.',
        KEYCODE_SLASH = '/',
        KEYCODE_0 = '0',
        KEYCODE_1 = '1',
        KEYCODE_2 = '2',
        KEYCODE_3 = '3',
        KEYCODE_4 = '4',
        KEYCODE_5 = '5',
        KEYCODE_6 = '6',
        KEYCODE_7 = '7',
        KEYCODE_8 = '8',
        KEYCODE_9 = '9',
        KEYCODE_COLON = ':',
        KEYCODE_SEMICOLON = ';',
        KEYCODE_LESS = '<',
        KEYCODE_EQUALS = '=',
        KEYCODE_GREATER = '>',
        KEYCODE_QUESTION = '?',
        KEYCODE_AT = '@',

        /*
        Skip uppercase letters
        */

        KEYCODE_LEFTBRACKET = '[',
        KEYCODE_BACKSLASH = '\\',
        KEYCODE_RIGHTBRACKET = ']',
        KEYCODE_CARET = '^',
        KEYCODE_UNDERSCORE = '_',
        KEYCODE_BACKQUOTE = '`',
        KEYCODE_a = 'a',
        KEYCODE_b = 'b',
        KEYCODE_c = 'c',
        KEYCODE_d = 'd',
        KEYCODE_e = 'e',
        KEYCODE_f = 'f',
        KEYCODE_g = 'g',
        KEYCODE_h = 'h',
        KEYCODE_i = 'i',
        KEYCODE_j = 'j',
        KEYCODE_k = 'k',
        KEYCODE_l = 'l',
        KEYCODE_m = 'm',
        KEYCODE_n = 'n',
        KEYCODE_o = 'o',
        KEYCODE_p = 'p',
        KEYCODE_q = 'q',
        KEYCODE_r = 'r',
        KEYCODE_s = 's',
        KEYCODE_t = 't',
        KEYCODE_u = 'u',
        KEYCODE_v = 'v',
        KEYCODE_w = 'w',
        KEYCODE_x = 'x',
        KEYCODE_y = 'y',
        KEYCODE_z = 'z',

        KEYCODE_CAPSLOCK = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_CAPSLOCK),

        KEYCODE_F1 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F1),
        KEYCODE_F2 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F2),
        KEYCODE_F3 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F3),
        KEYCODE_F4 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F4),
        KEYCODE_F5 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F5),
        KEYCODE_F6 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F6),
        KEYCODE_F7 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F7),
        KEYCODE_F8 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F8),
        KEYCODE_F9 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F9),
        KEYCODE_F10 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F10),
        KEYCODE_F11 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F11),
        KEYCODE_F12 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F12),

        KEYCODE_PRINTSCREEN = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_PRINTSCREEN),
        KEYCODE_SCROLLLOCK = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_SCROLLLOCK),
        KEYCODE_PAUSE = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_PAUSE),
        KEYCODE_INSERT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_INSERT),
        KEYCODE_HOME = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_HOME),
        KEYCODE_PAGEUP = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_PAGEUP),
        KEYCODE_DELETE = '\x7F',
        KEYCODE_END = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_END),
        KEYCODE_PAGEDOWN = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_PAGEDOWN),
        KEYCODE_RIGHT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_RIGHT),
        KEYCODE_LEFT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_LEFT),
        KEYCODE_DOWN = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_DOWN),
        KEYCODE_UP = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_UP),

        KEYCODE_NUMLOCKCLEAR = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_NUMLOCKCLEAR),
        KEYCODE_KP_DIVIDE = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_DIVIDE),
        KEYCODE_KP_MULTIPLY = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_MULTIPLY),
        KEYCODE_KP_MINUS = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_MINUS),
        KEYCODE_KP_PLUS = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_PLUS),
        KEYCODE_KP_ENTER = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_ENTER),
        KEYCODE_KP_1 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_1),
        KEYCODE_KP_2 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_2),
        KEYCODE_KP_3 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_3),
        KEYCODE_KP_4 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_4),
        KEYCODE_KP_5 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_5),
        KEYCODE_KP_6 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_6),
        KEYCODE_KP_7 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_7),
        KEYCODE_KP_8 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_8),
        KEYCODE_KP_9 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_9),
        KEYCODE_KP_0 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_0),
        KEYCODE_KP_PERIOD = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_PERIOD),

        KEYCODE_APPLICATION = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_APPLICATION),
        KEYCODE_POWER = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_POWER),
        KEYCODE_KP_EQUALS = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_EQUALS),
        KEYCODE_F13 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F13),
        KEYCODE_F14 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F14),
        KEYCODE_F15 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F15),
        KEYCODE_F16 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F16),
        KEYCODE_F17 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F17),
        KEYCODE_F18 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F18),
        KEYCODE_F19 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F19),
        KEYCODE_F20 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F20),
        KEYCODE_F21 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F21),
        KEYCODE_F22 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F22),
        KEYCODE_F23 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F23),
        KEYCODE_F24 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_F24),
        KEYCODE_EXECUTE = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_EXECUTE),
        KEYCODE_HELP = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_HELP),
        KEYCODE_MENU = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_MENU),
        KEYCODE_SELECT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_SELECT),
        KEYCODE_STOP = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_STOP),
        KEYCODE_AGAIN = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_AGAIN),
        KEYCODE_UNDO = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_UNDO),
        KEYCODE_CUT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_CUT),
        KEYCODE_COPY = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_COPY),
        KEYCODE_PASTE = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_PASTE),
        KEYCODE_FIND = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_FIND),
        KEYCODE_MUTE = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_MUTE),
        KEYCODE_VOLUMEUP = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_VOLUMEUP),
        KEYCODE_VOLUMEDOWN = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_VOLUMEDOWN),
        KEYCODE_KP_COMMA = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_COMMA),
        KEYCODE_KP_EQUALSAS400 =
            SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_EQUALSAS400),

        KEYCODE_ALTERASE = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_ALTERASE),
        KEYCODE_SYSREQ = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_SYSREQ),
        KEYCODE_CANCEL = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_CANCEL),
        KEYCODE_CLEAR = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_CLEAR),
        KEYCODE_PRIOR = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_PRIOR),
        KEYCODE_RETURN2 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_RETURN2),
        KEYCODE_SEPARATOR = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_SEPARATOR),
        KEYCODE_OUT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_OUT),
        KEYCODE_OPER = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_OPER),
        KEYCODE_CLEARAGAIN = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_CLEARAGAIN),
        KEYCODE_CRSEL = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_CRSEL),
        KEYCODE_EXSEL = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_EXSEL),

        KEYCODE_KP_00 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_00),
        KEYCODE_KP_000 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_000),
        KEYCODE_THOUSANDSSEPARATOR =
            SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_THOUSANDSSEPARATOR),
        KEYCODE_DECIMALSEPARATOR =
            SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_DECIMALSEPARATOR),
        KEYCODE_CURRENCYUNIT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_CURRENCYUNIT),
        KEYCODE_CURRENCYSUBUNIT =
            SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_CURRENCYSUBUNIT),
        KEYCODE_KP_LEFTPAREN = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_LEFTPAREN),
        KEYCODE_KP_RIGHTPAREN = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_RIGHTPAREN),
        KEYCODE_KP_LEFTBRACE = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_LEFTBRACE),
        KEYCODE_KP_RIGHTBRACE = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_RIGHTBRACE),
        KEYCODE_KP_TAB = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_TAB),
        KEYCODE_KP_BACKSPACE = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_BACKSPACE),
        KEYCODE_KP_A = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_A),
        KEYCODE_KP_B = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_B),
        KEYCODE_KP_C = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_C),
        KEYCODE_KP_D = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_D),
        KEYCODE_KP_E = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_E),
        KEYCODE_KP_F = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_F),
        KEYCODE_KP_XOR = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_XOR),
        KEYCODE_KP_POWER = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_POWER),
        KEYCODE_KP_PERCENT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_PERCENT),
        KEYCODE_KP_LESS = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_LESS),
        KEYCODE_KP_GREATER = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_GREATER),
        KEYCODE_KP_AMPERSAND = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_AMPERSAND),
        KEYCODE_KP_DBLAMPERSAND =
            SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_DBLAMPERSAND),
        KEYCODE_KP_VERTICALBAR =
            SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_VERTICALBAR),
        KEYCODE_KP_DBLVERTICALBAR =
            SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_DBLVERTICALBAR),
        KEYCODE_KP_COLON = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_COLON),
        KEYCODE_KP_HASH = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_HASH),
        KEYCODE_KP_SPACE = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_SPACE),
        KEYCODE_KP_AT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_AT),
        KEYCODE_KP_EXCLAM = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_EXCLAM),
        KEYCODE_KP_MEMSTORE = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_MEMSTORE),
        KEYCODE_KP_MEMRECALL = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_MEMRECALL),
        KEYCODE_KP_MEMCLEAR = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_MEMCLEAR),
        KEYCODE_KP_MEMADD = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_MEMADD),
        KEYCODE_KP_MEMSUBTRACT =
            SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_MEMSUBTRACT),
        KEYCODE_KP_MEMMULTIPLY =
            SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_MEMMULTIPLY),
        KEYCODE_KP_MEMDIVIDE = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_MEMDIVIDE),
        KEYCODE_KP_PLUSMINUS = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_PLUSMINUS),
        KEYCODE_KP_CLEAR = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_CLEAR),
        KEYCODE_KP_CLEARENTRY = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_CLEARENTRY),
        KEYCODE_KP_BINARY = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_BINARY),
        KEYCODE_KP_OCTAL = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_OCTAL),
        KEYCODE_KP_DECIMAL = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_DECIMAL),
        KEYCODE_KP_HEXADECIMAL =
            SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KP_HEXADECIMAL),

        KEYCODE_LCTRL = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_LCTRL),
        KEYCODE_LSHIFT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_LSHIFT),
        KEYCODE_LALT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_LALT),
        KEYCODE_LGUI = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_LGUI),
        KEYCODE_RCTRL = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_RCTRL),
        KEYCODE_RSHIFT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_RSHIFT),
        KEYCODE_RALT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_RALT),
        KEYCODE_RGUI = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_RGUI),

        KEYCODE_MODE = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_MODE),

        KEYCODE_AUDIONEXT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_AUDIONEXT),
        KEYCODE_AUDIOPREV = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_AUDIOPREV),
        KEYCODE_AUDIOSTOP = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_AUDIOSTOP),
        KEYCODE_AUDIOPLAY = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_AUDIOPLAY),
        KEYCODE_AUDIOMUTE = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_AUDIOMUTE),
        KEYCODE_MEDIASELECT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_MEDIASELECT),
        KEYCODE_WWW = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_WWW),
        KEYCODE_MAIL = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_MAIL),
        KEYCODE_CALCULATOR = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_CALCULATOR),
        KEYCODE_COMPUTER = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_COMPUTER),
        KEYCODE_AC_SEARCH = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_AC_SEARCH),
        KEYCODE_AC_HOME = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_AC_HOME),
        KEYCODE_AC_BACK = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_AC_BACK),
        KEYCODE_AC_FORWARD = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_AC_FORWARD),
        KEYCODE_AC_STOP = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_AC_STOP),
        KEYCODE_AC_REFRESH = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_AC_REFRESH),
        KEYCODE_AC_BOOKMARKS = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_AC_BOOKMARKS),

        KEYCODE_BRIGHTNESSDOWN =
            SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_BRIGHTNESSDOWN),
        KEYCODE_BRIGHTNESSUP = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_BRIGHTNESSUP),
        KEYCODE_DISPLAYSWITCH = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_DISPLAYSWITCH),
        KEYCODE_KBDILLUMTOGGLE =
            SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KBDILLUMTOGGLE),
        KEYCODE_KBDILLUMDOWN = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KBDILLUMDOWN),
        KEYCODE_KBDILLUMUP = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_KBDILLUMUP),
        KEYCODE_EJECT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_EJECT),
        KEYCODE_SLEEP = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_SLEEP),
        KEYCODE_APP1 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_APP1),
        KEYCODE_APP2 = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_APP2),

        KEYCODE_AUDIOREWIND = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_AUDIOREWIND),
        KEYCODE_AUDIOFASTFORWARD = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_AUDIOFASTFORWARD),

        KEYCODE_SOFTLEFT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_SOFTLEFT),
        KEYCODE_SOFTRIGHT = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_SOFTRIGHT),
        KEYCODE_CALL = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_CALL),
        KEYCODE_ENDCALL = SIMULACRA_SCANCODE_TO_KEYCODE(SCANCODE::SCANCODE_ENDCALL)
    };
}