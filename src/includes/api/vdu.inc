; MOS screen modes as documented here: https://agonconsole8.github.io/agon-docs/vdp/Screen-Modes/

VDU_MODE_640x480x16_60HZ:     equ 0
VDU_MODE_640x480x4_60HZ:      equ 1
VDU_MODE_640x480x2_60HZ:      equ 2

VDU_MODE_640x240x64_60HZ:     equ 3
VDU_MODE_640x240x16_60HZ:     equ 4
VDU_MODE_640x240x4_60HZ:      equ 5
VDU_MODE_640x240x2_60HZ:      equ 6

VDU_MODE_TELETEXT_60HZ:       equ 7

VDU_MODE_320x240x64_60HZ:     equ 8
VDU_MODE_320x240x16_60HZ:     equ 9
VDU_MODE_320x240x4_60HZ:      equ 10
VDU_MODE_320x240x2_60HZ:      equ 11

VDU_MODE_320x200x64_70HZ:     equ 12
VDU_MODE_320x200x16_70HZ:     equ 13
VDU_MODE_320x200x4_70HZ:      equ 14
VDU_MODE_320x200x2_70HZ:      equ 15

VDU_MODE_800x600x4_60HZ:      equ 16
VDU_MODE_800x600x2_60HZ:      equ 17

VDU_MODE_1024x768x2_60HZ:     equ 18
VDU_MODE_1024x768x4_60HZ:     equ 19

VDU_MODE_512x384x64_60HZ:     equ 20
VDU_MODE_512x384x16_60HZ:     equ 21
VDU_MODE_512x384x4_60HZ:      equ 22
VDU_MODE_512x384x2_60HZ:      equ 23

VDU_MODE_640x480x4_60HZ_DB:   equ 129
VDU_MODE_640x480x2_60HZ_DB:   equ 130

VDU_MODE_640x240x16_60HZ_DB:  equ 132
VDU_MODE_640x240x4_60HZ_DB:   equ 133
VDU_MODE_640x240x2_60HZ_DB:   equ 134

VDU_MODE_320x240x64_60HZ_DB:  equ 136
VDU_MODE_320x240x16_60HZ_DB:  equ 137
VDU_MODE_320x240x4_60HZ_DB:   equ 138
VDU_MODE_320x240x2_60HZ_DB:   equ 139

VDU_MODE_320x200x64_70HZ_DB:  equ 140
VDU_MODE_320x200x16_70HZ_DB:  equ 141
VDU_MODE_320x200x4_70HZ_DB:   equ 142
VDU_MODE_320x200x2_70HZ_DB:   equ 143

VDU_MODE_800x600x2_DB:        equ 145
VDU_MODE_1024x768x2_DB:       equ 146

VDU_MODE_512x384x16_DB:       equ 149
VDU_MODE_512x384x4_DB:        equ 150
VDU_MODE_512x384x2_DB:        equ 151

VDU_OUTPUT_STREAM_TO_VDP:           equ $18

; https://agonconsole8.github.io/agon-docs/vdp/System-Commands/#vdu-23-0-0a-n-set-cursor-start-line-and-appearance
VDU_CURSOR_OFF:                     equ 0
VDU_CURSOR_ON:                      equ 1
VDU_CURSOR_STEADY:                  equ 2
VDU_CURSOR_FLASH:                   equ 3

; https://agonconsole8.github.io/agon-docs/vdp/Bitmaps-API/
VDU_BITMAP_CREATE_FROM_BUFFER:     equ 21

; https://agonconsole8.github.io/agon-docs/vdp/Buffered-Commands-API/
VDU_BUFFER_CLEAR:                   equ 2
VDU_BUFFER_CONSOLIDATE:             equ 14

VDU_SCALING_ON:                     equ 1
VDU_SCALING_OFF:                    equ 0

; https://agonconsole8.github.io/agon-docs/vdp/VDU-Commands/#vdu-12-clear-text-area-cls
VDU_CLS:                            equ 12  

vdu_refresh:
    ld hl,@cmd         
    ld bc,@end-@cmd    
    rst.lil $18         
    ret
@cmd:  db 23,27,15
@end:  db 0x00

vdu_vblank:        
    push ix            
    ld a, $08
	rst.lil $08
    ld a, (ix + $00 + 0)
@wait:        
    cp a, (ix + $00 + 0)
    jr z, @wait
    pop ix
    ret