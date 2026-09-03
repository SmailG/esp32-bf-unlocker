import serial
import time

class ESP32Controller:
    def __init__(self, port='COM3', baudrate=115200): # Change COM3 to /dev/ttyUSB0 on Linux/Mac
        try:
            print(f"[+] Initializing C2 Bridge on {port}...")
            # timeout is required to prevent blocking indefinitely
            self.ser = serial.Serial(port, baudrate, timeout=1)
            
            # CRITICAL: Opening a serial port forces DTR to toggle, which resets the ESP32.
            # We must wait for the bootloader to finish before sending payloads.
            time.sleep(2) 
            print("[+] ESP32 Bridge Active.")
        except Exception as e:
            print(f"[-] Failed to open serial port: {e}")
            exit(1)

    def up(self):
        self.ser.write(b'U')
        time.sleep(0.2) # Allow target UI to process

    def right(self):
        self.ser.write(b'R')
        time.sleep(0.2)

    def enter(self):
        self.ser.write(b'E')
        time.sleep(0.2)

    def power_cycle(self):
        print("[*] Striking Limit Reached. Executing Hard Reset...")
        self.ser.write(b'P')
        # Wait for the 3-second relay cut, plus boot-up sequence of the Indego
        time.sleep(15) 

# Example of how to integrate this into the main zkrx script loop:
# Replace the old FTDI init with:
# hw = ESP32Controller(port='/dev/ttyUSB0')
# 
# Usage remains exactly the same in the brute force loop:
# hw.up()
# hw.right()
# hw.enter()
# hw.power_cycle()