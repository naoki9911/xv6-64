#include <Uefi.h>
#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/UefiBootServicesTableLib.h>
#include  <Protocol/BlockIo.h>
#include  <Protocol/LoadedImage.h>
#include  <Protocol/SimpleFileSystem.h>
#include  <Library/DevicePathLib.h>
#include  <Guid/FileInfo.h>
#include  <Library/MemoryAllocationLib.h>
#include  <Library/BaseMemoryLib.h>

EFI_STATUS LoadFile(CHAR16 *FileName, EFI_PHYSICAL_ADDRESS *FileAddr, UINTN *FilePageSize){
  EFI_STATUS Status;
  EFI_FILE_PROTOCOL *Root;
  EFI_FILE_PROTOCOL *File;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFile;

  Status = gBS->LocateProtocol(
    &gEfiSimpleFileSystemProtocolGuid,
    NULL,
    (VOID **)&SimpleFile
  );
  if (EFI_ERROR (Status)) {
    Print(L"Failed to Locate Simple File System Protocol.\n");
    return Status;
  }
  
  Status = SimpleFile->OpenVolume (SimpleFile, &Root);
  if (EFI_ERROR (Status)) {
    Print(L"Failed to Open Volume.\n");
    return Status;
  }
  Print(L"Loading File: %s\n",FileName);

  Status = Root->Open (Root, &File, FileName, EFI_FILE_MODE_READ, 0);
  if (EFI_ERROR (Status)) {
    Print(L"Failed to Open %s\n", FileName);
    return Status;
  }

  UINTN FileInfoBufferSize = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) * StrLen(FileName) + 2;
  UINT8 FileInfoBuffer[FileInfoBufferSize];
  Status = File->GetInfo(File, &gEfiFileInfoGuid, &FileInfoBufferSize, FileInfoBuffer);
  if (EFI_ERROR(Status)) {
    Print(L"Failed to Get FileInfo\n");
    return Status;
  }
  
  EFI_FILE_INFO *FileInfo = (EFI_FILE_INFO*)FileInfoBuffer;
  UINTN FileSize = FileInfo->FileSize;
  Print(L"FileSize=%d\n",FileSize);
  *FilePageSize = (FileSize + 4095) / 4096;
  *FileAddr = 0;
  Status = gBS->AllocatePages(
  AllocateAnyPages,
  EfiLoaderData,
  *FilePageSize,
  FileAddr);
  if (EFI_ERROR(Status)) {
    Print(L"Failed to Allocate Pages\n");
    return Status;
  }
  
  Status = File->Read(
    File,
    &FileSize,
    (VOID *)*FileAddr
    );
  if (EFI_ERROR (Status)) {
    Print(L"Failed to Load File\n");
    return Status;
  }
  Print(L"Successfully Loaded File: %s\n",FileName);
  
  return Status;
}
