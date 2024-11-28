;
; Title:		       Pac-Man
;
; Description:         A port of the 1980's game Pac-Man to the Agon Light 2
; Author:		       Andy McCall, mailme@andymccall.co.uk, others welcome!
;
; Created:		       2024-11-25 @ 17:28
; Last Updated:	       2024-11-25 @ 17:28
;
; Modinfo:

.assume adl=1
.org $040000

    jp start

; MOS header
.align 64
.db "MOS",0,1

    include "src/includes/system/mos_api.inc"
    include "src/includes/screen.inc"
    include "src/includes/cursor.inc"
    include "src/includes/text.inc"
    include "src/includes/sprite.inc"

start:
    push af
    push bc
    push de
    push ix
    push iy

    setScreenMode SCREENMODE_320x240x64_60HZ
    call setScreenScaling

    call cursorHide

    ld hl, loadGraphics
	ld bc, endLoadGraphics - loadGraphics
	rst.lil $18

    call setupSprites

    ; Print the 1UP text
    ld hl, up1_txt
    ld bc, up1_txt_end - up1_txt
    rst.lil $18

    ; Print the high score
    ld hl, high_score_data
    ld bc, high_score_data_end - high_score_data
    rst.lil $18

    ; Print the 2UP text
    ld hl, up2_txt
    ld bc, up2_txt_end - up2_txt
    rst.lil $18

game_loop:

    ld a, mos_getkbmap
	rst.lil $08

    ; If the Escape key is pressed
    ld a, (ix + $0E)    
    bit 0, a
    jp nz, quit

    jp game_loop

quit:
    setScreenMode SCREENMODE_640x480x4_60HZ
    call cursorFlash

    printText quit_msg

    pop iy
    pop ix
    pop de
    pop bc
    pop af
    ld hl,0

    ret

setupSprites:				
	ld hl, defineSprites
	ld bc, endDefineSprites - defineSprites
	rst.lil $18
	ret 

quit_msg:
    .db "Thank you for playing Pac-Man!",13,10,0

high_score_data:
    .db     31, 15, 0
    .db     "HIGH SCORE"
high_score_data_end:

up1_txt:
    .db     31, 9, 0
    .db     "1UP"
up1_txt_end:

up2_txt:
    .db     31, 28, 0
    .db     "2UP"
up2_txt_end:

loadGraphics:
	MAKEBUFFEREDCELL64K 250, 0, 16, 16, "src/data/pac-man.rgba" 
endLoadGraphics:

defineSprites:
	SELECT_SPRITE 0
	CLEAR_CURRENT_SPRITE

	ADD_SPRITE_FRAME 0

	ACTIVATE_SPRITES 1

endDefineSprites: