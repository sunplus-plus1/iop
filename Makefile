#set this env to skip clear IRAM
export 	SDCC_NOGENRAMCLEAR=1

ifneq ($V,1)
 Pecho=@echo
 P=@
else
 Pecho=@:
 P=
endif

STANDBY ?= 0

#######################################
# Build path
#######################################
BUILD_DIR  = __build
OUTPUT_DIR = out
TOOLS_DIR  = tools

DIR_COMMON = common
DIR_I2C    = driver/i2c
DIR_START  = startup

######################################
# target path
######################################
TARGET = dq8051_firmware

TARGET_OUT = $(BUILD_DIR)/$(TARGET)

#######################################
# cross compile
#######################################
PREFIX =
#PREFIX = ../SDCC-4.0.0/bin/
CC	= $(PREFIX)sdcc
AS	= $(PREFIX)sdas8051
PACK	= $(PREFIX)packihx

MCU_MODEL = -mmcs51
RM = rm -rf

# ------------------------------------------------------
# Usually SDCC's small memory model is the best choice.  If
# you run out of internal RAM, you will need to declare
# variables as "xdata", or switch to larger model

# ------------------------------------------------------
#IRAM_SIZE = --iram-size 256
IRAM_SIZE = --iram-size 256

ifeq ($(STANDBY),1)
#no XDATA,XRAM size 0
XRAM_SIZE = --xram-size 0x0
else
# EXT-MEM Size = 64K Bytes
XRAM_SIZE = --xram-size 0x10000
endif

# ------------------------------------------------------
#######################################
# FLAGS
#######################################
# compile as8051 flags

ASFLAGS = -plosgff

# C includes
C_INCLUDES = -Iinclude -Iinclude/$(DIR_COMMON) -Iinclude/$(DIR_I2C)

CFLAGS = $(MCU_MODEL) $(C_INCLUDES) $(MODEL)  --out-fmt-ihx --no-xinit-opt --std-sdcc99

ifeq ($(DEBUG), 1)
CFLAGS +=
else
CFLAGS += $(OPT)
endif

ifeq ($(STANDBY),1)
CFLAGS += -DSTANDBY
endif

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT =

# Memory Model (small, medium, large, huge)
ifeq ($(STANDBY),1)
MODEL  = --model-small
else
MODEL  = --model-large
endif

#######################################
# LDFLAGS
#######################################
LDFLAGS = $(MCU_MODEL)  $(MODEL) $(CODE_SIZE) $(IRAM_SIZE) $(XRAM_SIZE) $(STACK_ADDRESS) --out-fmt-ihx

#######################################
# build the code
#######################################

VPATH := $(DIR_COMMON) $(DIR_I2C) $(DIR_START)

ifeq ($(STANDBY),1)
C_SOURCES = standby_main.c $(DIR_COMMON)/Int_Vec.c
else
C_SOURCES = normal_main.c
C_SOURCES += $(DIR_COMMON)/Int_Vec.c  $(DIR_COMMON)/timer.c  $(DIR_COMMON)/vitrualserial.c $(DIR_COMMON)/delay.c
C_SOURCES += $(DIR_I2C)/i2c_slave.c $(DIR_I2C)/i2c_slave_common.c
endif

A_SOURCES = $(DIR_START)/crtstart.asm

C_OBJ_FILE = $(notdir $(C_SOURCES:.c=.c.rel) $(A_SOURCES:.asm=.asm.rel))

# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(C_OBJ_FILE))

.PHONY: all clean prepare bin_2_array

all: clean bin_2_array $(OBJECTS)
	$(CC) -o $(TARGET_OUT).ihx $(LDFLAGS) $(OBJECTS)
	$(PACK) $(TARGET_OUT).ihx > $(TARGET_OUT).hex

ifeq ($(STANDBY),1)
	srec_cat $(TARGET_OUT).hex -Intel -byte-swap 4 --fill 0xff 0 16384 -o $(TARGET_OUT).bin -Binary
	$(BUILD_DIR)/bin2array $(TARGET_OUT).bin $(OUTPUT_DIR)/iopstandby.c
else
	srec_cat $(TARGET_OUT).hex -Intel -byte-swap 4 --fill 0xff 0 65536 -o $(TARGET_OUT).bin -Binary
	$(BUILD_DIR)/bin2array $(TARGET_OUT).bin $(OUTPUT_DIR)/iopnormal.c
endif

bin_2_array: prepare
ifeq ($(STANDBY),1)
	@gcc $(TOOLS_DIR)/bin2array_standby.c -o $(BUILD_DIR)/bin2array
else
	@gcc $(TOOLS_DIR)/bin2array.c -o $(BUILD_DIR)/bin2array
endif
$(BUILD_DIR)/%.c.rel: %.c
	$(CC) -o $@ $(CFLAGS) -c $^

$(BUILD_DIR)/%.asm.rel: %.asm
	$(AS) $(ASFLAGS) -o $@ $^

prepare:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(OUTPUT_DIR)

#######################################
# clean up
#######################################

HEADER_FILE = 8051.h
HEADER_PATH = /usr/share/sdcc/include/mcs51

disasm: $(TARGET_OUT).hex
	$(Pecho) ./tools/mcs51-disasm.pl -M $(HEADER_FILE) -I $(HEADER_PATH) -fl -rj -as $(TARGET_OUT).hex > $(TARGET_OUT).a51

clean:
	$(Pecho) "Clean....."
	@$(RM) $(BUILD_DIR) $(OUTPUT_DIR)

p-%:
#	$(Pecho) "$* is '$($*)'"
	$(Pecho) '$*=$($*)'
	$(Pecho) '  origin =ls $(origin $*)'
	$(Pecho) '  value = $(value  $*)'
	$(Pecho) '  flavor = $(flavor $*)'
