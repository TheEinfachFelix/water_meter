#include <IoAbstractionWire.h>
#include <DeviceEvents.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
// here we create the object using new, and tell taskmanager to 
// own the memory (and delete it if it becomes completed) 
taskManager.registerEvent(new MyAnalogEvent(myDeviceRef, 15), true);

// here we assume a global instance of the event class instead
taskManager.registerEvent(&myGlobalEvent);
}


class MyAnalogEvent : public AnalogInEvent {
public:
    MyAnalogEvent(AnalogDevice* device, 15) :
            AnalogInEvent(device, 15, 500, ANALOGIN_EXCEEDS, 10) {
    }

    void exec() override {
        Serial.print("asdfj");
    }
};

void myRawAnalogIsr() {
    myAnalogEvent.readingAvailable();
     Serial.print("45651");
}
