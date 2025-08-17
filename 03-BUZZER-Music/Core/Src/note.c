#include "stm32f1xx_hal.h"
#include "note.h"

uint16_t get_freq(uint8_t note)
{
    const uint16_t midiFreqs[128] = {
        /* 0-11  C-1 到 B-1 */
        8, 9, 9, 10, 10, 11, 12, 12, 13, 14, 15, 15,

        /* 12-23 C0 到 B0 */
        16, 17, 18, 19, 21, 22, 23, 24, 26, 28, 29, 31,

        /* 24-35 C1 到 B1 */
        33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62,

        /* 36-47 C2 到 B2 */
        65, 69, 73, 78, 82, 87, 92, 98, 104, 110, 117, 123,

        /* 48-59 C3 到 B3 */
        131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247,

        /* 60-71 C4 到 B4 (中央C八度) */
        262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,

        /* 72-83 C5 到 B5 */
        523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,

        /* 84-95 C6 到 B6 */
        1046, 1109, 1175, 1245, 1318, 1397, 1480, 1568, 1661, 1760, 1865, 1976,

        /* 96-107 C7 到 B7 */
        2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951,

        /* 108-119 C8 到 B8 */
        4186, 4435, 4699, 4978, 5274, 5588, 5920, 6272, 6645, 7040, 7459, 7902,

        /* 120-127 C9 到 G9 */
        8372, 8870, 9397, 9956, 10548, 11175, 11840, 12544};

    return midiFreqs[note + 12];
}

// 时值
uint32_t duration(uint8_t bpm, Note note)
{
    uint16_t beat_ms = 60000 / bpm;
    uint32_t duration_ms = (beat_ms * 4) / note.beat;

    // 附点音符处理
    if (note.dotted)
    {
        duration_ms += duration_ms / 2; // 增加一半时长
    }
    return duration_ms;
}

// 播放单个音符
void note(TIM_HandleTypeDef *htim, uint32_t Channel, uint16_t bpm, const Note note)
{
    HAL_TIM_PWM_Start(htim, Channel); // 开启PWM,arr(100 - 1),psc(720 - 1)
    if (note.midi == 128)
    {
        __HAL_TIM_SET_COMPARE(htim, Channel, 0);
        HAL_Delay(duration(bpm, note) - 10);
    }
    else
    {
        uint32_t psc = 720000 / get_freq(note.midi);
        __HAL_TIM_SET_PRESCALER(htim, psc); // 设置prescaler预分频值
        __HAL_TIM_SET_COMPARE(htim, Channel, 30);
        HAL_Delay(duration(bpm, note));
    }
}