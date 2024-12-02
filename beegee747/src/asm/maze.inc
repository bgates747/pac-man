maze_cols: equ 0
maze_rows: equ 3
maze_tile_size: equ 6
maze_null_tile: equ 9
maze_x: equ 12
maze_y: equ 15
maze_base_bufferId: equ 18

; draw a maze based on a maze definition table
; inputs: ix = pointer to maze definition table
; outputs: pretty pixels
; destroys: all the things
; TODO: this could be significantly simplified if the null tile number 
;       and low byte of the base bufferId are 0
draw_maze:
; initialize variables
    push ix
    pop iy
    lea ix,ix+maze_base_bufferId+3 ; point to the first cell of the maze data
    ld hl,0
    ld (iy+maze_x),hl
    ld (iy+maze_y),hl
    ld l,(iy+maze_cols) ; l = num cols
    ld h,(iy+maze_rows) ; h = num rows
@loop:
    push hl ; row/col loop counter
    ld a,(ix) ; tile number
    cp (iy+maze_null_tile) ; is it the null tile?
    jr z,@next_tile
    ld hl,(iy+maze_base_bufferId) ; base bufferId
    ld de,0 ; clear deu and d
    ld e,(ix) ; tile number
    add hl,de ; hl = tile bufferId
    ; push hl ; DEBUG
    call vdu_buff_select
    ld bc,(iy+maze_x) ; x-coordinate
    ld de,(iy+maze_y) ; y-coordinate
    ; pop hl ; DEBUG
    ; call dumpRegistersHex ; DEBUG
    ; call waitKeypress ; DEBUG
    call vdu_plot_bmp
@next_tile:
    ld hl,(iy+maze_x) ; x-coordinate
    ld de,(iy+maze_tile_size) ; tile size
    add hl,de ; x-coordinate + tile size
    ld (iy+maze_x),hl ; x-coordinate = x-coordinate + tile size
    inc ix ; bump pointer to next tile
    pop hl ; row/col loop counter
    dec l
    jp nz,@loop
; ; DEBUG
;     push hl
;     call dumpRegistersHex
;     call waitKeypress
;     pop hl
; ; END DEBUG
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