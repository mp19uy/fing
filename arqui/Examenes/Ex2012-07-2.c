#define TRUE 1
#define FALSE 0

int hayMoneda;

void interrupt moneda() {
	if (hayMoneda) out(EXPULSAR, 0x00); // solo una moneda
	else hayMoneda = TRUE;
}

void interrupt figuras() {
	cuenta--;
}

void main() {
	int cuenta;
	//instalo interrupciones

	enable();

	while(TRUE) {
		hayMoneda = FALSE;
		while !(hayMoneda); // espero moneda
		while ((in(PALANCA) && 0x01) == 0); // espero accionen la palanca
		out(RUEDAS, 0x00); // ruedas girando
		cuenta = random();
		while (cuenta > 0);
		out (FRENOS, 0x01); // freno rueda derecha
		cuenta = random();
		while (cuenta > 0);
		out (FRENOS, 0x03); // freno rueda del medio
		cuenta = random();
		while (cuenta > 0);
		out (FRENOS, 0x07); // freno rueda izquierda
		pagar(); // verifico y pago si gana
	}