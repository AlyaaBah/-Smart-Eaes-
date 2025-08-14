# -Smart-Eaes-
Smart parking and access control system using Arduino and MIT App Inventor. Includes gate, elevator, sliding door, and lighting—all controllable via Bluetooth.

## Abstract  
Smart Eyes is an Arduino-based embedded system designed to simulate a smart facility with automated parking management, access control, and remote operation via a mobile application. The system integrates multiple subsystems including a servo-controlled gate, sliding door, elevator, and distributed lighting, all coordinated through sensor inputs and Bluetooth commands. The project demonstrates practical applications of embedded systems in urban automation and smart infrastructure.

## System Overview  
The system consists of the following functional modules:  
- **Smart Parking Gate**: Tracks vehicle entry and exit using IR sensors and controls gate access based on slot availability.  
- **Sliding Door Mechanism**: Activated by a proximity sensor to simulate automatic entry.  
- **Elevator System**: Operated via push buttons to simulate vertical transport.  
- **Lighting Control**: Three distributed LEDs controlled via Bluetooth commands.  
- **Mobile Application**: Developed using MIT App Inventor to enable remote control of all subsystems.

## Hardware Components  
- Arduino Uno  
- IR Sensors (2 units for entry/exit detection)  
- Ultrasonic Sensor (1 unit for door activation)  
- Servo Motor (for gate control)  
- DC Motors (for elevator and sliding door)  
- Push Buttons (for elevator control)  
- LCD Display (for system feedback)  
- Bluetooth Module  
- LEDs (3 units for lighting indicators)  
- External Power Supply

> *Note: Temperature sensor and second ultrasonic sensor were not used in the final implementation.*

## Software Architecture  
- **Programming Language**: C++ via Arduino IDE  
- **Communication**: Serial Bluetooth interface for mobile control  
- **Display**: LCD for real-time feedback on parking status and system actions  
- **Control Logic**:  
  - Debounced IR sensor readings for accurate vehicle tracking  
  - Servo motor control for gate operation  
  - Distance-based activation of sliding door  
  - Button-triggered elevator movement  
  - Bluetooth command parsing for remote control of all subsystems

## Mobile App Interface  
The mobile application, built using MIT App Inventor, provides intuitive control over all system components. Users can connect via Bluetooth, operate the gate, elevator, sliding door, and toggle lighting with dedicated buttons.

![Smart Eyes App Interface](App.jpg)

## Functional Flow  
1. **Vehicle Entry**:  
   - IR sensor detects incoming vehicle  
   - If slots are available, gate opens and slot count updates  
   - LCD displays confirmation message  
2. **Vehicle Exit**:  
   - IR sensor detects outgoing vehicle  
   - Gate opens and slot count updates  
3. **Sliding Door**:  
   - Activated when proximity is detected  
   - Motor logic ensures full open and close cycle  
4. **Elevator**:  
   - Moves up/down based on button input  
   - Motor stops automatically after each movement  
5. **Lighting System**:  
   - Controlled via Bluetooth commands from the mobile app  
6. **Remote Control**:  
   - All subsystems can be triggered via the app interface

## Applications  
- Smart parking systems  
- Automated building access  
- Educational models for embedded systems  
- Bluetooth-based remote control systems

## Future Enhancements  
- Replace delay functions with non-blocking logic (`millis()`)  
- Add feedback sensors for elevator position  
- Expand mobile app with real-time monitoring and status display  
- Integrate cloud-based control and data logging

---

**Created by Alyaa ⭐**
