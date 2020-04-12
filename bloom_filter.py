def h1(x, bloom_length):
    return x % bloom_length

def h2(x, bloom_length):
    return (x - h1(x, bloom_length)) % bloom_length


a = [60, 36, 43, 141]
bloom_length = 13
bfilter = [0] * bloom_length
for elem in a:
    bfilter[h1(elem, bloom_length)] = 1
    bfilter[h2(elem, bloom_length)] = 1
    print(h1(elem, 13), h2(elem, 13), sep=' ')

def check(array, bfilter):
    for elem in array:
        if bfilter[h1(elem, bloom_length)] == 1 and bfilter[h2(elem, bloom_length)] == 1:
            print('yes')
        else:
            print('no')


check([107, 29, 26], bfilter)
