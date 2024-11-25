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

start:
    push af
    push bc
    push de
    push ix
    push iy

    ld hl,program_name
    ld bc,0
    ld a,0
    rst.lil $18

    pop iy
    pop ix
    pop de
    pop bc
    pop af
    ld hl,0

    ret

program_name:
    .db "Pac-Man!",13,10,0
