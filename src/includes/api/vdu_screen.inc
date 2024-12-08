; Name: vdu_screen_clear
; Description: Clear the screen
; Note:
; URL: https://agonconsole8.github.io/agon-docs/vdp/VDU-Commands/#vdu-12-clear-text-area-cls
;
; Inputs: None
vdu_screen_clear:
    ld a, VDU_CLS
    rst.lil $10
    ret

; Name: vdu_screen_set_mode
; Description: Set the screen mode
; Note: MOS default is VDU_SCREENMODE_640x480x4_60HZ
; URL: https://agonconsole8.github.io/agon-docs/vdp/Screen-Modes/#vdu-22-mode
;
; Inputs: a, the bufferId to clear
;
vdu_screen_set_mode:
	ld (@arg),a        
	ld hl,@cmd         
	ld bc,@end-@cmd    
	rst.lil VDU_OUTPUT_STREAM_TO_VDP       
	ret
@cmd: db 22
@arg: db 0
@end:

; Name: vdu_screen_set_scaling
; Description: set the scaling mode
; Note: MOS default is scaling ON
; URL: https://agonconsole8.github.io/agon-docs/vdp/Screen-Modes/#vdu-23-0-c0-n
;
; Inputs: a, set the scaling mode, 1=on, 0=off
;
vdu_screen_set_scaling:
	ld (@arg),a        
	ld hl,@cmd         
	ld bc,@end-@cmd    
	rst.lil VDU_OUTPUT_STREAM_TO_VDP
	ret
@cmd: db 23,0,0xC0
@arg: db 0
@end: 
