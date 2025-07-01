# Sailing Start Timer

This project is a microcontroller-based horn system designed to automate race starts for sailboat regattas. It replaces manual countdowns and whistle systems with a reliable, consistent, and rugged solution tailored to race officials on the water.

## Summary

The Sailing Start Timer outputs a sequence of horn blasts that follow standard sailing race countdown rules. A single button press initiates the sequence, allowing race officials to focus on managing boats instead of watching the clock. The system is built with an Arduino and a waterproof speaker, and was designed to be both portable and weather-resistant.

## Features

- Automated horn sequence for 5-minute, 3-minute, or custom countdowns
- One-button operation for simple race start triggering
- Loud, waterproof horn for outdoor use
- Rugged and portable design suitable for mark boats or committee boats
- Custom enclosure and PCB designed for durability

## Hardware

- Arduino microcontroller
- Waterproof speaker module
- Push-button input
- Custom 3D-printed or machined enclosure
- Power system for extended outdoor operation (e.g. 12V or battery pack)

## Software

- Written in Arduino C++
- Timer-based logic to produce horn blasts at key intervals
- Debounced user input handling
- Configurable countdown intervals via code or DIP switches (if implemented)

## How It Works

1. User presses a button to trigger the countdown.
2. The microcontroller runs a timed sequence of horn blasts:
   - Long horn at 5:00
   - Warning signals at 4:00, 1:00, and 0:00 (based on racing rules)
3. Horn blasts are output through a waterproof horn module at full volume.
4. System resets automatically or after user input.

## Use Case

This device is intended for use by sailing race officials on the water. It simplifies race starts, ensures consistent timing, and reduces errors from manual systems.

## Author

**Brian Zagalsky**  
