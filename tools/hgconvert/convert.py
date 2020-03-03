from PIL import Image
import sys
import math
import struct

args = sys.argv[1:]

base = Image.open(args[-1])

if base.width != base.height:
    print("Input texture must be square!")
    exit()

print(args[-1][:-3] + "hg")

output = open(args[-1][:-3] + "hg", "wb")

output.write(base.tobytes())

output.close()

