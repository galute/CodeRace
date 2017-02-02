import time

numbers = []

def reverseLine(line):
    i = len(line)
    cardNumber = []
    i -= 1
    while i > 0:
        value = line[i - 1]
        asInt = int(value)
        i -= 1
        cardNumber.append(asInt)
    
    numbers.append(cardNumber)

def processNumbers():
    for number in numbers:
        oddAcc = 0
        evenAcc = 0
        idx = 0
        while idx < 16:
            digit = number[idx]
            if idx%2 is 0:
                oddAcc += digit
            else:
                evenNum = digit * 2
                if evenNum > 9:
                    evenNum -= 10
                evenAcc += evenNum
            idx += 1

        totalAcc = oddAcc + evenAcc

        if totalAcc%10 is 0:
            print('Success')
        else:
            print('Fail')



tstart = time.time()

f = open('./temp.txt', 'r')

for line in f:
    reverseLine(line)

processNumbers()

f.close()
tend = time.time()
elapsed = tend - tstart
print(elapsed)

