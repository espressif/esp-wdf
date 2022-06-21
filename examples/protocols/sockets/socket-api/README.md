# "socket-api" sample introduction

(See the README.md file in the upper level 'examples' directory for more information about examples.)

This sample demonstrates how to use WAMR socket-api to develop wasm network applications.
Three wasm applications are provided: send_rcv, tcp-server and tcp-client, and this sample demonstrates
how they communicate with each other.

## How to use example

### Hardware & Software Required

This example can be executed in ESP-WASMachine which is based on any ESP32/ESP32-S2/ESP32-S3 series boards, such as ESP-BOX.

### Build the sample

You can use the following command to build the project:

```
idf.py build
```

The generated wasm application will be located under folder `build`, such as `tcp_server.wasm`, `tcp_client.wasm`, `send_recv.wasm`, etc. 

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

Start the tcp server, which opens port 1234 and waits for clients to connect.

```bash
WASMachine> iwasm --addr-pool=0.0.0.0 wasm/tcp_server.wasm
```

The output of server is like:

```bash
[Server] Create socket
[Server] Bind socket
[Server] Listening on socket
[Server] Wait for clients to connect ..
[Server] Client connected
[Server] Communicate with the new connection #7 @ 0x1 ..
[Server] Shuting down the new connection #7 ..
```

Start the tcp client, which connects the server and receives message.

```bash
WASMachine> iwasm --addr-pool=127.0.0.1 wasm/tcp_client.wasm
```

The output of client is like:

```bash
[Client] Create socket
[Client] Connect socket
[Client] Client receive
[Client] 115 bytes received:
Buffer recieved:
Say Hi from the Server
Say Hi from the Server
Say Hi from the Server
Say Hi from the Server
Say Hi from the Server

[Client] BYE
```

`send_recv.wasm` contains a thread as a server and a thread as a client. They
send and receive data via 127.0.0.1:1234.

```bash
WASMachine> iwasm --addr-pool=127.0.0.1 wasm/send_recv.wasm
```

The output is:

```bash
Server is online ...
Client is running...
Start receiving.
Start sending.
Send 106 bytes successfully!
Receive 106 bytes successlly!
Data:
  The stars shine down
  It brings us light
  Light comes down
  To make us paths
  It watches us
  And mourns for us
```

Refer to [socket api document](https://github.com/bytecodealliance/wasm-micro-runtime/blob/main/doc/socket_api.md) for more details.
