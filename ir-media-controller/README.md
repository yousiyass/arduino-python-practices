## 🎛️ IR Media Controller

This is a practical hardware-software integration experiment. The goal of this project is to control the PC's media settings (volume, playback) remotely using a standard IR (Infrared) remote control and a microcontroller.

It serves as a great exercise in reading sensor data (IR receiver), handling hex codes, and sending string commands over a Serial connection.

### System Architecture

The project is split into two main parts:

* **Hardware (Arduino):** Uses an IR receiver to capture signals from a remote control. It translates these IR signals into specific text commands and sends them via the COM port.
* **Software (Python):** Runs continuously on the host PC. It listens to the Serial port and executes the corresponding media actions on the operating system whenever a valid command is received.

### Supported Commands
I mapped the remote buttons to the following standard media functions:
* `volume_up` 
* `volume_down` 
* `mute`
* `next_track` 
* `prev_track` 
* `play_pause`

### Developer Notes & Lessons Learned
During the development, I encountered `UnicodeDecodeError (0x80)` on the Python side. I learned that different IR remotes use different protocols, and unmapped hex values or signal noise can send "gibberish" bytes over UART. Handling these exceptions in Python with `errors='ignore'` was a key takeaway from this build.
