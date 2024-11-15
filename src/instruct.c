#include "instruct.h"

void ld_8bits(uint8_t *regist, uint16_t value)
{
    *regist = value;
}

void ld_r1_r2_8bits(uint8_t *r1, uint8_t r2)
{
    *r1 = r2;
}

void ld_r1_r2_16bits(uint16_t *r1, uint16_t r2)
{
    *r1 = r2;
}
