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


  Print(L"Hello UEFI!\n");
  while(1){
    asm("hlt");
  }
}
