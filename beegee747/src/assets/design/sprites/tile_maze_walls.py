from PIL import Image
import os
import shutil
import hashlib

def chop_and_deduplicate_tiles(source_dir, file_name, tile_width=8, tile_height=8, h_pitch=8, v_pitch=8, tiles_x=28, tiles_y=31, start_x=152, start_y=64):
    """
    Chops an image into tiles with specified width, height, and pitch,
    deduplicates the tiles based on their content, and saves unique tiles into a directory.

    Args:
        source_dir (str): Path to the source directory.
        file_name (str): Name of the source image file.
        tile_width (int): Width of each tile (default: 8).
        tile_height (int): Height of each tile (default: 8).
        h_pitch (int): Horizontal pitch between tiles (default: 8).
        v_pitch (int): Vertical pitch between tiles (default: 8).
        tiles_x (int): Number of tiles horizontally.
        tiles_y (int): Number of tiles vertically.
        start_x (int): Starting x-coordinate of the grid.
        start_y (int): Starting y-coordinate of the grid.
    """
    source_path = os.path.join(source_dir, file_name)
    target_dir = os.path.join(source_dir, os.path.splitext(file_name)[0])

    # Delete and recreate the target directory
    if os.path.exists(target_dir):
        shutil.rmtree(target_dir)
    os.makedirs(target_dir)

    # Open the source image
    img = Image.open(source_path)

    # Crop the image to the grid area starting at (start_x, start_y)
    crop_width = tiles_x * h_pitch
    crop_height = tiles_y * v_pitch
    cropped_img = img.crop((start_x, start_y, start_x + crop_width, start_y + crop_height))

    # Store unique tiles and their hashes
    unique_tiles = {}
    tile_count = 0

    for row in range(tiles_y):
        for col in range(tiles_x):
            # Calculate tile position within the cropped image
            x = col * h_pitch
            y = row * v_pitch
            tile = cropped_img.crop((x, y, x + tile_width, y + tile_height))
            
            # Generate a hash for the tile
            tile_hash = hashlib.md5(tile.tobytes()).hexdigest()

            # Check if the tile is unique
            if tile_hash not in unique_tiles:
                # Save the unique tile
                output_path = os.path.join(target_dir, f"tile_{tile_count:02}.png")
                tile.save(output_path)
                unique_tiles[tile_hash] = output_path
                tile_count += 1
                print(f"Saved unique tile {output_path}")

# Example usage
chop_and_deduplicate_tiles("beegee747/src/assets/design/sprites", "maze_walls.png")
