#!/usr/bin/env python3
from PIL import Image
import sys

def stucki_dithering(input_image_path, output_image_path):
    threshold = 128
    src = Image.open(input_image_path).convert("L")
    width, height = src.size
    out = Image.new("1", (width, height))  # 1-bit image (black and white)
    pixels = src.load()
    out_pixels = out.load()

    # Initialize error buffer
    errors = [[0 for _ in range(height)] for _ in range(width)]

    # Stucki diffusion matrix (normalized to 42)
    diffusion = [
        (1, 0, 8), (2, 0, 4),
        (-2, 1, 2), (-1, 1, 4), (0, 1, 8), (1, 1, 4), (2, 1, 2),
        (-2, 2, 1), (-1, 2, 2), (0, 2, 4), (1, 2, 2), (2, 2, 1)
    ]

    for y in range(height):
        for x in range(width):
            old_pixel = pixels[x, y] + errors[x][y]
            new_pixel = 255 if old_pixel >= threshold else 0
            out_pixels[x, y] = new_pixel
            quant_error = old_pixel - new_pixel

            for dx, dy, weight in diffusion:
                nx, ny = x + dx, y + dy
                if 0 <= nx < width and 0 <= ny < height:
                    errors[nx][ny] += quant_error * weight // 42

    out.save(output_image_path)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 stucki.py <input_image_path> <output_image_path>")
    else:
        stucki_dithering(sys.argv[1], sys.argv[2])
