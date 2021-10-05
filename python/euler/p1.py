def sum_3not5 (below):
	result = 0
	for n in range(0,below,3):
		if n % 5:
			result = result+n
	return result

def sum_5 (below):
	result = 0
	for n in range(0,below,5):
			result = result+n
	return result

p = sum_3not5(1000)
p = p + sum_5(1000)
print p
