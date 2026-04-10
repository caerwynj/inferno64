This is a build Inferno64 (MinGW branch) adopted for msys env.

## Install and run

Install [msys2](https://www.msys2.org/), run its shell and:
```
pacman -S mingw-w64-x86_64-gcc
pacman -S git
cd /opt
git clone https://github.com/sphynkx/inferno64
cd inferno64
git fetch -all
git switch MinGW
export MKSH=`which bash`.exe
export PATH=$PATH:/opt/inferno64/MinGW/amd64/bin/
export ROOT=$(pwd)
./makemk.sh
mk mkdirs
mk install
```
Run:
```
MinGW/amd64/bin/emu.exe -r. -g1200x600

```

## Modifications
As of MinGW branch:
Fixed build `mk` utility from scratch
Reworked some mkfiles - cmd-style commands replaced with bash-style ones; resolved cycle build issues.
Some tiny code modifications.
