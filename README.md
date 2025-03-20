# OBDII-Emulator

## About

OBDII-Emulator is an ESP32-based tool designed to emulate data sent by OBDII interface. It serves as a testing utility for the [CAR-BT-HMI](https://github.com/Lankow/car-bt-hmi) project. The emulator simulates real-time OBD-II data, responding to Bluetooth read requests with dynamically changing values based on a cycle time.

### OBD-II PIDs

OBDII-Emulation is performed as per [Wikipedia OBD-II PIDS](https://en.wikipedia.org/wiki/OBD-II_PIDs).

- **Implemented OBD-II PIDs**
  - Engine Speed `01 0C`
  - Vehicle Speed `01 0D`

### Key Features

- **Configuration**

  - The ESP32 acts as an access point with a static IP `(192.168.4.2)`.
  - Allows users to modify settings such as cycle time, min/max values, and increment steps.
  - Stored in `/data/default_config.json`, users can adjust SSID, password, and OBD parameter settings.
  - Configuration is stored in flash memory, allowing persistence across reboots.

- **Emulation**
  - Simulates real-time updates to OBD parameters and responds to Bluetooth requests with corresponding values.
  - Connect to `OBDII-ESP` via Bluetooth in order to send requests.

### Requirements

- **Software**:

  - VSCode as IDE
  - PlatformIO

- **Hardware**:
  - ESP32 board

### Using Commands

- Build: `pio run`
- Upload: `pio run nobuild -t upload`
- Upload Filesystem Image (default_config.json): `pio run -t uploadfs`
