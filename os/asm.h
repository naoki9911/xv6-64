#ifndef ASM_H
#define ASM_H
#include "stdint.h"
__attribute__((packed)) struct cpuid_reg {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
};

void cpuid_read(struct cpuid_reg *cpuid, uint32_t eax);

#endif

