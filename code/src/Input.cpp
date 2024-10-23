#include "Input.h"

/**
 * @brief Updates the previous key states with the current key states.
 */
void Input::updatePreviousKeys() {
    mPreviousKeys.resize(mNumKeys);
    for (int i = 0; i < mNumKeys; i++) {
        mPreviousKeys[i] = mCurrentKeys[i];
    }
}

/**
 * @brief Updates the current key states using SDL.
 */
void Input::updateCurrentKeys() {
    mCurrentKeys = SDL_GetKeyboardState(&mNumKeys);
}

/**
 * @brief Updates the list of keys that were pressed down this frame.
 */
void Input::updateDownKeys() {
    mDownKeys.resize(0);
    for (int i = 0; i < mPreviousKeys.size(); i++) {
        if (mCurrentKeys[i] == 1 && mPreviousKeys[i] == 0) {
            mDownKeys.push_back(i);
        }
    }
}

/**
 * @brief Updates the list of keys that were released this frame.
 */
void Input::updateUpKeys() {
    mUpKeys.resize(0);
    for (int i = 0; i < mPreviousKeys.size(); i++) {
        if (mCurrentKeys[i] == 0 && mPreviousKeys[i] == 1) {
            mUpKeys.push_back(i);
        }
    }
}

/**
 * @brief Updates the list of keys that are currently held down.
 */
void Input::updateHeldKeys() {
    mHeldKeys.resize(0);
    for (int i = 0; i < mNumKeys; i++) {
        if (mCurrentKeys[i]) {
            mHeldKeys.push_back(i);
        }
    }
}

/**
 * @brief Updates the mouse state.
 */
void Input::updateMouse() {
    mPreviousMouse = mCurrentMouse;
    mCurrentMouse = Mouse();

    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    mCurrentMouse.position.x = mouseX;
    mCurrentMouse.position.y = mouseY;

    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        mCurrentMouse.left = true;
    }

    if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        mCurrentMouse.right = true;
    }

    if (mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
        mCurrentMouse.middle = true;
    }
}

/**
 * @brief Constructs the Input object and initializes key states.
 */
Input::Input() {
    this->updateCurrentKeys();
    this->updatePreviousKeys();
}

/**
 * @brief Gets the singleton instance of the Input class.
 * @return Reference to the singleton instance.
 */
Input& Input::getInstance() {
    static Input instance;
    return instance;
}

/**
 * @brief Prints the current and previous key states to the console.
 */
void Input::print() {
    static long printID = 0;

    for (int i = 0; i < mNumKeys; i++) {
        if (mCurrentKeys[i] == 1) {
            std::cout << printID << ": mCurrentKeys[" << i << "] == " << keyToString((Key)i) << std::endl;
        }
    }

    for (int i = 0; i < mPreviousKeys.size(); i++) {
        if (mPreviousKeys[i] == 1) {
            std::cout << printID << ": mPrevousKeys[" << i << "] == " << keyToString((Key)i) << std::endl;
        }
    }

    printID++;
}

/**
 * @brief Updates all input states.
 */
void Input::update() {
    this->updateCurrentKeys();
    this->updateUpKeys();
    this->updateDownKeys();
    this->updateHeldKeys();
    this->updateMouse();
    this->updatePreviousKeys();
}

/**
 * @brief Gets the list of currently held keys.
 * @return Reference to the vector of held keys.
 */
std::vector<Uint8>& Input::getHeldKeys() {
    return mHeldKeys;
}

/**
 * @brief Gets the list of keys that were pressed down this frame.
 * @return Reference to the vector of down keys.
 */
std::vector<Uint8>& Input::getDownKeys() {
    return mDownKeys;
}

/**
 * @brief Gets the list of keys that were released this frame.
 * @return Reference to the vector of up keys.
 */
std::vector<Uint8>& Input::getUpKeys() {
    return mUpKeys;
}

/**
 * @brief Checks if any key is currently held down.
 * @return True if any key is held down, false otherwise.
 */
bool Input::AnyKey() {
    return !mHeldKeys.empty();
}

/**
 * @brief Checks if any key was pressed down this frame.
 * @return True if any key was pressed down, false otherwise.
 */
bool Input::AnyKeyDown() {
    return !mDownKeys.empty();
}

/**
 * @brief Gets the current mouse position.
 * @return The current mouse position as a Point.
 */
Point Input::MousePosition() {
    return mCurrentMouse.position;
}

/**
 * @brief Gets the axis value (implementation needed).
 * @return The axis value.
 */
double Input::GetAxis() {
    // Implementation needed
    return 0.0;
}

/**
 * @brief Checks if a specific key is currently held down.
 * @param key The key to check.
 * @return True if the key is held down, false otherwise.
 */
bool Input::GetKey(Key key) {
    for (const auto& heldKey : mHeldKeys) {
        if (heldKey == (Uint8)key) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Checks if a specific key was pressed down this frame.
 * @param key The key to check.
 * @return True if the key was pressed down, false otherwise.
 */
bool Input::GetKeyDown(Key key) {
    for (int i = 0; i < mDownKeys.size(); i++) {
        if (mDownKeys[i] == (int)key) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Checks if a specific key was released this frame.
 * @param key The key to check.
 * @return True if the key was released, false otherwise.
 */
bool Input::GetKeyUp(Key key) {
    for (const auto& upKey : mUpKeys) {
        if (upKey == (Uint8)key) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Checks if a specific mouse button is currently held down.
 * @param which The mouse button to check.
 * @return True if the mouse button is held down, false otherwise.
 */
bool Input::GetMouseButton(MouseButton which) {
    switch (which) {
    case MouseButton::LEFT:
        return mCurrentMouse.left;
    case MouseButton::MIDDLE:
        return mCurrentMouse.middle;
    case MouseButton::RIGHT:
        return mCurrentMouse.right;
    default:
        return false;
    }
}

/**
 * @brief Checks if a specific mouse button was pressed down this frame.
 * @param which The mouse button to check.
 * @return True if the mouse button was pressed down, false otherwise.
 */
bool Input::GetMouseButtonDown(MouseButton which) {
    switch (which) {
    case MouseButton::LEFT:
        return mPreviousMouse.left == 0 && mCurrentMouse.left == 1;
    case MouseButton::MIDDLE:
        return mPreviousMouse.middle == 0 && mCurrentMouse.middle == 1;
    case MouseButton::RIGHT:
        return mPreviousMouse.right == 0 && mCurrentMouse.right == 1;
    default:
        return false;
    }
}

/**
 * @brief Checks if a specific mouse button was released this frame.
 * @param which The mouse button to check.
 * @return True if the mouse button was released, false otherwise.
 */
bool Input::GetMouseButtonUp(MouseButton which) {
    switch (which) {
    case MouseButton::LEFT:
        return mPreviousMouse.left == 1 && mCurrentMouse.left == 0;
    case MouseButton::MIDDLE:
        return mPreviousMouse.middle == 1 && mCurrentMouse.middle == 0;
    case MouseButton::RIGHT:
        return mPreviousMouse.right == 1 && mCurrentMouse.right == 0;
    default:
        return false;
    }
}