import os
import shutil
from PIL import Image
from agonImages import img_to_rgba2, img_to_rgba8, convert_to_agon_palette

def make_images(buffer_id, images_type, asm_images_filepath, originals_dir, originals_subdirs, output_dir_png, output_dir_rgba, palette_name, palette_dir, palette_conv_type, transparent_rgb, del_non_png, do_palette):
    # Load the palette
    palette_filepath = f'{palette_dir}/{palette_name}'
    
    # Delete and recreate the RGBA output directory
    if os.path.exists(output_dir_rgba):
        shutil.rmtree(output_dir_rgba)
    os.makedirs(output_dir_rgba)

    # Delete and recreate the processed PNG output directory
    if os.path.exists(output_dir_png):
        shutil.rmtree(output_dir_png)
    os.makedirs(output_dir_png)

    # Process each subdirectory in originals_subdirs
    for subdir in originals_subdirs:
        subdir_path = os.path.join(originals_dir, subdir)

        if not os.path.isdir(subdir_path):
            print(f"Warning: Subdirectory {subdir} does not exist in {originals_dir}. Skipping...")
            continue

        # Convert .jpeg, .jpg, and .gif files to .png
        for input_image_filename in os.listdir(subdir_path):
            input_image_path = os.path.join(subdir_path, input_image_filename)
            if input_image_filename.endswith(('.jpeg', '.jpg', '.gif')):
                # Load the image
                img = Image.open(input_image_path)

                # Convert to .png format and save with the same name but .png extension
                png_filename = os.path.splitext(input_image_filename)[0] + '.png'
                png_filepath = os.path.join(subdir_path, png_filename)
                img.save(png_filepath, 'PNG')

                if del_non_png:
                    # Optionally, delete the original .jpeg, .jpg, or .gif file after conversion
                    os.remove(input_image_path)

        # Copy all .png files from the subdirectory to the output PNG directory
        for input_image_filename in os.listdir(subdir_path):
            if input_image_filename.endswith('.png'):
                input_image_path = os.path.join(subdir_path, input_image_filename)
                output_image_path = os.path.join(output_dir_png, input_image_filename)
                shutil.copy(input_image_path, output_image_path)

    # Scan the output directory for all .png files and sort them
    filenames = sorted([f for f in os.listdir(output_dir_png) if f.endswith('.png')])

    # Initialize variables
    num_images = 0
    image_type = 1  # RGBA2222

    image_list = []
    files_list = []
    buffer_ids = []

    # Process the images
    for input_image_filename in filenames:
        input_image_path = os.path.join(output_dir_png, input_image_filename)

        # Open the image file
        with Image.open(input_image_path) as img:
            # Apply palette conversion if required
            if do_palette:
                img = convert_to_agon_palette(img, 64, palette_conv_type, transparent_rgb)

            # Generate the appropriate RGBA file based on the image type
            file_name, ext = os.path.splitext(input_image_filename)
            if image_type == 1:
                rgba_filepath = f'{output_dir_rgba}/{file_name}.rgba2'
                img_to_rgba2(img, rgba_filepath)
            else:
                rgba_filepath = f'{output_dir_rgba}/{file_name}.rgba8'
                img_to_rgba8(img, rgba_filepath)

            # Collect assembly details
            buffer_ids.append(f'BUF_{file_name.upper()}: equ {buffer_id}\n')

            image_width, image_height = img.width, img.height
            image_filesize = os.path.getsize(rgba_filepath)

            image_list.append(f'\tdl {image_type}, {image_width}, {image_height}, {image_filesize}, fn_{file_name}, {buffer_id}\n')

            files_list.append(f'fn_{file_name}: db "{images_type}/{file_name}.rgba2",0 \n') 

            buffer_id += 1
            num_images += 1

    # Write the assembly file
    with open(f'{asm_images_filepath}', 'w') as f:
        f.write(f'; Generated by make_images.py\n\n')

        f.write(f'{images_type}_num_images: equ {num_images}\n\n')

        f.write(f'; buffer_ids:\n')
        f.write(''.join(buffer_ids))
        f.write(f'\n') 

        f.write(f'{images_type}_image_list: ; type; width; height; filename; bufferId:\n')
        f.write(''.join(image_list))
        f.write(f'\n') 

        f.write(f'; files_list: ; filename:\n')
        f.write(''.join(files_list))

if __name__ == '__main__':
    buffer_id =             256
    images_type =           'sprites'
    asm_images_filepath =  f'beegee747/src/asm/images_{images_type}.inc'
    originals_dir =        f'beegee747/assets'
    originals_subdirs =    ['blinky', 'cherry', 'clyde', 'inky', 'maze', 'pac-man', 'pellet', 'pinky', 'power-pellet', 'reverse', 'strawberry']
    output_dir_png =       f'beegee747/assets/proc/{images_type}'
    output_dir_rgba =      f'beegee747/tgt/{images_type}'
    palette_name =          'Agon64.gpl'
    palette_dir =           'beegee747/build/palettes'
    palette_conv_type =     'RGB'  # Can be 'RGB' or 'HSV'
    transparent_rgb =       (0, 0, 0, 0)
    del_non_png =           False
    do_palette =            True   # Enable palette conversion
    make_images(buffer_id, images_type, asm_images_filepath, originals_dir, originals_subdirs, output_dir_png, output_dir_rgba, palette_name, palette_dir, palette_conv_type, transparent_rgb, del_non_png, do_palette)