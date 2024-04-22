#include <gb/gb.h>
#include <stdio.h>
#include "background.c"
#include "backgroundmap.c"

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
    set_bkg_data(0, 7, backgroundtiles);
    set_bkg_tiles(0, 0, 40, 18, backgroundmap);

    SHOW_BKG;
    DISPLAY_ON;

    while (1)
    {
        scroll_bkg(1, 0);
        pdelay(3);
    }
}