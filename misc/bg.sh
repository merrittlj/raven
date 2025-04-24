#!/bin/sh
# $1: src image $2: dst dir
src="$1"
fn="${src##*/}"
dst="${fn%.*}"

magick $src -resize 200x200 -colorspace Gray ./$dst.png # NON-linear gray!!
python3 stucki.py ./$dst.png ./$dst.png
mv ./$dst.png $2/
python3 LVGLImage.py --ofmt C --cf I1 --compress NONE -o $2 $2/$dst.png
echo "\${PROJECT_SOURCE_DIR}/display/icons/$dst.c"
./f $2/$dst.png
