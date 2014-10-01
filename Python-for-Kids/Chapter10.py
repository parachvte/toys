''' Chapter10. useful python modules
1.turtle
2.copy/deepcopy
3.keyword
4.random(randin(), choice(), shuffle())
5.sys(stdin, stdout, exit())
6.time(time(), asctime(), localtime(), sleep())
7.pickle(dump(data, file), load(file))
'''

print '#1: copied cars'

import copy
class Car:
    pass
car1 = Car()
car1.wheels = 4
car2 = car1
car2.wheels = 3
print(car1.wheels)
car3 = copy.copy(car1)
car3.wheels = 6
print(car1.wheels)
# 3 and 3
raw_input()

print '#2 pickled favorites'

import pickle
favorites = ['reading', 'guitar', 'coding', 'music']
save_file = open('favorites.dat', 'wb')
pickle.dump(favorites, save_file)
save_file.close()

save_file = open('favorites.dat', 'rb')
favorites2 = pickle.load(save_file)
print favorites2
