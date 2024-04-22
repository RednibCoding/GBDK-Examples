#include <gb/gb.h>
#include <stdio.h>
#include "Smily.c"

void pdelay(uint8_t numVbls)
{
    uint8_t i;
    for (i = 0; i < numVbls; i++)
    {
        vsync();
    }
}

// Press F5 to compile and run the compiled game.gb in the Emulicous Emulator/Debugger
void main(void)
{
    uint8_t currentSpriteIndex = 0;
    uint8_t buttons = 0;

    set_sprite_data(0, 2, Smily);
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);

    SHOW_SPRITES;

    while (1)
    {
        currentSpriteIndex = 1 - currentSpriteIndex;
        set_sprite_tile(0, currentSpriteIndex);

        buttons = joypad();

        if (buttons & J_LEFT)
        {
            scroll_sprite(0, -2, 0);
        }
        if (buttons & J_RIGHT)
        {
            scroll_sprite(0, 2, 0);
        }
        if (buttons & J_UP)
        {
            scroll_sprite(0, 0, -2);
        }
        if (buttons & J_DOWN)
        {
            scroll_sprite(0, 0, 2);
        }

        pdelay(3);
    }
}