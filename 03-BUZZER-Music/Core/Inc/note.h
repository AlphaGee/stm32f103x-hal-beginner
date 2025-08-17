#ifndef __H
#define __H

#include "stm32f1xx_hal.h"

typedef struct
{
    uint16_t midi;      // 音高
    uint8_t beat;       // 时值比例 1 2 4 8 16
    uint8_t dotted : 1; // 附点标志 (位域)
} Note;

uint16_t get_freq(uint8_t note);

uint32_t duration(uint8_t bpm, Note note);

void note(TIM_HandleTypeDef *htim, uint32_t Channel, uint16_t bpm, const Note note);

#endif