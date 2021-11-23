#include <EEPROM.h>

void setup()
{
    float f = 0.00f // variable to store data read from EEPROM.
    int eeAddress = 0; // EEPROM address to start reading from

    Serial.begin(9600);
    while(!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.print("Read float from EEPROM: ");
    EEPROM.get(eeAddress, f);
    Serial.println(f, 3);
    secondTest(); // run the next test.
}

struct MyObject
{
    float field1;
    byte field2;
    char name[10];
};

void secondTest()
{
    int eeAddress = sizeof(float); // move address to the next byte after float 'f'.

    MyObject customVar; // variable to store custom object read from EEPROM.
    EEPROM.get(eeAddress, customVar);
    Serial.println("Read custom object from EEPROM: ");
    Serial.println(customVar.field1);
    Serial.println(customVar.field2);
    Serial.println(customVar.name);
}

void loop()
{
    /* Empty loop */
}