vdu_plot_set_fill:
    ld (@c0),a
    ld hl,@cmd
    ld bc,@end-@cmd
    rst.lil $18
    ret
@cmd:   db 18, 0
@c0: 	db 0x00
@end:   

vdu_plot_filled_rect:
    ld (@x0),bc
    ld (@y0),de
    ld (@x1),ix
    ld (@y1),iy
    ld a,25 ; write back the byte
    ld (@y0+2),a ; that got stomped
	ld hl,@cmd
	ld bc,@end-@cmd
	rst.lil $18
	ret
@cmd:   db 25, 4
@x0: 	dw 0x0000
@y0: 	dw 0x0000
        db 25, 101
@x1: 	dw 0x0000
@y1: 	dw 0x0000
@end:   db 0x00

vdu_plot_line:
    ld (@x0),bc
    ld (@y0),de
    ld (@x1),ix
    ld (@y1),iy
    ld a,25 ; write back the byte
    ld (@y0+2),a ; that got stomped
    ld hl,@cmd
    ld bc,@end-@cmd
    rst.lil $18
    ret
@cmd:   db 25, 4
@x0:    dw 0x0000
@y0:    dw 0x0000
        db 25, 5
@x1:    dw 0x0000
@y1:    dw 0x0000
@end:   db 0x00