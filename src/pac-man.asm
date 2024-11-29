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

    ld hl, VDUdata                      ; address of string to use
    ld bc, endVDUdata - VDUdata         ; length of string
    rst.lil $18                         ; Call the MOS API to send data to VDP

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

our_sprite: EQU     0                   ; sprite ID - always start at 0 upwards

VDUdata:
    .db 23, 0, 192, 0                   ; set to non-scaled graphics

    .db 23, 0, $A0                      ; clear all buffers
    .dw -1                              ; ID, -1 for ALL as a WORD
    .db 2                               ; clear command

    .db 23, 27, 16                      ; clear all sprite and bitmap data


    ; ------------------
    ; create buffered bitmaps

    MAKEBUFFEREDBITMAP 64002, 16, 16, "src/assets/pac-man.rgba2" 
    MAKEBUFFEREDBITMAP 64003, 16, 16, "src/assets/blinky.rgba2" 
    MAKEBUFFEREDBITMAP 64004, 16, 16, "src/assets/pellet.rgba2"  

    ; Maze bitmaps
    MAKEBUFFEREDBITMAP 64020, 16, 16, "src/assets/close_wall.rgba2" 
    MAKEBUFFEREDBITMAP 64021, 16, 16, "src/assets/close_straight_corner.rgba2"
    MAKEBUFFEREDBITMAP 64022, 16, 16, "src/assets/close_rounded_corner.rgba2"

    ; ------------------
    ; SETUP THE SPRITE

    SELECT_SPRITE 0
    CLEAR_CURRENT_SPRITE
    ADD_SPRITE_FRAME 64002
    ACTIVATE_SPRITES 1
    SHOW_CURRENT_SPRITE

    MOVE_SPRITE 0, 140,90

    SELECT_SPRITE 1
    CLEAR_CURRENT_SPRITE
    ADD_SPRITE_FRAME 64003
    ACTIVATE_SPRITES 2
    SHOW_CURRENT_SPRITE

    MOVE_SPRITE 1, 100,30

    ; ------------------
    ; just PLOT a bitmap, not sprite

    .db 23, 27, $20                     ; select bitmap
    .dw 64004                           ; id WORD

    .db 25, 237                         ; plot a bitmap
    .dw 148, 90                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 156, 90                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 164, 90                          ; at x,y WORDs

    .db 23, 27, $20                     ; select bitmap
    .dw 64022                           ; id WORD
    .db 25, 237                         ; plot a bitmap
    .dw 28, 209                          ; at x,y WORDs

    .db 23, 27, $20                     ; select bitmap
    .dw 64020                           ; id WORD
    .db 25, 237                         ; plot a bitmap
    .dw 39, 210                          ; at x,y WORDs
    
    .db 25, 237                         ; plot a bitmap
    .dw 55, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 71, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 87, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 103, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 103, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 119, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 135, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 151, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 167, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 183, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 183, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 199, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 215, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 215, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 231, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 247, 210                          ; at x,y WORDs

    .db 25, 237                         ; plot a bitmap
    .dw 263, 210                          ; at x,y WORDs

    .db 23, 27, $20                     ; select bitmap
    .dw 64022                           ; id WORD
    .db 25, 237                         ; plot a bitmap
    .dw 279, 209                          ; at x,y WORDs

endVDUdata: