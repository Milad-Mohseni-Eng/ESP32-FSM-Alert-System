# ESP32 FSM Alert System

Finite State Machine (FSM)-based embedded monitoring system using ESP32, OLED display, LEDs, buzzer, and button interaction.

---

## Features

- Finite State Machine (FSM) architecture
- OLED real-time status display
- Multi-state system behavior
- Short press and long press detection
- Timeout-based state transitions
- LED state indicators
- Buzzer alert feedback

---

## System States

| State | Behavior |
|-------|----------|
| OFF | All LEDs OFF |
| IDLE | LED1 ON |
| ALERT | LED2 ON |
| ERROR | LED3 ON |
| ACTIVE | All LEDs ON |

---

## State Logic

- Short button press → IDLE
- Long button press (>3s) → ACTIVE
- No interaction for 3 seconds → ALERT
- No interaction for 7 seconds → ERROR

---

## Hardware Used

- ESP32 Dev Board
- SSD1306 OLED Display (I2C)
- Push Button
- 3 LEDs
- Active Buzzer
- Breadboard + jumper wires

---

## Pin Configuration

| Component | GPIO |
|-----------|------|
| LED1 | 15 |
| LED2 | 2 |
| LED3 | 4 |
| Buzzer | 14 |
| Button | 13 |
| OLED SDA | 21 |
| OLED SCL | 22 |

---

## Libraries Used

- Wire
- Adafruit_GFX
- Adafruit_SSD1306

---

## Wiring

### OLED
- SDA → GPIO21
- SCL → GPIO22
- VCC → 3.3V
- GND → GND

### LEDs
- LED1 → GPIO15
- LED2 → GPIO2
- LED3 → GPIO4

### Button
- One side → GPIO13
- Other side → GND

### Buzzer
- Positive → GPIO14
- Negative → GND

---

## Project Structure

ESP32-FSM-Alert-System/
│
├── src/
│   └── main.ino
│
├── images/
│   ├── wiring.jpg
│   └── oled_demo.jpg
│
├── README.md
└── LICENSE

---

## Embedded Concepts Demonstrated

- Finite State Machines (FSM)
- GPIO control
- OLED graphics
- Event-driven programming
- Timeout monitoring
- Long press detection
- Embedded UI feedback

---

## Author

Milad Mohseni

Embedded Systems & IoT
