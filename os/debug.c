#include "debug.h"
#include "console.h"
#include "asm.h"

#include "structs.h"

void debug_info_graphic(struct GraphicConfig *g_conf){
    console_puts_str("[Graphic] FrameBase:0x");
    console_puts_hex(g_conf->frame_base);
    console_puts_str("\n[Graphic] FrameSize:");
    console_puts_dec(g_conf->frame_size);
    console_puts_str("\n[Graphic] H_Reso:");
    console_puts_dec(g_conf->horizontal_resolution);
    console_puts_str("\n[Graphic] V_Reso:");
    console_puts_dec(g_conf->vertical_resolution);
    console_puts_str("\n[Graphic] PixelsPerScanLine:");
    console_puts_dec(g_conf->pixels_per_scan_line);
    console_puts_str("\n");
}

const static char* cpuid_feat_ecx[29] = {"SSE3", "PCLMUL", "DTES64", "MONITOR", "DS_CPL", "VMX", "SMX", "EST", "TM2",
    "SSE3", "CID", "",
    "FMA", "CX16", "ETPRD", "PDCM", "", "PCIDE", "DCA", "SSE4_1", "SSE4_2", "x2APIC", "MOVBE", "POPCNT", "", "AES", "XSAVE",
    "OSXSAVE", "AVX"};

const static char* cpuid_feat_edx[32] = {"FPU", "VMW", "DE", "PSE", "TSC", "MSR", "PAE", "MCE", "CX8", "APIC", "", "SEP",
    "MTRR", "PGE", "MCA", "CMOV", "PAT", "PSE36", "PSN", "CLF", "", "DTES", "ACPI", "MMX", "FXSR", "SSE", "SSE2", "SS",
    "HTT", "TM1", "IA64", "PBE"};
void debug_info_cpuid(){
    struct cpuid_reg cpuid;
    uint8_t cpuid_str[14];

    //EAX = 0 (Get CPU Vendor)
    cpuid_read(&cpuid, 0);
    cpuid_str[0] = cpuid.ebx >> 0;
    cpuid_str[1] = cpuid.ebx >> 8;
    cpuid_str[2] = cpuid.ebx >> 16;
    cpuid_str[3] = cpuid.ebx >> 24;
    cpuid_str[4] = cpuid.edx >> 0;
    cpuid_str[5] = cpuid.edx >> 8;
    cpuid_str[6] = cpuid.edx >> 16;
    cpuid_str[7] = cpuid.edx >> 24;
    cpuid_str[8] = cpuid.ecx >> 0;
    cpuid_str[9] = cpuid.ecx >> 8;
    cpuid_str[10] = cpuid.ecx >> 16;
    cpuid_str[11] = cpuid.ecx >> 24;
    cpuid_str[12] = '\n';
    cpuid_str[13] = 0;
    console_puts_str("\n[CPUID] CPU Vendor:");
    console_puts_str((char *)cpuid_str);

    //EAX = 1
    cpuid_read(&cpuid, 1);
    console_puts_str("[CPUID] CPU Features:");
    for(int i=0;i<29;i++){
        if(cpuid.ecx & (1 << i)){
            console_puts_str(cpuid_feat_ecx[i]);
            console_puts_str(" ");
        }
    }
    for(int i=0;i<32;i++){
        if(cpuid.edx & (1 << i)){
            console_puts_str(cpuid_feat_edx[i]);
            console_puts_str(" ");
        }
    }
}

void debug_info_bootparam(struct BootParam *boot_param){
    console_puts_str("[Boot] Kernel Address:");
    console_puts_hex(boot_param->kernel_addr);
    console_puts_str("\n[Boot] Kernel Entry Address:");
    console_puts_hex(boot_param->kernel_entry);
    console_puts_str("\n[Boot] RSDP Address:");
    console_puts_hex(boot_param->rsdp_addr);
    console_puts_str("\n");
}
