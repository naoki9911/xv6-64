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
  CHAR16 *KernelFileName = L"\\kernel";
  EFI_PHYSICAL_ADDRESS KernelBaseAddr;

  RelocateELF(KernelFileName, &KernelBaseAddr);


  struct BootParam boot_param;
  GetGraphicMode(ImageHandle,&(boot_param.graphic_config));

  typedef unsigned long (EntryPoint)(struct BootParam*);
  EntryPoint *Entry = (EntryPoint*)(KernelBaseAddr);
  Entry(&boot_param);
  Print(L"Hello UEFI!\n");
  while(1){
    asm("hlt");
  }
}
