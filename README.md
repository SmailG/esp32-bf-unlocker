# esp32-bf-unlocker

You will need to install pyserial (⁠pip install pyserial⁠) and Ardunio IDE (or PlatformIO).


## Deployment Instructions
1. Flash the Board: Open the Arduino IDE, select your specific ESP32 development board variant, set the baud rate to ⁠115200⁠, and upload the code.
2. Verify the Interface: Before hooking it up to the target, you can open the Serial Monitor in the Arduino IDE (set to 115200 baud). Type ⁠U⁠, ⁠R⁠, ⁠E⁠, or ⁠P⁠ and hit send. You can use a multimeter on the ESP32 pins to verify they briefly drop to continuity with Ground when triggered.
3. Physical Integration: * Disconnect power from the target.
 - Wire the common Ground and the 4 GPIO pins as detailed previously.
 Connect the target's power through the relay.
 Connect the ESP32 to your laptop via USB.
4. Execute: Run your modified Python orchestrator to begin the audit. Ensure you are monitoring the physical setup closely during the initial run to verify the relay correctly power-cycles the board after the threshold is met.


## ESP32 Wiring & Infrastructure
 - Target GND -> ESP32 GND (Critical: You must tie the grounds together to share a common reference voltage).
 - Target Up Button Header -> ESP32 GPIO 12
 - Target Right Button Header -> ESP32 GPIO 14
 - Target Enter Button Header -> ESP32 GPIO 27
 - Relay IN / Signal -> ESP32 GPIO 26

Which should be:
 ESP32 GND to Mower GND.
 ESP32 GPIO A to Up Button.
 ESP32 GPIO B to Right Button.
 ESP32 GPIO C to Enter Button.
 ESP32 GPIO D to the Relay module.
 
Note: Wire the mower's main power line through the Normally Closed (NC) terminals of your relay. Activating the relay breaks the circuit.
