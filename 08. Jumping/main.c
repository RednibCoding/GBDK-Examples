#include <gb/gb.h>
#include <stdio.h>

int8_t playerpos[2];
int8_t gravity = 2;
int8_t jumpForce = 10;
uint8_t floorYPos = 100;

unsigned char bloke[] =
    {
        0x00, 0x00, 0x38, 0x38, 0x7C, 0x44, 0x7F, 0x7F,
        0x44, 0x74, 0x46, 0x7C, 0x40, 0x78, 0x24, 0x3C,
        0x18, 0x3C, 0x00, 0x24, 0x00, 0x24, 0x00, 0x24,
        0x00, 0x24, 0x00, 0x36, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x38, 0x38, 0x7C, 0x44, 0x7F, 0x7F,
        0x44, 0x74, 0x46, 0x7C, 0x40, 0x78, 0x24, 0x3C,
        0x18, 0x3C, 0x00, 0x22, 0x00, 0x22, 0x00, 0x22,
        0x00, 0x23, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x38, 0x38, 0x7C, 0x44, 0x7F, 0x7F,
        0x44, 0x74, 0x46, 0x7C, 0x40, 0x78, 0x24, 0x3C,
        0x18, 0x3C, 0x00, 0x42, 0x00, 0x42, 0x00, 0x42,
        0x00, 0x42, 0x00, 0x63, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x38, 0x38, 0x7C, 0x44, 0x7F, 0x7F,
        0x44, 0x74, 0x46, 0x7C, 0x40, 0x78, 0x24, 0x3C,
        0x18, 0x3C, 0x00, 0x44, 0x00, 0x44, 0x00, 0x44,
        0x00, 0x64, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00};

void pdelay(uint8_t numVbls)
{
    uint8_t i;
    for (i = 0; i < numVbls; i++)
    {
        vsync();
    }
}

uint8_t jump_sprite(uint8_t spriteId, uint8_t spritePosX, uint8_t *spritePosY, uint8_t floorPosY, int8_t jumpForce, int8_t gravity)
{
    static int8_t curSpeedY = 0;
    static uint8_t isJumping = 0;

    int8_t possibleSurfaceY;

    if (isJumping == 0)
    {
        isJumping = 1;
        curSpeedY = jumpForce;
    }

    if (isJumping == 1)
    {

        curSpeedY -= gravity;
        (*spritePosY) = (*spritePosY) - curSpeedY;

        // Check if on ground/floor
        if ((*spritePosY) >= floorPosY)
        {
            possibleSurfaceY = floorPosY;
        }
        else
        {
            possibleSurfaceY = -1;
        }

        if (possibleSurfaceY > -1)
        {
            isJumping = 0;
            move_sprite(spriteId, spritePosX, possibleSurfaceY);
        }
        else
        {
            move_sprite(spriteId, spritePosX, (*spritePosY));
        }
    }

    return isJumping;
}

// Press F5 to compile and run the compiled game.gb in the Emulicous Emulator/Debugger
void main(void)
{
    uint8_t isJumping = 0;

    set_sprite_data(0, 8, bloke);
    set_sprite_tile(0, 0);

    playerpos[0] = 10;
    playerpos[1] = floorYPos;

    move_sprite(0, playerpos[0], playerpos[1]);

    DISPLAY_ON;
    SHOW_SPRITES;

    while (1)
    {
        if (joypad() & J_A || isJumping)
        {
            isJumping = jump_sprite(0, playerpos[0], &playerpos[1], floorYPos, jumpForce, gravity);
        }
        if (joypad() & J_LEFT)
        {
            playerpos[0] -= 2;
        }
        if (joypad() & J_RIGHT)
        {
            playerpos[0] += 2;
        }

        move_sprite(0, playerpos[0], playerpos[1]);

        pdelay(3);
    }
}