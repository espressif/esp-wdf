# ESP HTTP Client Example

(See the README.md file in the upper level 'examples' directory for more
information about examples.)

`esp_http_client` example demonstrates the usage of `esp_http_client` manager component for building a HTTP client application.

## How to use example

### Hardware & Software Required

This example can be executed in ESP-WASMachine which is based on any ESP32/ESP32-S2/ESP32-S3 series boards, such as ESP-BOX.

> Note: Please check the device is connected with a router.

### Configure the project

Open the project configuration menu (`idf.py menuconfig`), set following parameters under Example Configuration Options:

* Set `Enable HTTP Basic Authentication` of example to be enable or disable.
* Set `Enable HTTP Digest Authentication` of example to be enable or disable.

> Note: Please check the option is match with ESP-WASMachine project.

### Build the sample

You can use the following command to build the project:

```
idf.py build
```

The generated wasm application will be located under folder `build`, such as `esp_http_client.wasm`, etc.

## Run workload

You need to copy the generated wasm file to `ESP-WASMachine/main/fs_image/wasm` and re-program the file system of ESP-WASMachine by `idf.py -p PORT storage-flash` in ESP-WASMachine project.

If you have already connected the serial output to you PC, and open a terminal program for the serial port, you will see some serial output like this:

```
Type 'help' to get the list of commands.
Use UP/DOWN arrows to navigate through command history.
Press TAB when typing command name to auto-complete.
WASMachine>
```

Start the HTTP client:

```bash
WASMachine> iwasm wasm/esp_http_client.wasm
```

The output of HTTP client is like:

```bash
Start http example
HTTP_EVENT_ON_CONNECTED
HTTP_EVENT_HEADER_SENT
HTTP_EVENT_ON_HEADER, key=Date, value=Tue, 09 Aug 2022 07:09:42 GMT
HTTP_EVENT_ON_HEADER, key=Content-Type, value=application/json
HTTP_EVENT_ON_HEADER, key=Content-Length, value=292
HTTP_EVENT_ON_HEADER, key=Connection, value=keep-alive
HTTP_EVENT_ON_HEADER, key=Server, value=gunicorn/19.9.0
HTTP_EVENT_ON_HEADER, key=Access-Control-Allow-Origin, value=*
HTTP_EVENT_ON_HEADER, key=Access-Control-Allow-Credentials, value=true
HTTP_EVENT_ON_DATA, len=282
HTTP_EVENT_ON_DATA, len=10
HTTP_EVENT_ON_FINISH
.
.
.
.
.
.
HTTP Status = 206, content_length = 10
HTTP_EVENT_HEADER_SENT
HTTP_EVENT_ON_HEADER, key=Content-Type, value=text/plain
HTTP_EVENT_ON_HEADER, key=Content-Length, value=10
HTTP_EVENT_ON_HEADER, key=Connection, value=keep-alive
HTTP_EVENT_ON_HEADER, key=Date, value=Tue, 09 Aug 2022 06:05:47 GMT
HTTP_EVENT_ON_HEADER, key=Last-Modified, value=Thu, 24 Feb 2022 13:01:40 GMT
HTTP_EVENT_ON_HEADER, key=x-amz-version-id, value=zW5JZW290Ntf5ONi5QVkzEYgFIvB4dE0
HTTP_EVENT_ON_HEADER, key=Server, value=AmazonS3
HTTP_EVENT_ON_HEADER, key=ETag, value="01736d2357bcbceff8accdcf7a09d6ea"
HTTP_EVENT_ON_HEADER, key=Content-Range, value=bytes 11-20/79
HTTP_EVENT_ON_HEADER, key=X-Cache, value=Hit from cloudfront
HTTP_EVENT_ON_HEADER, key=Via, value=1.1 04904401d608fcf25189f8fad65fe7a4.cloudfront.net (CloudFront)
HTTP_EVENT_ON_HEADER, key=X-Amz-Cf-Pop, value=HKG54-C1
HTTP_EVENT_ON_HEADER, key=X-Amz-Cf-Id, value=SglZiA6e5EePm8YXzZOAc1KWnnCzoSnn5F4PrIWtKx3en0WX_ucOKg==
HTTP_EVENT_ON_HEADER, key=Age, value=3896
HTTP_EVENT_ON_DATA, len=10
HTTP_EVENT_ON_FINISH
HTTP Status = 206, content_length = 10
HTTP_EVENT_DISCONNECTED
Finish http example
```

> Note: Both `No server verification option set` of `http_redirect_to_https` and `couldn't get hostname for :not.existent.url:` of `https_with_invalid_url` are correct behavior.