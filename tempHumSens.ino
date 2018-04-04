#include <DHT.h>
#include "SSD1306.h"

/*********** defines ************/

#define DHT_PIN 5
#define DHT_TYPE DHT11

/*********** locals ************/

SSD1306 display(0x3c, D3, D5);
DHT dht(DHT_PIN, DHT_TYPE);

/**
 * @brief struct to hold last sensor reading
 */
typedef struct readings_s{
  float Humidity;
  float Temperature;
} readings_t;
readings_t DHT_data = {0, 0};


/*********** functions ************/
/**
 * @brief function for reading humidity and temperature
 * 
 * @param   none
 * @return  will return false if first/second reading failed, true otherwise
 */
bool readDHT(){
  DHT_data.Humidity    = dht.readHumidity();
  if(isnan(DHT_data.Humidity)){    //reading successful?
    return false;
  }
  DHT_data.Temperature = dht.readTemperature();
  if(isnan(DHT_data.Temperature)){ //reading successful?
    return false;
  }
  return true; //we got here, so reading should've been successful
}

/**
 * @brief Take recent reading and display on OLED
 * 
 * @param   none
 * @return  none
 */
void displayTempHumid(){
  display.clear();
  display.drawString(0, 0, "Humidity: " + String(DHT_data.Humidity) + "%\t"); 
  display.drawString(0, 16, "Temp: " + String(DHT_data.Temperature) + "C"); 
}

/**
 * @brief initialization of display and sensor
 * 
 * @param   none
 * @return  none
 */
void setup() {
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  dht.begin(); // initialize the dht
}

/**
 * @brief mainlopp
 * 
 * @param   none
 * @return  none
 */
void loop() {
  if(!readDHT()){
    delay(500);
  }
  else{
    displayTempHumid();
    display.display();
    delay(2000);
  }
}
