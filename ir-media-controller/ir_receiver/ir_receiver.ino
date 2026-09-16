#include <IRremote.hpp>
#define IR_RECEIVER_PIN 11

String convert(int x) {
  if (x == 7) { return "volume_up"; };
  if (x == 11) { return "volume_down"; };
  if (x == 104) { return "play_pause"; };
  if (x == 98) { return "next_track"; };
  if (x == 101) { return "prev_track"; };
  if (x == 15) { return "mute"; };
}

void setup() {
  Serial.begin(9600);

  IrReceiver.begin(IR_RECEIVER_PIN);
}

void loop() {

  if (IrReceiver.decode()) {
    String result = convert(IrReceiver.decodedIRData.command);
    Serial.println(result);
    delay(200);
  }

  IrReceiver.resume();
}
