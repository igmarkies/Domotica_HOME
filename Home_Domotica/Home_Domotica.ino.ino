#include <VirtualWire.h>
#include <VirtualWire_Config.h>

void Transmitter();
float Battery_Check();

uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;

int FUNCTIE = 0;
int ID = 0x40;
int DEST = 0;
int LRC = 0;

byte SEND[] {0x01, 4, FUNCTIE, ID, DEST, 0x04, LRC};
//           start, lengte, function, ID, Destination ID, stop, LRC positieve


void setup() {
  Serial.begin(9600);  // Debugging only
  Serial.println("setup");

  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);  // Bits per sec

  vw_rx_start();       // Start the receiver PLL running
}

void loop() {

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    if (buf[4] == 0x41) {

    };
  };
} //End Main

void Transmitter() {                                                        //transmit all data with size 7

  Serial.println("Send message");
  for (int i = 0; i <= 7; i++) {
    Serial.print (SEND [i], HEX);
    Serial.print (" ");
  }
  Serial.println (" ");

  const char *msg = SEND;
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx(); // Wait until the whole message is gone
  delay(200);
}

float Battery_Check() {
  int sensorValue = analogRead(A0); //read the A0 pin value
  float voltage = sensorValue * (5.00 / 1023.00) * 2; //convert the value to a true voltage.
  lcd.setCursor(0,0);
  lcd.print("voltage = ");
  lcd.print(voltage); //print the voltage to LCD
  lcd.print(" V");
  if (voltage < 6.50) //set the voltage considered low battery here
  {
    digitalWrite(led_pin, HIGH);
  }
}
