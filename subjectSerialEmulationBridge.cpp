// ESP32 Open-Drain Keystroke Emulator - C2 Bridge
// Designed to interface with 3.3V pulled-up logic systems without voltage injection.

// Define target GPIO mapping
#define PIN_UP 12
#define PIN_RIGHT 14
#define PIN_ENTER 27
#define PIN_RELAY 26

void setup() {
    // Initialize serial communication with the Python orchestrator
    Serial.begin(115200);
    
    // Initialize pins in High-Impedance (floating) state (INPUT).
    // The target board's pull-up resistors will hold these lines HIGH (3.3V).
    // We do NOT use INPUT_PULLUP, as the target already provides the pull-up voltage.
    pinMode(PIN_UP, INPUT); 
    pinMode(PIN_RIGHT, INPUT);
    pinMode(PIN_ENTER, INPUT);
    
    // Initialize Relay (Assuming active-high relay module, adjust if your module is active-low)
    pinMode(PIN_RELAY, OUTPUT);
    digitalWrite(PIN_RELAY, LOW); 
}

// Emulate an open-drain pull to ground to simulate a physical finger press
void triggerPress(int pin) {
    pinMode(pin, OUTPUT);     // Take control of the line
    digitalWrite(pin, LOW);   // Pull to ground (simulate button press)
    
    // 150ms is a standard membrane press debounce time. 
    // If the target drops inputs, increase this slightly.
    delay(150);               
    
    pinMode(pin, INPUT);      // Release line back to High-Z (floating)
}

void loop() {
    // Await execution commands from the orchestration script
    if (Serial.available()) {
        char cmd = (char)Serial.read();
        
        switch (cmd) {
            case 'U': // Up
                triggerPress(PIN_UP);
                break;
            case 'R': // Right
                triggerPress(PIN_RIGHT);
                break;
            case 'E': // Enter
                triggerPress(PIN_ENTER);
                break;
            case 'P': // Power Cycle / Hard Reset
                // Trigger the relay to break the main power circuit
                digitalWrite(PIN_RELAY, HIGH);
                
                // Hold the power cut for 3 seconds to ensure capacitors discharge
                // and the target board completely loses state.
                delay(3000); 
                
                // Re-engage power
                digitalWrite(PIN_RELAY, LOW);
                break;
            default:
                // Ignore unrecognized bytes to prevent erratic behavior
                break;
        }
    }
}
