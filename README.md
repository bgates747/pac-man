![Pac-Man](https://github.com/andymccall/pac-man/blob/main/assets/header.jpg?raw=true)

## Pac-Man

Pac-Man, originally called Puck Man in Japan, is a 1980 maze video game developed and released by Namco for arcades. In North America, the game was released by Midway Manufacturing as part of its licensing agreement with Namco America. The player controls Pac-Man, who must eat all the dots inside an enclosed maze while avoiding four colored ghosts. Eating large flashing dots called "Power Pellets" causes the ghosts to temporarily turn blue, allowing Pac-Man to eat them for bonus points.

This project intents to hold the most perfect arcade port of the 1980's arcade game Pac-Mac to the Agon Light 2 possible, within the limitations of the platform.

Controls will be either by keyboard or via the [EIGHTSBITWIDE Arcade board](https://andymccall.co.uk/electronics/retrocomputing/agon/basic/2024/07/09/agon-light-2-arcade-controller-board.html).

# Resolution / Maze

The arcade game uses a resolution of 224 x 288, dividing each value by 8 yields a grid that is 28 x 36 tiles in size.  The maze makes use of the entire horizontal plane, but vertically the first 24 pixels and the bottom 16 pixels are used for the UI rather than the maze, this means the maze uses a resolution of 224 x 248 using 28 x 31 tiles.

The Agon Light 2 re-write will make use of the systems graphics mode 20, which has a resolution of 512x384 with 16 colours a refresh rate of 60Hz.  Dividing this resolution by 8 yeilds a grid that is 64 x 48 tiles in size. This will allow the game to use a perfect copy of the original maze using the original tile size of 28 x 31.  The top and bottom game UI will be spaced out to make use of the larger resolution and it will utilize black bars on the side of the playfield, these may be populated with extra information in debug mode.


# Colour Scheme

Colour Scheme other than black and white

Name: Yellow
Hex: #ffff00
RGB: (255, 255, 0)
CMYK: 0, 0, 1, 0

Name: Neon Blue
Hex: #1919a6
RGB: (25, 25, 166)
CMYK: 0.849, 0.849, 0, 0.349

Name: Bluebonnet
Hex: #2121de
RGB: (33, 33, 222)
CMYK: 0.851, 0.851, 0, 0.129

Name: Tumbleweed
Hex: #dea185
RGB: (222, 161, 133)
CMYK: 0, 0.274, 0.400, 0.129
Red	

Hex: #fd0000
RGB: (253, 0, 0)
CMYK: 0, 1, 1, 0.007

Name: Electric Green
Hex: #00ff00
RGB: (0, 255, 0)
CMYK: 1, 0, 1, 0

Name: Black
Hex: #ffffff
RGB: (255, 255, 255)
CMYK: 1, 1, 1, 1

Name: White
Hex: #000000
RGB: (0, 0, 0)
CMYK: 0, 0, 0, 0