#!/bin/bash
if [ ! -e image/EFI/BOOT ]; then
  mkdir -p image/EFI/BOOT
fi

if [ -e bootloader/build ]; then
#        rm -rf bootloader/build/*
fi

cd edk2
source edksetup.sh
build -p bootloader/xv6-64_loader.dsc

cd ../os
make
cp kernel ../image/.
