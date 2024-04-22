#include <gb/gb.h>
#include <stdio.h>
#include "entity.c"
#include "Sprites.c"

entity_t ship;
entity_t bug;

void entity_move(entity_t *entity)
{
    uint8_t spritesz = 8; // 8 by 8 pixels
    move_sprite(entity->spriteIds[0], entity->x, entity->y);
    move_sprite(entity->spriteIds[1], entity->x + spritesz, entity->y);
    move_sprite(entity->spriteIds[2], entity->x, entity->y + spritesz);
    move_sprite(entity->spriteIds[3], entity->x + spritesz, entity->y + spritesz);
}

void ship_init(entity_t *ship)
{
    ship->x = 80;
    ship->y = 130;
    ship->width = 16;
    ship->height = 16;

    // load sprites
    set_sprite_tile(0, 0);
    ship->spriteIds[0] = 0;
    set_sprite_tile(1, 1);
    ship->spriteIds[1] = 1;
    set_sprite_tile(2, 2);
    ship->spriteIds[2] = 2;
    set_sprite_tile(3, 3);
    ship->spriteIds[3] = 3;

    entity_move(ship);
}

void bug_init(entity_t *bug)
{
    bug->x = 30;
    bug->y = 0;
    bug->width = 16;
    bug->height = 16;

    // load sprites
    set_sprite_tile(4, 4);
    bug->spriteIds[0] = 4;
    set_sprite_tile(5, 5);
    bug->spriteIds[1] = 5;
    set_sprite_tile(6, 6);
    bug->spriteIds[2] = 6;
    set_sprite_tile(7, 7);
    bug->spriteIds[3] = 7;

    entity_move(bug);
}

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
    set_sprite_data(0, 8, Sprites);

    ship_init(&ship);
    bug_init(&bug);

    SHOW_SPRITES;
    DISPLAY_ON;

    while (1)
    {
        if (joypad() & J_LEFT)
        {
            ship.x -= 2;
        }
        if (joypad() & J_RIGHT)
        {
            ship.x += 2;
        }

        bug.y += 5;

        if (bug.y > 144 + bug.height)
        {
            bug.y = 0;
            bug.x = ship.x;
        }

        entity_move(&ship);
        entity_move(&bug);

        pdelay(3);
    }
}