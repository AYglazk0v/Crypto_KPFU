import string
import time
import random

def padTo512bits(binary):
    binaryLen = bin(len(binary))[2:]
    binary += '1'
    mod = len(binary) % 512
    while mod != 448:
        binary += '0'
        mod = len(binary) % 512
    binary = ''.join(splitByElements(binary, 8)[::-1])
    binary = ''.join(splitByElements(binary, 32)[::-1])
    binaryLen = '0' * (64 - len(binaryLen)) + binaryLen
    binaryLen = ''.join(splitByElements(binaryLen, 32)[::-1])
    binary += binaryLen
    return binary

def splitByElements(string, Range):
    return [string[i:i+Range] for i in range(0, len(string), Range)]

def stringToBinary(str):
    return ''.join(format(ord(j), '08b') for j in str)

def leftRot(a, s):
    return ((a << s) | (a >> (32 - s)))

def  F(x, y, z):
    return (x & y) | (~x & z)

def  G(x, y, z):
    return (x & y) | (x & z) | (y & z)

def  H(x, y, z):
    return x ^ y ^ z

def R1(A, B, C, D, Xk, s):
    return leftRot((A + F(B, C, D) + Xk) % (2**32), s)

def R2(A, B, C, D, Xk, s):
    return leftRot((A + G(B, C, D) + Xk + 0x5A827999) % (2**32), s)

def R3(A, B, C, D, Xk, s):
    return leftRot((A + H(B, C, D) + Xk + 0x6ED9EBA1) % (2**32), s)

def MD4(R, fl):
    N = len(R)

    A, B, C, D = 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476
    # A, B, C, D = 0x67452302, 0xefcdab99, 0x98badffe, 0x10325476
    X = [0] * 16

    for i in range(0, N):
        X = [int(x, 2) for x in splitByElements(R[i], 32)]

        AA, BB, CC, DD = A, B, C, D
        A = R1(A, B, C, D, X[0], 3); D = R1(D, A, B, C, X[1], 7); C = R1(C, D, A, B, X[2], 11); B = R1(B, C, D, A, X[3], 19);
        A = R1(A, B, C, D, X[4], 3); D = R1(D, A, B, C, X[5], 7); C = R1(C, D, A, B, X[6], 11); B = R1(B, C, D, A, X[7], 19);
        A = R1(A, B, C, D, X[8], 3); D = R1(D, A, B, C, X[9], 7); C = R1(C, D, A, B, X[10], 11); B = R1(B, C, D, A, X[11], 19);
        A = R1(A, B, C, D, X[12], 3); D = R1(D, A, B, C, X[13], 7); C = R1(C, D, A, B, X[14], 11); B = R1(B, C, D, A, X[15], 19);
        
        A = R2(A, B, C, D, X[0], 3); D = R2(D, A, B, C, X[4], 5); C = R2(C, D, A, B, X[8], 9); B = R2(B, C, D, A, X[12], 13);
        A = R2(A, B, C, D, X[1], 3); D = R2(D, A, B, C, X[5], 5); C = R2(C, D, A, B, X[9], 9); B = R2(B, C, D, A, X[13], 13);
        A = R2(A, B, C, D, X[2], 3); D = R2(D, A, B, C, X[6], 5); C = R2(C, D, A, B, X[10], 9); B = R2(B, C, D, A, X[14], 13);
        A = R2(A, B, C, D, X[3], 3); D = R2(D, A, B, C, X[7], 5); C = R2(C, D, A, B, X[11], 9); B = R2(B, C, D, A, X[15], 13);

        # A = R3(A, B, C, D, X[0], 3); D = R3(D, A, B, C, X[8], 9); C = R3(C, D, A, B, X[4], 11); B = R3(B, C, D, A, X[12], 15);
        # A = R3(A, B, C, D, X[2], 3); D = R3(D, A, B, C, X[10], 9); C = R3(C, D, A, B, X[6], 11); B = R3(B, C, D, A, X[14], 15);
        # A = R3(A, B, C, D, X[1], 3); D = R3(D, A, B, C, X[9], 9); C = R3(C, D, A, B, X[5], 11); B = R3(B, C, D, A, X[13], 15);
        # A = R3(A, B, C, D, X[3], 3); D = R3(D, A, B, C, X[11], 9); C = R3(C, D, A, B, X[7], 11); B = R3(B, C, D, A, X[15], 15);
    
        A = (A + AA) % (2**32)
        B = (B + BB) % (2**32)
        C = (C + CC) % (2**32)
        D = (D + DD) % (2**32)

    if fl: return ''.join(splitByElements(hex(A)[2:],2)[::-1])
    return ''.join(splitByElements(hex(A)[2:],2)[::-1]) + ''.join(splitByElements(hex(B)[2:],2)[::-1]) + ''.join(splitByElements(hex(C)[2:],2)[::-1]) + ''.join(splitByElements(hex(D)[2:],2)[::-1])

