
/*  Proyecto de inicio PulseSensor y probador de señal.
 *  The Best Way to Get Started  With, or See the Raw Signal of, your PulseSensor.com™ & Arduino.
 *
 *  Here is a link to the tutorial
 *  https://pulsesensor.com/pages/code-and-guide
 *
 *  WATCH ME (Tutorial Video):
 *  https://www.youtube.com/watch?v=RbB8NSRa5X4
 *
 *
-------------------------------------------------------------
1) Esto muestra un pulso humano en vivo.
2) Visualización en vivo en el "Trazador de serie" de Arduino.
3) Parpadea un LED en cada latido.
4) Esta es la señal directa del sensor de pulso.
5) Un excelente primer paso para solucionar problemas de su circuito y conexiones.
6) Código "legible para humanos" que sea amigable para los novatos ".

*/


//  Variables
int PulseSensorPurplePin = 0;         // Sensor de pulso ALAMBRE MARRON conectado a ANALOG PIN 0
int LED13 = 13;                       // El Arduion a bordo LED


int Senial;                // contiene los datos sin procesar entrantes. El valor de la señal puede variar de 0-1024
int Threshold = 550;       // Determine qué señal debe "contar como un latido" y cuál debe realizar.


// The SetUp Function:
void setup() {
  pinMode(LED13,OUTPUT);         // pin que parpadeará a los latidos de tu corazón!
  Serial.begin(9600);            // Configurar la comunicación serial a cierta velocidad.

}

// The Main Loop Function
void loop() {

  Senial = analogRead(PulseSensorPurplePin);  // Lea el valor del PulseSensor.
                                              // Asigne este valor a la variable "Señal".

   Serial.println(Senial);                    // Envíe el valor de la señal al trazador de serie.


   if(Senial > Threshold){                    // Si la señal está por encima de "550", entonces "encienda" el LED integrado de Arduino.
     digitalWrite(LED13,HIGH);
   } else {
     digitalWrite(LED13,LOW);                 //  De lo contrario, la señal debe estar por debajo de "550", así que "apague" este LED.
   }


delay(10);


}
