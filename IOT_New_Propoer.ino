//email devadharshiniks10@gmail.com.
//@#qwerty@#
//Your username is health_12345.
//Projectiot@2025
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "4c7fd77f-f150-4a78-9be5-47daa5c5b458";
const char SSID[]               = "projectiot";    // Network SSID (name)
const char PASS[]               = "1234567890";    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]         = "BuHbLoGR0rbrl?LptyOYL0hZi";    // Secret device password

void onBOChange();
void onHRChange();
void onBed1Change();
void onBed2Change();
void onTempChange();

int bO;
int hR;
bool bed1;
bool bed2;
float temp;

unsigned long lastUpdateTime = 0;  // Variable to track the time of last update
const unsigned long updateInterval = 1000;  // Set update interval (1 second)

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(bO, READWRITE, ON_CHANGE, onBOChange);
  ArduinoCloud.addProperty(hR, READWRITE, ON_CHANGE, onHRChange);
  ArduinoCloud.addProperty(bed1, READWRITE, ON_CHANGE, onBed1Change);
  ArduinoCloud.addProperty(bed2, READWRITE, ON_CHANGE, onBed2Change);
  ArduinoCloud.addProperty(temp, READWRITE, ON_CHANGE, onTempChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

void setup() {
  Serial.begin(9600);
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);  // Enable debug messages for troubleshooting
  ArduinoCloud.printDebugInfo();
}

void loop() {
  unsigned long currentMillis = millis();

  // Only update the cloud once every 'updateInterval' milliseconds (1 second)
  if (currentMillis - lastUpdateTime >= updateInterval) {
    ArduinoCloud.update(); // Update IoT Cloud
    lastUpdateTime = currentMillis;
  }

  // Handle serial input and update variables based on identifiers
  if (Serial.available() > 0) {
    char identifier = Serial.read();
    Serial.print(identifier);
    delay(50);
    switch (identifier) {
      case 'T': temp = Serial.parseFloat(); break; 
      case 'H': hR = Serial.parseInt(); break; 
      case 'S': bO = Serial.parseInt(); break; 
      case 'B': bed1 = false; break;
      case 'b': bed1 = true; break;
      case 'D': bed2 = false; break;
      case 'd': bed2 = true; break;    }
  }
}

void onTempChange()  {}
void onTempStatusChange()  {}
void onHRChange()  {}
void onBOChange()  {}
void onBed1Change()  {}
void onBed2Change()  {}
