#!/bin/bash
cd edk2
source edksetup.sh
build -p bootloader/xv6-64_loader.dsc
