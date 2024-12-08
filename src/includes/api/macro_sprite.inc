; Name: macro_sprite_select_sprite
; Description: Select a sprite
; Note: 
; URL:
;
; Inputs: Sprite Number
; Returns: None
; Destroys: None
    macro macro_sprite_select_sprite spriteNumber
    .db 23,27,4
    .db spriteNumber
    endmacro


; Name: macro_sprite_clear_current
; Description: Clear the current sprite
; Note: 
; URL:
;
; Inputs: Sprite Number
; Returns: None
; Destroys: None
    macro macro_sprite_clear_current 
    .db 23,27,5
    endmacro

; Name: macro_sprite_clear_current
; Description: Clear the current sprite
; Note: 
; URL:
;
; Inputs: Sprite Number
; Returns: None
; Destroys: None
   macro macro_sprite_add_frame bitmapNumber
    .db 23,27,$26
    .dw bitmapNumber
    endmacro


; Name: macro_sprite_hide_current
; Description: Hide the current sprite
; Note: 
; URL:
;
; Inputs: None
; Returns: None
; Destroys: None
    macro macro_sprite_hide_current 
    .db 23,27,12
    endmacro


    ; ------------------

    macro macro_sprite_show_current 
    .db 23,27,11
    endmacro


    ; ------------------

    macro SHOW_SPRITE spriteNumber
    .db 23,27,4
    .db spriteNum
    .db 23,27,11
    endmacro

    ; ------------------

    macro HIDE_SPRITE spriteNum
    .db 23,27,4                         ; select sprite...
    .db spriteNum                       ; with ID spriteNum
    .db 23,27,12                        ; show current sprite
    endmacro


    ; ------------------

    macro macro_sprite_activate spriteNumber
    .db 23,27,7                         ; activate
    .db spriteNumber                             ; this many
    .db 23,27,15                        ; update sprites in GPU.
    endmacro


   
; Name: macro_sprite_move
; Description: Move a sprite
; Note: 
; URL:
;
; Inputs: None
; Returns: None
; Destroys: None
    macro macro_sprite_move spriteNumber, x, y
    .db 23, 27, 4, spriteNumber
    .db 23, 27, 13
    .dw x, y
    .db 23, 27, 15
    endmacro