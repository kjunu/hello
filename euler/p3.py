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
			j = i
			#print "index:",i
		i+=j
	return n/j

print largest_prime_factor(600851475143)
print largest_prime_factor(13195)
print largest_prime_factor(29)
print largest_prime_factor(30)
