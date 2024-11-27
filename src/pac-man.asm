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

start:
    push af
    push bc
    push de
    push ix
    push iy

    setScreenMode SCREENMODE_320x240x64_60HZ
    call setScreenScaling

    call cursorHide

game_loop:

    ; Print the high score
    ld hl, high_score_data
    ld bc, high_score_data_end - high_score_data
    rst.lil $18

    ; Show pac-man
    ld hl, pac_man_data
    ld bc, pac_man_data_end - pac_man_data
    rst.lil $18

    ; Show the red-ghost
    ld hl, red_ghost_data
    ld bc, red_ghost_data_end - red_ghost_data
    rst.lil $18

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

quit_msg:
    .db "Thank you for playing Pac-Man!",13,10,0

high_score_data:
    .db     31, 15, 0
    .db     "HIGH SCORE"
high_score_data_end:

pac_man:    EQU     0
red_ghost:  EQU     1
pac_man_sprite: EQU     0
red_ghost_sprite: EQU     0

pac_man_data:
    .db 23, 0, 192, 0

    .db 23, 27, 0, pac_man
    .db 23, 27, 1
    .dw 12, 13
    incbin     "src/data/pac-man.data"

    .db 23, 27, 4, pac_man_sprite
    .db 23, 27, 5
    .db 23, 27, 6, pac_man
    .db 23, 27, 7, 1
    .db 23, 27, 11

    .db 23, 27, 4, pac_man_sprite
    .db 23, 27, 13
    .dw 150, 100

    .db 23, 27, 15

pac_man_data_end:

red_ghost_data:
    .db 23, 0, 192, 0

    .db 23, 27, 0, red_ghost
    .db 23, 27, 1
    .dw 14, 14
    incbin     "src/data/red-ghost.data"

    .db 23, 27, 4, red_ghost_sprite
    .db 23, 27, 5
    .db 23, 27, 6, red_ghost
    .db 23, 27, 7, 1
    .db 23, 27, 11

    .db 23, 27, 4, red_ghost_sprite
    .db 23, 27, 13
    .dw 100, 90

    .db 23, 27, 15

red_ghost_data_end: