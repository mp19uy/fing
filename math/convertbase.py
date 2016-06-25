# EN: Converts a number from base 10 to base X
# ES: Convierte un numero de base 10 a base X 

def base10toBaseX(num, base):
	alphabet = [0,1,2,3,4,5,6,7,8,9,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']
	result = []
	
	while (num > 0 ):
		rest = num % base
		num = num // base
		result.append(alphabet[rest])
	result.reverse()
	print(result,"base",base)
num = 1
while (num > 0):
	num = int(input('Numero a convertir: '))
	base = int(input('en base: '))
	base10toBaseX(num,base)
