# Switch Example

`switch` example demonstrates the usage of `esp-rainmaker` component for building a switch application.

## How to use example

### Hardware & Software Required

This example can be executed in ESP-WASMachine which is based on any ESP32/ESP32-S2/ESP32-S3 series boards, such as ESP-BOX.

For this example, BLE is chosen as the default mode of provisioning, over which the provisioning related communication is to take place.

In the provisioning process the device is configured as a Wi-Fi station with specified credentials.

Once configured, the device will retain the Wi-Fi configuration and BLE is turned off and disabled to free the memory used by the BLE stack after provisioning is complete.

> Note: Since ESP32-S2 does not support BLE, the SoftAP will be the default mode of transport in that case.

### Application Required

ESP RainMaker applications are available for various platforms. See below

#### Platform : Android

For Android, a ESP RainMaker application along with source code is available on GitHub : [esp-rainmaker-android](https://github.com/espressif/esp-rainmaker-android)

#### Platform : iOS

For iOS, a ESP RainMaker application along with source code is available on GitHub : [esp-rainmaker-ios](https://github.com/espressif/esp-rainmaker-ios)

### Configure the project

Open the project configuration menu (`idf.py menuconfig`), set following parameters under ESP RainMaker App Wi-Fi Provisioning Configuration Options:

* Set `Show provisioning QR code` of example to be enable or disable.
* Set `Provisioning Transport method` of example to be BLE/Soft AP.
* Set `Provisioning Name Prefix` of example to be Provisioning Name Prefix.

### Build the sample

You can use the following command to build the project:

```
idf.py build
```

The generated wasm application will be located under folder `build`, such as `switch.wasm`, etc.

## Run workload

You need to copy the generated wasm file to `ESP-WASMachine/main/fs_image/wasm` and re-program the file system of ESP-WASMachine by `idf.py -p PORT storage-flash` in ESP-WASMachine project.

If you have already connected the serial output to you PC, and open a terminal program for the serial port, you will see some serial output like this:

```
Type 'help' to get the list of commands.
Use UP/DOWN arrows to navigate through command history.
Press TAB when typing command name to auto-complete.
WASMachine>
```

Start the switch application:

```bash
WASMachine> iwasm wasm/switch.wasm
```

The output of wifi provisioning is like:

```bash
I (14444) esp_rmaker_work_queue: Work Queue created.
I (14444) esp_claim: Initialising Self Claiming. This may take time.
W (14464) esp_claim: Generating the private key. This may take time.
I (18574) esp_rmaker_node: Node ID ----- 7CDFA1E86C14
I (18574) esp_rmaker_ota: OTA state = 2
I (18574) esp_rmaker_ota_using_topics: OTA enabled with Topics
I (18584) esp_rmaker_time_service: Time service enabled
I (18594) esp_rmaker_time: Initializing SNTP. Using the SNTP server: pool.ntp.org
I (18604) esp_rmaker_core: Starting RainMaker Work Queue task
I (18614) esp_rmaker_work_queue: RainMaker Work Queue task started.
W (18614) BT_INIT: esp_bt_mem_release not implemented, return OK
I (18624) wifi_prov_scheme_ble: BT memory released
Starting provisioning
I (18634) phy_init: phy_version 501,94697a2,Apr  7 2022,20:49:08
W (18634) phy_init: failed to load RF calibration data (0x1102), falling back to full calibration
I (18764) wifi:mode : sta (7c:df:a1:e8:6c:14)
I (18764) wifi:enable tsf
W (18774) BT_INIT: esp_bt_controller_mem_release not implemented, return OK
I (18774) BT_INIT: BT controller compile version [d913766]
I (18784) BT_INIT: Bluetooth MAC: 7c:df:a1:e8:6c:16

I (18784) protocomm_nimble: BLE Host Task Started
I (18784) wifi_prov_mgr: Provisioning started with service name : PROV_E86C14
I (18794) NimBLE: GAP procedure initiated: stop advertising.

I (18814) NimBLE: GAP procedure initiated: advertise;
SI (18814) NimBLE: disc_mode=2
cI (18814) NimBLE:  adv_channel_map=0 own_addr_type=0 adv_filter_policy=0 adv_itvl_min=256 adv_itvl_max=256
I (18824) NimBLE:

I (18804) wifi_provisioning_wrapper: Provisioning started app for Provisioning.
```

Enabling `CONFIG_APP_WIFI_PROV_SHOW_QR` will display a QR code on the serial terminal, which can be scanned from the ESP RainMaker phone apps to start the Wi-Fi provisioning process.

The monitor log should display something like this :

```
Scan this QR code from the ESP RainMaker phone app for Provisioning.
Encoding below text with ECC LVL 0 & QR Code Version 5
{"ver":"v1","name":"PROV_E86C14","pop":"a1e86c14","transport":"ble"}

  █▀▀▀▀▀█ ▄█ ▄▄ █▄▀▀▄▀▄▀█▀█ █▀▀▀▀▀█
  █ ███ █ ▄█▀█ ▄ ▄▄▄█ ▀█▄▄▀ █ ███ █
  █ ▀▀▀ █ ▄ █ ▀▄ ▄█▄ ▀█▀ ▀▀ █ ▀▀▀ █
  ▀▀▀▀▀▀▀ ▀ ▀ █ ▀ █ █ ▀▄█ ▀ ▀▀▀▀▀▀▀
  ▀█▀██ ▀███▀ ▀█▄ ▄▀▄▄▀▄▄ ▀▀▄▀ ▀▄█▄
  ▀ ▀ ▄ ▀  █▄█▀▀ █ ▀▀ ▀█▄▄ █▀▄  ▄█
  ▀ ▄▀▄█▀▀▄█▄▀▄▀ ▀█▀▀▄▄▄▄▀ ▀▄▀▀ ▄▀▄
   ▀▄█▀▄▀▀▀▀█ ▄▀ ▀▀ ▀▄ █▀▄▀█ ▀█ ▄▀▄
   ▀ ▄█ ▀▄██▄ ▀▀▀▀█▀▀▄ ▄    ▄▀▀▀ █▄
  █▀ ▀▀█▀▄█ ▄█▀▀ ▀▄ ▄▄ ▄ ▄  ▄█▀ ▄▀▄
  ▄ ▄ █ ▀▄█▀█▀▄█▀ ▄▀██▀  ▀▀▄▄█▀ ▄ ▄
  █ ▄ ▀▀▀▄███ ▄ ▀█▀▀█▄ █▀▄█ █▀▄▄▄▄▄
  ▀ ▀ ▀▀▀ ▄█▄ ▀▀▀▀▄██▄ ▄ ▄█▀▀▀██▄▄█
  █▀▀▀▀▀█ ▀ ██▀ █▀  ▄  ▄ ▄█ ▀ █ ▄▀
  █ ███ █ █▄ ▀█▀ ▀█▀█▄█▄█ █▀▀██▀▄▀
  █ ▀▀▀ █ █ ▀  ▀ █▄▀█▄██ ▄█ ▀█▄▀█▀
  ▀▀▀▀▀▀▀ ▀▀▀▀ ▀▀▀▀▀ ▀  ▀▀▀ ▀▀   ▀


If QR code is not visible, copy paste the below URL in a browser.
https://rainmaker.espressif.com/qrcode.html?data={"ver":"v1","name":"PROV_E86C14","pop":"a1e86c14","transport":"ble"}
```

Make sure to note down the BLE device name (starting with `PROV_`) displayed in the serial monitor log (eg. PROV_E86C14). This will depend on the MAC ID and will be unique for every device.

Above ESP RainMaker phone apps will perform the provisioning steps, and the monitor log should display something like this :

```
Received Wi-Fi credentials
        SSID     : myssid
        Password : mypassword
.
.
.
I (58594) esp_netif_handlers: sta ip: 172.168.10.183, mask: 255.255.255.0, gw: 172.168.10.1
I (58594) wifi_provisioning_wrapper: Connected with IP Address:172.168.10.183
I (58604) wifi_prov_mgr: STA Got IP
I (58604) wifi_provisioning_wrapper: Provisioning successful
.
.
.
I (58614) esp_claim: Starting the Self Claim Process. This may take time.
I (58614) rmaker_wrapper: RainMaker Claim Started.
I (59694) esp-x509-crt-bundle: Certificate validated
I (62474) HTTP_CLIENT: Body received in fetch header state, 0x3fccb771, 129
I (62864) esp-x509-crt-bundle: Certificate validated
I (62874) NimBLE: GAP procedure initiated: stop advertising.

I (62884) NimBLE: GAP procedure initiated: stop advertising.

I (62894) NimBLE: GAP procedure initiated: terminate connection; conn_handle=1 hci_reason=19

E (62924) protocomm_nimble: Error setting advertisement data; rc = 30
W (62944) Timer: Timer not stopped
W (62954) Timer: Timer not stopped
I (62984) wifi_prov_mgr: Provisioning stopped
W (62984) BT_INIT: esp_bt_mem_release not implemented, return OK
I (62984) wifi_prov_scheme_ble: BTDM memory released
I (65554) HTTP_CLIENT: Body received in fetch header state, 0x3fcccd26, 502
I (65574) esp_claim: Self Claiming was successful. Certificate received.
I (65574) rmaker_wrapper: RainMaker Claim Successful.
I (65604) esp_mqtt_glue: AWS PPI: ?Platform=APN3|A0|RM|ES00|RMDev|1x0|7CDFA1E86C14
I (65604) esp_mqtt_glue: Initialising MQTT
I (65604) esp_mqtt_glue: Connecting to a1p72mufdu6064-ats.iot.us-east-1.amazonaws.com
I (65614) esp_mqtt_glue: Waiting for MQTT connection. This may take time.
I (66664) esp-x509-crt-bundle: Certificate validated
I (69014) esp_mqtt_glue: MQTT Connected
W (69024) rmaker_wrapper: Unhandled RainMaker Common Event: 3
I (69024) esp_rmaker_node_config: Reporting Node Configuration of length 1168 bytes.
I (69044) esp_rmaker_param: Params MQTT Init done.
I (69044) esp_rmaker_param: Reporting params (init): {"Switch":{"Name":"Switch","Power":true},"Time":{"TZ":"","TZ-POSIX":""},"Schedule":{"Schedules":[]},"Scenes":{"Scenes":[]}}
I (69054) esp_rmaker_ota_using_topics: Subscribing to: node/7CDFA1E86C14/otaurl
I (69074) esp_rmaker_user_mapping: MQTT Publish: {"node_id":"7CDFA1E86C14","user_id":"cd96c2f5-a870-42bf-9a80-91e35d9fc17f","secret_key":"ab6c4e1e-9fb7-48fa-8992-a9039c638e3e"}
W (70144) rmaker_wrapper: Unhandled RainMaker Common Event: 5
W (70154) rmaker_wrapper: Unhandled RainMaker Common Event: 5
W (70154) rmaker_wrapper: Unhandled RainMaker Common Event: 5
W (70164) rmaker_wrapper: Unhandled RainMaker Common Event: 5
I (70164) esp_rmaker_user_mapping: User Node association message published successfully.
```

Toggling the button on the phone app and the monitor log should display something like this :

```
Received write request via : Cloud
Received value = false for Switch - Power
.
.
.
Received write request via : Cloud
Received value = true for Switch - Power
```
