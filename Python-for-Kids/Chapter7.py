'''#1 basic moon weight function'''
def moon_weight(weight, add):
    for i in range(15):
        weight += add
    print 'your weight on moon after 15 years is %s' % (weight * 0.165)
moon_weight(30, 0.25)
raw_input()

'''#2 moon weight function and years'''
def moon_weight(weight, add, year):
    for i in range(year):
        weight += add
    print 'your weight on moon after %s years is %s' % (year, weight * 0.165)
moon_weight(90, 0.25, 5)
raw_input()

'''#3 moon weight program'''
def moon_weight(weight, add, year):
    for i in range(year):
        weight += add
    print 'your weight on moon after %s years is %s' % (year, weight * 0.165)
weight = int(raw_input('Please enter your current Earth weight: '))
add = int(raw_input('Please enter the amount your weight might increase each year: '))
year = int(raw_input('Please enter the number of years: '))
moon_weight(weight, add, year)
raw_input()
raw_input()
