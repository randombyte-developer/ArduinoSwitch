#include <RCSwitch.h>

#define led 13
#define houseCode "00111"
#define socketCount 4
char* socketCodes[] = {"10000", "0", "00100", "0"}; //0:A 1:B 2:C 3:D
int socketPins[4][2] = {{2,3}, {4,7}, {5,6}, {8,9}};

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableTransmit(9);
  pinMode(led, OUTPUT);
  for(int i = 2; i <= 9; i++) {
    pinMode(i, INPUT);
  }
}

void loop() {
  //every socket
  for(int i = 0; i < 4; i++) {
    int firstPin = 0;
    int secondPin = 0;
    for(int j = 0; j < 4; j++) {
      firstPin += digitalRead(socketPins[i][0]) == HIGH ? 1 : 0;
      secondPin += digitalRead(socketPins[i][1]) == HIGH ? 1 : 0;
      delay(95);
    }
    /*String so = "#";
    String f = "F:";
    String s = ";S:";
    String semi = ";";
    String output = so + i + semi + f + firstPin + s + secondPin + semi;
    Serial.print(output);*/
    String y = "+";
    String n = "-";
    Serial.print(firstPin > secondPin ? y : n);
  }
  Serial.println();
}

//blink
void bl(int pin, int millisOn) {
  digitalWrite(pin, HIGH);
  delay(millisOn);
  digitalWrite(pin, LOW);
}

void sendSwitch(int socket, boolean enabled) {
  if (socket >= socketCount) return; //Illegal access
  if (enabled == true) {
    mySwitch.switchOn(houseCode, socketCodes[socket]);
  } else {
    mySwitch.switchOff(houseCode, socketCodes[socket]);
  }
}
