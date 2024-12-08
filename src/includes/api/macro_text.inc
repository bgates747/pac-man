; Name: macro_text_print
; Description: Print a zero terminated string
; Note: 
; URL:
;
; Inputs: text, 
; Returns: None
; Destroys: None
    MACRO macro_text_print text
        ld hl,text
        ld bc,0
        ld a,0
        rst.lil VDU_OUTPUT_STREAM_TO_VDP
	ENDMACRO