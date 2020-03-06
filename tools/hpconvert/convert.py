import sys

args = sys.argv[1:]


in_file = open(args[-1], "r")        
out_file = open(args[-1][:-3] + "hp", "wb")

for line in in_file:
    out_file.write(bytes.fromhex(line))
    #pass

out_file.close()
in_file.close()