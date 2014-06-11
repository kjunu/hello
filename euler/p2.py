def fib2(below):
	a, b = 0, 1
	result = []
	while a < below:
		if not a % 2:
			result.append(a)
		a, b = b , a+b
	return result

print sum(fib2(4000000))
