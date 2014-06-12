def factorial(number):
	i = 1
	n = 1
	while i <= number:
		n*=i
		i+=1
	return n

def largest_factor(n):
	i = 2
	while i < n:
		if not n % i:
			ret = i
#print ret
			return n/ret
		i+=1
	return n 

def is_prime(n):
	if largest_factor(n) == n:
		return 1
	else:
		return 0

def smallest_multiple(number):
	
	i = number*(number-1)

	while i <= factorial(number):
		
		j = 2
		while j <= number:
			if i % j:
				break
			j+=1

		if j == number+1 :
			return i
		
		i+=1

	return i

def get_prime(number):
	
	prime = []
	i = 2
	while i <= number:
		if is_prime(i):
			prime.append(i)
		i+=1
	i = 2
	
	return prime

def can_div(number, div):
	if number % div:
		return 0
	else :
		return 1 + can_div(number/div, div)

def smallest_multiple2(number):
	prime =	get_prime(number)
	d = {1:1}
	for i in  prime :
		d[i] = 0

	j = 2
	while j <= number:
		for i in  prime :
			temp = can_div(j, i)
			if temp  > d[i]:
				d[i] = temp
		j+=1	

	print d
	result = 1
	for i in  prime :
		j=0
		while j < d[i]:
			result *= i
			j+=1
	
	return result 

print factorial(3)
print smallest_multiple(6)
print "7:",is_prime(7)
print "8:",is_prime(8)
print "18:",is_prime(18)
print "19:",is_prime(19)
print get_prime(20)

print smallest_multiple2(20)
	
