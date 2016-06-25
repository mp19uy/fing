# EN: Extended Euclidean algorithm
# ES: Algoritmo de Euclides extendido

def multiply_2x2(m1, m2):
	m3 = [[0,0],[0,0]]
	for i in range(2):
		for j in range(2):
			m3[i][j] = (m1[i][0]*m2[0][j]) + (m1[i][1]*m2[1][j])
	return m3

def info(a,b,q,m): # prints info about te process
	print("a= ",a)
	print("b= ",b)
	print("q= ",q)
	print(m)
	print("---------------------------")

def extended_euclidean(a, b):
	A = a
	B = b
	m = [[1,0],[0,1]]
	info(a,b,"no value yet","")
	
	while b > 0:
		q = a//b
		tmp = b
		b = a%b
		a = tmp
		m = multiply_2x2([[0,1],[1,-q]],m)
		info(a,b,q,m)
	
	print("mcd("+str(A)+","+str(B)+")"+" = ("+str(m[0][0])+")*("+str(A)+") + ("+str(m[0][1])+")*("+str(B)+") = "+str(a))


a = int(input('Ingrese a: '))
b = int(input('Ingrese b: '))

extended_euclidean(a,b)