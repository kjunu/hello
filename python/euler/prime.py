def largest_factor(n):
	i = 2
	while i < n:
		if not n % i:
			ret = i
			return n/ret
		i+=1
	return n 

def largest_prime_factor(n):
	i = 2
	j = 1
	while i < n:
		if not	n % i:
			j = i
		i+=j
	return n/j

def is_prime(n):
	if largest_prime_factor(n) == n:
		return 1
	else:
		return 0

def get_prime(number):
	prime = []
	i = 2
	while i <= number:
		if is_prime(i):
			prime.append(i)
		i+=1
	
	return prime

#print "prime", get_prime(9999)
