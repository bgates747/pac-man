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
    ld hl,0
    ld hl,400
    
    add hl,de
    call vdu_buffer_select
    ld bc, 100
    ld de, 100
    call vdu_bitmap_plot
    ret