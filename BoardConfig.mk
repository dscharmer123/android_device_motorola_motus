# Copyright (C) 2007 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# config.mk
#
# Product-specific compile-time definitions.
#

# WARNING: This line must come *before* including the proprietary
# variant, so that it gets overwritten by the parent (which goes
# against the traditional rules of inheritance).
USE_CAMERA_STUB := true

# inherit from the proprietary version
-include vendor/motorola/motus/BoardConfigVendor.mk

TARGET_BOARD_PLATFORM := msm7k
TARGET_CPU_ABI := armeabi-v6j
TARGET_CPU_ABI2 := armeabi
TARGET_ARCH_VARIANT := armv6j
TARGET_BOARD_PLATFORM_GPU := qcom

#TARGET_NO_BOOTLOADER := true

# Wifi related defines
BOARD_WPA_SUPPLICANT_DRIVER := WEXT
WPA_SUPPLICANT_VERSION      := VER_0_6_X
BOARD_WLAN_DEVICE           := dhd
WIFI_DRIVER_MODULE_PATH     := "/system/lib/modules/dhd.ko"
WIFI_DRIVER_FW_STA_PATH     := "/system/etc/firmware/fw_bcm4325.bin"
WIFI_DRIVER_FW_AP_PATH      := "/system/etc/firmware/fw_bcm4325_apsta.bin"
WIFI_DRIVER_MODULE_ARG      := "firmware_path=/system/etc/firmware/fw_bcm4325.bin nvram_path=/system/etc/firmware/nvram.txt"
WIFI_DRIVER_MODULE_NAME     := "dhd"

TARGET_BOOTLOADER_LIBS := \
	libboot_board_motus \
	libboot_arch_msm7k \
	libboot_arch_armv6

TARGET_BOOTLOADER_LINK_SCRIPT := \
	hardware/msm7k/boot/boot.ld

BOARD_KERNEL_CMDLINE := no_console_suspend=1 console=null quiet

BOARD_PREBUILT_LIBAUDIO := true

BOARD_HAVE_BLUETOOTH := true
BOARD_HAVE_BLUETOOTH_BCM := true

BOARD_VENDOR_USE_AKMD := akm8973

BOARD_VENDOR_QCOM_AMSS_VERSION := 6225

# The size of a block that can be marked bad.
BOARD_FLASH_BLOCK_SIZE := 131072

# OpenGL drivers config file path
BOARD_EGL_CFG := device/motorola/motus/prebuilt/lib/egl/egl.cfg

BOARD_NO_RGBX_8888 := true

# Use libcamera2
BOARD_USES_OLD_CAMERA_HACK := true

# No authoring clock for OpenCore on Motus
BOARD_NO_PV_AUTHORING_CLOCK := true

BOARD_USES_QCOM_LIBS := true

#bootloopy
#BOARD_USES_ECLAIR_LIBCAMERA := true

TARGET_RELEASETOOLS_EXTENSIONS := device/motorola/common

TARGET_BOOTLOADER_BOARD_NAME := motus
TARGET_OTA_ASSERT_DEVICE := motus
PRODUCT_BUILD_PROP_OVERRIDES += TARGET_BOOTLOADER_BOARD_NAME=motus


# # cat /proc/mtd
#dev: size erasesize name
#mtd0: 00300000 00020000 "boot"
#mtd1: 08ac0000 00020000 "system"
#mtd2: 0df80000 00020000 "userdata"
#mtd3: 00040000 00020000 "misc"
#mtd4: 00500000 00020000 "recovery"
#mtd5: 06000000 00020000 "cache"
#mtd6: 00080000 00020000 "splash"
BOARD_BOOTIMAGE_PARTITION_SIZE := 0x00300000
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 0x00500000
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 0x08ac0000
BOARD_USERDATAIMAGE_PARTITION_SIZE := 0x0df80000
BOARD_RECOVERYIMAGE_MAX_SIZE := $(call image-size-from-data-size,0x00500000)

BOARD_KERNEL_BASE := 0x10000000
BOARD_PAGE_SIZE := 0x800

BOARD_CUSTOM_RECOVERY_KEYMAPPING:= ../../device/motorola/motus/recovery/recovery_ui.c


#TARGET_RECOVERY_UI_LIB := librecovery_ui_motus librecovery_ui_moto
TARGET_PREBUILT_KERNEL := device/motorola/motus/kernel
