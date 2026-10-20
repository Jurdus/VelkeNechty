from PIL import Image, ImageOps
import sys

img = Image.open(sys.argv[1]).convert("L")
img = ImageOps.fit(img, (128, 128))      # crop to square and resize
img = ImageOps.autocontrast(img)
img = img.convert("1")                   # 1-bit with Floyd-Steinberg dithering

data = []
for y in range(128):
    for xb in range(16):
        b = 0
        for bit in range(8):             # leftmost pixel = bit 0 (LSB first)
            if img.getpixel((xb * 8 + bit, y)):   # white
                b |= 1 << bit
        data.append(b)

with open("image.h", "w") as f:
    f.write("#include <stdint.h>\n")
    f.write("const uint8_t image_data[128 * 16] = {\n")
    for i in range(0, len(data), 16):
        f.write("  " + ", ".join(f"0x{v:02X}" for v in data[i:i+16]) + ",\n")
    f.write("};\n")

img.save("preview.png")