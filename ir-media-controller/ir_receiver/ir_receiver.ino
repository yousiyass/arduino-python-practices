#include <IRremote.hpp>
#define IR_ALICI_PIN 11

String donustur(int x) {
  if (x == 7) { return "SES_ARTIR"; };
  if (x == 11) { return "SES_AZALT"; };
  if (x == 104) { return "DURDUR"; };
  if (x == 98) { return "ILERI"; };
  if (x == 101) { return "GERI"; };
  if (x == 15) { return "MUTE"; };
}

void setup() {
  Serial.begin(9600);

  IrReceiver.begin(IR_ALICI_PIN);
}

void loop() {

  if (IrReceiver.decode()) {
    String result = donustur(IrReceiver.decodedIRData.command);
    Serial.println(result);
    delay(200);
  }

  IrReceiver.resume();
}
