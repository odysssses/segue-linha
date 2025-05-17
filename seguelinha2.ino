#include <autocalibralib.h>
#include <L298NM.h>

#include <EEPROM.h>


#define M_E 9
#define M_D 11
#define DIR_E 8
#define DIR_D 10

// Criando instância dos motores
L298NM robo(M_E, DIR_E, M_D, DIR_D);

int vel = 127;

///////////////////////

LineSensor sensorE(A3, 3);  // Sensor IV esquerdo com LED no pino 3
LineSensor sensorD(A1, 4); // Sensor IV direito com LED no pino 4

///////////////////////

void setup() {
  //Este código depende de uma calibração já presente em outro código, crie um ou use o primeiro exemplo da biblioteca "autocalibralib.h"
  sensorE.setThreshold(static_cast<int>(EEPROM.read(0)));
  sensorD.setThreshold(static_cast<int>(EEPROM.read(1)));
}

///////////////////////

void loop() {
  bool pretoESQUERDO = sensorE.isBlack();
  bool pretoDIREITO = sensorD.isBlack();
  
  //pretoNOME: O sensor lê preto. !pretoNOME: O sensor lê branco.
  if ((pretoESQUERDO) && (!pretoDIREITO)) { 
    robo.turnLeft(vel); delay(200);
  } else if ((!pretoESQUERDO) && (pretoDIREITO)) {
    robo.turnRight(vel); delay(200);
  } else {
    robo.forward(vel);
  }
}
