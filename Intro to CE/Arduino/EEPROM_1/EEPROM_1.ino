#include <EEPROM.h>

struct MyObject 
{
    float field1;
    byte field2;
    char name[10];
};

void setup()
{
    Serial.begin(9600);
    while(!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    float f = 123.456f; // variable to store in EEPROM.
    int eeAddress = 0; // location we want the data to be put.
    EEPROM.put(eeAddress, f);
    Serial.println("Written float data type!");

    // data to store
    MyObject customVar = 
    {
        3.14f,
        65,
        "Working!"
    };
    eeAddress += sizeof(float); // move address to the next byte after float 'f'.
    EEPROM.put(eeAddress, customVar);
    Serial.print("Written custom data type! \n");
}

void loop()
{
    /* Empty loop */
}
