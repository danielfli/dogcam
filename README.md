# dogcam Project

## Environment

### Setting for Raspi

```bash
sudo apt update
sudo apt upgrade
sudo rpi-update
```

### Build

```bash
mkdir build
cd build
cmake ..
make -j2
```
## Install GStreamer

[README](https://gstreamer.freedesktop.org/documentation/installing/on-linux.html?gi-language=c)

## libcamera Library 

### Depends
[Link Quelle](https://libcamera.org/getting-started.html)
```bash
sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
sudo apt install libboost-dev
sudo apt-get install python3-yaml python3-ply python3-jinja2
sudo apt install libgnutls28-dev openssl
sudo apt install libdw-dev libunwind-dev
sudo apt install meson
sudo pip3 install --upgrade meson
sudo pip3 install pyyaml ply
```
### Build libcamera Library

[LINK Quelle](https://githubmemory.com/repo/jhihn/libcamera-apps)

```bash
cd dogcam/external
git clone https://git.libcamera.org/libcamera/libcamera.git
cd libcamera
meson build
cd build
meson configure -Dpipelines=raspberrypi -Dtest=false
cd ..
ninja -C build -j2
sudo ninja -C build install
```

## libcamera-app

### Build libcamera-app 
[Link Quelle](https://libcamera.org/getting-started.html)

```bash
cd dogcam/external
git clone https://github.com/raspberrypi/libcamera-apps.git
cd libcamera-apps
mkdir build
cd build
cmake ..
make -j2
```