bpm = 252

for i in range(0, 4):
    output = 1 << 4+i
    output |= int(bpm%10)
    bpm /= 10
    print("{0:08b}".format(output))
