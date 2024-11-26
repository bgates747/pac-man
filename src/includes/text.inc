    MACRO printText TEXT
        ld hl,TEXT
        ld bc,0
        ld a,0
        rst.lil $18
	ENDMACRO