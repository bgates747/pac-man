max_enemy_sprites: db 4

; sprite_type
enemy_dead: equ 0
enemy_seeker: equ 1
enemy_medium: equ 2
enemy_large: equ 3
landing_pad: equ 4
laser_turret: equ 5
fireballs: equ 6
explosion: equ 7

move_enemies:
; are there any active enemies or explosions?
    ld a,(table_active_sprites)
    and a ; will be zero if no alive enemies or explosions
    jp nz,@they_live
    ld hl,enemies_dead
    ld (enemies_state),hl
    ret
@they_live:
; initialize pointers and loop counter
    ld iy,table_base ; set iy to first record in table
    ld b,table_max_records ; loop counter
@move_loop:
    ld (table_pointer),iy ; update table pointer
    push bc ; backup loop counter
; check sprite_type to see if sprite is active
    ld a,(iy+sprite_type)
    and a ; if zero, sprite is dead 
    jp z,@next_record ; ... and we skip to next record
; otherwise we prepare to move the sprite
    ld a,(iy+sprite_id) ; get spriteId
    call vdu_sprite_select ; select sprite 
    ld hl,(iy+sprite_move_program) ; load the behavior subroutine address
    CALL_HL
; move_enemies_loop_return: return from behavior subroutines
    ld iy,(table_pointer) ; get back table pointer
; now we check results of all the moves
    bit sprite_just_died,(iy+sprite_collisions)
    jp z,@draw_sprite ; if not dead, draw sprite
    call table_deactivate_sprite 
    jp @next_record ; and to the next record
@draw_sprite:
    ld bc,(iy+sprite_x)
    ld de,(iy+sprite_y)
    call vdu_sprite_move_abs168
; fall through to @next_record
@next_record:
    lea iy,iy+table_bytes_per_record
    xor a ; clears carry flag
    ld (sprite_screen_edge),a ; clear screen edge collision flag
    pop bc ; get back our loop counter
    djnz @move_loop ; loop until we've checked all the records
    ret ; and we're out

; ; ######### SPRITE BEHAVIOR ROUTINES #########
; ; each sprite in the table must have one of these defined
; ; but they need not be unique to a particular sprite
; ; these are jumped to from move_enemies_do_program,but could come from other places
; ; and have the option but not obligation to go back to move_enemies_loop_return
; ; but they can call anything they want between those two endpoints
; move_programs: ; bookmark in case we want to know the first address of the first subroutine

check_enemy_player_collisions:
; check for collisions with player
    ld ix,player_start_variables
    bit sprite_alive,(ix+sprite_collisions)
    ret z ; player dead, no collision
    call check_collision
    ret p ; no collision
    jp enemy_kill
; end move_enemy_seeker
orientation_to_player:
    ld iy,(table_pointer) ; TODO: see if we can get IY to land here with the proper value
    ld bc,(iy+sprite_x)
    ld de,(iy+sprite_y)
    ld ix,(player_x)
    ld iy,(player_y)
    call dxy168
    push bc
    push de
    call atan2_168fast
    pop de
    pop bc
    ld iy,(table_pointer) ; TODO: see if we can get IY to land here with the proper value
    ret

; this routine vanquishes the enemy sprite
; inputs: table_pointer set to sprite record
; destroys: everything except index registers
; returns: an incandescent ball of debris and gas
enemy_kill:
    ld iy,(table_pointer); TODO: see if we can get IY to land here with the proper value
; tally up points
    ld hl,(player_score)
    ld bc,0 ; clear bcu
    ld c,(iy+sprite_points)
    add hl,bc
    ld (player_score),hl
    set sprite_just_died,(iy+sprite_collisions)
    ret
; end enemy_kill

; TODO: implement this
scare_ghosts:
    ret