# ProjectEuler
# problem 100: Arranged probability
# See solution here: http://www.mathblog.dk/project-euler-100-blue-discs-two-blue/
__Author = 'Ryannnnnnn'

blue, total = 15, 21
while total < 10**12:
    blue, total = 3 * blue + 2 * total - 2, 4 * blue + 3 * total - 3
print blue
