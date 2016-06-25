# EN: Factorization of a number
# ES: Descomposicion factorial de un numero

# Here's a list of algorithms to factor numbers: 
# https://en.wikipedia.org/wiki/Integer_factorization#Factoring_algorithms
# 
# Solution #1 - uses trial division
import math

n = int(input('Ingrese n: '))
o = int(input('Minimo[0] o Máximo[1]?: '))
i = 2
if (o == 1):
    while i*i < n:
       while n % i == 0:
          n = n / i
       i=i+1
    print(n)

else:
    found = False
    while (i < n**2) or (not found):
        if n % i == 0:
            print(i)
            found = True
        i=i+1

