# define ESTADO_ESPERO_BOTON_TICKET 0
# define ESTADO_ESPERO_CIERRE_CASILLERO_BOTON 1
# define ESTADO_ERROR_SIN_CASILLEROS 2
# define ESTADO_ESPERO_CIERRE_CASILLERO_TICKET 3

# define CUARENTA_Y_CINCO_SEGUNDOS 2250
# define CINCO_SEGUNDOS 250

# define APERTURA_CASILLEROS ...
# define ESTADO_CASILLEROS ...
# define PANEL ...
# define TICKET ...

# define MASK_PITIDO 1
# define MASK_LED 2

int estado;
int hayBoton;
int casilleroAbriendo;
int enAlarma;
unsigned short codigoTicket;

struct casillero{
	char libre;
	unsigned short codigoApertura;
};

casillero[16] casilleros;

void main(){

	estado = 0;
	hayBoton = 0;
	hayTicket = 0;
	enAlarma = 0;
	for (int j = 0; j < 16; j++){
		casilleros.libre = 1;
	}

	// instalo interrupciones
	enable();

	while(1){
		switch(estado){
			case ESTADO_ESPERO_BOTON_TICKET:
				if (hayBoton){
					hayBoton = 0;
					// presionaron el boton, me fijo si hay locker libre
					int j;
					for (j = 0; j < 16; j++){
						if (casilleros[j].libre) break;
					}
					if (j == 16){ // No hay casilleros libres, doy error
						OUT(PANEL, MASK_LED);
						estado = ESTADO_ERROR_SIN_CASILLEROS;
						contando = 0;
						tics = 0;
					}else{ // El casillero j está libre, lo uso
						casilleroAbriendo = j;
						casilleros[j].libre = 0;
						OUT(APERTURA_CASILLEROS, 1 << j); // abro el casillero
						contando = true;
						tics = 0;
						estado = ESTADO_ESPERO_CIERRE_CASILLERO_BOTON;
					}
				}else if (hayTicket){
					hayTicket = 0;
					// Busco el codigo correspondiente para saber cuál abrir
					int j;
					for (j = 0; j < 16; j++){
						if ((casilleros[j].codigoApertura == codigoTicket)
									&& casilleros[j].libre == 0){
							casilleroAbriendo = j;
							break;
						}
					} 
					// Abro el casillero y lo marco como libre
					casilleros[j].libre = 1;
					OUT(APERTURA_CASILLEROS, 1 << j); // abro el casillero
					contando = true;
					tics = 0;
					estado = ESTADO_ESPERO_CIERRE_CASILLERO_TICKET;
				}
				break;
			
			case ESTADO_ESPERO_CIERRE_CASILLERO_BOTON:
			case ESTADO_ESPERO_CIERRE_CASILLERO_TICKET:
				short estado = IN(ESTADO_CASILLEROS);
				if (!(estado & (1 << casilleroAbriendo))){ 
					estado = ESTADO_ESPERO_BOTON_TICKET;
					contado = false;
					if (enAlarma){ // Si activé la alarma, la apago
						OUT(PANEL, 0);
						enAlarma = 0;
					}
					if (estado == ESTADO_ESPERO_CIERRE_CASILLERO_BOTON){
						// Si el casillero se abrió por botón imprimo el 
						// ticket
						unsinged short rand = random();
						OUT(TICKET, rand);
						casilleros[casilleroAbriendo].codigoApertura = rand;
					}
				}else if (tics > CUARENTA_Y_CINCO_SEGUNDOS){
					OUT(PANEL, MASK_PITIDO | MASK_LED);
					contando = 0;
					tics = 0;
					enAlarma = 1;
				}
				break;
			
			case ESTADO_ERROR_SIN_CASILLEROS:
				if (tics > CINCO_SEGUNDOS){
					OUT(PANEL, 0);
					contando = 0;
					tics = 0;
					estado = ESTADO_ESPERO_BOTON_TICKET;
				}
				break;
		}
	}
}

void interrupt timer(){
	if (contando){
		tics++;
	}
}

void interrupt boton(){
	hayBoton = 1;
}

void interrupt ticket(){
	hayTicket = 1;
	codigoTicket = IN(TICKET);
}

