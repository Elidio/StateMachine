#include <MemoryFree.h>

#include "StateMachine.h"

class STATEMACHINE(Blink) {
  private:
    int port;
    int waitTime;
    CREATE_STATE(low);
    CREATE_STATE(high);
    
    void low() {
      digitalWrite(port, LOW);
      *this << &STATE(high)<< waitTime;
    }
    void high() {
      digitalWrite(port, HIGH);
      *this << &STATE(low)<< waitTime;
    }
  public:
    Blink(int port = 0, int waitTime = 0) :
      port(port),
      waitTime(waitTime),
      INIT_STATE(low),
      INIT_STATE(high)
      {
        pinMode(port, OUTPUT);
        *this << &STATE(low);
      }
};

Blink *led1, *led2, *led3;


void setup() {
  Serial.begin(115200);
  Serial.println(freeMemory());
  led1 = new Blink(12, 300);
  Serial.println(freeMemory());
  led2 = new Blink(11, 500);
  Serial.println(freeMemory());
  led3 = new Blink(10, 700);
  Serial.println(freeMemory());
}

void loop() {
    (*led2)();
    (*led1)();
    (*led3)();
}
