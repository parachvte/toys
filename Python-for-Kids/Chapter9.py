print '#1 mystery code'

a = abs(10) + abs(-10)
print a
b = abs(-10) + -10
print b
# a = 20 b = 0

print '#2 a hidden message'
string = 'this if is you not are a reading very this good then way you to have\
hide done a it message wrong'
odd = 1
for i in string.split():
    if odd == 1: print i,
    odd ^= 1
print

print '#3 copy a file'
# basic usage of 'open', 'write', 'read', 'close'
