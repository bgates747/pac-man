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

    ; Set the text color
    MACRO macro_text_set_color color
    	ld a, 17
    	rst.lil $10
	    ld a, color
	    rst.lil $10
    ENDMACRO