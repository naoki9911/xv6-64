#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>

#include "file_loader.h"
#include "relocate.h"
#include "graphic.h"
#include "structs.h"

EFI_STATUS
    EFIAPI
UefiMain (
        IN EFI_HANDLE ImageHandle,
        IN EFI_SYSTEM_TABLE *SystemTable
        )
{
    EFI_STATUS Status;
    CHAR16 *KernelFileName = L"\\kernel";
    EFI_PHYSICAL_ADDRESS KernelBaseAddr;

    RelocateELF(KernelFileName, &KernelBaseAddr);


    struct BootParam boot_param;
    boot_param.kernel_addr = KernelBaseAddr;
    boot_param.kernel_entry = KernelBaseAddr;
    GetGraphicMode(ImageHandle,&(boot_param.graphic_config));



    typedef unsigned long (EntryPoint)(struct BootParam*);
    EntryPoint *Entry = (EntryPoint*)(KernelBaseAddr);
    VOID *vendor_table;

    EfiGetSystemConfigurationTable(&gEfiAcpiTableGuid,&vendor_table);
    boot_param.rsdp_addr = (UINT64)vendor_table;

    struct MemoryMap MemoryMap = {4096,NULL,4096,0,0,0};
    Status = gBS->AllocatePool(EfiLoaderData, MemoryMap.BufferSize, &MemoryMap.Buffer);
    if(EFI_ERROR(Status)){
        Print(L"Failed to allocate memory to get memory map\n");
        return Status;
    }

    gBS->GetMemoryMap(
            &MemoryMap.MapSize,
            (EFI_MEMORY_DESCRIPTOR*)MemoryMap.Buffer,
            &MemoryMap.MapKey,
            &MemoryMap.DescriptorSize,
            &MemoryMap.DescriptorVersion);

    Status = gBS->ExitBootServices(ImageHandle, MemoryMap.MapKey);
    if(EFI_ERROR(Status)){
        Print(L"Failed to exit boot services\n");
        return Status;
    }

    Entry(&boot_param);

    return Status;
}
