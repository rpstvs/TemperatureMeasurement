#include <c8051f340.h>


#define RS P3_1
#define E P3_3
#define LCD P1
#define RW P3_2 



void configDevice(void);
void escreveTempLCD(void);
void numeroASCII_total(void);
void configLCD(void);
void pulsaEnable(void);
char unidadesASCII(char numero);
char dezenasASCII(char numero);
void configTimer(void);
void convADC(void);
char centenasASCII(char numero);

unsigned char temp = 0;
unsigned int ponto = 46;
unsigned char dist_dec=' ';
unsigned char temp_d=' ';
unsigned char temp_u=' ';
float temperature = 0;



	
void main(void){
	SP=0x60; 
	configDevice();
	configTimer();
	configLCD();
	while(1){
	AD0BUSY = 1;
	while(AD0INT == 0);
	convADC();
	numeroASCII_total();
	escreveTempLCD();
	
	}

}




void configTimer(void){
	TMOD=0b00010010; 
	

}

char centenasASCII(char numero)
{
	char valor;
	char divisao;
	divisao=numero/100;
	valor=divisao+'0';
	return valor;
}


char dezenasASCII(char numero)
{
	char valor;
	char divisao;
	divisao=numero/10;
	valor=divisao+'0';
	return valor;
}

char unidadesASCII(char numero)
{
	char valor;
	char resto;
	resto=numero%10;
	valor=resto+'0';
	return valor;
}
void escreveValorLCD(char valor,char tipoDado)
{
	RW=0;
	RS=tipoDado;
	LCD=valor;
	pulsaEnable();
}


void convADC(void){
	temp = ADC0H << 8;
	temp |= ADC0L;
	temperature = (temp * 3.3 / 1024.0) - 0.5;
        temperature = temperature / 0.01;

}


void pulsaEnable(void)
{
	unsigned int i; 
	E=1;
	for(i=0;i<10;i++); 
	E=0;
	for(i=0;i<3000;i++); 
}

void configLCD(void)
{
	escreveValorLCD(0b00111000,0);
	escreveValorLCD(0b00001100,0);
	escreveValorLCD(0b00000001,0);
	escreveValorLCD(0b00000110,0);
	escreveValorLCD(0b10000000,0);
}

void numeroASCII_total(void)
{
	temp_d=dezenasASCII(temperature);
	temp_u=unidadesASCII(temperature);
}
	
void escreveTempLCD(void)
{
	escreveValorLCD(0b10000100,0);
	escreveValorLCD(temp_d,1);
	escreveValorLCD(temp_u,1);
	escreveValorLCD('C',1);
	
	
}

void configDevice(void)
{
	P3MDIN = 0xEF; 
	P3MDOUT = 0xE0; 
	XBR1 = 0x40; 
	REF0CN = 0x08; 
	AMX0P = 0x08; 
	AMX0N = 0x1F; 
	ADC0CN = 0x80; 
	OSCICN = 0x83; 
	XBR0 = 0x01; 
	PCA0MD&= 0xBF; 
	PCA0MD = 0x00; 
}


