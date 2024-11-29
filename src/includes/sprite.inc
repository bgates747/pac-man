    macro MAKEBUFFEREDBITMAP id, width, height, data

    ; write data to the buffer

    .db     23,0,$A0                    ; write block
    .dw     id                          ; ID (word)
    .db     0                           ; 'write' command

    .dw     width *  height             ; data size assuming RGBA2222
            
    incbin data

    ; convert buffer block to bitmap with ID

    .db     23,27,$20                   ; select buffer bitmap to use
    .dw     id                          ; ID (word)

    ; create a bitmap from that ID

    .db     23,27,$21                   ; create bitmap from buffer
    .dw     width, height               ; width, height (both words)
    .db     1                           ; type 1 (RGBA2222)         

    endmacro

    ; ------------------

    macro SELECT_SPRITE spriteNum
    .db 23,27,4                         ; select sprite...
    .db spriteNum                       ; with ID spriteNum
    endmacro


    ; ------------------

    macro CLEAR_CURRENT_SPRITE 
    .db 23,27,5                         ; clear frames in current sprite
    endmacro

    ; ------------------

    macro ADD_SPRITE_FRAME bitmapNum
    .db 23,27,$26                         ; add bitmap data as frame to current sprite.
    .dw bitmapNum                       ; with ID bitmapNum
    endmacro


    ; ------------------

    macro HIDE_CURRENT_SPRITE 
    .db 23,27,12                        ; show current sprite
    endmacro


    ; ------------------

    macro SHOW_CURRENT_SPRITE 
    .db 23,27,11                        ; show current sprite
    endmacro


    ; ------------------

    macro SHOW_SPRITE spriteNum
    .db 23,27,4                         ; select sprite...
    .db spriteNum                       ; with ID spriteNum
    .db 23,27,11                        ; show current sprite
    endmacro

    ; ------------------

    macro HIDE_SPRITE spriteNum
    .db 23,27,4                         ; select sprite...
    .db spriteNum                       ; with ID spriteNum
    .db 23,27,12                        ; show current sprite
    endmacro


    ; ------------------

    macro ACTIVATE_SPRITES num
    .db 23,27,7                         ; activate
    .db num                             ; this many
    .db 23,27,15                        ; update sprites in GPU.
    endmacro


    ; ------------------

    macro MOVE_SPRITE spriteNum, x, y
    .db 23, 27, 4, spriteNum            ; select sprite 0 
    .db 23, 27, 13                      ; move currrent sprite to...
    .dw x, y                            ; x,y (as words)
    .db 23, 27, 15                      ; update sprites in GPU
    endmacro


    ; ------------------

    macro RECTANGLE colour, x1, y1, x2, y2
    .db 18, 0, colour                   ; set graphics colour: mode (0), colour 45 = purple

    .db 25, 69                          ; PLOT: mode (69 is a point in current colour),
    .dw x1, y1                          ; X; Y;

    .db 25, 101                         ; PLOT: mode (101 is a filled rectangle),
    .dw x2, y2                          ; X; Y;

    endmacro