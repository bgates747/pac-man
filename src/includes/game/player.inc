player_1_start:
    ld a, (credit)
    dec a
    ld (credit), a
    ret

player_2_start:
    ld a, (credit)
    dec a
    ld (credit), a
    ret