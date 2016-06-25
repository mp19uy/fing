*===========*
|Codigo en C|
*===========*

void cambiar_luces(unsigned char color, short cantidad_oficinas, unsigned char* lista_oficinas){
	for(short i = 0; i< cantidad_oficinas; i++){
		out(033h, (lista_oficinas[i] << 8 | color));
	}
}

*===========*
|Codigo 8086|
*===========*

Ejemplo invocación:

mov AL, color
push color
push cantidad_oficinas
call cambiar_luces
----------------
----------------

Codigo de cambiar_luces:

cambiar_luces PROC
	push BP
	mov BP, SP
	push AX
	push BX
	push CX
	push SI
	mov BX, [BP+4]
	mov CX, [BP+6]
	; Se ubica el IP para el retorno
	mov SI, [BP+2]
	mov [BP+6], SI
	
	mov SI, 0
	
for:
	cmp CX, SI
	je fin

	mov AH, [BX+SI]
	; El color ya está en AL
	out 033h, AX
	add SI, 1
	jmp for

fin:
	pop SI
	pop CX
	pop BX
	pop AX
	pop BP
	; Se descarta el parámetro adicional y se deja a SP apuntando a IP para el retorno
	add SP, 4

	ret
cambiar_luces ENDP