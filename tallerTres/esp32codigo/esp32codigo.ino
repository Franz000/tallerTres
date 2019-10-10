#include <WiFi.h>
#include <HTTPClient.h>


#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 1000
#define REPORTING_PERIOD_MS_1 2

const char* ssid     = "HUAWEI Mate 20 lite";
const char* password = "franz0000";

const char* serverName = "http://192.168.43.168/taller3/esp32server/data.php";
const String peticion_paciente = "http://192.168.43.168/taller3/esp32server/ob_pa.php?api=franz123456789";
String apiKey = "franz123456789";

#define pulsePin 35

volatile int BPM;               // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;            // holds the incoming raw data
volatile int IBI = 600;         // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false; // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;    // becomes true when Arduoino finds a beat.


volatile int rate[10];                    // array to hold last ten IBI values
volatile unsigned long sampleCounter = 0; // used to determine pulse timing
volatile unsigned long lastBeatTime = 0;  // used to find IBI
volatile int P = 2170;                     // used to find peak in pulse wave, seeded
volatile int T = 2170;                     // used to find trough in pulse wave, seeded
volatile int thresh = 2190;                // used to find instant moment of heart beat, seeded
volatile int amp = 100;                   // used to hold amplitude of pulse waveform, seeded
volatile boolean firstBeat = true;        // used to seed rate array so we startup with reasonable BPM
volatile boolean secondBeat = false;      // used to seed rate array so we startup with reasonable BPM

void getBPM();
// PulseOximeter is the higher level interface to the sensor
// it offers:
// * beat detection reporting
// * heart rate calculation
// * SpO2 (oxidation level) calculation
PulseOximeter pox;

uint32_t tsLastReport = 0;
uint32_t tsLastReport_1 = 0;
String id_paciente ="";

TaskHandle_t Task1;
// Callback (registered below) fired when a pulse is detected
void onBeatDetected()
{
  Serial.println("Beat!");
}

void setup()
{


  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());


  //BOTON ... 
  if ((WiFi.status() == WL_CONNECTED)) { 
    HTTPClient http;
    http.begin(peticion_paciente); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
        id_paciente=payload;
      }
    else {
      Serial.println("Error on HTTP request");
    }
    http.end();
    
  }
  

  //delay(2000);

  Serial.print("Initializing pulse oximeter..");

  // Initialize the PulseOximeter instance
  // Failures are generally due to an improper I2C wiring, missing power supply
  // or wrong target chip


  xTaskCreatePinnedToCore(
    Task1code, /* Function to implement the task */
    "Task1", /* Name of the task */
    10000,  /* Stack size in words */
    NULL,  /* Task input parameter */
    0,  /* Priority of the task */
    &Task1,  /* Task handle. */
    0); /* Core where the task should run */

  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }

  pox.setOnBeatDetectedCallback(onBeatDetected);


}
float heart = 0.0;
int spo2 = 0;
int enviar = 0;

void loop()
{
  if (QS == true)
  {
    Serial.print("*** Heart-Beat Happened *** "); //ASCII Art Madness
    Serial.print("BPM: ");
    Serial.println(BPM);
    QS = false;
  }
  // Make sure to call update as fast as possible
  pox.update();

  // Asynchronously dump heart rate and oxidation levels to the serial
  // For both, a value of 0 means "invalid"
  if(millis() - tsLastReport_1 > REPORTING_PERIOD_MS_1)
  {
    getBPM();
    tsLastReport_1 = millis();
  }
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    heart = pox.getHeartRate();
    spo2 = pox.getSpO2();
    enviar = 1;
    Serial.print("Heart rate:");
    Serial.print(heart);
    Serial.print("bpm / SpO2:");
    Serial.print(spo2);
    Serial.println("%");
    tsLastReport = millis();

    //pox.begin();
    //pox.setOnBeatDetectedCallback(onBeatDetected);
  }

}


void Task1code( void * parameter) {
  for (;;) {
      if (WiFi.status() == WL_CONNECTED) {
        if (enviar==1) {
          enviar=0;
          HTTPClient http;
          http.begin(serverName);
          http.addHeader("Content-Type", "application/x-www-form-urlencoded");
          String httpRequestData = "api=" + apiKey + "&hr=" + heart
                                   + "&spo2=" + spo2 + "&pa="+id_paciente;
          //Serial.print("httpRequestData: ");
          //Serial.println(httpRequestData);
          int httpResponseCode = http.POST(httpRequestData);
          if (httpResponseCode > 0) {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
          }
          else {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
          }
          // Free resources
          http.end();
          Serial.println("OK");
          //delay(2000);
        }
    }
  }
}

void getBPM()
{
    Signal = analogRead(pulsePin); // read the Pulse Sensor
    sampleCounter += 2;
    int N = sampleCounter - lastBeatTime;
    if (Signal < thresh && N > (IBI / 5) * 3)
    {
        if (Signal < T) // T is the trough
        {
            T = Signal; // keep track of lowest point in pulse wave
        }
    }
    if (Signal > thresh && Signal > P)
    {               // thresh condition helps avoid noise
        P = Signal; // P is the peak
    }
    if (N > 250)
    { // avoid high frequency noise
        if ((Signal > thresh) && (Pulse == false) && (N > (IBI / 5) * 3))
        {
            Pulse = true;                       // set the Pulse flag when we think there is a pulse
            IBI = sampleCounter - lastBeatTime; // measure time between beats in mS
            lastBeatTime = sampleCounter;       // keep track of time for next pulse

            if (secondBeat)
            {                                // if this is the second beat, if secondBeat == TRUE
                secondBeat = false;          // clear secondBeat flag
                for (int i = 0; i <= 9; i++) // seed the running total to get a realisitic BPM at startup
                {
                    rate[i] = IBI;
                }
            }

            if (firstBeat) // if it's the first time we found a beat, if firstBeat == TRUE
            {
                firstBeat = false; // clear firstBeat flag
                secondBeat = true; // set the second beat flag
                return;            // IBI value is unreliable so discard it
            }
            word runningTotal = 0; // clear the runningTotal variable

            for (int i = 0; i <= 8; i++)
            {                            // shift data in the rate array
                rate[i] = rate[i + 1];   // and drop the oldest IBI value
                runningTotal += rate[i]; // add up the 9 oldest IBI values
            }

            rate[9] = IBI;              // add the latest IBI to the rate array
            runningTotal += rate[9];    // add the latest IBI to runningTotal
            runningTotal /= 10;         // average the last 10 IBI values
            BPM = 60000 / runningTotal; // how many beats can fit into a minute? that's BPM!
            QS = true;                  // set Quantified Self flag
                                        // QS FLAG IS NOT CLEARED INSIDE THIS ISR
        }

    }

    if (Signal < thresh && Pulse == true)
    {                                // when the values are going down, the beat is over
        Pulse = false;               // reset the Pulse flag so we can do it again
        amp = P - T;                 // get amplitude of the pulse wave
        thresh = amp / 2 + T;        // set thresh at 50% of the amplitude
        P = thresh;                  // reset these for next time
        T = thresh;
    }

    if (N > 2500)
    {                                 // if 2.5 seconds go by without a beat
        thresh = 2170;                 // set thresh default
        P = 2170;                      // set P default
        T = 2170;                      // set T default
        lastBeatTime = sampleCounter; // bring the lastBeatTime up to date
        firstBeat = true;             // set these to avoid noise
        secondBeat = false;           // when we get the heartbeat back
    }
}
