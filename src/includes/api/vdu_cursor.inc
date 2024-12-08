; Name: vdu_cursor_on
; Description: Turns the cursor on
; Note:
; URL: https://agonconsole8.github.io/agon-docs/vdp/System-Commands/#vdu-23-0-0a-n-set-cursor-start-line-and-appearance
;
; Inputs:
;
vdu_cursor_on:    
    ld hl,@cmd
    ld bc,@end-@cmd
    rst.lil VDU_OUTPUT_STREAM_TO_VDP
    ret
@cmd:
    db 23,1,VDU_CURSOR_ON
@end:

; Name: vdu_cursor_off
; Description: Turns the cursor on
; Note:
; URL: https://agonconsole8.github.io/agon-docs/vdp/System-Commands/#vdu-23-0-0a-n-set-cursor-start-line-and-appearance
;
; Inputs:
;
vdu_cursor_off:	
	ld hl,@cmd
	ld bc,@end-@cmd
	rst.lil VDU_OUTPUT_STREAM_TO_VDP
	ret
@cmd:
	db 23,1,VDU_CURSOR_OFF
@end:

; Name: vdu_cursor_steady
; Description: Turns the cursor on
; Note:
; URL: https://agonconsole8.github.io/agon-docs/vdp/System-Commands/#vdu-23-0-0a-n-set-cursor-start-line-and-appearance
;
; Inputs:
;
vdu_cursor_steady:    
    ld hl,@cmd
    ld bc,@end-@cmd
    rst.lil VDU_OUTPUT_STREAM_TO_VDP
    ret
@cmd:
    db 23,1,VDU_CURSOR_STEADY
@end:

; Name: vdu_cursor_flash
; Description: Turns the cursor on
; Note:
; URL: https://agonconsole8.github.io/agon-docs/vdp/System-Commands/#vdu-23-0-0a-n-set-cursor-start-line-and-appearance
;
; Inputs:
;
vdu_cursor_flash:    
    ld hl,@cmd
    ld bc,@end-@cmd
    rst.lil VDU_OUTPUT_STREAM_TO_VDP
    ret
@cmd:
    db 23,1,VDU_CURSOR_FLASH
@end: