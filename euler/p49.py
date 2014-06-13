from prime import get_prime

def digit_filter(number, digit):
	result = []

	for n in number:
		if len(str(n))>=digit:
			result.append(n)	
	
	return	result 
def has_same_number(number1, number2):
	num1 = str(number1)
	num2 = str(number2)
#	print num1,num2
	for n in num1:
		if num1.count(n) != num2.count(n):
			return 0
		else: 
			continue
	return 1
		

def has_diff_number(number):

	num = str(number)
	for n in num:
		if num.count(n) > 2:
			return 0
		else: 
			continue
	return 1

def prime_permutations(digit):
	candidate = digit_filter(get_prime(pow(10,digit)-1), digit)
	
	i = 0
	do_nothing = 0
	while i < len(candidate):
		j = i
		while j < len(candidate):
			diff = []	
			diff.append(candidate[j]-candidate[i])
			
			if not has_diff_number(candidate[i]):
				j+=1
				continue
			elif diff[0] == 0:
				j+=1
				continue
			
			if not has_same_number(candidate[i],candidate[j]):
				j+=1
				continue
#			elif not digit_filter(diff,digit-1):
#				j+=1
#				continue
			try:
				candidate.index(candidate[i] + (diff[0] * 2))
			except ValueError:
				j+=1
				continue	
			
			if not has_same_number(candidate[i],candidate[j]+ diff[0]):
				j+=1
				continue
			
			print candidate[i],candidate[j],diff,candidate[i] + (diff[0] * 2)
			j+=1
		i+=1

#print digit_filter([9999], 4)
#print has_same_number(1234, 4321)
#print has_same_number(1234, 4991)
#print has_diff_number(1234)
#print has_diff_number(1224)
#print "prime", get_prime(9999)
print prime_permutations(4)


