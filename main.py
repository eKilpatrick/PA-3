import random
import math

def LinearBackoff(N):
    totalSlots = 0
    win_size = 2
    remaining_devices = N

    while remaining_devices != 0:
        randList = [0] * win_size
        for i in range(0,remaining_devices):
            randNum = random.randint(0,win_size-1)
            randList[randNum] += 1

        lastSlot = 0
        for i in range(0,win_size):
            if randList[i] == 1:
                remaining_devices -= 1
                lastSlot = i
        if remaining_devices == 0:
            totalSlots += lastSlot
        else:
            totalSlots += win_size

        win_size += 1
    return totalSlots

def BinaryBackoff(N):
    totalSlots = 0
    win_size = 2
    remaining_devices = N

    while remaining_devices != 0:
        randList = [0] * win_size
        for i in range(0,remaining_devices):
            randNum = random.randint(0,win_size-1)
            randList[randNum] += 1
        
        lastSlot = 0
        for i in range(0,win_size):
            if randList[i] == 1:
                remaining_devices -= 1
                lastSlot = i
        if remaining_devices == 0:
            totalSlots += lastSlot
        else:
            totalSlots += win_size
        
        win_size = win_size * 2
    return totalSlots

def LogLogBackoff(N):
    totalSlots = 0
    win_size = 4
    remaining_devices = N

    while remaining_devices != 0:
        randList = [0] * win_size
        for i in range(0,remaining_devices):
            randNum = random.randint(0,win_size-1)
            randList[randNum] += 1
        
        lastSlot = 0
        for i in range(0,win_size):
            if randList[i] == 1:
                remaining_devices -= 1
                lastSlot = i
        if remaining_devices == 0:
            totalSlots += lastSlot
        else:
            totalSlots += win_size
        
        win_size = math.floor((1 + 1/(math.log2(math.log2(win_size)))) * win_size)
    return totalSlots

def main():
    with open('linearyLatency.txt', 'w') as linFile, open('binaryLatency.txt', 'w') as binFile, open('loglogLatency.txt', 'w') as logFile:
        for num_devices in range(100, 6100, 100):
            print('Running Test for N: ', num_devices)
            sumLinear = 0
            sumBinary = 0
            sumLogLog = 0
            for i in range(0,10):
                sumLinear += LinearBackoff(num_devices)
                sumBinary += BinaryBackoff(num_devices)
                sumLogLog += LogLogBackoff(num_devices)
            avgLinear = sumLinear / 10
            avgBinary = sumBinary / 10
            avgLogLog = sumLogLog / 10
            linFile.write(str(avgLinear))
            linFile.write('\n')
            binFile.write(str(avgBinary))
            binFile.write('\n')
            logFile.write(str(avgLogLog))
            logFile.write('\n')
        
    
        
if __name__=='__main__':
    main()