from PIL import Image
import sys
import math
import struct

args = sys.argv[1:]


output = open(args[-2][:-3] + "hf", "wb")

for i in range(8):
    a = 0
    output.write(a.to_bytes(1,"big"))

def loadImg (id):
    base = Image.open(args[id])
    px = base.load()
    if base.width != base.height:
        print("Input texture must be square!")
        exit()
    for c_y in range(8):
        for c_x in range(8):
            p_x = c_x * 8;
            p_y = c_y * 8;
            for i_y in range(8):
                result = 0
                for i_x in range(8):
                    g_x = p_x + i_x;
                    g_y = p_y + i_y;
                    exponent = 8-i_x-1
                    value = int(2**exponent);
                    if px[g_x,g_y] != 0:
                        result += value
                output.write(result.to_bytes(1,"big"))

loadImg(-2)
loadImg(-1)

output.close()
