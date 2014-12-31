# eCos makefile

# This is a generated file - do not edit

export PREFIX := /home/sontd/workspace/Sem7/RT/final/ecos-tools-bin-110209.i386linux/ecos_install
export COMMAND_PREFIX := arm-eabi-
export CC := $(COMMAND_PREFIX)gcc
export OBJCOPY := $(COMMAND_PREFIX)objcopy
export HOST := UNIX
export AR := $(COMMAND_PREFIX)ar

export REPOSITORY := /home/sontd/workspace/Sem7/RT/final/ecos/packages
PACKAGE := language/c/libc/stdlib/current
OBJECT_PREFIX := language_c_libc_stdlib
CFLAGS := -Wall -Wpointer-arith -Wstrict-prototypes -Wundef -Woverloaded-virtual -Wno-write-strings -mcpu=cortex-m3 -mthumb -g -O2 -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions
LDFLAGS := -mcpu=cortex-m3 -mthumb -Wl,--gc-sections -Wl,-static -Wl,-n -g -nostdlib
VPATH := $(REPOSITORY)/$(PACKAGE)
INCLUDE_PATH := $(INCLUDE_PATH) -I$(PREFIX)/include $(foreach dir,$(VPATH),-I$(dir) -I$(dir)/src -I$(dir)/tests) -I.
MLT := $(wildcard $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.ldi $(REPOSITORY)/$(PACKAGE)/include/pkgconf/mlt*.h)
TESTS := tests/abs tests/atoi tests/atol tests/bsearch tests/div tests/getenv tests/labs tests/ldiv tests/qsort tests/rand1 tests/rand2 tests/rand3 tests/rand4 tests/srand tests/strtol tests/strtoul

build: headers libtarget.a.stamp

LIBRARY := libtarget.a
COMPILE := src/abs.cxx src/atox.cxx src/bsearch.cxx src/div.cxx src/getenv.cxx src/qsort.cxx src/rand.cxx src/strtod.cxx src/strtol.cxx src/strtoul.cxx src/system.cxx src/strtoll.cxx src/strtoull.cxx
OBJECTS := $(COMPILE:.cxx=.o.d)
OBJECTS := $(OBJECTS:.cpp=.o.d)
OBJECTS := $(OBJECTS:.c=.o.d)
OBJECTS := $(OBJECTS:.S=.o.d)

$(LIBRARY).stamp: $(OBJECTS)
	$(AR) rcs $(PREFIX)/lib/$(@:.stamp=) $(foreach obj,$?,$(if $(obj:%.o=),$(dir $(obj))$(OBJECT_PREFIX)_$(notdir $(obj:.o.d=.o)),$(obj)))
	@cat $(foreach obj,$^,$(obj:.o=.o.d)) > $(@:.stamp=.deps)
	@touch $@

headers: mlt_headers $(PREFIX)/include/cyg/libc/stdlib/abs.inl $(PREFIX)/include/cyg/libc/stdlib/div.inl $(PREFIX)/include/cyg/libc/stdlib/atox.inl

$(PREFIX)/include/cyg/libc/stdlib/abs.inl: $(REPOSITORY)/$(PACKAGE)/include/abs.inl
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/libc/stdlib/div.inl: $(REPOSITORY)/$(PACKAGE)/include/div.inl
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

$(PREFIX)/include/cyg/libc/stdlib/atox.inl: $(REPOSITORY)/$(PACKAGE)/include/atox.inl
	@mkdir -p $(dir $@)
	@cp $< $@
	@chmod u+w $@

include $(REPOSITORY)/pkgconf/rules.mak

