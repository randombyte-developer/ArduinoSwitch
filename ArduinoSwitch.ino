#include <RCSwitch.h>

#define led 13
#define houseCode "00111"
#define socketCount 4
char* socketCodes[] = {"10000", "0", "00100", "0"}; //0:A 1:B 2:C 3:D
int sockets[4][2] = {{6, -1}, {-1, -1}, {2, -1}, {-1, -1}}; //first: pin for switch for that socket, second: previous state(HIGH/LOW)

RCSwitch mySwitch = RCSwitch();

void setup() {
  mySwitch.enableTransmit(9);
  pinMode(led, OUTPUT);
  for(int i = 0; i < socketCount; i++) {
    pinMode(sockets[i][0], INPUT);
  }
}

void loop() {
  for(int i = 0; i < socketCount; i++) {
    if (sockets[i][0] == -1) {
      //undefined -> ignore
      continue;  
    }
    int state = digitalRead(sockets[i][0]);
    if (sockets[i][1] != state) {
      bl(led, 100);
      sendSwitch(i, state == HIGH ? true : false);
      sockets[i][1] = state;
    }
  }
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
