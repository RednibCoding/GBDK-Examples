#include <gb/gb.h>
#include <stdio.h>

// Press F5 to compile and run the compiled game.gb in the Emulicous Emulator/Debugger
void main(void)
{
    printf("Press any button to play the sound...");

    // These registers must be in this specific order
    NR52_REG = 0x80; // Turns on sound
    NR50_REG = 0x77; // sets the valume for both: left and right channel just set to max 0x77
    NR51_REG = 0xFF; // select which channels we want to use in this case all of them.

    while (1)
    {
        UBYTE joypad_state = joypad();

        if (joypad_state)
        {
            // 5-0 sound length
            NR41_REG = 0b00011111; // maximum length

            // volume envelope
            // 7-4 initial volume of envelope (0: no sound)
            // 3 envelope direction (0: decrease, 1: increase)
            // 2-0 number of envelope sweep (n:0-7) (0: stop envelope operation)
            NR42_REG = 0b11110001; // start at full volume, fade down, 1 envelope sweep

            // 7-4 shift clock frequencs (s)
            // 3 counter step/width (0: 15 bits, 1: 7 bits)
            // 2-0 dividing ration of frequencies (r)
            NR43_REG = 0b00110000; // shift clock frequency 3, step 0, dividing ratio 0

            // 7 initial (1: restart sound)
            // 6 controls if last forever or stops when NR41 ends
            // (1: step output when length in NR41 expires)
            // 5-0 unused
            NR44_REG = 0b11110000; // start sound , not continuous

            delay(300);
        }
    }
}