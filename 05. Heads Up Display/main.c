#include <gb/gb.h>
#include <gbdk/font.h>
#include <stdio.h>
#include "background.c"
#include "backgroundmap.c"
#include "windowmap.c"

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
    font_t min_font;

    font_init();
    min_font = font_load(font_min);
    font_set(min_font);

    set_bkg_data(37, 7, backgroundtiles);
    set_bkg_tiles(0, 0, 40, 18, backgroundmap);

    set_win_tiles(0, 0, 5, 1, windowmap);
    move_win(7, 120);

    SHOW_BKG;
    SHOW_WIN;
    DISPLAY_ON;

    while (1)
    {
        scroll_bkg(1, 0);
        pdelay(3);
    }
}