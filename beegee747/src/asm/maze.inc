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
    call vdu_buff_select
    ld bc,(iy+maze_x) ; x-coordinate
    ld de,(iy+maze_y) ; y-coordinate
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

; converts screen coordinates to map cell coordinates
; inputs: ix = pointer to map defintion, ub.c = x-coordinate, ud.e = y-coordinate in 16.8 fixed point format
; outputs: bc,de = row,col, hl = cell index, ix = pointer to cell data
; destroys: a, hl, ix
; notes: map and screen coordinates assume inverted y-axis with origin at top left
;        tile size must be a power of two
;        screen coordinates are treated as unsigned with no checks to the contrary
screen_to_map:
; get the x-coordinate
    push bc
    pop hl
    call hlu_udiv256 ; hl = int(x)
    ld a,(ix+maze_tile_size)
    call shr_hlu_log2a ; hl = int(int(x) / tile size) = col
    ex de,hl ; uh.l = y-coordinate, de = col
; get the y-coordinate
    call hlu_udiv256 ; hl = int(y)
    ld a,(ix+maze_tile_size)
    call shr_hlu_log2a ; hl = int(int(y) / tile size) = row
    push hl ; save row
; compute cell index = row * cols + col
; at this point hl = row, de = col
    ld h,(ix+maze_cols)
    mlt hl ; hl = row * cols
    add hl,de ; hl = row * cols + col = cell index
    ex de,hl ; de = cell index, hl = col
; point to cell data
    lea ix,ix+maze_base_bufferId+3
    add ix,de
; return results
    ex de,hl ; de = col, hl = cell index
    push de
    pop bc ; bc = col
    pop de ; de = row

    ret

; converts map cell coordinates to screen coordinates
; inputs: ix = pointer to map definition, ub.c = col, ud.e = row in 16.8 fixed point format
; outputs: bc,de = x,y as 24-bit integers
; destroys: a, hl, bc, de
map_to_screen:
; get the x-coordinate
    push bc
    pop hl ; uh.l = col
    ld a,(ix+maze_tile_size)
    call shl_hlu_log2a ; uh.l = col * tile size
    push hl ; save x-coordinate
; get the y-coordinate
    ex de,hl ; uh.l = row
    ld a,(ix+maze_tile_size)
    call shl_hlu_log2a ; uh.l = row * tile size
; return results
    ex de,hl ; de = y-coordinate
    pop bc ; bc = x-coordinate
    ret

; get a pointer to a map cell from col and row input
; by computing cell index = row * cols + col
; inputs: ix = pointer to map definition, ub.c = col, ud.e = row in 16.8 fixed point format
; returns: ix = pointer to cell data, hl = cell index, a = cell value
; destroys: a, hl, ix
map_get_cell:
    ld l,d ; int(row)
    ld h,(ix+maze_cols)
    mlt hl ; row * cols
    ld a,b ; int(col)
    add a,l 
    ld l,a
    ld a,0 ; we need carry
    adc a,h
    ld h,a ; hl = cell index
    ex de,hl ; can't add ix,hl
    lea ix,ix+maze_base_bufferId+3 ; point to cell 0
    add ix,de ; point to cell data
    ld a,(ix) ; cell value
    ex de,hl ; restore de, hl = cell index
    ret
; end map_get_cell