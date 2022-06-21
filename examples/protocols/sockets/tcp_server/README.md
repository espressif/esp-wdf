
# TCP Server example

(See the README.md file in the upper level 'examples' directory for more information about examples.)

The application creates a TCP socket with the specified port number and waits for a connection request from the client. After accepting a request from the client, connection between server and client is established and the application waits for some data to be received from the client. Received data are printed as ASCII text and retransmitted back to the client.

## How to use example

In order to create TCP client that communicates with TCP server example, choose one of the following options.

There are many host-side tools which can be used to interact with the UDP/TCP server/client. 
One command line tool is [netcat](http://netcat.sourceforge.net) which can send and receive many kinds of packets. 
Note: please replace `192.168.0.167 3333` with desired IPV4/IPV6 address (displayed in monitor console) and port number in the following command.

### TCP client using netcat
```
nc 192.168.0.167 3333
```

### Hardware & Software Required

This example can be executed in ESP-WASMachine which is based on any ESP32/ESP32-S2/ESP32-S3 series boards, such as ESP-BOX.

### Configure the project

Open the project configuration menu (`idf.py menuconfig`), set following parameters under Example Configuration Options:

* Set `IP version` of the example to be IPV4 or IPV6.

* Set `Port` number of the socket, that server example will create.

* Set `TCP keep-alive idle time(s)` value of TCP keep alive idle time. This time is the time between the last data transmission.

* Set `TCP keep-alive interval time(s)` value of TCP keep alive interval time. This time is the interval time of keepalive probe packets.

* Set `TCP keep-alive packet retry send counts` value of TCP keep alive packet retry send counts. This is the number of retries of the keepalive probe packet.

## Build the sample

You can use the following command to build the project:

```
idf.py build
```

The generated wasm application will be located under folder `build`, such as `tcp_server.wasm`, etc. 

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

Start the tcp server, which opens configured port and waits for clients to connect and receive data sent from the client (application).

```bash
WASMachine> iwasm --addr-pool=0.0.0.0 wasm/tcp_server.wasm
```

The output of server is like:

```bash
Socket created
Socket bound, port 3333
Socket listening
Received 5 bytes: 11111
Connection closed
Socket listening
```