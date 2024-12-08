; draw a maze based on a maze definition table
; inputs: ix = pointer to maze definition table
; outputs: pretty pixels
; destroys: all the things
; TODO: this could be significantly simplified if the null tile number 
;       and low byte of the base bufferId are both 0
;draw_maze:
; initialize variables
;    push ix
;    pop iy
;    ld hl,0
;    ld hl,400
;    
;    add hl,de
;    call vdu_buffer_select
;    ld bc, 100
;    ld de, 100
;    call vdu_bitmap_plot
;    ret

maze_cols: equ 0
maze_rows: equ 3
maze_tile_size: equ 6
maze_null_tile: equ 9
maze_x: equ 12
maze_y: equ 15
maze_base_bufferId: equ 18
orient_up: equ 2
orient_left: equ 1
orient_down: equ 3
orient_right: equ 0

origin_top: equ 0 ; DEBUG
origin_left: equ 128

; draw a maze based on a maze definition table
; inputs: ix = pointer to maze definition table
; outputs: pretty pixels
; destroys: all the things
; TODO: this could be significantly simplified if the null tile number 
;       and low byte of the base bufferId are both 0
draw_maze:
; initialize variables
    push ix
    pop iy
    lea ix,ix+maze_base_bufferId+3 ; point to the first cell of the maze data
    ld hl,0
    ld (iy+maze_x),hl
    ld (iy+maze_y),hl
    ld l,(iy+maze_cols)
    ld h,(iy+maze_rows)
@loop:
    push hl ; row/col loop counter
    ld a,(ix) ; tile number
    cp (iy+maze_null_tile) ; is it the null tile?
    jr z,@next_tile ; yes, so don't draw anything
    ld hl,(iy+maze_base_bufferId) ; base bufferId
    ld de,0 ; clear deu and d
    ld e,(ix) ; tile number
    add hl,de ; hl = tile bufferId
    call vdu_buffer_select
    ld bc,(iy+maze_x) ; x-coordinate
    ld de,(iy+maze_y) ; y-coordinate
    call vdu_bitmap_plot
@next_tile:
    ld hl,(iy+maze_x) ; x-coordinate
    ld de,(iy+maze_tile_size) ; tile size
    add hl,de ; x-coordinate + tile size
    ld (iy+maze_x),hl ; x-coordinate = x-coordinate + tile size
    inc ix ; bump pointer to next tile
    pop hl ; row/col loop counter
    dec l
    jp nz,@loop
    dec h
    ret z ; done
    ld l,(iy+maze_cols) ; number of columns
    push hl
    ld hl,(iy+maze_y) ; y-coordinate
    ld de,(iy+maze_tile_size) ; tile size
    add hl,de ; y-coordinate + tile size
    ld (iy+maze_y),hl ; y-coordinate = y-coordinate + tile size
    ld hl,0 ; x-coordinate
    ld (iy+maze_x),hl ; x-coordinate = 0
    pop hl
    jp @loop

; VDU 29, x; y;: Set graphics origin
; This command sets the graphics origin. 
; The origin is the point on the screen where the coordinates (0,0) are located.
; inputs: bc=x0,de=y0
; outputs; nothing
; destroys: a might make it out alive
vdu_set_gfx_origin:
    ld (@x0),bc
    ld (@y0),de
    ld hl,@cmd
    ld bc,@end-@cmd
    rst.lil $18
    ret
@cmd:   db 29 ; set graphics origin command
@x0: 	dw 0x0000 ; set by bc
@y0: 	dw 0x0000 ; set by de
@end:   db 0x00	  ; padding