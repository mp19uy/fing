#define TIMER_FREC ...
#define C 344
#define MAX_DIST 8
#define TICS_MAX_DIST 2 * MAX_DIST * TIMER_FREC / C

boolean readingDistance = false;
int tics = 0; 

int getDistance() {
	int result;

	out(PING,128); // genero onda en el MUS
	tics = 0; // inicializo contador de tiempo transcurrido
	readingDistance = true; // le “aviso” al timer que cuente
	while (readingDistance); // espero a que la onda regrese o timeOut
		if (tics > TICS_MAX_DIST)
			result = -1; // no recibi eco
		else
			result = 1000 * C * tics / TIMER_FREC / 2; // calculo la distancia en mm por fórmula
	
return result;
} // fin metodo getDistance

void timer() {
	if (readingDistance) {
		tics ++;
		if ((in(ECHO) & 0x80) || (tics > TICS_MAX_DIST))
			readingDistance = false;
	}

} // fin del manejador de interrupciones