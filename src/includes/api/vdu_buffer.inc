; Name: vdu_buffer_clear
; Description: Clear a single buffer
; Notes:
;
; Inputs: hl, the bufferId to clear
;
vdu_buffer_clear:
    ld a,l
    ld (@bufferId),a
    ld a,h
    ld (@bufferId+1),a
    ld hl,@cmd
    ld bc,@end-@cmd
    rst.lil VDU_OUTPUT_STREAM_TO_VDP
    ret
@cmd:       db 23,0,0xA0
@bufferId:	dw 0x0000
		    db VDU_BUFFER_CLEAR
@end:


; Name: vdu_buffer_clear_all
; Description: Clear all the buffers
; Notes:
;
; Inputs: None
;
vdu_buffer_clear_all:
    ld hl,@start
    ld bc,@end-@start
    rst.lil VDU_OUTPUT_STREAM_TO_VDP
    ret
@start: db 23,0,$A0
      dw -1
      db VDU_BUFFER_CLEAR
@end:


; Name: vdu_buffer_consolodate
; Description: Consolidate blocks in a buffer
; Notes:
; URL: https://agonconsole8.github.io/agon-docs/vdp/Buffered-Commands-API/#command-14-consolidate-blocks-in-a-buffer
;
; Inputs: None
;
vdu_buffer_consolidate:
    ld a,l
    ld (@bufferId),a
    ld a,h
    ld (@bufferId+1),a
    ld hl,@beg
    ld bc,@end-@beg
    rst.lil VDU_OUTPUT_STREAM_TO_VDP
    ret
@beg: db 23,0,$A0
@bufferId: dw 0x0000
           db VDU_BUFFER_CONSOLIDATE
@end:


; Name: vdu_buffer_select
; Description: Select a bitmap using a bufferID
; Notes:
; URL:
;
; Inputs: hl, bufferId
;
vdu_buffer_select:
	ld (@bufferId),hl
	ld hl,@cmd
	ld bc,@end-@cmd
	rst.lil VDU_OUTPUT_STREAM_TO_VDP
	ret
@cmd: db 23,27,0x20
@bufferId: dw 0x0000
@end: db 0x00


; load a vdu buffer from local memory
; inputs: hl = bufferId ; bc = length ; de = pointer to data
vdu_buffer_load:
    ld (@length),bc
    push de ; save data pointer
; send the vdu command string
    ld a,l
    ld (@bufferId),a
    ld a,h
    ld (@bufferId+1),a
    ld hl,@cmd
    ld bc,@end-@cmd
    rst.lil $18
; send the buffer data
    pop hl ; pointer to data
    ld bc,(@length)
    rst.lil $18 ; send it
    ret
; Upload data :: VDU 23, 0 &A0, bufferId; 0, length; <buffer-data>
@cmd:       db 23,0,0xA0
@bufferId:	dw 0x0000
		    db 0 ; load buffer
@length:	dw 0x0000
@end: db 0 ; padding