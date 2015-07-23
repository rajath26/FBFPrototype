import math

k = 10
m = 6250.0

def expected_val(n, offset):
	base_prob = math.exp(-k*n/m)#(1.0 - 1.0/m)**(k*n) 
	bits = k - offset
	sum_e = 0
	for i in range(bits+1):
		sum_e += i*(1 - base_prob)**i * base_prob**(bits-i)
	return sum_e

def p_fp(n, prior):
	val = (1.0 - math.exp(-k*n/m))**(k - prior)
	return val

def p_fp_fbf3_orig(n1, n2, n3):
	val = 1 - p_fp(n1, 0) * p_fp(n2, 0)
	val *= 1 - p_fp(n2, 0) * p_fp(n3, 0)
	val *= 1 - p_fp(n3, 0)
	return 1 - val

def p_fp_fbf3_orig2(n1, n2, n3):
	val = p_fp(n1, 0) * p_fp(n2, 0)
	val += p_fp(n2, 0) * p_fp(n3, 0)
	val += p_fp(n3, 0)
	return val

def p_fp_fbf3_new(n1, n2, n3):
	val = 1 - p_fp(n1, 0)
	prior1 = expected_val(n1, 1)
	val *= 1 - p_fp(n2 - n1, prior1) * p_fp(n3 - (n2 - n1), k + prior1)
	prior2 = expected_val(n2 - n1, int(prior1))
	val *= 1 - p_fp(n3 - (n2 - n1), prior2)
	return 1 - val

print p_fp_fbf3_orig(150, 300, 150)
print p_fp_fbf3_new(150, 300, 150)
