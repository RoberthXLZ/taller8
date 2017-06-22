#include <stdio.h>    // Standard input/output definitions
#include <stdlib.h>
#include <string.h>   // String function definitions
#include <unistd.h>   // para usleep()
#include <getopt.h>
#include <math.h>

#include "arduino-serial-lib.h"

float calculateSD(float data[]);

void error(char* msg)
{
    fprintf(stderr, "%s\n",msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	int fd = -1;
	int baudrate = 9600;  // default
	int contador=1;
	char temp='t', hum='h';
	char* humedad=&hum;
	char* temperatura=&temp;
	char buffer[3];
	float artemp[12];
	float arhum[12];
	float mt;
	float mh;

	fd = serialport_init("/dev/ttyACM1", baudrate);

	if( fd==-1 )
	{
		error("couldn't open port");
		return -1;
	}

	serialport_flush(fd);

	while(1){
		write(fd,temperatura,1);
		usleep(5000000);
		read(fd,buffer,1);
		artemp[contador]=buffer[0];
		printf("Temperatura: %d\n",buffer[0]);

		write(fd, humedad, 1);
		usleep(5000000);
		read(fd, buffer, 1);
		arhum[contador]=buffer[0];
		printf("Humedad : %d\n", buffer[0]);

		if(contador==12){
			mt=calculateSD(temp);
			mh=calculateSD(hum);

			printf("Temperatura Media : %.3f y su desviacion es: %.3f\n" ,mt, pow(mt,2));
			printf("Humedad Media: %.3f y su desviacion es: %.3f\n" ,mh, pow(mh,2));
			counter=-1;
		}
		contador++;

	}
	
	
	close( fd );
	return 0;	
}

/* Ejemplo para calcular desviacion estandar y media */
float calculateSD(float data[])
{
    float sum = 0.0, mean, standardDeviation = 0.0;

    int i;

    for(i = 0; i < 10; ++i)
    {
        sum += data[i];
    }

    mean = sum/10;

    for(i = 0; i < 10; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation / 10);
}

/*
float promedio(float data[]){
	int cont=0, media=0,suma=0  ;	
	while(data.lengt){
		suma=suma+data[i];
		cont=cont+1;		
	}	
	return 
}*/
