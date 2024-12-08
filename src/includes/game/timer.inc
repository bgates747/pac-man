timestamp_now: dl 0
timestamp_old: dl 0
timestamp_chg: dl 0

; Name: game_timer_tick
; Description: Update the global timestamp from the system clock
; Note:
; URL: 
;
; Inputs: None
; Rerurns: hl, time elapsed in 1/120ths of a second
;          ix, pointer to syvars table
; Destroys: af,hl,de,ix
game_timer_tick:
    ld de,(timestamp_now)   ; get previous time
    ld (timestamp_old),de   ; save previous time
    MOSCALL mos_sysvars     ; ix points to syvars table
    ld hl,(ix+sysvar_time)  ; get current time
    ld (timestamp_now),hl   ; save current time
    xor a                   ; clear carry
    sbc hl,de               ; hl = time elapsed
    ld (timestamp_chg),hl   ; save elapsed time
    ret