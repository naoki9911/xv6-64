BOOT_LOADER = bootloader/build/DEBUG_GCC5/X64/xv6-64_loader.efi
BOOT_IMAGE_PATH = image/EFI/BOOT
OVMF_CODE = ovmf/OVMF_CODE.fd
OVMF_VARS = ovmf/OVMF_VARS.fd
run:
	./build.sh
	cp -r $(BOOT_LOADER) $(BOOT_IMAGE_PATH)/BOOTX64.efi
	qemu-system-x86_64 \
	-drive if=pflash,format=raw,readonly,file=$(OVMF_CODE) \
	-drive if=pflash,format=raw,file=$(OVMF_VARS) \
	-drive if=ide,file=fat:rw:image,index=0,media=disk \
	-gdb tcp::4321 \
	-m 2048 \
	-smp 4 \
	-monitor stdio
#	-nographic
debug:
#	./build.sh
	cp -r $(BOOT_LOADER) $(BOOT_IMAGE_PATH)/BOOTX64.efi
	qemu-system-x86_64 \
	-drive if=pflash,format=raw,readonly,file=$(OVMF_CODE) \
	-drive if=pflash,format=raw,file=$(OVMF_VARS) \
	-drive if=ide,file=fat:rw:image,index=0,media=disk \
	-gdb tcp::4321 \
	-m 2048 \
	-smp 2 \
	-monitor stdio \
#	-net nic,model=e1000 \
#	-net bridge,br=br0
