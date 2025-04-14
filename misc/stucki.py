#!/usr/bin/env python3
from PIL import Image
import sys

def stucki_dithering(input_image_path, output_image_path):
    threshold = 128
    # Open the source image (assumed to be grayscale)
    src = Image.open(input_image_path).convert("L")
    width, height = src.size
    out = Image.new("1", (width, height))  # Create an empty black-and-white image for output
    pixels = src.load()
    out_pixels = out.load()

    # Initialize the error array (list of lists)
    errors = [[0 for _ in range(height)] for _ in range(width)]

    for y in range(height - 2):
        for x in range(2, width - 2):
            # Get the grayscale pixel value (it's just one channel in grayscale mode)
            gray = pixels[x, y]
            error = 0

            # Apply the Stucki dithering algorithm
            if gray + errors[x][y] < threshold:
                error = gray + errors[x][y]
                gray = 0
            else:
                error = gray + errors[x][y] - 255
                gray = 255

            # Distribute the error
            errors[x + 1][y] += (8 * error) // 42
            errors[x + 2][y] += (4 * error) // 42

            errors[x - 2][y + 1] += (2 * error) // 42
            errors[x - 1][y + 1] += (4 * error) // 42
            errors[x][y + 1] += (8 * error) // 42
            errors[x + 1][y + 1] += (4 * error) // 42
            errors[x + 2][y + 1] += (2 * error) // 42

            errors[x - 2][y + 2] += (1 * error) // 42
            errors[x - 1][y + 2] += (2 * error) // 42
            errors[x][y + 2] += (4 * error) // 42
            errors[x + 1][y + 2] += (2 * error) // 42
            errors[x + 2][y + 2] += (1 * error) // 42

            # Set the pixel with the new dithered black-and-white value
            out_pixels[x, y] = 255 if gray == 255 else 0

    # Save the output image
    out.save(output_image_path)

# Check if the script is run directly and take input and output file paths as arguments
if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 stucki.py <input_image_path> <output_image_path>")
    else:
        input_image_path = sys.argv[1]
        output_image_path = sys.argv[2]
        stucki_dithering(input_image_path, output_image_path)
