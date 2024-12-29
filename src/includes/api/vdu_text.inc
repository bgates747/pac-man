; Name: vdu_text_print
; Description: Print a zero terminated string
; Note:
; URL: https://agonconsole8.github.io/agon-docs/MOS-API/#rst-18h-output-a-stream-of-characters-to-the-vdp-mos-103-or-above
;
; Inputs: hl, pointer to the string to print
; Returns: None
; Destroys: None
vdu_text_print:
    push bc
    ld bc, 0
    ld a, 0
    rst.lil VDU_OUTPUT_STREAM_TO_VDP
    pop bc
    ret

vdu_text_set_at:
    ld hl,@y0+1
    ld (hl),d
    dec hl
    ld (hl),e
    dec hl ;ld hl,@x0+1
    ld (hl),b
    dec hl
    ld (hl),c
    dec hl
    dec hl ;ld hl,@cmd
    ld bc,@end-@cmd
    rst.lil $18
    ret
@cmd:   db 25, 4
@x0:     dw 0x0000
@y0:     dw 0x0000
@end: