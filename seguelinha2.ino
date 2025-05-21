#include <autocalibralib.h>
#include <L298NM.h>

#include <EEPROM.h>


#define motorESQUERDO 9
#define motorDIREITO 11
#define direcaoESQUERDO 8
#define direcaoDIREITO 10

// Criando instância dos motores
L298NM robo(motorESQUERDO, direcaoESQUERDO, motorDIREITO, direcaoDIREITO);

int vel = 127;

///////////////////////

LineSensor sensorE(A0, LED_BUILTIN);  // Sensor IV esquerdo
LineSensor sensorD(A1, LED_BUILTIN); // Sensor IV direito

///////////////////////

void setup() {
  /*Este código depende de uma calibração já presente em outro código, crie um ou use o primeiro exemplo da biblioteca 
  "autocalibralib.h" (se não quiser, comente as próximas 2 linhas e descomente as debaixo, que usam valores fixos, você pode alterá-los se quiser)**/
  
  //sensorE.setThreshold(static_cast<int>(EEPROM.read(0)));
  //sensorD.setThreshold(static_cast<int>(EEPROM.read(1)));
  sensorE.setThreshold(300);
  sensorD.setThreshold(300);
}

///////////////////////

void loop() {
  bool pretoESQUERDO = sensorE.isBlack();
  bool pretoDIREITO = sensorD.isBlack();
  
  //1: preto, 0: branco
  if (pretoESQUERDO=1 && pretoDIREITO=0) { 
    robo.turnLeft(vel); delay(200);
  } else if (pretoESQUERDO=0 && pretoDIREITO=1) {
    robo.turnRight(vel); delay(200);
  } else {
    robo.forward(vel);
  }
}
