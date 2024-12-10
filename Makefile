# ----------------------------
# Makefile Options
# ----------------------------

NAME			   = main
EZ80ASM            = ez80asm
EZ80ASM_FLAGS      = -x
RM                 = rm -f
FAB_AGON_EMU       = fab-agon-emulator
FAB_AGON_EMU_FLAGS = --vdp ~/development/tools/fab-agon/firmware/vdp_console8.so --mos ~/development/tools/fab-agon/firmware/mos_console8.bin --sdcard bin/
RELEASE_DIR 	   = release
GIT_INFO 		   := $(shell git describe --always --tags)
BUILD_YEAR 		   := $(shell date +'%Y')

default: all

all:
	@echo "Building project..."
	mkdir -p bin
	$(EZ80ASM) $(EZ80ASM_FLAGS) src/$(NAME).asm
	mv src/$(NAME).bin bin/$(NAME).bin

package: all
	@echo "Packaging project..."
	mkdir -p release
	cp README.md release/
	cp bin/$(NAME).bin release/
	cd release && zip -r $(NAME)-$(GIT_INFO).zip *
	rm -rf release/README.md release/$(NAME).bin
	
clean:
	@echo "Cleaning project..."
	rm -rf bin
	rm -rf release
	rm -rf src/*.bin
	rm -rf $(NAME)*.zip

run:
	@echo "Launching emulator..."
	$(FAB_AGON_EMU) $(FAB_AGON_EMU_FLAGS)