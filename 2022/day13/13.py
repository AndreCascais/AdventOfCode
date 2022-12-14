l = [[eval(packet) for packet in packetPair.split("\n")] for packetPair in open(0).read().split("\n\n")]

print(l)

