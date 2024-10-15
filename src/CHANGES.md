# Development Changes

## 0.8.152 - 2024-10-07
* patching MqTT library to prevent raise conditions while using semaphores
* update ESP32 espressif platform to `0.6.9`
* update ESPAsyncWebServer to `3.3.12`
* merge: avoid using pkg_resources because it's deprecated in python 3.12 #1759
* merge: HA discovery IP address fix, HA json output fix #1760

## 0.8.151 - 2024-10-03
* don't interrupt current command by setting a new limit #1757
* add button for CMT inverters to catch them independend on which frequency they were before #1749
* increased communication queue length from 100 to 200 for ESP32-S3

## 0.8.150 - 2024-10-02
* fix nullptr exception
* modified MqTT to not publish while not connected
* removed patch for Webserver library - obsolete

## 0.8.149 - 2024-10-01
* fixed send power limit #1757
* merged: Fix minor typos #1758
* fix redirect after login with newest webserver version

## 0.8.148 - 2024-09-30
* fixed send power limit #1757
* fix redirect after login

## 0.8.147 - 2024-09-29
* improved queue, added mutex
* fixed send power limit #1757

## 0.8.146 - 2024-09-23
* fix reset ticker #1754
* disable MqTT second and minute ticker on network loss
* converted many `std::bind` to its lambda pendant
* fix redirect after login

## 0.8.145 - 2024-09-22
* fix NTP related issues #1748 #1752
* fix MqTT discovery total #1715
* upgrade webserver version for ESP32 devices

## 0.8.144 - 2024-09-14
* fix NTP lookup if internet connection is not there
* added fallback for NTP to gateway IP

## 0.8.143 - 2024-08-29
* fixed crash #1743

## 0.8.142 - 2024-08-28
* merge PR: add read_temp_c to system + mqtt #1739
* improved sending limits of multiple inverters in very short timeframe #1726
* don't show '0 dBm' once no inverter is available, changed to '-- dBm'

## 0.8.141 - 2024-08-16
* switch AsyncWebserver to https://github.com/mathieucarbou/ESPAsyncWebServer
* fix missing translations to German #1717
* increased maximum number of alarms to 50 for ESP32 #1470
* fix German translation #1688
* fix display of delete and edit buttons in `/setup` #1372
* fix display IP in ePaper display (ETH or WiFi, static or DHCP) #1439

# RELEASE 0.8.140 - 2024-08-16

## 0.8.139 - 2024-08-15
* fix reload after save for WiFi configurations (5s -> 20s)

## 0.8.138 - 2024-08-15
* fix ePaper not functional #1722

## 0.8.137 - 2024-08-13
* fix storage of timezone and region #1723

## 0.8.136 - 2024-08-12
* fix save settings for ESP32 devices #1720

## 0.8.135 - 2024-08-11
* translated `/system` #1717
* added default pin seetings for opendtufusion board
* fixed ethernet static IP
* fixed ethernet MAC address read back

## 0.8.134 - 2024-08-10
* combined Ethernet and WiFi variants - Ethernet is now always included, but needs to be enabled if needed
* improved statistic data in `/system`
* redesigned `/system`

## 0.8.133 - 2024-08-10
* Ethernet variants now support WiFi as fall back / configuration

## 0.8.132 - 2024-08-09
* fix boot loop once no ePaper is connected #1713, #1714
* improved refresh routine of ePeper
* added default pin seetings for opendtufusion board

## 0.8.131 - 2024-08-08
* improved refresh routine of ePaper, full refresh each 12h #1107 #1706

## 0.8.130 - 2024-08-04
* fix message `ERR_DUPLICATE_INVERTER` #1705, #1700
* merge PR: Power limit command accelerated #1704
* merge PR: reduce update cycle of ePaper from 5 to 10 seconds #1706
* merge PR: small fixes in different files #1711
* add timestamp to JSON output #1707
* restart Ahoy using MqTT #1667

## 0.8.129 - 2024-07-11
* sort alarms ascending #1471
* fix alarm counter for first alarm
* prevent add inverter multiple times #1700

