ifndef V
	Q = @
endif

SRC = src
OUT = build

TOOLCHAIN = xtensa-lx106-elf
AS = $(TOOLCHAIN)-as
ASFLAGS = --warn --fatal-warnings 

CC = $(TOOLCHAIN)-gcc
CCFLAGS = -Wall -ffreestanding -Isrc/include -c -g -Wl,-static -Wl,--gc-sections -Wl,-EL

LD = $(TOOLCHAIN)-ld
LDFLAGS = -Map $(OUT)/firmware.map  -nostartfiles -T 
LIB_GCC = $(shell xtensa-lx106-elf-gcc -print-libgcc-file-name)

MAKE_COMMANDS = clean
.PHONY: clean 


ifeq ($(filter $(MAKECMDGOALS),$(MAKE_COMMANDS)),)
EXAMPLES = $(shell ls examples)
EXAMPLE ?= $(firstword $(MAKECMDGOALS))

ifeq ($(EXAMPLE),)
$(info Example name is not defined)

else ifeq ($(filter $(EXAMPLE), $(EXAMPLES)), )
$(info Example is not defined, check examples directory)
EXAMPLE =

endif
endif

S_FILES := $(wildcard $(SRC)/arch/*.S)
LD_FILES := $(wildcard $(SRC)/ld/*.ld) 

S_OBJS := $(addprefix $(OUT)/,$(S_FILES:.S=.o))
S_OBJS := $(subst /src,,$(S_OBJS))

C_FILES := $(wildcard $(SRC)/**/*.c)
C_FILES += $(wildcard $(SRC)/*.c)
H_FILES := $(wildcard $(SRC)/**/**/*.h)
H_FILES += $(wildcard $(SRC)/*.h)

C_OBJS := $(addprefix $(OUT)/,$(C_FILES:.c=.o))
C_OBJS := $(subst /src,,$(C_OBJS))


EXAMPLE_FILES = $(wildcard examples/$(EXAMPLE)/*.c)
EXAMPLE_OBJS := $(addprefix $(OUT)/, $(EXAMPLE_FILES:.c=.o))
EXAMPLE_OBJS := $(subst /src,,$(EXAMPLE_OBJS))

$(EXAMPLE): $(LD_FILES) $(S_OBJS) $(C_OBJS) $(EXAMPLE_OBJS) 
	@echo "Building ELF firmware..." 
	$(Q)$(LD) $(LDFLAGS) $^ $(LIB_GCC) -o $(OUT)/firmware.elf
	@echo "Complete" 

$(S_OBJS): $(OUT)/%.o: $(SRC)/%.S
	$(Q)mkdir -p $(@D)
	@echo "Compiling $(@D)/$(@F:.o=.S) ..."
	$(Q)$(CC) $(CCFLAGS) $< -o $@ 

$(EXAMPLE_OBJS): $(EXAMPLE_FILES)
	$(Q) mkdir -p $(@D)
	@echo "Compiling $(@D)/$(@F:.o=.c) ..."
	$(Q)$(CC) $(CCFLAGS) $< -o $@ 

$(C_OBJS): $(OUT)/%.o: $(SRC)/%.c
	$(Q)mkdir -p $(@D)
	@echo "Compiling $(@D)/$(@F:.o=.c) ..."
	$(Q)$(CC) $(CCFLAGS) $< -o $@ $(LIB)



clean:
	@echo "cleaning build directory"
	$(Q)rm -rf build 

