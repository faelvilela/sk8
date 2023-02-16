#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
Adafruit_MPU6050 mpu;

// Tricks possíveis até o momento: Ollie, Nollie, Flip, Varial e Shove it.

bool hasFirstTrick = false;
String firstTrick = "";
String secondTrick = "";

void setup() {

pinMode(D5, OUTPUT);
Serial.begin(115200);
  while (!Serial)
    delay(10);

  Serial.println("MPU6050 Iniciando!");

if (!mpu.begin()) {
  Serial.println("Sensor init failed");
  while (1)
    yield();
}

mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
mpu.setGyroRange(MPU6050_RANGE_500_DEG);
mpu.setFilterBandwidth(MPU6050_BAND_10_HZ);
}

void loop() {
  int count;

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  if (a.acceleration.x > 3) {
    for(count = 1; count <= 2; count++)
      tone(D5, 220);
      delay(500);
      noTone(D5);
      delay(500);
      firstTrick.length() == 0 ? firstTrick = "Ollie" : secondTrick = "Ollie";
  }

  if (a.acceleration.x < -3) {
      tone(D5, 220);
      delay(1000);
      noTone(D5);
      delay(500);
      firstTrick.length() == 0 ? firstTrick = "Nollie" : secondTrick = "Nollie";
  }


  if (a.acceleration.z < -3) {
      tone(D5, 220);
      delay(1000);
      noTone(D5);
      delay(500);
      firstTrick.length() == 0 ? firstTrick = "Flip" : secondTrick = "Flip";
  }

  if (g.gyro.z > 3) {
      tone(D5, 220);
      delay(1000);
      noTone(D5);
      delay(500);
      firstTrick.length() == 0 ? firstTrick = "Varial" : secondTrick = "Varial";
  }

  if (g.gyro.z < -3) {
      tone(D5, 220);
      delay(1000);
      noTone(D5);
      delay(500);
      firstTrick.length() == 0 ? firstTrick = "Shove It" : secondTrick = "Shove It";
  }
    
   Serial.print("Primeira Manobra - ");
   Serial.println(firstTrick);
   Serial.print("Segunda Manobra - ");
   Serial.println(secondTrick);

   if(firstTrick.length() > 0 && secondTrick.length() > 0) {
    // Caso as duas manobras forem iguais dá um toque agudo senão um grave
    if (firstTrick == secondTrick) {
      tone(D5, 200);
      delay(500);
      noTone(D5);
      tone(D5, 250);
      delay(500);
      noTone(D5);
      tone(D5, 300);
      delay(500);
      noTone(D5);
    } else {
      tone(D5, 200);
      delay(500);
      noTone(D5);
      tone(D5, 100);
      delay(500);
      noTone(D5);
    }
      firstTrick = "";
      secondTrick = "";
   }

  delay(1000);
}

// Descricao Manobras
// Ollie -> Aceleração positiva do eixo X
// Nollie -> Aceleração negativa do eixo X
// Nollie -> Aceleração positiva do eixo Z
// Varial -> Rotação Z positiva
// Shove It -> Rotação Z negativa