credit_deposit:
    ld a, (credit)
    inc a
    ld (credit), a
    ret