def getHash(binary,flag):
    binaryBy512 = padTo512bits(binary)
    binaryBlocks = splitByElements(binaryBy512, 512)
    hash = MD4(binaryBlocks, flag)
    return hash

def Task2(binary,k,hash1):
    binaryChange = list(binary)
    for i in range(0,k):
        binaryChange[i] = str(int(binary[i])^1)
    binaryChange = ''.join(binaryChange)
    print(f'start bin: {binary}\tmodificatuin {k} bit left: {binaryChange}')
    hash2 = getHash(binaryChange,0)
    print(f'start hash:{hash1}\tnew hash: {hash2}')
    changes = str(bin(int(hash1,16)^int(hash2,16))).count('1')
    print(f'Number of changes in hash: {changes}')

def generateString(length):
    return ''.join(random.choices(string.ascii_lowercase, k=length))

def Task3(k, L):
    hash_list=list()
    words=list()
    word=generateString(L)
    start = time.time()
    hash=hex(int(bin(int(getHash(stringToBinary(word),1),base=16))[2:k+2],2))[2:]
    while True :
        if hash in hash_list and word not in words:
            break
        hash_list.append(hash)       
        words.append(word)
        word=generateString(L)
        hash=hex(int(bin(int(getHash(stringToBinary(word),1),base=16))[2:k+2],2))[2:]
    for i in range(len(hash_list)):
        if hash==hash_list[i]:
            collision_hash=hash_list[i]
            collision_word=words[i]
            break
    print (f'M = {word}\tM\' = {collision_word}')
    print (f'h = {hash}\th\' = {collision_hash}')
    print(f"count str= {len(words)}")
    print(f'time: {time.time()-start}')

def Task4(password, k):
    #  password=input('pass M: ')
    #  k=int(input('k= '))
     hash_pass=hex(int(bin(int(getHash(stringToBinary(password),1),16))[2:k+2],2))[2:]
     print(f'hash M: {hash_pass}')
     kol=0
     while True:
        word=generateString(len(password))
        hash=hex(int(bin(int(getHash(stringToBinary(word),1),16))[2:k+2],2))[2:]
        kol += 1
        if hash == hash_pass and password != word:
            print(f"M`: {word}\nhash: {hash}")
            print(f"number of attempts: {kol}")
            break

if __name__ == '__main__':
    task = (int(input("task = ")))
    if (task == 1):
        binary = stringToBinary(input('input str: '))
        hash = getHash(binary,0)
        print(f'hash: {hash}')
    elif (task == 2):
        # binary = stringToBinary(input('input str: '))
        binary = stringToBinary('donpython')
        hash = getHash(binary,0)
        for i in range(24):
            i+=1
        # count_sym = int(input('count add 1: '))
            print(i)
            Task2(binary, i ,hash)
    elif (task == 3):
        for i in range(32):
            i+=1
            print(i)
            Task3(i, 48)
    elif (task == 4):
        password = 'Say the password and come in'
        for i in range(24):
            i += 1
            Task4(password, i)
    elif (task == 6):
        L = int(input('L='))
        w = generateString(L)
        b = stringToBinary(w)
        start = time.time()
        hash = getHash(b,0)
        stop = time.time()
        print(f'h: {hash}')
        print(f'time: {stop - start}')
