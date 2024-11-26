
C_VDP_STREAM:    equ $18

C_CURSOR_HIDE:   equ 0
C_CURSOR_SHOW:   equ 1
C_CURSOR_STEADY: equ 2
C_CURSOR_FLASH:  equ 3

cursorHide:    
    ld hl,@cmd
    ld bc,@end-@cmd
    rst.lil C_VDP_STREAM
    ret
@cmd:
    db 23,1,C_CURSOR_HIDE
@end:

cursorShow:    
    ld hl,@cmd
    ld bc,@end-@cmd
    rst.lil C_VDP_STREAM
    ret
@cmd:
    db 23,1,C_CURSOR_SHOW
@end:

cursorSteady:    
    ld hl,@cmd
    ld bc,@end-@cmd
    rst.lil C_VDP_STREAM
    ret
@cmd:
    db 23,1,C_CURSOR_STEADY
@end:

cursorFlash:    
    ld hl,@cmd
    ld bc,@end-@cmd
    rst.lil C_VDP_STREAM
    ret
@cmd:
    db 23,1,C_CURSOR_FLASH
@end: