
# TCP Client example

(See the README.md file in the upper level 'examples' directory for more information about examples.)

The application creates a TCP socket and tries to connect to the server with predefined IP address and port number. When a connection is successfully established, the application sends message and waits for the answer. After the server's reply, application prints received reply as ASCII text, waits for 2 seconds and sends another message.

## How to use example

In order to create TCP server that communicates with TCP Client example, choose one of the following options.

There are many host-side tools which can be used to interact with the UDP/TCP server/client. 
One command line tool is [netcat](http://netcat.sourceforge.net) which can send and receive many kinds of packets. 
Note: please replace `192.168.0.167 3333` with desired IPV4/IPV6 address (displayed in monitor console) and port number in the following command.

### TCP server using netcat
```
nc -l 192.168.0.167 3333
```

### Hardware & Software Required

This example can be executed in ESP-WASMachine which is based on any ESP32/ESP32-S2/ESP32-S3 series boards, such as ESP-BOX.

### Configure the project

Open the project configuration menu (`idf.py menuconfig`), set following parameters under Example Configuration Options:

* Set `IP version` of example to be IPV4 or IPV6.

* Set `IPV4 Address` in case your chose IP version IPV4 above.

* Set `IPV6 Address` in case your chose IP version IPV6 above.

* Set `Port` number that represents remote port the example will connect to.

## Build the sample

You can use the following command to build the project:

```
idf.py build
```

The generated wasm application will be located under folder `build`, such as `tcp_client.wasm`, etc. 

> Note that `iwasm` of ESP-WASMachine is built with libc-wasi and lib-pthread enabled.

## Run workload

You need to copy the generated wasm file to `ESP-WASMachine/main/fs_image/wasm` and re-program the file system of ESP-WASMachine by `idf.py -p PORT storage-flash` in ESP-WASMachine project.

If you have already connected the serial output to you PC, and open a terminal program for the serial port, you will see some serial output like this:

```
Type 'help' to get the list of commands.
Use UP/DOWN arrows to navigate through command history.
Press TAB when typing command name to auto-complete.
WASMachine>
```

Start the tcp client, which opens configured IP addr and port, waits for connected with TCP server and receive data sent from the server (application).

```bash
WASMachine> iwasm --addr-pool=0.0.0.0 wasm/tcp_client.wasm
```

The output of server is like:

```bash
Socket created, connecting to 192.168.0.167:3333
Successfully connected
Received 1 bytes from 192.168.0.167
Received 0 bytes from 192.168.0.167:

recv failed: errno 0
Shutting down socket and restarting...
Socket created, connecting to 192.168.0.167:3333
Socket unable to connect: errno 0
```