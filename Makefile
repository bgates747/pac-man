# ----------------------------
# Makefile Options
# ----------------------------

NAME			   = pac-man
EZ80ASM            = ez80asm
EZ80ASM_FLAGS      = -x
RM                 = rm -f
FAB_AGON_EMU       = fab-agon-emulator
FAB_AGON_EMU_FLAGS = --vdp ~/development/tools/fab-agon/firmware/vdp_console8.so --mos ~/development/tools/fab-agon/firmware/mos_console8.bin --sdcard bin/

default: all

all:
	@echo "Building project..."
	mkdir -p bin
	$(EZ80ASM) $(EZ80ASM_FLAGS) src/$(NAME).asm
	mv src/$(NAME).bin bin/$(NAME).bin

clean:
	@echo "Cleaning project..."
	rm -rf bin
	rm -rf src/*.bin
	
run:
	@echo "Launching emulator..."
	$(FAB_AGON_EMU) $(FAB_AGON_EMU_FLAGS) 