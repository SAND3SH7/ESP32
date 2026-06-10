#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Your custom I2C pins
#define I2C_SDA 21
#define I2C_SCL 22

// Initialize LCD (Address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- Marquee Variables ---
String scrollMessage = "Hacker Here - System compromised - Access granted - ";
int scrollPos = 0;
unsigned long lastScrollTime = 0;
const int scrollSpeed = 300; // Milliseconds between shifts (lower is faster)

void setup() {
  // Start I2C with pins 26 and 27
  Wire.begin(I2C_SDA, I2C_SCL);
  
  // Initialize the LCD screen and turn on backlight
  lcd.init();
  lcd.backlight();

  // Clear any old text
  lcd.clear();
}

void loop() {
  // Non-blocking timer to shift the text smoothly
  if (millis() - lastScrollTime > scrollSpeed) {
    lastScrollTime = millis();
    
    lcd.setCursor(0, 0); // Always write to the first row
    
    // Create a 16-character window that shifts through the long message
    String displayStr = scrollMessage + "                "; 
    lcd.print(displayStr.substring(scrollPos, scrollPos + 16));
    
    scrollPos++;
    // Reset loop once the message reaches the end
    if (scrollPos > scrollMessage.length()) {
      scrollPos = 0;
    }
  }
}