#ifndef __PLAYER_H
#define __PLAYER_H

#include "stm32f1xx_hal.h"
#include "note.h"

typedef struct
{
    const char *name;
    const Note *notes;
    uint16_t length;
    uint16_t bpm;
} Melody;

extern Melody song1;
extern Melody song2;
extern Melody song3;

void melody(TIM_HandleTypeDef *htim, uint32_t Channel, uint16_t length, uint16_t bpm, const Note *song);

#endif