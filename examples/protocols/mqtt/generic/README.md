# ESP-MQTT Generic Sample application

(See the README.md file in the upper level 'examples' directory for more information about examples.)

This example connects to the broker mqtt.eclipseprojects.io using ssl/tcp/ws/wss transport and as a demonstration subscribes/unsubscribes and send a message on certain topic.
(Please note that the public broker is maintained by the community so may not be always available, for details please see this [disclaimer](https://iot.eclipse.org/getting-started/#sandboxes))

It uses ESP-MQTT library which implements mqtt client to connect to mqtt broker.

## How to use example

### Hardware & Software Required

This example can be executed in ESP-WASMachine which is based on any ESP32/ESP32-S2/ESP32-S3 series boards, such as ESP-BOX.

### Configure the project

* Open the project configuration menu (`idf.py menuconfig`)
* Select MQTT broker under "Example Configuration" menu. It supports SSL/TCP/WS/WSS.

PEM certificate for this example could be extracted from an openssl `s_client` command connecting to mqtt.eclipseprojects.io.
In case a host operating system has `openssl` and `sed` packages installed, one could execute the following command to download and save the root certificate to a file (Note for Windows users: Both Linux like environment or Windows native packages may be used).
```
echo "" | openssl s_client -showcerts -connect mqtt.eclipseprojects.io:8883 | sed -n "1,/Root/d; /BEGIN/,/END/p" | openssl x509 -outform PEM >mqtt_eclipse_org.pem
```
Please note that this is not a general command for downloading a root certificate for an arbitrary host;
this command works with mqtt.eclipseprojects.io as the site provides root certificate in the chain, which then could be extracted
with text operation.

### Build and Install

You can use the following command to build the project:

```
idf.py build
```

The generated wasm application will be located under folder `build`. You can use `host_tool` to install wasm application to ESP-WASMachine.

```
host_tool -S 192.168.31.203 -P 8080 -i mqtt -f build/mqtt_generic.wasm
```

- Note that `192.168.31.203` is the IP address of ESP-WASMachine.

If you have already connect the serial output to you PC, and open a terminal program for the serial port, you will see some serial output like this:

## Example Output

```
Install WASM app success!
WASM app 'mqtt' started
MQTT_EVENT_CONNECTED
sent subscribe successful, msg_id=9369
sent subscribe successful, msg_id=7058
sent unsubscribe successful, msg_id=50818
MQTT_EVENT_SUBSCRIBED, msg_id=0
sent publish successful, msg_id=0
MQTT_EVENT_SUBSCRIBED, msg_id=0
sent publish successful, msg_id=0
MQTT_EVENT_UNSUBSCRIBED, msg_id=0
MQTT_EVENT_DATA
TOPIC=/topic/qos0
DATA=data
MQTT_EVENT_DATA
TOPIC=/topic/qos0
DATA=data
```

