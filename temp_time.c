#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

#define MAX_TIME 85
#define DHT11PIN 7
int dht11_val[5]={0,0,0,0,0};


void dht11_read_val(char *argx[])
{ FILE *f = fopen(argx[1], "a+");
  
  time_t ltime; /* calendar time */
  ltime=time(NULL); /* get current cal time */
  
  uint8_t lststate=HIGH;
  uint8_t counter=0;
  uint8_t j=0,i;
  float farenheit;
  for(i=0;i<5;i++)
    dht11_val[i]=0;
  pinMode(DHT11PIN,OUTPUT);
  digitalWrite(DHT11PIN,LOW);
  delay(18);
  digitalWrite(DHT11PIN,HIGH);
  delayMicroseconds(40);
  pinMode(DHT11PIN,INPUT);
  for(i=0;i<MAX_TIME;i++)
  {
    counter=0;
    while(digitalRead(DHT11PIN)==lststate){
      counter++;
      delayMicroseconds(1);
      if(counter==255)
        break;
    }
    lststate=digitalRead(DHT11PIN);
    if(counter==255)
      break;
        // top 3 transistions are ignored
    if((i>=4)&&(i%2==0)){
      dht11_val[j/8]<<=1;
      if(counter>16)
        dht11_val[j/8]|=1;
      j++;
    }
  }
      // verify cheksum and print the verified data
  if((j>=40)&&(dht11_val[4]==((dht11_val[0]+dht11_val[1]+dht11_val[2]+dht11_val[3])& 0xFF)))
  {
    farenheit=dht11_val[2]*9./5.+32;
    fprintf(f,"%d.%d,%d.%d,%s",dht11_val[0],dht11_val[1],dht11_val[2],dht11_val[3],asctime(localtime(&ltime)));
    printf("Humidity = %d.%d %% Temperature = %d.%d *C (%.1f *F) %s",dht11_val[0],dht11_val[1],dht11_val[2],dht11_val[3],farenheit,asctime(localtime(&ltime)));
    
    int temp_hatori;
    temp_hatori = dht11_val[2];
    if (temp_hatori > 23)
	{
	system("python mail.py");
	}

  }
  else
  {
    return ;
  }
 fclose(f);
}
int main ( int argc, char *argv[] )
{
	char file_name;
    if ( argc != 2 )
    {
        printf( "usage: %s filename", argv[0] );
    }
    else 
    {
		printf("Interfacing Temperature and Humidity Sensor (DHT11) With Raspberry Pi\n");
		if(wiringPiSetup()==-1)
		  {	 
		  	exit(1);
		  }
		  while(1)
		  {
		   dht11_read_val(argv);
		   delay(3000);
		  }
		 return 0;

    }
}


/*
int main(void)
{
  printf("Interfacing Temperature and Humidity Sensor (DHT11) With Raspberry Pi\n");
  if(wiringPiSetup()==-1)
    exit(1);
  while(1)
  {
   dht11_read_val();
   delay(3000);
 }
 return 0;
}
*/

