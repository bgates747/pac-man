; VDU 23, 27, 4, n: Select sprite n
; inputs: a is the 8-bit sprite id
vdu_sprite_select:
    ld (@sprite),a        
    ld hl,@cmd         
    ld bc,@end-@cmd    
    rst.lil $18         
    ret
@cmd:    db 23,27,4
@sprite: db 0x00
@end:

; VDU 23, 27, 7, n: Activate n sprites
; inputs: a is the number of sprites to activate
; prerequisites: each sprite activated must have at least one frame attached to it
vdu_sprite_activate:
    ld (@num),a        
    ld hl,@cmd         
    ld bc,@end-@cmd    
    rst.lil $18         
    ret
@cmd: db 23,27,7
@num: db 0x00
@end:

; VDU 23, 27, 8: Select next frame of current sprite
; inputs: none
; prerequisites: vdu_sprite_select
vdu_sprite_next_frame:
    ld hl,@cmd         
    ld bc,@end-@cmd    
    rst.lil $18         
    ret
@cmd: db 23,27,8
@end:

; VDU 23, 27, 11: Show current sprite
; inputs: none
; prerequisites: vdu_sprite_select
vdu_sprite_show:
    ld hl,@cmd         
    ld bc,@end-@cmd    
    rst.lil $18         
    ret
@cmd: db 23,27,11
@end:

; VDU 23, 27, 10, n: Select the nth frame of current sprite
; inputs: a is frame number to select
; prerequisites: vdu_sprite_select
vdu_sprite_select_frame:
    ld (@frame),a        
    ld hl,@cmd         
    ld bc,@end-@cmd    
    rst.lil $18         
    ret
@cmd:    db 23,27,10
@frame:  db 0x00
@end:

vdu_sprite_move_abs:
    ld (@sprite_x), bc
    ld (@sprite_y), de
    ld hl,@cmd         
    ld bc,@end-@cmd    
    rst.lil $18         
    ret
@cmd:  db 23,27,13
@sprite_x: dw 0x0000
@sprite_y: dw 0x0000
@end:  db 0x00

; VDU 23, 27, 14, x; y;: Move current sprite by x, y pixels
; inputs: bc is x coordinate, de is y coordinate
; prerequisites: vdu_sprite_select
vdu_sprite_move_rel:
    ld (@dx),bc
    ld (@dy),de
    ld hl,@cmd         
    ld bc,@end-@cmd    
    rst.lil $18         
    ret
@cmd: db 23,27,14
@dx:  dw 0x0000
@dy:  dw 0x0000
@end: db 0x00 ; padding