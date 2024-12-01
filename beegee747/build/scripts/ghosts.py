from PIL import Image
import os

def chop_image(image_path):
    """
    Chops an image into 16x16 tiles with specified skipping and naming rules,
    saving them into pre-existing directories named after their respective groups.

    Args:
        image_path (str): Path to the input image.
    """
    img = Image.open(image_path)
    tile_width, tile_height = 16, 16
    h_pitch, v_pitch = 17, 16
    tiles_per_row = 8
    rows = 5

    # Define groups and their properties
    groups = [
        ("blinky", 8),
        ("inky", 8),
        ("clyde", 8),
        ("pinky", 8),
        ("reverse", 4)
    ]

    tile_count = 0
    group_index = 0
    group_name, group_length = groups[group_index]

    for row in range(rows):
        for col in range(tiles_per_row):
            # Calculate tile's position
            x = col * h_pitch
            y = row * v_pitch

            # Skip the first two tiles
            if tile_count < 2:
                tile_count += 1
                continue

            # Update group when its length is exceeded
            if (tile_count - 2) >= sum(group[1] for group in groups[:group_index + 1]):
                group_index += 1
                if group_index >= len(groups):
                    return  # Stop when all groups are processed
                group_name, group_length = groups[group_index]

            # Crop the tile
            tile = img.crop((x, y, x + tile_width, y + tile_height))
            # Save the tile in the group's directory
            group_dir = group_name
            tile_index = (tile_count - 2) % group_length
            output_path = os.path.join(group_dir, f"{group_name}_{tile_index}.png")
            tile.save(output_path)
            tile_count += 1

# Replace with your image path
chop_image("ghosts.png")
