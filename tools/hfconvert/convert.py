from PIL import Image
import sys
import math
import struct

args = sys.argv[1:]

base = Image.open(args[-2])
px = base.load()

if base.width != base.height:
    print("Input texture must be square!")
    exit()

output = open(args[-2][:-3] + "hf", "wb")

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
            print(result, result.to_bytes(1,"big"))
            output.write(result.to_bytes(1,"big"))

base = Image.open(args[-1])
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
            print(result, result.to_bytes(1,"big"))
            output.write(result.to_bytes(1,"big"))

output.close()
