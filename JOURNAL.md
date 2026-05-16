# CodeDeck Journal

## Design Session 1

**Project:** CodeDeck  
**Started:** 4:32 PM  
**Ended:** 6:59 PM  
**Type of work:** Design, documentation, firmware planning, wiring, CAD, zine

Today I started CodeDeck from scratch. I wanted to make a hardware project that connects to something I already care about: coding in C++. The idea became a small desk gadget for coding focus, with buttons, LEDs, and an OLED display for focus timers, break timers, and simple status feedback.

During this session, I created the GitHub repository and organized the project files. I wrote the first README so someone opening the repo can understand what CodeDeck is, what it does, why I made it, and how it is supposed to be used. I also added a BOM in CSV format with the main parts needed for the project.

I wrote the first version of the Arduino/C++ firmware. The firmware includes focus and break modes, button input, LED output, timer logic, and OLED display updates. It is still untested on real hardware, but it gives the project a real firmware starting point instead of only being a visual design.

I also made a wiring diagram in Wokwi showing the Arduino Nano, OLED display, three buttons, three LEDs, and resistors. After that, I worked on the CAD concept for the case in Tinkercad. The case design includes a screen cutout, three button holes, three LED holes, screw posts, and simple internal electronics blocks to show where the Arduino and display/button parts fit.

Finally, I made the Fallout zine page for CodeDeck and added it to the repository. The page explains the project, shows the design, includes the features, and has a QR code to the GitHub repo.

### Files worked on

- README.md
- bom/bom.csv
- firmware/CodeDeck.ino
- wiring/wiring-diagram.png
- images/full-cad-assembly.png
- images/top-view.png
- images/inside-view.png
- zine/codedeck-zine.png

### What I still need to do

- Get the physical parts
- Build the circuit IRL
- Test and fix the firmware on real hardware
- Improve the case if needed after measuring parts
- Take final photos and demo video after building