    macro SELECT_SPRITE spriteNumber
        .db 23,27,4
        .db spriteNumber
    endmacro

    macro CLEAR_CURRENT_SPRITE 
        .db 23,27,5
    endmacro

    macro ADD_SPRITE_FRAME bitmapNumber
        .db 23,27,6
        .db bitmapNumber
    endmacro

    macro HIDE_CURRENT_SPRITE 
        .db 23,27,12
    endmacro

    macro ACTIVATE_SPRITES number
        .db 23,27,7
        .db number
        .db 23,27,15
    endmacro

    macro MAKEBUFFEREDCELL64K screenId, id, width, height, data

        .db 23,0,$A0
        .dw screenId*256+id
        .db 0

        .dw width*height

        incbin data

        .db 23,27,$20
        .dw screenId*256+id

        .db 23,27,$21
        .dw width, height
        .db 1
    endmacro