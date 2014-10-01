'''#1 are you rich?'''
money = 2000
if money > 1000:
	print 'I\'m rich!'
else:
	print 'I\'m not rich!'
	print 'But I might be later...'
# spaces/tabs not match
raw_input()

'''#2 twinkies'''
num = int(raw_input('input a integer number:'))
if num < 100 or num > 500:
	print 'Too few or too many'
raw_input()

'''#3just the right number'''
num = int(raw_input('input a integer number:'))
if 100 < num < 500:
	print 'Between 100 and 500'
elif 1000 < num < 5000:
	print 'Between 1000 and 5000'
else:
	print 'out of control'
raw_input()

'''#4 I can fight those ninjas'''
num = int(raw_input('input number of ninja:'))
if num < 10:
        print 'I can fight those ninjas!'
elif num < 30:
	print 'It\'ll be a struggle, but I can take emm'
else:
	print 'That\'s too many!'
raw_input()
