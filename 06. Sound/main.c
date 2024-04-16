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
            // channel 1 register 0: frequency sweep settings
            // 7 Unused
            // 6-4 Sweep time (0: sweeping off)
            // 3 sweep direction (1: decrease, 0: increase)
            // 2-0 sweep trshift amount (0: sweeping off)
            NR10_REG = 0b00010110; // sweep time 1, sweep direction increase, shift amount per step 110

            // channel 1 register 1: wave pattern duty and lenght
            // 7-6 wave pattern duty cycle 0-3
            // 5-0 sound length (higher the number shorter the sound)
            NR11_REG = 01000000; // duty cycle 1 (25%), wave lenght 0 (long)

            // channel 1 register 2: vlume envelope (makes the colume get louder or quiter each "tick")
            // 7-4 (initial) channel volume
            // 3 volume sweep direction (0: down, 1: up)
            // 2-0 length of each step in sweep (0: sweeping off)
            // Note: each step is n/64 seconds long, where n is 1-7
            NR12_REG = 0b01110011; // volume 7, sweep down, step length 3

            // channel 1 register 3: frequency LSbs (least significant bits) and noise options
            // 7-0 0 least significant bits of frequency (3 most significant bits are set in register 4)
            NR13_REG = 0b00000000;

            // channel 1 register 4: playback and frequency MSbs
            // 7 initialize (trigger channel start, aka channel init) (write only)
            // 6 consecutive select/length counter enable (read/write).
            // 5-3 unused
            // 2-0 3 most significant bits of frequency
            NR14_REG = 0b11000011; // initialize, no consecutive, frequency == MSB + LSB = 011 0000 0000

            delay(300);
        }
    }
}