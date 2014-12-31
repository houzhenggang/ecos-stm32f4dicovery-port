# GNU ARM Embedded Toolchain
CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy
OD=arm-none-eabi-objdump

# Build Parameters: MCU Flags, Definitions, Includes, 
#                   Compile Flags, Linker Script, Linker Flags
MCFLAGS=-mcpu=cortex-m4 -mthumb -mlittle-endian -O2 -ffunction-sections -fdata-sections  \
-mfpu=fpv4-sp-d16  -mthumb-interwork #-mfloat-abi=hard
DEFS=-DUSE_STDPERIPH_DRIVER -DSTM32F4XX
INCLUDES=-Iecos_install/include 
CFLAGS=-c $(MCFLAGS) $(DEFS) $(INCLUDES)
LDSCRIPT = ecos_install/lib/target.ld
LDFLAGS=-Lecos_install/lib -T $(LDSCRIPT) -nostdlib --specs=nano.specs --specs=rdimon.specs -lc -lc -lrdimon $(MCFLAGS)

# Inputs: C Sources, Assembler Sources
SOURCES=hello.c
#ASMSOURCES=../../../Libraries/CMSIS/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f4xx.s

# Outputs: Object Files, ELF Executable & 
#          Converted ELF Executable to Intel HEX format
OBJECTS=$(SOURCES:%.c=%.o)
#OBJECTS+=$(ASMSOURCES:%.s=%.o)
EXECUTABLE=hello.elf
TARGET=hello.hex

# Build Rules
.PHONY: release
release: $(TARGET)

.PHONY: all
all: $(TARGET)

.PHONY: debug
debug: CFLAGS+=-g # Add debug flag
debug: LDFLAGS+=-g
debug: $(TARGET) 

$(TARGET): $(EXECUTABLE)
	$(CP) -O ihex $< $@
	@echo "Objcopy from ELF to IHEX complete!\n"

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	@echo "Linking complete!\n"

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	@echo "Compiled "$<"!\n"

%.o: %.s
	$(CC) $(CFLAGS) $< -o $@
	@echo "Assambled "$<"!\n"

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(TARGET)
