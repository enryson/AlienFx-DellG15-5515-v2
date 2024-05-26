# AlienFX for Dell G15 5515 v2 (C++ edition)

#### Disclaimer
Now you can control the keyboard lights on a DELL G15 5515.
For now this is a terminal application write using C++ for better performance and control, and implementing a PROTO-SDK of the ALIENFX.

the goal is to write a GUI APP and a API so softwares can interact with.

This new implementation fixes all the bugs with the PYTHON version
A complete stable way to using the lights

## Features
- Control the 4 zones of the keyboard

## Upcoming
- Installer
- GUI
- API
- other effects
- other devices and layouts
- AUR package/ Flatpack?

## Install process

Depenencies (Arch Linux)
```sh
sudo pacman -S libusb libstdc++ gcc-libs glibc systemd libcap
```
Depenencies (Debian)
```sh
sudo apt-get update
sudo apt-get install libusb-1.0-0 libstdc++6 libc6 libgcc1 libudev1 libcap2
```

Depenencies (fedora)
```sh
sudo dnf install libusb libstdc++ glibc libgcc systemd-libs libcap
```

Clonning the project
```sh
cd ~
mkdir GitHub
git clone https://github.com/enryson/AlienFX-DellG15-5515-v2.git
cd AlienFX-DellG15-5515-v2

```

Build and Install
```sh
sudo make install

```

AlienFX uses USB protocol for the lights
For access without SUDO you need change the access of the USB controller
Just copy the RULES file to the correct directory and reboot OR refresh the UDEV permissions
```sh
sudo cp rules/10-alienfx.rules /etc/udev/rules.d/
```

# Finally!

Usage
```sh
alienfx-cli all=255,255,255

```
to configure the colors you need to setup a value between 0 and 255
The sequence is R,G,B
so to make the keyboard color Red
```sh
alienfx-cli all=255,0,0

```

# Special thanks to:
[T-Troll]https://github.com/T-Troll With some notes on the hexdata payload on his windows take on the SDK [alienfx-tools]https://github.com/T-Troll/alienfx-tools
[Cheaterman](https://gist.github.com/Cheaterman) for the LIBUSB example usage [elc_ng.py](https://gist.github.com/Cheaterman/accd912c6886f4055f45d0594b88553c)
