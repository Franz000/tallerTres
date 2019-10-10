void enviar_i2c(byte direccion_i2c, byte registro, byte valor)
{
  Wire.beginTransmission(direccion_i2c);
  Wire.write(registro);
  Wire.write(valor);
  Wire.endTransmission();
}

boolean recibir_i2c(byte direccion_i2c, byte registro, byte cantidad, byte *destino)
{
  boolean lectura_correcta=false;
  const unsigned long TIMEOUT=50;
  Wire.beginTransmission(direccion_i2c);
  Wire.write(registro);
  Wire.endTransmission(false);
  Wire.requestFrom(direccion_i2c,cantidad);
  unsigned long cronometro=millis();
  while(Wire.available()<cantidad&&(unsigned long)(millis()-cronometro)<TIMEOUT);
  if(Wire.available()==cantidad)
  {
    lectura_correcta=true;
    for(byte contador=0;contador<cantidad;destino[contador]=Wire.read(),contador++);
  }
  return lectura_correcta;
}

