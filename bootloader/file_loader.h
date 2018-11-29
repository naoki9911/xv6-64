#ifndef FILE_LOADER_H
#define FILE_LOADER_H

EFI_STATUS LoadFile(CHAR16 *FileName, EFI_PHYSICAL_ADDRESS *FileAddr, UINTN *FilePageSize);

#endif
