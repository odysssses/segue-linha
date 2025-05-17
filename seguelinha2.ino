/////////////////////
//IN 1 e 2: OUT2 
//IN 3 e 4: OUT1
#define dirR 7 // direção do motor direito: Para frente / Para trás (HIGH ou LOW)_ porta IN1 ponte H;
#define mR 8 // velocidade do motor direito ( 0 a 255) _ Porta IN2 ponte H; 
#define dirL 9 //direção do motor esquerdo: Para frente / Para trás (HIGH ou LOW)_ porta IN3 ponte H;
#define mL 10 // velocidade do motor esquerdo ( 0 a 255) _ Porta IN4 ponte H;

int vel = 127;
int vel0 = 0;

///////////////////////

const int ledverde = 4;
const int ledverm = 3;
#define sensorL A4
#define sensorR A1

int pretogL;
int pretogR;
char ivL;
char ivR;

////////////////////////

char defcor(int val, int pretog) {
  if (val <= pretog + 70) {
    return 'p';
  } else {
    return 'b';
  }
}

void pisca(int t, int led) {
  for (int i = 0; i < t; i++) {
    delay(1000);
    digitalWrite(led, HIGH);
    Serial.print("piscou: ");
    switch (led) {case 3: Serial.println("vermelho"); break; case 4: Serial.println("verde");}
    delay(50);
    digitalWrite(led, LOW);
  }
}

/////////////////////////

void m() {
  analogWrite(mL, vel);
  analogWrite(mR, vel);
}

void mov(int t) {
  digitalWrite(dirL, LOW);
  digitalWrite(dirR, LOW);
  m();
  delay(t);
}

void turnL(int t) {
  digitalWrite(dirL, HIGH);
  digitalWrite(dirR, LOW);
  m();  
  delay(t);
}

void turnR(int t) {
  digitalWrite(dirL, LOW);
  digitalWrite(dirR, HIGH);
  m();  
  delay(t);
}

void back(int t) {
  digitalWrite(dirL, HIGH);
  digitalWrite(dirR, HIGH);
  m();  
  delay(t);
}

///////////////////////////

void setup() {
  pinMode(mL, OUTPUT);
  pinMode(mR, OUTPUT);
  pinMode(dirL, OUTPUT);
  pinMode(dirR, OUTPUT);
  
  pinMode(ledverde, OUTPUT);
  pinMode(ledverm, OUTPUT);
  pinMode(sensorL, INPUT);
  pinMode(sensorR, INPUT);

  Serial.begin(9600);

  pisca(3, ledverm); pretogL = analogRead(sensorL); pisca(1, ledverde);
  pisca(3, ledverm); pretogR = analogRead(sensorR); pisca(1, ledverde);
}

////////////////////////////

void loop() {
  ivL = defcor(analogRead(sensorL), pretogL);
  ivR = defcor(analogRead(sensorR), pretogR);

  Serial.print("Sensor esquerdo: "); Serial.print(ivL); Serial.print(" // Sensor direito: "); Serial.println(ivR);
  
  if ((ivL == 'p') && (ivR == 'b')) { 
    back(50);
    turnL(200);
  } else if((ivL == 'b') && (ivR == 'p')) {
    turnR(200);
    back(50);
  } else {
     mov(1);
  }
}
