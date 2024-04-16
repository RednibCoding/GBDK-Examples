#include <gb/gb.h>
#include <stdio.h>
#include "Smily.c"

// Press F5 to compile and run the compiled game.gb in the Emulicous Emulator/Debugger
void main(void)
{
    uint8_t currentSpriteIndex = 0;

    set_sprite_data(0, 2, Smily);
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);

    SHOW_SPRITES;

    while (1)
    {
        currentSpriteIndex = 1 - currentSpriteIndex;
        set_sprite_tile(0, currentSpriteIndex);
        delay(500);
        scroll_sprite(0, 10, 0);
    }
}