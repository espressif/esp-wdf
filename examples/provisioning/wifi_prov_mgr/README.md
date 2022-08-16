# Wi-Fi Provisioning Manager Example

(See the README.md file in the upper level 'examples' directory for more information about examples.)

`wifi_prov_mgr` example demonstrates the usage of `wifi_provisioning` manager component for building a provisioning application.

## How to use example

### Hardware & Software Required

This example can be executed in ESP-WASMachine which is based on any ESP32/ESP32-S2/ESP32-S3 series boards, such as ESP-BOX.

For this example, BLE is chosen as the default mode of transport, over which the provisioning related communication is to take place.

In the provisioning process the device is configured as a Wi-Fi station with specified credentials. 

Once configured, the device will retain the Wi-Fi configuration and BLE is turned off and disabled to free the memory used by the BLE stack after provisioning is complete.

> Note: Since ESP32-S2 does not support BLE, the SoftAP will be the default mode of transport in that case.

### Application Required

Provisioning applications are available for various platforms. See below

#### Platform : Android

For Android, a provisioning application along with source code is available on GitHub : [esp-idf-provisioning-android](https://github.com/espressif/esp-idf-provisioning-android)

#### Platform : iOS

For iOS, a provisioning application along with source code is available on GitHub : [esp-idf-provisioning-ios](https://github.com/espressif/esp-idf-provisioning-ios)

### Configure the project

Open the project configuration menu (`idf.py menuconfig`), set following parameters under Example Configuration Options:

* Set `Provisioning Transport` of example to be BLE/Soft AP.
* Set `Show provisioning QR code` of example to be enable or disable.
* Set `Reset provisioned status of the device` of example to be enable or disable.

### Build the sample

You can use the following command to build the project:

```
idf.py build
```

The generated wasm application will be located under folder `build`, such as `wifi_prov_mgr.wasm`, etc.

## Run workload

You need to copy the generated wasm file to `ESP-WASMachine/main/fs_image/wasm` and re-program the file system of ESP-WASMachine by `idf.py -p PORT storage-flash` in ESP-WASMachine project.

If you have already connected the serial output to you PC, and open a terminal program for the serial port, you will see some serial output like this:

```
Type 'help' to get the list of commands.
Use UP/DOWN arrows to navigate through command history.
Press TAB when typing command name to auto-complete.
WASMachine>
```

Start the wifi provisioning:

```bash
WASMachine> iwasm wasm/wifi_prov_mgr.wasm
```

The output of wifi provisioning is like:

```bash
Starting provisioning
Provisioning started with service name : PROV_E86C14
```

Enabling `CONFIG_EXAMPLE_PROV_SHOW_QR` will display a QR code on the serial terminal, which can be scanned from the ESP Provisioning phone apps to start the Wi-Fi provisioning process.

The monitor log should display something like this :

```
Provisioning started
Scan this QR code from the provisioning application for Provisioning.
Encoding below text with ECC LVL 0 & QR Code Version 10
{"ver":"v1","name":"PROV_E86C14","pop":"abcd1234","transport":"ble"}
GAP procedure initiated: advertise; disc_mode=2 adv_channel_map=0 own_addr_type=0 adv_filter_policy=0 adv_itvl_min=256 adv_itvl_max=256

  █▀▀▀▀▀█ ▀▀▀█▄█   ▀▀▄ █▄ ▀ █▀▀▀▀▀█
  █ ███ █  ▀▄█ █▄ ▀▄█ ▄██ █ █ ███ █
  █ ▀▀▀ █  ▄▀█▀▄▀ ▀█▄▀  ██  █ ▀▀▀ █
  ▀▀▀▀▀▀▀ █▄▀ █▄█▄█ ▀ █ █ ▀ ▀▀▀▀▀▀▀
  ▀▀ ▀▀ ▀  ▀▄ ▀▄ ▄▀▀▀█ ▀▄ ▀ ▀▄▄ ▄▄▀
  ███▄█▄▀ █▀  ▀▀▀▀▄▄█   █▀ █  ▄█▄█▀
  ▀███▀ ▀▄▄██ ▄▄██▄ ▀▀▀▀   ▄▀█ ▀▄▄▀
  ▄███  ▀██▀▀ ▄ ▄█▄▀▀█▄ ▀▄▀▄▄█  ▄
  ▀█▀ █▄▀▀ ▀▀█▀▀ █▀▄▀▄▀ ▄█  ███▄ ██
  ██▀█  ▀▄█ █▄▀▄███▀▄▀█ ▀█ █▀▀ ▀▄▄▀
  █▄▀▄█▀▀ ▀▄ ▀▄▄█▄▀▀█▄█▄█▀▀█ ▀▄ ▄▀
  █ ▄█▄ ▀ ▄▀ █▄  ▀█▄█▄▀▀█▀█ ▄█ ▀▄▄█
  ▀▀▀▀  ▀ █▀█▀▀▄▄██▄█▀█ ▀██▀▀▀█▄▄▀
  █▀▀▀▀▀█   ▄█▀▀▀██ ▄▀▄ █▄█ ▀ █ ▄ ▄
  █ ███ █ █ ▀▄█▀▀█▀▄█▄▄ ▀██▀▀▀▀▄▄▀▀
  █ ▀▀▀ █ ▄█ ▀ ▄█▀█ █▀ ▀▀███▄▀█ █▄█
  ▀▀▀▀▀▀▀ ▀  ▀  ▀▀ ▀     ▀▀▀▀▀▀


If QR code is not visible, copy paste the below URL in a browser.
https://espressif.github.io/esp-jumpstart/qrcode.html?data={"ver":"v1","name":"PROV_E86C14","pop":"abcd1234","transport":"ble"}
```

Make sure to note down the BLE device name (starting with `PROV_`) displayed in the serial monitor log (eg. PROV_E86C14). This will depend on the MAC ID and will be unique for every device.

Above ESP Provisioning phone apps will perform the provisioning steps, and the monitor log should display something like this :

```
Received Wi-Fi credentials
        SSID     : myssid
        Password : mypassword
.
.
.
I (77502) esp_netif_handlers: sta ip: 192.168.3.164, mask: 255.255.255.0, gw: 192.168.3.1
Connected with IP Address:192.168.3.164
I (77512) wifi_prov_mgr: STA Got IP
Provisioning successful
wifi_prov_mgr: Provisioning stopped
```
