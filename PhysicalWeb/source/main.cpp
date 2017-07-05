#include "MicroBit.h"

MicroBit uBit;

char URL[] = "https://goo.gl/gVTexW"; //Change this with your shorten URL
const int8_t CALIBRATED_POWERS[] = {-49, -37, -33, -28, -25, -20, -15, -10};

uint8_t advertising = 0;
uint8_t tx_power_level = 6;

void startAdvertising() {
    uBit.bleManager.advertiseEddystoneUrl(URL, CALIBRATED_POWERS[tx_power_level-1], true);
    uBit.bleManager.setTransmitPower(tx_power_level);
    advertising = 1;
}


// we use events abd the 'connected' variable to keep track of the status of the Bluetooth connection
void onConnected(MicroBitEvent) {
    uBit.display.print("C");
}

void onDisconnected(MicroBitEvent) {
    uBit.display.print("D");
}

int main() {
    uBit.init();
	
	  uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, onConnected);
    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_DISCONNECTED, onDisconnected);
	
    new MicroBitIOPinService(*uBit.ble, uBit.io);
    startAdvertising();
    release_fiber();
}