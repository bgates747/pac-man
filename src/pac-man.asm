;
; Title:		       Pac-Man
;
; Description:         A port of the 1980's game Pac-Man to the Agon Light 2
; Author:		       Andy McCall, mailme@andymccall.co.uk, others welcome!
;
; Created:		       2024-11-25 @ 17:28
; Last Updated:	       2024-11-25 @ 17:28
;
; Modinfo:

.assume adl=1
.org $040000

    jp start

; MOS header
.align 64
.db "MOS",0,1

; API includes
    include "src/includes/system/mos_api.inc"
    include "src/includes/api/vdu.inc"
    include "src/includes/api/vdu_screen.inc"
    include "src/includes/api/vdu_cursor.inc"
    include "src/includes/api/vdu_buffer.inc"
    include "src/includes/api/vdu_bitmap.inc"
    include "src/includes/api/vdu_text.inc"
    include "src/includes/api/sprite.inc"
    include "src/includes/api/macro_sprite.inc"
    include "src/includes/api/macro_text.inc"
    include "src/includes/api/macro_bitmap.inc"

; Application includes
    include "src/includes/game/vdu_data.inc"
    include "src/includes/game/images_sprites.inc"
    include "src/includes/game/timer.inc"
    include "src/includes/game/maze/maze.inc"
    include "src/includes/game/maze/maze_wall_map.inc"

; Character Sprites
    include "src/includes/game/sprites/pac_man/pac_man.inc"
    include "src/includes/game/sprites/pac_man/pac_man_life.inc"
    include "src/includes/game/sprites/ghosts/blinky.inc"
    include "src/includes/game/sprites/ghosts/pinky.inc"
    include "src/includes/game/sprites/ghosts/inky.inc"
    include "src/includes/game/sprites/ghosts/clyde.inc"
    include "src/includes/game/sprites/ghosts/reverse.inc"
    include "src/includes/game/sprites/fruit/fruit.inc"
    include "src/includes/game/sprites/fruit/cherry.inc"
    include "src/includes/game/sprites/fruit/berry.inc"
    include "src/includes/game/sprites/fruit/orange.inc"
    include "src/includes/game/sprites/fruit/apple.inc"
    include "src/includes/game/sprites/fruit/melon.inc"
    include "src/includes/game/sprites/fruit/galaxian.inc"
    include "src/includes/game/sprites/fruit/bell.inc"
    include "src/includes/game/sprites/fruit/key.inc"

; Maze Bitmaps
    include "src/includes/game/sprites/maze/maze_tile.inc"

start:
    push af
    push bc
    push de
    push ix
    push iy

    call vdu_buffer_clear_all

    ld a, VDU_SCREENMODE_512x384x64_60HZ
    call vdu_screen_set_mode

    ld a, VDU_SCALING_ON
    call vdu_screen_set_scaling

    call vdu_cursor_off

    ld hl, vdu_data                      ; address of string to use
    ld bc, vdu_data_end - vdu_data         ; length of string
    rst.lil $18                         ; Call the MOS API to send data to VDP

    ; Print the 1UP text
    ld hl, up1_txt
    ld bc, up1_txt_end - up1_txt
    rst.lil $18

    ; Print the high score
    ld hl, high_score_data
    ld bc, high_score_data_end - high_score_data
    rst.lil $18

    ; Print the 2UP text
    ld hl, up2_txt
    ld bc, up2_txt_end - up2_txt
    rst.lil $18

    ld bc,origin_left+8
    ld de,origin_top+8
    call vdu_set_gfx_origin

    ld ix,maze_wall
    ld hl,SPRITE_MAZE_TILE_00
    call draw_maze

    ld bc,origin_left
    ld de,origin_top
    call vdu_set_gfx_origin

    call vdu_vblank

    call vdu_refresh

    call game_timer_tick

game_loop:

    call game_timer_tick

    ld a, mos_getkbmap
	rst.lil $08

    ; If the Escape key is pressed
    ld a, (ix + $0E)    
    bit 0, a
    jp nz, quit

    jp game_loop

quit:

    ld hl, VDU_SCREENMODE_640x480x4_60HZ
    call vdu_screen_set_mode

    call vdu_cursor_flash

    ld hl, quit_msg
    call vdu_text_print

    pop iy
    pop ix
    pop de
    pop bc
    pop af
    ld hl,0

    ret

quit_msg:
    .db "Thank you for playing Pac-Man!",13,10,0

high_score_data:
    .db     31, 27, 3
    .db     "HIGH SCORE"
high_score_data_end:

up1_txt:
    .db     31, 20, 3
    .db     "1UP"
up1_txt_end:

up2_txt:
    .db     31, 41, 3
    .db     "2UP"
up2_txt_end: