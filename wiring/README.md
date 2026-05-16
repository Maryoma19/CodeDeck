# Wiring

Put the wiring diagram here.

Suggested pin map:

| Component | Microcontroller Pin |
|---|---|
| Mode button | D2 |
| Start/Pause button | D3 |
| Reset button | D4 |
| Focus LED | D8 |
| Break LED | D9 |
| Done LED | D10 |
| OLED SDA | A4 |
| OLED SCL | A5 |
| OLED VCC | 5V or 3.3V |
| OLED GND | GND |

Button wiring:

- One side of each button goes to the assigned digital pin.
- The other side goes to GND.
- The firmware uses `INPUT_PULLUP`, so external button resistors are optional.

LED wiring:

- Digital pin to resistor.
- Resistor to LED anode.
- LED cathode to GND.

