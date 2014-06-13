def largest_factor(n):
	i = 2
	while i < n:
		if not n % i:
			ret = i
			print ret
			return n/ret
		i+=1
	return n 

def largest_prime_factor(n):
	i = 2
	j = 1
	while i < n:
		if not	n % i:
			print "match:",i,j
			j = i
		i+=j
		print "index:",i,j
	return n/j

def largest_prime_factor2(n):
	factor = 2
	last_factor = 1

	while n > 1:
		if not	n % factor:
			last_factor = factor
			n = n / factor
			while n % factor == 0:
				n = n / factor
		factor = factor + 1
	
	return last_factor

print largest_prime_factor(600851475143)
print largest_prime_factor(13195)
print largest_prime_factor(29)
print largest_prime_factor(70)
