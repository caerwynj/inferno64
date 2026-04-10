This is a build Inferno64 (MinGW branch) adopted for MSYS2 env.

## Install and run

Install [MSYS2](https://www.msys2.org/), run its shell and:
```bash
pacman -S mingw-w64-x86_64-gcc
pacman -S upx
pacman -S git
cd /opt
git clone https://github.com/sphynkx/inferno64
cd inferno64
git fetch -all
git switch msys2
export MKSH=`which bash`.exe
export PATH=$PATH:/opt/inferno64/MinGW/amd64/bin/
export ROOT=$(pwd)
./makemk.sh
mk mkdirs
mk install
```
Run:
```bash
MinGW/amd64/bin/emu.exe -r. -g1200x600

```

## Modifications
As of MinGW branch:
* Fixed build `mk` utility from scratch
* Reworked some mkfiles - cmd-style commands replaced with bash-style ones; resolved cycle build issues.
* Some tiny code modifications.
* Set static linking to prevent MSYS2 dlls requirement.
* Set strip and upx pack for final binary (5.3M -> 396k). Optionally - added params in `mkconfig`.
* Running app and wm window are beautified by app icon.