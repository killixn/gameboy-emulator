#ifndef INSTRUCT_H
#define INSTRUCT_H

#include <stdint.h>

void ld(uint8_t *r, uint16_t value);
void ld_r1_r2(void *r1, uint8_t size, uint8_t r2);

void swap(void *r, uint8_t size, uint8_t *flags);
void dda(uint8_t *a, uint8_t *flags);
void cpl(uint8_t *a, uint8_t *flags);
void ccf(uint8_t *flags);
void scf(uint8_t *flags);
void nop(void);
void halt(void);
void stop(void);
void di(void);
void ei(void);

void rlc(void *n, uint8_t size, uint8_t *flags);
void rl(void *n, uint8_t size, uint8_t *flags);
void rrc(void *n, uint8_t size, uint8_t *flags);
void rr(void *n, uint8_t size, uint8_t *flags);

void sla(void *n, uint8_t size, uint8_t *flags);
void sra(void *n, uint8_t size, uint8_t *flags);
void srl(void *n, uint8_t size, uint8_t *flags);

void bit(uint8_t b, void *r, uint8_t size, uint8_t *flags);
void set(uint8_t b, void *r, uint8_t size);
void res(uint8_t b, void *r, uint8_t size);

void jp_hl(uint16_t *pc, uint16_t *hl);

#endif /* !INSTRUCT_H */
