#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>
//#include  <Protocol/BlockIo.h>
//#include  <Protocol/LoadedImage.h>
//#include  <Protocol/SimpleFileSystem.h>
//#include  <Library/DevicePathLib.h>
//#include  <Guid/FileInfo.h>
//#include  <Guid/Acpi.h>
//#include  <Library/MemoryAllocationLib.h>
//#include  <Library/BaseMemoryLib.h>

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
  GetGraphicMode(ImageHandle,&(boot_param.graphic_config));

  typedef unsigned long (EntryPoint)(struct BootParam*);
  EntryPoint *Entry = (EntryPoint*)(KernelBaseAddr);

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
