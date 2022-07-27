#include <avr/io.h>
#include <avr/interrupt.h>

int NUM[] = {63,6,91,79,102,109,125,7,127,103}; //números de 0 a 9 que serão mostrados no display
unsigned char memoria = 0; //váriavel auxiliar de memória do tempo inicializada em 0
int cont = 0; //variável contadora

ISR(TIMER0_OVF_vect){
	
	TCNT0 = 12; //garante de a interrupção por estouro do timer irá ocorrer a cada 250ms
	memoria++; //toda vez que a interrupção por estouro do timer ocorrer a cada 2050ms a variável auxiliar de memória do tempo irá iniciar a contagem
	
	if(memoria==4){ //as instruções ocorrem somente na borda de subida 
		memoria=0; //toda vez que a borda de subida é detectada a contagem da variável auxiliar de memória do tempo recomeça
		cont++; //variável contadora incrementada a cada borda de subida
		if(cont>9) cont=0; //quando a variável contadora for maior que 9 ela é zerada novamente
		  PORTB = NUM[cont]; //quando a variável contadora é zerada o display recebe o valor definido pelo vetor na sua posição, que começa em 0
	}
}


int main(void)
{
	DDRB = 0b11111111; //define a porta B como saída
	TCCR0 = 0b00000101; //habilita prescaler de 1024
	TCNT0 = 12; //inicia a contagem em 12 (250ms para ocorrer a chamada da interrupção por estouro do timer 0)
	TIMSK |= 1; //habilita a interrupção do timer 0
	sei(); //habilita as interrupções gerais
	
	PORTB = NUM[cont]; //começa a contagem de 0
	
    while (1) {}
	
}

