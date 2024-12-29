small_screen:

    push ix

; Top line
    ld a, VDU_COL_WHITE
    call vdu_plot_set_fill
    ld bc, 98
    ld de, 98
    ld ix, 420
    ld iy, 98
    call vdu_plot_line

; Left line
    ld a, VDU_COL_WHITE
    call vdu_plot_set_fill
    ld bc, 98
    ld de, 98
    ld ix, 98
    ld iy, 256
    call vdu_plot_line

; Bottom line
    ld a, VDU_COL_WHITE
    call vdu_plot_set_fill
    ld bc, 98
    ld de, 256
    ld ix, 420
    ld iy, 256
    call vdu_plot_line

; Right line
    ld a, VDU_COL_WHITE
    call vdu_plot_set_fill
    ld bc, 420
    ld de, 98
    ld ix, 420
    ld iy, 256
    call vdu_plot_line


; First column of long bars
    ld a, VDU_COL_WHITE
    call vdu_plot_set_fill
    ld bc, 100
    ld de, 100
    ld ix, 139
    ld iy, 199
    call vdu_plot_filled_rect

    ld a, VDU_COL_BRIGHT_YELLOW
    call vdu_plot_set_fill
    ld bc, 140
    ld de, 100
    ld ix, 179
    ld iy, 199
    call vdu_plot_filled_rect

    ld a, VDU_COL_BRIGHT_CYAN
    call vdu_plot_set_fill
    ld bc, 180
    ld de, 100
    ld ix, 219
    ld iy, 199
    call vdu_plot_filled_rect

    ld a, VDU_COL_BRIGHT_GREEN
    call vdu_plot_set_fill
    ld bc, 220
    ld de, 100
    ld ix, 259
    ld iy, 199
    call vdu_plot_filled_rect

    ld a, VDU_COL_BRIGHT_MAGENTA
    call vdu_plot_set_fill
    ld bc, 260
    ld de, 100
    ld ix, 299
    ld iy, 199
    call vdu_plot_filled_rect

    ld a, VDU_COL_BRIGHT_RED
    call vdu_plot_set_fill
    ld bc, 300
    ld de, 100
    ld ix, 339
    ld iy, 199
    call vdu_plot_filled_rect

    ld a, VDU_COL_BRIGHT_BLUE
    call vdu_plot_set_fill
    ld bc, 340
    ld de, 100
    ld ix, 379
    ld iy, 214
    call vdu_plot_filled_rect

; Second row of blocks of narrow bars
    ld a, VDU_COL_BRIGHT_RED
    call vdu_plot_set_fill
    ld bc, 100
    ld de, 200
    ld ix, 159
    ld iy, 214
    call vdu_plot_filled_rect

    ld a, VDU_COL_WHITE
    call vdu_plot_set_fill
    ld bc, 160
    ld de, 200
    ld ix, 219
    ld iy, 214
    call vdu_plot_filled_rect

    ld a, VDU_COL_BRIGHT_YELLOW
    call vdu_plot_set_fill
    ld bc, 220
    ld de, 200
    ld ix, 279
    ld iy, 214
    call vdu_plot_filled_rect

    ld a, VDU_COL_BRIGHT_CYAN
    call vdu_plot_set_fill
    ld bc, 280
    ld de, 200
    ld ix, 339
    ld iy, 214
    call vdu_plot_filled_rect

; Third row of squares
    ld a, VDU_COL_DARK_BLUE
    call vdu_plot_set_fill
    ld bc, 100
    ld de, 215
    ld ix, 139
    ld iy, 254
    call vdu_plot_filled_rect

    ld a, VDU_COL_BLACK
    call vdu_plot_set_fill
    ld bc, 140
    ld de, 215
    ld ix, 179
    ld iy, 254
    call vdu_plot_filled_rect

    ld a, VDU_COL_DARK_MAGENTA
    call vdu_plot_set_fill
    ld bc, 180
    ld de, 215
    ld ix, 219
    ld iy, 254
    call vdu_plot_filled_rect

    ld a, VDU_COL_BLACK
    call vdu_plot_set_fill
    ld bc, 220
    ld de, 215
    ld ix, 259
    ld iy, 254
    call vdu_plot_filled_rect

    ld a, VDU_COL_DARK_GREY
    call vdu_plot_set_fill
    ld bc, 260
    ld de, 215
    ld ix, 299
    ld iy, 254
    call vdu_plot_filled_rect

    ld a, VDU_COL_WHITE
    call vdu_plot_set_fill
    ld bc, 300
    ld de, 215
    ld ix, 312
    ld iy, 254
    call vdu_plot_filled_rect

    ld a, VDU_COL_MID_GREY
    call vdu_plot_set_fill
    ld bc, 313
    ld de, 215
    ld ix, 326
    ld iy, 254
    call vdu_plot_filled_rect

    ld a, VDU_COL_DARK_GREY
    call vdu_plot_set_fill
    ld bc, 327
    ld de, 215
    ld ix, 339
    ld iy, 254
    call vdu_plot_filled_rect

; Black stripe
    ld a, VDU_COL_BLACK
    call vdu_plot_set_fill
    ld bc, 100
    ld de, 130
    ld ix, 379
    ld iy, 150
    call vdu_plot_filled_rect

   ld hl, BITRIOTDEV_SMALL_LOGO_ID
    call vdu_buffer_select
    ld bc, 140
    ld de, 135
    call vdu_bitmap_plot

    pop ix

    ret