proc sumaMatrices 
	xor DX, DX // DX = 0 

inicioForArreglo: 
	cmp DX, CANT_MATRICES 
	je fin 
	mov BX, DX
	mov CL, 5
	shl BX, CL
	xor AX, AX // AX = 0, AX acumulador 
	xor CX, CX // CX = 0, CX contador 
	add BX, MATRICES 

inicioForMatriz: 
	cmp CX, 16 
	je finForMatriz 
	mov SI, CX 
	shl SI, 1 
	add AX, ES:[BX+SI] 
	inc CX 
	jmp inicioForMatriz 

finForMatriz: 
	mov BX, PESOS_MATRICES 
	mov SI, DX 
	shl SI, 1 
	mov [BX+SI], AX 
	inc DX 
	jmp inicioForArreglo
fin:
	ret