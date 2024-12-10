;
; Title:		       02-helloworld - Assembler Example
;
; Description:         A program that outputs Hello, World! on the Agon Light 2
;                      intended to check your environment works with no
;                      issues
; Author:		       Andy McCall, mailme@andymccall.co.uk
;
; Created:		       2024-08-22 @ 18:21
; Last Updated:	       2024-08-22 @ 18:21
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

    ld hl,hello_msg
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

hello_msg:
    .db "Hello, World!",13,10,0
