"""Convert a small PNG icon into a C array for the Sharp LS013B7DH03 framebuffer.

Usage:
    python3 icon.py food.png            # dark pixels -> black, transparent -> white
    python3 icon.py food.png invert     # swap black and white

Creates icon_<name>.h with ICON_<NAME>_W, ICON_<NAME>_H and icon_<name>[].
Format matches lcd_buffer: leftmost pixel = bit 0 of each byte, 1 = white.
"""
import os
import sys
from PIL import Image, ImageOps

if len(sys.argv) < 2:
    sys.exit(__doc__)

path = sys.argv[1]
opts = set(a.lower() for a in sys.argv[2:])
name = os.path.splitext(os.path.basename(path))[0].replace("-", "_").replace(" ", "_").lower()

img = Image.open(path).convert("RGBA")
bg = Image.new("RGBA", img.size, "white")
bg.alpha_composite(img)                      # transparent -> white
img = bg.convert("L").point(lambda p: 255 if p > 128 else 0)
if "invert" in opts:
    img = ImageOps.invert(img)

w, h = img.size
row_bytes = (w + 7) // 8
data = []
for y in range(h):
    for xb in range(row_bytes):
        b = 0
        for bit in range(8):
            x = xb * 8 + bit
            if x >= w or img.getpixel((x, y)):   # padding and white pixels = 1
                b |= 1 << bit
        data.append(b)

out = "icon_%s.h" % name
with open(out, "w") as f:
    f.write("#include <stdint.h>\n")
    f.write("#define ICON_%s_W %d\n" % (name.upper(), w))
    f.write("#define ICON_%s_H %d\n" % (name.upper(), h))
    f.write("static const uint8_t icon_%s[%d] = {\n" % (name, len(data)))
    for i in range(0, len(data), row_bytes):
        f.write("  " + ", ".join("0x%02X" % v for v in data[i:i + row_bytes]) + ",\n")
    f.write("};\n")
print("wrote", out, "(%dx%d, %d bytes)" % (w, h, len(data)))