/**
 * @file InputStructs.h
 * @brief Defines structures and enumerations for input handling, including keyboard, mouse, and controller inputs.
 */

#ifndef INPUTSTRUCTS_H
#define INPUTSTRUCTS_H

#include <string>
#include "Structs.h"


/**
 * @enum MouseButton
 * @brief Enumeration for mouse buttons.
 */
enum class MouseButton { 
    LEFT = 1, 
    MIDDLE = 2, 
    RIGHT = 3 
};

/**
 * @struct Mouse
 * @brief Structure to represent the state of the mouse.
 */
struct Mouse {
    Point position; ///< The position of the mouse.

    bool left = false;   ///< State of the left mouse button.
    bool middle = false; ///< State of the middle mouse button.
    bool right = false;  ///< State of the right mouse button.
};

/**
 * @enum Key
 * @brief Enumeration for all keyboard, mouse, and controller keys.
 */
enum class Key {
    Key_UNKNOWN = 0,

    // ABC keys
    Key_A = 4,
    Key_B = 5,
    Key_C = 6,
    Key_D = 7,
    Key_E = 8,
    Key_F = 9,
    Key_G = 10,
    Key_H = 11,
    Key_I = 12,
    Key_J = 13,
    Key_K = 14,
    Key_L = 15,
    Key_M = 16,
    Key_N = 17,
    Key_O = 18,
    Key_P = 19,
    Key_Q = 20,
    Key_R = 21,
    Key_S = 22,
    Key_T = 23,
    Key_U = 24,
    Key_V = 25,
    Key_W = 26,
    Key_X = 27,
    Key_Y = 28,
    Key_Z = 29,

    // Number keys
    Key_1 = 30,
    Key_2 = 31,
    Key_3 = 32,
    Key_4 = 33,
    Key_5 = 34,
    Key_6 = 35,
    Key_7 = 36,
    Key_8 = 37,
    Key_9 = 38,
    Key_0 = 39,

    // Special keys
    Key_Enter = 40,
    Key_Escape = 41,
    Key_Backspace = 42,
    Key_Tab = 43,
    Key_Space = 44,

    Key_Minus = 45,
    Key_Equals = 46,
    Key_LeftBracket = 47,
    Key_RightBracket = 48,
    Key_Backslash = 49,
    Key_NONUSHASH = 50,
    Key_Semicolon = 51,
    Key_Apostrophe = 52,
    Key_Grave = 53,
    Key_Comma = 54,
    Key_Period = 55,
    Key_Slash = 56,

    Key_CapsLock = 57,

    // Function keys
    Key_F1 = 58,
    Key_F2 = 59,
    Key_F3 = 60,
    Key_F4 = 61,
    Key_F5 = 62,
    Key_F6 = 63,
    Key_F7 = 64,
    Key_F8 = 65,
    Key_F9 = 66,
    Key_F10 = 67,
    Key_F11 = 68,
    Key_F12 = 69,

    
    Key_PrintScreen = 70,
    Key_ScrollLock = 71,
    Key_Pause = 72,
    Key_Insert = 73,
    Key_Home = 74,
    Key_PageUp = 75,
    Key_Delete = 76,
    Key_End = 77,
    Key_PageDown = 78,
    Key_Right = 79,
    Key_Left = 80,
    Key_Down = 81,
    Key_Up = 82,

    Key_NUMLOCKCLEAR = 83,
    Key_NumDivide = 84,
    Key_NumMultiply = 85,
    Key_NumMinus = 86,
    Key_NumPlus = 87,
    Key_NumEnter = 88,
    Key_Num1 = 89,
    Key_Num2 = 90,
    Key_Num3 = 91,
    Key_Num4 = 92,
    Key_Num5 = 93,
    Key_Num6 = 94,
    Key_Num7 = 95,
    Key_Num8 = 96,
    Key_Num9 = 97,
    Key_Num0 = 98,
    Key_KP_PERIOD = 99,

    Key_LControl = 224,
    Key_LShift = 225,
    Key_LAlt = 226,
    Key_LGui = 227,
    Key_RControl = 228,
    Key_RShift = 229,
    Key_RAlt = 230,
    Key_RGui = 231,

    // Mouse buttons
    Mouse_LeftButton,
    Mouse_RightButton,
    Mouse_MiddleButton,

    // Controller buttons
    Controller_A,
    Controller_B,
    Controller_X,
    Controller_Y,
    Controller_LeftBumper,
    Controller_RightBumper,
    Controller_Back,
    Controller_Start,
    Controller_LeftStick_Down,
    Controller_RightStick_Down,
    Controller_DPad_Up,
    Controller_DPad_Down,
    Controller_DPad_Left,
    Controller_DPad_Right,

    Key_NumberOfKeys = 512
};

/**
 * @enum DefAction
 * @brief Enumeration for default actions.
 */
enum class DefAction {
    Move_Up,    ///< Move up action.
    Move_Left,  ///< Move left action.
    Move_Down,  ///< Move down action.
    Move_Right, ///< Move right action.

    Undefined   ///< Undefined action.
};

std::string keyToString(Key key);

int stringToKeyID(std::string aKeyString);

std::string actionToString(DefAction action);

int stringToActionID(std::string aKeyString);

#endif // INPUTSTRUCTS_H