## 0.8.128 - 2024-07-10
* add environments for 16MB flash size ESP32-S3 aka opendtufusion
* prevent duplicate alarms, update end time once it is received #1471

## 0.8.127 - 2024-06-21
* add grid file #1677
* merge PR: Bugfix Inv delete not working with password protection #1678

## 0.8.126 - 2024-06-12
* merge PR: Update pubMqtt.h - Bugfix #1673 #1674

## 0.8.125 - 2024-06-09
* fix ESP8266 compilation
* merge PR: active_PowerLimit #1663

## 0.8.124 - 2024-06-06
* improved MqTT `OnMessage` (threadsafe)
* support of HERF inverters, serial number is converted in Javascript #1425
* revert buffer size in `RestAPI` for ESP8266 #1650

## 0.8.123 - 2024-05-30
* fix ESP8266, ESP32 static IP #1643 #1608
* update MqTT library which enhances stability #1646
* merge PR: MqTT JSON Payload pro Kanal und total, auswählbar #1541
* add option to publish MqTT as json
* publish rssi not on ch0 any more, published on `topic/rssi`
* add total power to index page (if multiple inverters are configured)
* show device name in html title #1639
* update AsyncWebserver library to `3.2.2`
* add environment name to filename of coredump

## 0.8.122 - 2024-05-23
* add button for donwloading coredump (ESP32 variants only)

## 0.8.121 - 2024-05-20
* fix ESP32 factory image generation
* fix plot of history graph #1635

## 0.8.120 - 2024-05-18
* fix crash if invalid serial number was set -> inverter will be disabled automatically
* improved and fixed factory image generation
* fix HMT-1800-4T number of inputs #1628

## 0.8.119 - 2024-05-17
* fix reset values at midnight if WiFi isn't available #1620
* fix typo in English versions
* add yield day to history graph #1614
* added script and [instructions](../manual/factory_firmware.md) how to generate factory firmware which includes predefined settings
* added button for downloading coredump (ESP32 variants only) to `/system`. Once a crash happens the reason can be checked afterwards (even after a reboot)
* added support of HERF inverters, serial number is converted in Javascript
* added device name to HTML title
* added feature to restart Ahoy using MqTT
* added feature to publish MqTT messages as JSON as well (new setting)
* add timestamp to JSON output
* improved communication to inverter
* improved translation to German
* improved HTML pages, reduced in size by only including relevant contents depending by chip type
* improved history graph in WebUI
* improved network routines
* improved Wizard
* improved WebUI by disabling upload and import buttons when no file is selected
* improved queue, only add new object once they not exist in queue
* improved MqTT `OnMessage` (threadsafe)
* improved read of alarms, prevent duplicates, update alarm time if there is an update
* improved alarms are now sorted in ascending direction
* improved by prevent add inverter multiple times
* improved sending active power controll commands
* improved refresh routine of ePaper, full refresh each 12h
* redesigned WebUI on `/system`
* changed MqTT retained flags
* change MqTT return value of power limit acknowledge from `boolean` to `float`. The value returned is the same as it was set to confirm reception (not the read back value)
* converted ePaper and Ethernet to hal-SPI
* combined Ethernet and WiFi variants - Ethernet is now always included, but needs to be enabled if needed
* changed: Ethernet variants (W5500) now support WiFi as fall back / configuration
* switch AsyncWebserver library
* fixed autodiscovery for homeassistant
* fix reset values functionality
* fix read back of active power control value, now it has one decimal place
* fix NTP issues
* fixed MqTT discovery field `ALARM_MES_ID`
* fix close button color of modal windows in dark mode
* fixed calculation of max AC power
* fixed reset values at midnight if WiFi isn't available
* fixed HMT-1800-4T number of inputs
* fix crash if invalid serial number was set -> inverter will be disabled automatically
* fixed ESP8266, ESP32 static IP
* fixed ethernet MAC address read back
* update several libraries to more recent versions
* removed `yield efficiency` because the inverter already calculates correct

full version log: [Development Log](https://github.com/lumapu/ahoy/blob/development03/src/CHANGES.md)
