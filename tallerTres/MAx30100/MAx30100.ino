#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 10

// El oxímetro de pulso es la interfaz de nivel superior para el sensor
// Ofrece:
// * informes de detección de latidos
// * cálculo de la frecuencia cardíaca
// * Cálculo de SpO2 (nivel de oxidación)
PulseOximeter pox;

uint32_t tsLastReport = 0;

// La devolución de llamada (registrada a continuación) se dispara cuando se detecta un pulso
void onBeatDetected()
{
  Serial.println("Latido!");
}

void setup()
{
  Serial.begin(9600);

  Serial.print("Inicializando oxímetro de pulso..");

  // Inicializar la instancia de PulseOximeter
  // Las fallas generalmente se deben a un cableado I2C incorrecto, falta de suministro de energía
  // o chip de destino incorrecto
  if (!pox.begin()) {
    Serial.println("HA FALLADO");
    for (;;);
  } else {
    Serial.println("ÉXITO");
  }

  /* La corriente predeterminada para el LED IR es de 50 mA y podría cambiarse.
    descomentando la siguiente línea. Consulte MAX30100_Registers.h para ver todas las opciones disponibles.
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  */

  // Registre una devolución de llamada para la detección de latidos
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
  // Asegúrese de llamar a la actualización lo más rápido posible
  pox.update();

  // Asynchronously dump heart rate and oxidation levels to the serial
  // For both, a value of 0 means "invalid"
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print("Heart rate:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / SpO2:");
    Serial.print(pox.getSpO2());
    Serial.println("%");

    tsLastReport = millis();
  }
}
