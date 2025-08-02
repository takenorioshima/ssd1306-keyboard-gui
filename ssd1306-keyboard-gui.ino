#include <Wire.h>
#include <SSD1306Wire.h>

SSD1306Wire display(0x3C, SDA, SCL);

const char* noteNames[12] = {
  "C", "Db", "D", "Eb", "E", "F",
  "Gb", "G", "Ab", "A", "Bb", "B"
};

// Draw key.
void drawKey(int x, int y, int radius, bool isActive) {
  if (isActive) {
    display.fillCircle(x, y, radius);
  } else {
    display.drawCircle(x, y, radius);
  }
}

// Draw keyboard.
void drawKeyboard(const int* activeNotes, int length) {
  display.clear();

  const int baseX = 16;
  const int baseY = 40;
  const int radius = 8;
  const int whiteKeySpacing = 16;

  // Draw C D E F G A B.
  const int whiteNotes[] = { 0, 2, 4, 5, 7, 9, 11 };
  for (int i = 0; i < 7; i++) {
    int notePitchClass = whiteNotes[i];
    int x = baseX + i * whiteKeySpacing;

    bool isActive = false;
    for (int j = 0; j < length; j++) {
      if ((activeNotes[j] % 12) == notePitchClass) {
        isActive = true;
        break;
      }
    }

    drawKey(x, baseY, radius, isActive);
  }

  // Draw C#, D#, F#, G#, A#.
  const int blackNoteOffsets[] = { 1, 3, 6, 8, 10 };
  const int blackKeyXOffsets[] = { 1, 2, 4, 5, 6 };

  for (int i = 0; i < 5; i++) {
    int notePitchClass = blackNoteOffsets[i];
    int x = baseX + blackKeyXOffsets[i] * whiteKeySpacing - 8;
    int y = baseY - 14;

    bool isActive = false;
    for (int j = 0; j < length; j++) {
      if ((activeNotes[j] % 12) == notePitchClass) {
        isActive = true;
        break;
      }
    }

    drawKey(x, y, radius, isActive);
  }

  // Sample: Header text.
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 0, "SSD1306 KEYBOARD GUI");

  // Sample: Footer text.
  String noteStrings = "";
  String noteNumbers = "";
  for (int j = 0; j < length; j++) {
    noteStrings += noteNames[activeNotes[j] % 12];
    noteNumbers += String(activeNotes[j]);
    if (j < length - 1){
      noteStrings += " ";
      noteNumbers += " ";
    }
  }
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 54, noteStrings);
  
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 54, noteNumbers);

  display.display();
}

void setup() {
  Serial.begin(115200);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}

void loop() {
  // Sample: C, E, G
  int activeNotes[] = { 60, 64, 67 };
  drawKeyboard(activeNotes, sizeof(activeNotes) / sizeof(activeNotes[0]));

  delay(1000);

  // Sample: C#, F#, A#
  int activeNotes2[] = { 61, 66, 70 };
  drawKeyboard(activeNotes2, sizeof(activeNotes2) / sizeof(activeNotes2[0]));

  delay(1000);

  // Sample: D, E, A
  int activeNotes3[] = { 62, 64, 69 };
  drawKeyboard(activeNotes3, sizeof(activeNotes3) / sizeof(activeNotes3[0]));

  delay(1000);
}
