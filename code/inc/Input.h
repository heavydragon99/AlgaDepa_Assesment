#ifndef INPUT_H
#define INPUT_H

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <SDL.h>

#include "InputStructs.h"
#include "Structs.h"

/**
 * @class Input
 * @brief Manages input states including keyboard and mouse inputs.
 */
class Input {
public:
    /**
     * @brief Gets the singleton instance of the Input class.
     * @return Reference to the singleton instance.
     */
    static Input& getInstance();

    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

    void print();
    void update();

    std::vector<Uint8>& getHeldKeys();
    std::vector<Uint8>& getDownKeys();
    std::vector<Uint8>& getUpKeys();

    bool AnyKey();
    bool AnyKeyDown();
    Point MousePosition();
    double GetAxis();
    bool GetKey(Key key);
    bool GetKeyDown(Key key);
    bool GetKeyUp(Key key);
    bool GetMouseButton(MouseButton which);
    bool GetMouseButtonDown(MouseButton which);
    bool GetMouseButtonUp(MouseButton which);

private:
    void updatePreviousKeys();
    void updateCurrentKeys();
    void updateDownKeys();
    void updateUpKeys();
    void updateHeldKeys();
    void updateMouse();

    /**
     * @brief Constructs the Input object and initializes key states.
     */
    Input();

private:
    Mouse mCurrentMouse;  ///< Current mouse state.
    Mouse mPreviousMouse; ///< Previous mouse state.

    const Uint8* mCurrentKeys = nullptr; ///< Current keyboard state.
    int mNumKeys = 0;                    ///< Number of keys.

    std::vector<Uint8> mPreviousKeys; ///< Previous keyboard state.
    std::vector<Uint8> mDownKeys;     ///< Keys pressed down this frame.
    std::vector<Uint8> mUpKeys;       ///< Keys released this frame.
    std::vector<Uint8> mHeldKeys;     ///< Keys currently held down.
};

#endif // INPUT_H