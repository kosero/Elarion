//
// Created by kosero on 15.07.2025.
//

#ifndef INPUT_MAP_HXX
#define INPUT_MAP_HXX

#include <raylib.h>

inline bool UI_LEFT() { return IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT); }
inline bool UI_RIGHT() { return IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT); }
inline bool UI_UP() { return IsKeyDown(KEY_W) || IsKeyDown(KEY_UP); }
inline bool UI_DOWN() { return IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN); }

#endif //INPUT_MAP_HXX
