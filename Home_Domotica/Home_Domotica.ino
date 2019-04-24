#include <VirtualWire.h>
#include <VirtualWire_Config.h>

struct Data {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
}DATA;




void setup() {
  Serial.begin(9600);  // Debugging only
  Serial.println("setup");

  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);  // Bits per sec

  vw_rx_start();       // Start the receiver PLL running
}

void loop() {

    if (vw_get_message(DATA.buf, DATA.buflen)) // Non-blocking
    {
    
    };
}
