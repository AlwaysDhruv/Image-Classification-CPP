import os
import sys
from PIL import Image

def preprocess_image(path):
    img = Image.open(path).convert("L")
    img = img.resize((64, 64))
    pixel = [round(float(p) / 255.0, 2) for p in img.getdata()]
    return pixel

def get_output_filename(input_path):
    base_name = os.path.basename(input_path)
    name_without_ext = os.path.splitext(base_name)[0]
    return name_without_ext + ".txt"

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python preprocess2.py <input_image> [output_file.txt]")
        sys.exit(1)

    input_image = sys.argv[1] if len(sys.argv) >= 2 else None
    if not os.path.isfile(input_image):
        print(f"File not found: {input_image}")
        sys.exit(1)

    os.makedirs("pixel", exist_ok=True)
    output_filename = get_output_filename(input_image)
    output_path = os.path.join("pixel", output_filename)

    try:
        pixel = preprocess_image(input_image)
        if len(pixel) != 64 * 64:
            raise ValueError(f"Image must be resized to 64x64 (got {len(pixel)} pixel)")
        with open(output_path, "w") as out_file:
            out_file.write(",".join(map(str, pixel)) + "\n")
    except Exception as e:
        print(f"Error processing image: {e}")
        sys.exit(1)