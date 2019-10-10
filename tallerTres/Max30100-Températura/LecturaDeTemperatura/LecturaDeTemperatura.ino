#include <Wire.h>
#include "MAX30100.h"
#include "enviar_recibir_i2c.h"
 
#define INTERVALO_LECTURAS 1000
#define CANTIDAD_LECTURAS_MEDIA 10
#define PIN_INTERRUPCION 7 /* Usando una placa Arduino Leonardo */
 
byte max30100_buffer[4]; /* Una operación de lectura del MAX30100 devuelve como máximo 4 bytes (dos enteros de 16 bits) */
bool interrupcion_activa=false;
float temperatura_actual;
float temperatura_media;
float temperatura_total=0;
unsigned int cantidad_lecturas=1; /* Empieza en la lectura número 1 e incrementa después de calcular la media */
unsigned long cronometro;
 
void setup()
{
  pinMode(PIN_INTERRUPCION,INPUT_PULLUP);
  Wire.begin();
  enviar_i2c(MAX30100_DIRECCION,MAX30100_INTERRUPCION_ACTIVA,MAX30100_TEMPERATURA_LISTA);
  Serial.begin(9600);
  while(!Serial); /* Usando una placa Arduino Leonardo */
  cronometro=millis();
}
 
void loop()
{
  if((unsigned long)(millis()-cronometro)>INTERVALO_LECTURAS)
  {
    cronometro=millis();
    attachInterrupt(digitalPinToInterrupt(PIN_INTERRUPCION),leer_temperatura,LOW);
    enviar_i2c(MAX30100_DIRECCION,MAX30100_CONFIGURACION_MODO,MAX30100_TEMPERATURA_ACTIVAR);
  }
  if(interrupcion_activa)
  {
    interrupcion_activa=false;
    recibir_i2c(MAX30100_DIRECCION,MAX30100_INTERRUPCION_ESTADO,1,max30100_buffer); /* Leer la interrupción (además) la desactiva */
    if
    (
      max30100_buffer[0]&MAX30100_TEMPERATURA_LISTA &&  /* La interrupción has sido producida por el fin de la ADC de la temperatura */
      recibir_i2c(MAX30100_DIRECCION,MAX30100_TEMPERATURA,2,max30100_buffer) /* Se han recibido correctamente los datos del MAX30100 */
    )
    {
      temperatura_actual=max30100_buffer[0]+(float)max30100_buffer[1]/16.0; /* Parte entera más dieciseisavos de grado */
      temperatura_total+=temperatura_actual;
      temperatura_media=temperatura_total/cantidad_lecturas++;
      if(cantidad_lecturas>CANTIDAD_LECTURAS_MEDIA)
      {
        Serial.println("La temperatura del MAX30100 es de "+String(temperatura_media,DEC)+" °C");
        cantidad_lecturas=1;
        temperatura_total=0;
      }
    }
  }
}
 
void leer_temperatura()
{
  detachInterrupt(digitalPinToInterrupt(PIN_INTERRUPCION)); 
  interrupcion_activa=true;
}
