# libcamera-app Output 

### Befehl

./libcamera-jpeg -n -o test12.jpg

## Output 

```bash
[0:08:34.894301893] [1857]  INFO Camera camera_manager.cpp:293 libcamera v0.0.0+3375-94a1afd0
[0:08:34.949343491] [1861] ERROR CameraSensor camera_sensor.cpp:535 'ov5647 10-0036': Camera sensor does not support test pattern modes.
[0:08:35.203310732] [1861]  INFO RPI raspberrypi.cpp:1256 Registered camera /base/soc/i2c0mux/i2c@1/ov5647@36 to Unicam device /dev/media2 and ISP device /dev/media0
[0:08:35.205932032] [1857]  INFO Camera camera.cpp:1028 configuring streams: (0) 1296x972-YUV420
[0:08:35.207217229] [1861]  INFO RPI raspberrypi.cpp:730 Sensor: /base/soc/i2c0mux/i2c@1/ov5647@36 - Selected sensor format: 1296x972-SGBRG10_1X10 - Selected unicam format: 1296x972-pGAA
[0:08:35.238709884] [1869]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Saturation = 1.000000
[0:08:35.238948268] [1869]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Contrast = 1.000000
[0:08:35.239043378] [1869]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Brightness = 0.000000
[0:08:35.239102062] [1869]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: AwbMode = 0
[0:08:35.239269095] [1869]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Sharpness = 1.000000
[0:08:35.239377704] [1869]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: ExposureValue = 0.000000
[0:08:35.239460369] [1869]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: AeExposureMode = 0
[0:08:35.239517868] [1869]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: FrameDurationLimits = [ 33333, 33333 ]
[0:08:35.239662088] [1869]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: AeMeteringMode = 0
[0:08:35.239729586] [1869]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: NoiseReductionMode = 3
[0:08:35.258666527] [1861]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
[0:08:35.258734581] [1861]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
[0:08:35.258763655] [1861]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
[0:08:35.258790376] [1861]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
[0:08:35.258816987] [1861]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
[0:08:35.258843320] [1861]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
[0:08:35.258869245] [1861]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
[0:08:40.368261245] [1857]  INFO Camera camera.cpp:1028 configuring streams: (0) 2592x1944-YUV420 (1) 2592x1944-SGBRG10_CSI2P
[0:08:40.369495165] [1861]  INFO RPI raspberrypi.cpp:730 Sensor: /base/soc/i2c0mux/i2c@1/ov5647@36 - Selected sensor format: 2592x1944-SGBRG10_1X10 - Selected unicam format: 2592x1944-pGAA
[0:08:40.404990733] [1894]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Saturation = 1.000000
[0:08:40.405143618] [1894]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Contrast = 1.000000
[0:08:40.405222913] [1894]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Brightness = 0.000000
[0:08:40.405295301] [1894]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: AwbMode = 0
[0:08:40.405373540] [1894]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Sharpness = 1.000000
[0:08:40.405445242] [1894]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: ExposureValue = 0.000000
[0:08:40.405520167] [1894]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: AeExposureMode = 0
[0:08:40.405593387] [1894]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: FrameDurationLimits = [ 100, 1000000000 ]
[0:08:40.405687978] [1894]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: AeMeteringMode = 0
[0:08:40.405762347] [1894]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: NoiseReductionMode = 2
[0:08:40.408610069] [1861]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
Still capture image received
```

## Ausführlich 

### Befehl:

./libcamera-jpeg -v 1 -n -o test12.jpg

