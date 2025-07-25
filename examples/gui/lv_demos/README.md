# LVGL generic sample applications

These examples shows LVGL internal demos with RGB LCD.

* [lv_demo_benchmark](./lv_demo_benchmark/)
* [lv_demo_music](./lv_demo_music/)
* [lv_demo_stress](./lv_demo_stress/)
* [lv_demo_widgets](./lv_demo_widgets/)

## How to use example

### Hardware

These examples can be executed in ESP-WASMachine based on the following development boards:

- [ESP32-S3-BOX](https://github.com/espressif/esp-box/blob/v0.3.0/docs/hardware_overview/esp32_s3_box/hardware_overview_for_box_cn.md)

- [ESP32-S3-BOX-Lite](https://github.com/espressif/esp-box/blob/v0.3.0/docs/hardware_overview/esp32_s3_box_lite/hardware_overview_for_lite_cn.md)

- [ESP32-P4-Function-EV-Board](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32p4/esp32-p4-function-ev-board/index.html)

### Configure the project

* Open the project configuration menu (`idf.py menuconfig`)
* Select "Enable LVGL" in the configuration options.

Please note that if the development board is `ESP32-S3-BOX` or `ESP32-S3-BOX-Lite`, you need to enable `CONFIG_LV_COLOR_16_SWAP` under the "LVGL" menu, if the development board is `ESP32-P4-Function-EV-Board`, you need to disable `CONFIG_LV_COLOR_16_SWAP`.

### Build and Install

You can use the following command to build the project:

```
idf.py build
```

The generated wasm application will be located under folder `build`, there are two methods to download and run the application:

1. Store the compiled firmware in the file system and run the WebAssembly application by executing relevant commands. For the specific process, please refer to the relevant [document](https://github.com/espressif/esp-wasmachine/README_CN.md#4.4-Run WebAssembly Application) of ESP-WASMachine.

2. You can also use `host_tool` to remotely install a WebAssembly application to ESP-WASMachine. The command format is following:

```
host_tool -S 192.168.31.203 -P 8080 -i gui -f build/lv_demo_widgets.wasm
```

- Note that `192.168.31.203` is the IP address of ESP-WASMachine.

If you have already connect the serial output to you PC, and open a terminal program for the serial port, you will see some serial output like this:

## Example Output

```
 (22988) wm_wamr_app_mgr: host is established!
I (22989) wm_wamr_app_mgr: recv 2048 bytes from host
I (22990) wm_wamr_app_mgr: recv 2048 bytes from host
I (22992) wm_wamr_app_mgr: recv 2048 bytes from host
I (23003) wm_wamr_app_mgr: recv 2048 bytes from host
I (23005) wm_wamr_app_mgr: recv 2048 bytes from host
I (23006) wm_wamr_app_mgr: recv 1280 bytes from host
I (23017) wm_wamr_app_mgr: recv 2048 bytes from host
I (23018) wm_wamr_app_mgr: recv 2048 bytes from host
I (23020) wm_wamr_app_mgr: recv 2048 bytes from host
I (23031) wm_wamr_app_mgr: recv 2048 bytes from host
I (23033) wm_wamr_app_mgr: recv 2048 bytes from host
I (23034) wm_wamr_app_mgr: recv 2048 bytes from host
I (23046) wm_wamr_app_mgr: recv 2048 bytes from host
I (23047) wm_wamr_app_mgr: recv 2048 bytes from host
I (23048) wm_wamr_app_mgr: recv 896 bytes from host
I (23060) wm_wamr_app_mgr: recv 2048 bytes from host
I (23061) wm_wamr_app_mgr: recv 2048 bytes from host
I (23062) wm_wamr_app_mgr: recv 224 bytes from host
I (23073) wm_wamr_app_mgr: recv 2048 bytes from host
I (23074) wm_wamr_app_mgr: recv 2048 bytes from host
I (23075) wm_wamr_app_mgr: recv 224 bytes from host
I (23089) wm_wamr_app_mgr: recv 1440 bytes from host
I (23091) wm_wamr_app_mgr: recv 2048 bytes from host
I (23092) wm_wamr_app_mgr: recv 2048 bytes from host
I (23104) wm_wamr_app_mgr: recv 2048 bytes from host
I (23105) wm_wamr_app_mgr: recv 2048 bytes from host
I (23106) wm_wamr_app_mgr: recv 1664 bytes from host
I (23118) wm_wamr_app_mgr: recv 2048 bytes from host
I (23119) wm_wamr_app_mgr: recv 2048 bytes from host
I (23120) wm_wamr_app_mgr: recv 448 bytes from host
I (23131) wm_wamr_app_mgr: recv 2048 bytes from host
I (23133) wm_wamr_app_mgr: recv 2048 bytes from host
I (23134) wm_wamr_app_mgr: recv 2048 bytes from host
I (23146) wm_wamr_app_mgr: recv 2048 bytes from host
I (23147) wm_wamr_app_mgr: recv 2048 bytes from host
I (23148) wm_wamr_app_mgr: recv 1280 bytes from host
I (23159) wm_wamr_app_mgr: recv 2048 bytes from host
I (23161) wm_wamr_app_mgr: recv 2048 bytes from host
I (23162) wm_wamr_app_mgr: recv 224 bytes from host
I (23173) wm_wamr_app_mgr: recv 2048 bytes from host
I (23174) wm_wamr_app_mgr: recv 2048 bytes from host
I (23175) wm_wamr_app_mgr: recv 1440 bytes from host
I (23187) wm_wamr_app_mgr: recv 2048 bytes from host
I (23188) wm_wamr_app_mgr: recv 2048 bytes from host
I (23189) wm_wamr_app_mgr: recv 448 bytes from host
I (23200) wm_wamr_app_mgr: recv 2048 bytes from host
I (23202) wm_wamr_app_mgr: recv 2048 bytes from host
I (23203) wm_wamr_app_mgr: recv 2048 bytes from host
I (23214) wm_wamr_app_mgr: recv 2048 bytes from host
I (23216) wm_wamr_app_mgr: recv 2048 bytes from host
I (23217) wm_wamr_app_mgr: recv 2048 bytes from host
I (23229) wm_wamr_app_mgr: recv 2048 bytes from host
I (23230) wm_wamr_app_mgr: recv 2048 bytes from host
I (23231) wm_wamr_app_mgr: recv 1664 bytes from host
I (23243) wm_wamr_app_mgr: recv 2048 bytes from host
I (23244) wm_wamr_app_mgr: recv 2048 bytes from host
I (23245) wm_wamr_app_mgr: recv 896 bytes from host
I (23256) wm_wamr_app_mgr: recv 2048 bytes from host
I (23258) wm_wamr_app_mgr: recv 2048 bytes from host
I (23259) wm_wamr_app_mgr: recv 224 bytes from host
I (23270) wm_wamr_app_mgr: recv 2048 bytes from host
I (23271) wm_wamr_app_mgr: recv 2048 bytes from host
I (23272) wm_wamr_app_mgr: recv 1440 bytes from host
I (23284) wm_wamr_app_mgr: recv 224 bytes from host
I (23285) wm_wamr_app_mgr: recv 1440 bytes from host
I (23286) wm_wamr_app_mgr: recv 1440 bytes from host
I (23297) wm_wamr_app_mgr: recv 2048 bytes from host
I (23299) wm_wamr_app_mgr: recv 2048 bytes from host
I (23300) wm_wamr_app_mgr: recv 1664 bytes from host
I (23311) wm_wamr_app_mgr: recv 2048 bytes from host
I (23313) wm_wamr_app_mgr: recv 192 bytes from host
Install WASM app success!
WASM app 'app0' started
I (23368) wm_wamr_app_mgr: send 8 bytes to host
I (23368) ESP32_P4_EV: Setting LCD backlight: 100%
I (23369) wm_wamr_app_mgr: send 16 bytes to host
sent 16 bytes to host
I (23385) wm_wamr_app_mgr: close host socket 55

```

## Troubleshooting

* Program upload failure

    * Hardware connection is not correct: run `idf.py -p PORT monitor`, and reboot your board to see if there are any output logs.
    * The baud rate for downloading is too high: lower your baud rate in the `menuconfig` menu, and try again.

* Nothing on screen

    * Check the hardware connection between `ESP-BOX` or `ESP32-P4-Function-EV-Board` and screen
    * Check [ESP-WDF LVGL version](https://github.com/espressif/esp-wdf/blob/master/components/extended_wasm_app/esp_lvgl/include/esp_lvgl.h) and [ESP-WASMachine LVGL version](https://github.com/espressif/esp-wasmachine/blob/master/components/wasmachine_ext_wasm_native/private_include/wm_ext_wasm_native_lvgl.h): the latest ESP-WDF LVGL application and ESP-WASMachine LVGL components are component are Espressif's customized version `1.0.0`, corresponding to the LVGL upstream version `8.4.0`.
    Custom LVGL version number contains the following fields: `Major.Minor.patch`.
    If the `Major` or `Minor` part of the LVGL version of ESP-WDF and ESP-WASMachine does not match, the LVGL version of ESP-WDF is incompatible with that of ESP-WASMachine.

For any technical queries, please open an [issue](https://github.com/espressif/esp-wdf/issues) on GitHub. We will get back to you soon.