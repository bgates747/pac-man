    assume adl=1 
    org 0x040000 
    jp start 
    align 64 
    db "MOS" 
    db 00h 
    db 01h 

start: 
    push af
    push bc
    push de
    push ix
    push iy
    call init
    call main

exit:
    pop iy
    pop ix
    pop de
    pop bc
    pop af
    ld hl,0

    ret

; API INCLUDES
    include "mos_api.inc"
    include "functions.inc"
    include "arith24.inc"
    include "maths.inc"
    include "files.inc"
    include "fixed168.inc"
    include "images.inc"
    include "timer.inc"
    include "vdu.inc"
    include "vdu_fonts.inc"
    include "vdu_plot.inc"
    include "vdu_sprites.inc"

; APPLICATION INCLUDES
    include "collisions.inc"
    include "enemies.inc"
    include "images_sprites.inc"
    include "maze.inc"
    include "maze_index.inc" ; DEBUG
    include "maze_walls.inc"
    include "maze_path.inc"
    include "maze_pellets.inc"
    include "player.inc"
    include "sprites.inc"
    include "state.inc"

init:
    ret

main:
    call printNewLine
    ld ix,maze_index
    ld bc,0x003733 ; 55.2
    ld de,0x001666 ; 22.4
    call screen_to_cell
    ld a,(ix)
    call dumpRegistersHex
    call printNewLine

main_end:
    ret