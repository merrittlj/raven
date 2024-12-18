#!/bin/sh
rm -r processed_png
rm -r ravenicons
mkdir -p processed_png
mkdir -p ravenicons
for file in ./svg/*.svg; do
    name=$(basename $file)
    magick convert -size 100x100 $file processed_png/${name%%.*}.png
done
python3 LVGLImage.py --ofmt C --cf I1 --compress LZ4 -o ravenicons processed_png/

# for file in ravenicons/*.c; do  echo "\${PROJECT_SOURCE_DIR}/display/icons/$file"; done
