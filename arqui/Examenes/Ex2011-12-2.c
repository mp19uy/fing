*=============*
|Codigo PASCAL|
*=============*

function mcCarthy(Integer n): Integer;
begin
	if (n <= 100)
 		mcCarthy := mcCarthy( mcCarthy(n+11))
 	else
 		mcCarthy := n – 10;
end

*===========*
|Codigo 8086|
*===========*

mcCarthy proc
	push BP ; respaldar registros y ajustar BP para acceder a al stack 
	mov BP, SP
	push AX

	mov AX, [BP+4] ; cargar AX con el parametro n
	cmp AX, 100
	ja else
	add AX, 11 ; calcular n+11
	push AX ; coloco el parametro para la llamada 
	call mcCarthy ; calcular M(n+11) dejando en el
	call mcCarthy ; calcular M(M(n+11)
	pop AX ; obtener el resultado del stack
	jmp fin
else:
	sub AX, 10
fin:
	mov [BP+4], AX ; colocar resultado en el stack en lugar del parametro de entrada
	pop AX ; restaurar registros
	pop BP
	ret ; retorno
endp