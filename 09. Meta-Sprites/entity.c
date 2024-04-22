#include <gb/gb.h>

typedef struct
{
    uint8_t spriteIds[4]; // all characters use 4 sprites
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
} entity_t;