#ifndef RELOCATE_H_
#define RELOCATE_H_

EFI_STATUS RelocateELF(CHAR16* FilePath, EFI_PHYSICAL_ADDRESS* RelocateAddr);

#endif
