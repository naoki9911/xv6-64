#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Protocol/GraphicsOutput.h>
#include  <Uefi.h>
#include  <Protocol/BlockIo.h>
#include  <Protocol/LoadedImage.h>
#include  <Protocol/SimpleFileSystem.h>
#include  <Library/DevicePathLib.h>
#include  <Guid/FileInfo.h>
#include  <Library/BaseMemoryLib.h>
#include "graphic.h"
#include "structs.h"

EFI_STATUS GetGraphicMode(
    IN EFI_HANDLE ImageHandle,
    OUT struct GraphicConfig *graphic_config
    )
{
  EFI_STATUS Status;
  UINTN NumGopHandles = 0;
  EFI_HANDLE *GopHandles = NULL;
  EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;

  Status = gBS->LocateHandleBuffer(
      ByProtocol,
      &gEfiGraphicsOutputProtocolGuid,
      NULL,
      &NumGopHandles,
      &GopHandles);
  if(EFI_ERROR(Status)){
    Print(L"Failed to get LocateHandleBuffer\n");
    return Status;
  }

  Status = gBS->OpenProtocol(
      GopHandles[0],
      &gEfiGraphicsOutputProtocolGuid,
      (VOID **)&Gop,
      ImageHandle,
      NULL,
      EFI_OPEN_PROTOCOL_GET_PROTOCOL);
  if(EFI_ERROR(Status)){
    Print(L"Failed to Open GOP\n");
    return Status;
  }

  FreePool(GopHandles);


//  UINT32 GraphicModeInfoIndex = 0;
  //UINT64 Resolution = 0;
  UINTN SizeOfInfo;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *GraphicModeInfo;

  for(UINT32 i=0; i<Gop->Mode->MaxMode; i++){
    Status = Gop->QueryMode(Gop, i, &SizeOfInfo, &GraphicModeInfo);
    if(EFI_ERROR(Status)){
      Print(L"Failed to get QueryMode\n");
      return Status;
    }

    //UITN32 H = GraphicModeInfo->HorizontalResolution;
    //UINT32 V = GraphicModeInfo->VerticalResolution;
  }

  Print(L"Current Mode %u, %ux%u\n",Gop->Mode->Mode,
      Gop->Mode->Info->HorizontalResolution,
      Gop->Mode->Info->VerticalResolution);

  graphic_config->frame_base = Gop->Mode->FrameBufferBase;
  graphic_config->frame_size = Gop->Mode->FrameBufferSize;
  graphic_config->horizontal_resolution = Gop->Mode->Info->HorizontalResolution;
  graphic_config->vertical_resolution = Gop->Mode->Info->VerticalResolution;
  graphic_config->pixels_per_scan_line = Gop->Mode->Info->PixelsPerScanLine;
  return Status;
}
