.intel_syntax noprefix

.global cpuid_read
cpuid_read:
        mov r9, rdi
        mov eax, esi
        cpuid
        mov [r9], eax
        mov [r9 + 4], ebx
        mov [r9 + 8], ecx
        mov [r9 + 12], edx
        ret
