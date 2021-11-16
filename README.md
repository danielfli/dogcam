# dogcam Project

## Environment

### Setting - Raspberry Pi Zero

- Cross compiling use this steps - set the compiler from the raspberrypi/tools

Clone: [Tool-Chain Raspberry Pi](https://github.com/raspberrypi/tools)

Change the path in: /cmake/toolchain-rpi.cmake to the Tool-Chain

- Do the follow:

```bash
mkdir build_armv6
cd build_armv6
cmake --build_armv6 . -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain-rpi.cmake .. 
make  
```

### Setting - Raspberry Pi "other" (Not tested)

```bash
mkdir build
cd build
cmake ..
make 
```
