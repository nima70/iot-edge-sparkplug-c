# TAHU MQTT Sparkplug B Example
This project demonstrates a simple MQTT Sparkplug B implementation using the Mosquitto MQTT client library and the Tahu Protobuf library.

## Project Structure
```plaintext
TAHU_TEST/
│
├── include/                   # Header files
│   ├── pb_common.h            # Protobuf common utilities
│   ├── pb_decode.h            # Protobuf decoder
│   ├── pb_encode.h            # Protobuf encoder
│   ├── pb.h                   # Protobuf definitions
│   ├── tahu.h                 # Tahu Sparkplug helper utilities
│   └── tahu.pb.h              # Tahu Protobuf definitions
│
├── lib/                       # Compiled library files
│   └── libtahu.so             # Tahu shared library
│
├── src/                       # Source files
│   ├── publisher.c            # Publisher application
│   └── subscriber.c           # Subscriber application
│
├── Makefile                   # Build configuration
└── README.md                  # Project documentation
```
## Dependencies
Ensure the following libraries are installed:

- Mosquitto (MQTT Client Library)
- Protobuf (Protocol Buffers)
- Tahu (Sparkplug B Protobuf Implementation)

## How to Build
Run the following commands to build the project:

Clean previous builds:

```bash
make clean
```
Build the shared library and executable files:

```bash
make
```
This will create two executables:

- publisher: Publishes Sparkplug B messages.
- subscriber: Subscribes to Sparkplug B messages and decodes them.

## How to Run
Start the Mosquitto Broker:

```bash
mosquitto -v
```
Run the Subscriber:

```bash
./subscriber
```
Run the Publisher:

```bash
./publisher
```
The subscriber will display incoming messages on the terminal.

## Example Topics
The project uses the following Sparkplug B topic structure:

```bash
spBv1.0/MyGroup/DBIRTH/MyNode/MyDevice
```
## Notes
The METRIC_DATA_TYPE_INT32 constant is defined manually in the source code.
Ensure the Tahu shared library (libtahu.so) is accessible via LD_LIBRARY_PATH.

## License
This project uses the Eclipse Public License 2.0.

## Contributors
Cirrus Link Solutions - Original Sparkplug B implementation.
Nima Shokouhfar - Adapted and implemented for testing.
Let me know if you need further refinements or additions! 🚀