# ===================================================================
# Makefile for "the noexistence of you and me" Linux Distro
#
# This Makefile handles:
#   - Compiling the init program.
#   - Creating an initramfs.
#   - Testing the kernel + initramfs directly with QEMU.
#   - Building a final, bootable ISO with ISOLINUX.
#   - Placing all generated artifacts in an 'out/' directory.
# ===================================================================

# --- Configuration ---

# Kernel location. User specified.
KERNEL := kernel/bzImage

# Compiler and flags for the init program.
# -Os     = Optimize for size.
# -static = No dynamic library dependencies.
# -Wall   = Enable all standard warnings.
CC := gcc
CFLAGS := -Os -static -Wall -Wextra

# Tool to strip the binary for even smaller size.
STRIP ?= strip

# --- Paths and Names ---

# All output goes into the 'out' directory.
OUT_DIR     := out
RAMDISK_DIR := $(OUT_DIR)/ramdisk
ISO_STAGING := $(OUT_DIR)/iso_root
INITRAMFS   := $(RAMDISK_DIR)/initramfs.cpio.gz
ISO_NAME    := $(OUT_DIR)/noexistence.iso

# Source and final location for the init binary inside the rootfs.
INIT_SRC  := src/init/init.c
INIT_BIN  := rootfs/sbin/init


# --- Targets ---

# Phony targets don't represent actual files. This prevents conflicts.
.PHONY: all clean run-qemu iso

# The default target, executed when you just run 'make'.
all: $(INIT_BIN)

# Rule to build the init binary.
$(INIT_BIN): $(INIT_SRC)
	@echo "  [CC]    Compiling init: $< -> $@"
	@mkdir -p $(shell dirname $(INIT_BIN))
	@$(CC) $(CFLAGS) -o $@ $<
	@echo "  [STRIP] Stripping binary: $@"
	@$(STRIP) $@

# Rule to generate the initramfs. This is a dependency for other targets.
$(INITRAMFS): all
	@echo "  [INITRAMFS] Creating RAM disk image: $@"
	@mkdir -p $(RAMDISK_DIR)
	@(cd rootfs && find . -print0 | cpio --null -ov --format=newc | gzip -9 > ../$@)

# Target to run the OS in QEMU for quick testing.
run-qemu: $(INITRAMFS)
	@echo "  [QEMU]    Booting kernel with custom initramfs..."
	@qemu-system-x86_64 \
		-kernel $(KERNEL) \
		-initrd $(INITRAMFS) \
		-append "console=ttyS0 quiet root=/dev/ram0 rdinit=/sbin/init" \
		-nographic \
		-serial mon:stdio \
		-m 256M

# Target to generate the final, bootable ISO image.
iso: $(INITRAMFS)
	@echo "  [PREP-ISO] Preparing ISO staging area in '$(ISO_STAGING)'..."
	@# 1. Create a clean staging area.
	@rm -rf $(ISO_STAGING)
	@mkdir -p $(ISO_STAGING)/boot
	@# 2. Copy the root filesystem contents, bootloader, kernel, and initramfs.
	@cp -a rootfs/. $(ISO_STAGING)/
	@cp -r isolinux $(ISO_STAGING)/
	@cp $(KERNEL) $(ISO_STAGING)/boot/vmlinuz
	@cp $(INITRAMFS) $(ISO_STAGING)/boot/initramfs.gz
	@echo "  [ISO]      Creating ISOLINUX bootable ISO: $(ISO_NAME)"
	@# 3. Create the ISO from the clean staging area.
	@mkisofs -o $(ISO_NAME) \
		-R \
		-b isolinux/isolinux.bin \
		-c isolinux/boot.cat \
		-no-emul-boot \
		-boot-load-size 4 \
		-boot-info-table \
		$(ISO_STAGING)
	@echo "  [ISO-CLEAN] ISO created. Staging area will be removed by 'make clean'."

# Target to clean up the entire project.
clean:
	@echo "  [CLEAN] Removing all compiled files and the output directory..."
	@rm -f $(INIT_BIN)
	@rm -rf $(OUT_DIR)
