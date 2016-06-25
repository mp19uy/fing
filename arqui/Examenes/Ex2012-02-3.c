#define TRUE 0x01
#define FALSE 0x00
#define RELAX 0x08
#define BED 0x04
#define UP 0x02
#define STOP 0x01
#define RESPALDO 0x04
#define ASIENTO 0x02
#define APOYAPIES 0x01

unsigned char hayTecla, teclaUp, teclaStop. teclaRelax, teclaBed, pasoRespaldo, pasoAsiento, pasoApoyaPies;

void interrupt tecla() {
	unsigned char leoTecla;
	
	leoTecla = in(TECLAS);
	if (hayTecla && ((leoTecla && 0x0F) == 0x00)) {
		hayTecla = FALSE;
		teclaRelax = FALSE;
		teclaBed = FALSE;
		teclaUp = FALSE;
		teclaStop = FALSE;
	}
	else {
		if (!(hayTecla)) {
			hayTecla = TRUE;
			if ((leoTecla && RELAX) == RELAX) teclaRelax = TRUE;
			else if ((leoTecla && BED) == BED) teclaBed = TRUE;
			else if ((leoTecla && UP) == UP) teclaUp = TRUE;
			else teclaStop = TRUE;
		}
	}
}

void interrupt finPaso() {
	unsigned char leoPaso;
	
	leoPaso = in(PASO_MOTOR);
	if ((leoPaso && RESPALDO) == RESPALDO) pasoRespaldo = TRUE;
	if ((leoPaso && ASIENTO) == ASIENTO) pasoAsiento = TRUE;
	if ((leoPaso && APOYAPIES) == RESPALDO) pasoApoyPies = TRUE;
}


void main() {
	unsigned char leoSensores, upActivo;

	hayTecla = FALSE;
	teclaRelax = FALSE;
	teclaBed = FALSE;
	teclaUp = FALSE;
	teclaStop = FALSE;
	pasoRespaldo = TRUE;
	pasoAsiento = TRUE;
	pasoApoyaPies = TRUE;
	upActivo = FALSE;
	out(MOTORES, 0x00);
	// instalo rutinas de interrupción
	enable();
	while (TRUE) {
		if (hayTecla) {
			if (teclaRelax) {
				upActivo = FALSE;
				while (hayTecla) {
					leoSensores = in(SENSORES);
					if ((leoSensores && 0x0F00) != 0x0900) {
						if (pasoRespaldo) {
							pasoRespaldo = FALSE;
							if ((leoSensores && 0x0F00) > 0x0900) 
								out(MOTORES, 0x20);
							else
								out(MOTORES, 0x30);
						}
					}
					if ((leoSensores && 0x00F0) != 0x0040) {
						if (pasoAsiento) {
							pasoAsiento = FALSE;
							if ((leoSensores && 0x00F0) > 0x0040) 
								out(MOTORES, 0x08);
							else
								out(MOTORES, 0x0C);
						}
					}
					if ((leoSensores && 0x000F) != 0x0009) {
						if (pasoApoyaPies) {
							pasoApoyaPies = FALSE;
							if ((leoSensores && 0x000F) > 0x0900) 
								out(MOTORES, 0x02);
							else
								out(MOTORES, 0x03);
						}
					}		
				}
			}

			if (teclaBed) {
				upActivo = FALSE;
				while (hayTecla) {
					leoSensores = in(SENSORES);
					if ((leoSensores && 0x0F00) != 0x0F00) {
						if (pasoRespaldo) {
							pasoRespaldo = FALSE;
							out(MOTORES, 0x30);
						}
					}
					if ((leoSensores && 0x00F0) != 0x00F0) {
						if (pasoAsiento) {
							pasoAsiento = FALSE;
							out(MOTORES, 0x0C);
						}
					}
					if ((leoSensores && 0x000F) != 0x000F) {
						if (pasoApoyaPies) {
							pasoApoyaPies = FALSE;
							out(MOTORES, 0x03);
						}
					}
				}
			}
			if (teclaUP) upActivo = TRUE;
			if (teclaSTOP) upActivo = FALSE;
		}

		if (upActivo) {
			leoSensores = in(SENSORES);
			if ((leoSensores && 0x0F00) != 0x0000) {
				if (pasoRespaldo) {
					pasoRespaldo = FALSE;
					out(MOTORES, 0x20);
				}
			}
			if ((leoSensores && 0x00F0) != 0x0000) {
				if (pasoAsiento) {
					pasoAsiento = FALSE;
					out(MOTORES, 0x08);
				}
			}
			if ((leoSensores && 0x000F) != 0x0000) {
				if (pasoApoyaPies) {
					pasoApoyaPies = FALSE;
					out(MOTORES, 0x02);
				}
			}
		}
	}
}