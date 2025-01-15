#include "raylib.h"

typedef struct Door {
    Rectangle hitbox;
    bool isPlayerOnTop;
} Door;
