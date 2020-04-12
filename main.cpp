#include "mbed.h"
#include "Sht31.h"
#include "K30.h"
 
Sht31 sen1a(PB_9, PB_8);
Sht31 sen1b(PB_9, PB_8, true);
K30 Co2_1(PB_9, PB_8, 0x68);

Sht31 sen2a(PC_12, PB_10);
Sht31 sen2b(PC_12, PB_10, true);
K30 Co2_2(PC_12, PB_10, 0x68);

Sht31 sen3a(PB_4, PA_8);
Sht31 sen3b(PB_4, PA_8, true);
K30 Co2_3(PB_4, PA_8, 0x68);
 
DigitalIn bttn(USER_BUTTON); 
DigitalOut myled(LED1);
 
Serial pc(USBTX, USBRX);

char buff[56];

void int_to_byte(char *data, uint16_t val);
void float_to_byte(char *data, float *val);

int main()
{
    
    buff[0] = 'a'; 
    buff[55] = '\n';
    while (1) {
        
        float t = sen1a.readTemperature();
        float h = sen1a.readHumidity();
        Co2_1.readCo2(); // I have to call the read function twice for it to work no idea why
        
        if (Co2_1.readCo2())
        {
            pc.printf("A: Co2 Value: %u \n", Co2_1.CO2());
            int_to_byte(buff+1, Co2_1.CO2());
            }
         else {
            pc.printf("A: Failed to read Co2 sensor\n");
            int_to_byte(buff+1, (uint8_t)0);
        } 

        if (! isnan(t)) {  // check if 'is not a number'
            pc.printf("A: Sensor 1 temperature: %0.2f\n", t);
            float_to_byte(buff+3, &t);
           // pc.printf("Byte Array %X, %X, %X, %X\n",  buff[3], buff[4], buff[5], buff[6]);
        } else { 
            pc.printf("A: Sensor 1 Failed to read temperature\n");
            float_to_byte(buff+3, 0);
        }
      
        if (! isnan(h)) {  // check if 'is not a number'
        //Serial.print("Hum. % = "); 
            pc.printf("A: Sensor 1 Humidity: %0.2f\n", h);
            float_to_byte(buff+7, &h);
        } else {
            pc.printf("A: Sensor 1 Failed to read humidity\n");
            float_to_byte(buff+7, 0);
        } 
        
        t = sen1b.readTemperature();
        h = sen1b.readHumidity();
        
        if (! isnan(t)) {  // check if 'is not a number'
            pc.printf("A: Sensor 2 temperature: %0.2f\n", t);
            float_to_byte(buff+11, &t);
        } else { 
            pc.printf("A: Sensor 2 Failed to read temperature\n");
            float_to_byte(buff+11, 0);
        }
        
        if (! isnan(h)) {  // check if 'is not a number'; 
            pc.printf("A: Sensor 2 Humidity: %0.2f\n", h);
            float_to_byte(buff+15, &h);
        } else {
            pc.printf("A: Sensor 2Failed to read humidity\n");
            float_to_byte(buff+15, 0);
        } 
        
        //--########################################################
        // Arangement B
        //--########################################################
        t = sen2a.readTemperature();
        h = sen2a.readHumidity();
        Co2_2.readCo2(); // I have to call the read function twice for it to work no idea why
        
        if (Co2_2.readCo2())
        {
            pc.printf("B: Co2 Value: %u \n", Co2_2.CO2());
            int_to_byte(buff+19, Co2_2.CO2());
            }
         else {
            pc.printf("B: Failed to read Co2 sensor\n");
            int_to_byte(buff+19, 0);
        } 

        if (! isnan(t)) {  // check if 'is not a number'
            pc.printf("B: Sensor 1 temperature: %0.2f\n", t);
            float_to_byte(buff+21, &t);
        } else { 
            pc.printf("B: Sensor 1 Failed to read temperature\n");
            float_to_byte(buff+21, 0);
        }
      
        if (! isnan(h)) {  // check if 'is not a number'
            pc.printf("B: Sensor 1 Humidity: %0.2f\n", h);
            float_to_byte(buff+25, &h);
        } else {
            pc.printf("B: Sensor 1 Failed to read humidity\n");
            float_to_byte(buff+25, 0);
        } 
        
        t = sen2b.readTemperature();
        h = sen2b.readHumidity();
        
        if (! isnan(t)) {  // check if 'is not a number'
            pc.printf("B: Sensor 2 temperature: %0.2f\n", t);
            float_to_byte(buff+29, &t);
        } else { 
            pc.printf("B: Sensor 2 Failed to read temperature\n");
            float_to_byte(buff+29, 0);
        }
        
        if (! isnan(h)) {  // check if 'is not a number'
        //Serial.print("Hum. % = "); 
            pc.printf("B: Sensor 2 Humidity: %0.2f\n", h);
            float_to_byte(buff+33, &h);
        } else {
            pc.printf("B: Sensor 2 Failed to read humidity\n");
            float_to_byte(buff+33, 0);
        } 
        
         //--########################################################
        // Arangement c
        //--########################################################
        t = sen3a.readTemperature();
        h = sen3a.readHumidity();
        Co2_3.readCo2(); // I have to call the read function twice for it to work no idea why
        
        if (Co2_3.readCo2())
        {
            pc.printf("C: Co2 Value: %u \n", Co2_3.CO2());
            int_to_byte(buff+37, Co2_3.CO2());
            }
         else {
            pc.printf("C: Failed to read Co2 sensor\n");
            int_to_byte(buff+37, 0);
        } 

        if (! isnan(t)) {  // check if 'is not a number'
            pc.printf("C: Sensor 1 temperature: %0.2f\n", t);
            float_to_byte(buff+39, &t);
        } else { 
            pc.printf("C: Sensor 1 Failed to read temperature\n");
            float_to_byte(buff+39, 0);
        }
      
        if (! isnan(h)) {  // check if 'is not a number'
            pc.printf("C: Sensor 1 Humidity: %0.2f\n", h);
            float_to_byte(buff+43, &h);
        } else {
            pc.printf("C: Sensor 1 Failed to read humidity\n");
            float_to_byte(buff+43, 0);
        } 
        
        t = sen3b.readTemperature();
        h = sen3b.readHumidity();
        
        if (! isnan(t)) {  // check if 'is not a number'
            pc.printf("C: Sensor 2 temperature: %0.2f\n", t);
            float_to_byte(buff+47, &t);
        } else { 
            pc.printf("C: Sensor 2 Failed to read temperature\n");
            float_to_byte(buff+47, 0);
        }
        
        if (! isnan(h)) {  // check if 'is not a number'
        //Serial.print("Hum. % = "); 
            pc.printf("C: Sensor 2 Humidity: %0.2f\n", h);
            float_to_byte(buff+51, &h);
        } else {
            pc.printf("C: Sensor 2 Failed to read humidity\n");
            float_to_byte(buff+51, 0);
        } 
        
        wait(2);    //Give time for tx buffer to clear
        for (int i = 0; i<56; i++) pc.putc(buff[i]);
        myled = !myled;
        wait(8);
    }
 
}

//-- Convert floating point to byte array
void float_to_byte(char *data, float *val) {
      memcpy(data, val, sizeof(float)); 
}

//-- Convert integer to byte array
void int_to_byte(char *data, uint16_t val) {
      memcpy(data, &val, sizeof val); 
}