```bash
pi@devenv:~/projects/dogcam/external/libcamera-apps/build $ ./libcamera-jpeg -v 1 -n -o test.jpg
Options:
    verbose: 1
    info_text:#%frame (%fps fps) exp %exp ag %ag dg %dg
    timeout: 5000
    width: 0
    height: 0
    output: test.jpg
    post_process_file:
    rawfull: 0
    preview: none
    qt-preview: 0
    transform: identity
    roi: all
    metering: centre
    exposure: normal
    ev: 0
    awb: auto
    flush: false
    wrap: 0
    brightness: 0
    contrast: 1
    saturation: 1
    sharpness: 1
    framerate: 30
    denoise: auto
    viewfinder-width: 0
    viewfinder-height: 0
    tuning-file: (libcamera)
    lores-width: 0
    lores-height: 0
    mode: unspecified
    viewfinder-mode: unspecified
    encoding: jpg
    quality: 93
    raw: 0
    restart: 0
    timelapse: 0
    framestart: 0
    datetime: 0
    timestamp: 0
    keypress: 0
    signal: 0
    thumbnail width: 320
    thumbnail height: 240
    thumbnail quality: 70
    latest:
    immediate 0
Running without preview window
Opening camera...
[2:20:10.074979529] [11998]  INFO Camera camera_manager.cpp:293 libcamera v0.0.0+3375-94a1afd0
[2:20:10.109501184] [12000] ERROR CameraSensor camera_sensor.cpp:535 'ov5647 10-0036': Camera sensor does not support test pattern modes.
[2:20:10.263419840] [12000]  INFO RPI raspberrypi.cpp:1256 Registered camera /base/soc/i2c0mux/i2c@1/ov5647@36 to Unicam device /dev/media2 and ISP device /dev/media0
Acquired camera /base/soc/i2c0mux/i2c@1/ov5647@36
Configuring viewfinder...
Viewfinder size chosen is 1296x972
[2:20:10.265880190] [11998]  INFO Camera camera.cpp:1028 configuring streams: (0) 1296x972-YUV420
[2:20:10.267302400] [12000]  INFO RPI raspberrypi.cpp:730 Sensor: /base/soc/i2c0mux/i2c@1/ov5647@36 - Selected sensor format: 1296x972-SGBRG10_1X10 - Selected unicam format: 1296x972-pGAA
Camera streams configured
Buffers allocated and mapped
Viewfinder setup complete
Requests created
[2:20:10.291714658] [12005]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Saturation = 1.000000
[2:20:10.291887675] [12005]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Contrast = 1.000000
[2:20:10.291945805] [12005]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Brightness = 0.000000
[2:20:10.291990508] [12005]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: AwbMode = 0
[2:20:10.292123285] [12005]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Sharpness = 1.000000
[2:20:10.292177951] [12005]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: ExposureValue = 0.000000
[2:20:10.292234413] [12005]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: AeExposureMode = 0
[2:20:10.292277802] [12005]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: FrameDurationLimits = [ 33333, 33333 ]
[2:20:10.292367931] [12005]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: AeMeteringMode = 0
[2:20:10.292414060] [12005]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: NoiseReductionMode = 3
[2:20:10.295233536] [12000]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
[2:20:10.295285443] [12000]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
[2:20:10.295313202] [12000]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
[2:20:10.295338369] [12000]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
[2:20:10.295364146] [12000]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
[2:20:10.295390091] [12000]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
[2:20:10.295415498] [12000]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
Camera started!
Camera stopped!
Tearing down requests, buffers and configuration
Configuring still capture...
[2:20:15.429718059] [11998]  INFO Camera camera.cpp:1028 configuring streams: (0) 2592x1944-YUV420 (1) 2592x1944-SGBRG10_CSI2P
[2:20:15.431370767] [12000]  INFO RPI raspberrypi.cpp:730 Sensor: /base/soc/i2c0mux/i2c@1/ov5647@36 - Selected sensor format: 2592x1944-SGBRG10_1X10 - Selected unicam format: 2592x1944-pGAA
Camera streams configured
Buffers allocated and mapped
Still capture setup complete
Requests created
[2:20:15.489784186] [12008]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Saturation = 1.000000
[2:20:15.489972943] [12008]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Contrast = 1.000000
[2:20:15.490127720] [12008]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Brightness = 0.000000
[2:20:15.490223441] [12008]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: AwbMode = 0
[2:20:15.490323514] [12008]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: Sharpness = 1.000000
[2:20:15.490419254] [12008]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: ExposureValue = 0.000000
[2:20:15.490513920] [12008]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: AeExposureMode = 0
[2:20:15.490602623] [12008]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: FrameDurationLimits = [ 100, 1000000000 ]
[2:20:15.490720067] [12008]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: AeMeteringMode = 0
[2:20:15.490811195] [12008]  INFO IPARPI raspberrypi.cpp:626 Request ctrl: NoiseReductionMode = 2
[2:20:15.494043557] [12000]  INFO RPISTREAM rpi_stream.cpp:133 No buffers available for ISP Output0
Camera started!
Camera stopped!
Still capture image received
Exposure time: 38775
Ag 4 Dg 1.00017 Total 4.00068
Thumbnail dimensions are 320 x 240
Thumbnail size 7367
JPEG size is 1176516
EXIF data len 266
Closing Libcamera application(frames displayed 110, dropped 0)
Camera stopped!
Tearing down requests, buffers and configuration
Camera closed
```
