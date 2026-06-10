#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Your custom I2C pins
#define I2C_SDA 21
#define I2C_SCL 22

// Initialize LCD (Address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Create a custom heart character
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

// --- Blinking Variables ---
unsigned long lastBlinkTime = 0;
const int blinkInterval = 250; // Milliseconds between blinks (lower is faster)
bool textVisible = true;       // Keeps track of whether the text is currently showing

void setup() {
  // Start I2C with defined pins
  Wire.begin(I2C_SDA, I2C_SCL);
  
  // Initialize the LCD screen and turn on backlight
  lcd.init();
  lcd.backlight();

  // Load the custom heart character into LCD memory
  lcd.createChar(0, heart);
  lcd.clear();

  // --- Print Row 0 (Stays static) ---
  lcd.setCursor(0, 0); 
  lcd.print("You + Me = ");
  lcd.write(0); // Prints the heart
}

void loop() {
  // Non-blocking timer to blink the bottom row
  if (millis() - lastBlinkTime > blinkInterval) {
    lastBlinkTime = millis();
    textVisible = !textVisible; // Flip the switch (true becomes false, false becomes true)
    
    lcd.setCursor(0, 1); // Move to the start of the second row
    
    if (textVisible) {
      lcd.print("System: Love ON "); // Print the message
    } else {
      lcd.print("                "); // Print 16 blank spaces to "erase" it
    }
  }
}