'''#1 the hello loop'''
for x in range(20):
    print 'hello %s' % x
    if x < 9: break
# only print 'hello 0'
raw_input()

'''#2 even numbers'''
age = 9
for i in range(1, age + 1, 2): print i
raw_input()

'''#3 my five favorite ingredients'''
ingredients = ['snails', 'leeches', 'gorilla belly-button lint',
               'caterpillar eyebrows', 'centipede toes']
for i in range(len(ingredients)):
    print i, ingredients[i]
raw_input()

'''#4 your weight on the moon'''
weight = 50.0
for i in range(15): weight += 1.0
print weight * 0.165
raw_input()
