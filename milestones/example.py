# example.py by Amen Abreha
# 10/22/2026
# Creates an r by c board, r and c are from user input
# This is mostly to get a feel for Python, this is my first Python program

r = int(input())
c = int(input())
print('  ', end='')
for i in range(1, r+1):
    print(i, end=' ')
print('\n', end='')
for i in range(c):
    print(i+1, end=' ')
    for i in range(r):
        print('-', end=' ')
    print('\n', end='')
