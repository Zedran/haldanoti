# Installation

## Table of contents

* [Linux](#linux)
    * [Packages](#packages)
        * [AppImage](#appimage)
        * [DEB](#deb)
        * [RPM](#rpm)
    * [Source](#source)
        * [Requirements](#requirements)
        * [Build and install](#build-and-install)
        * [Uninstall](#uninstall)
* [Windows](#windows)
    * [Installer](#installer)
    * [Source](#source-1)
        * [Requirements](#requirements-1)
        * [Build and install](#build-and-install-1)
        * [Uninstall](#uninstall-1)

## Linux

### Packages

Download one of the available packages from the most recent [release](https://github.com/Zedran/haldanoti/releases/latest) and follow instructions in the relevant section below.

#### AppImage

Built on Debian stable 64bit.

AppImage can be installed using integration tools, such as [AppImageLauncher](https://github.com/TheAssassin/AppImageLauncher), or used manually:

```sh
chmod +x ./haldanoti*.AppImage
./haldanoti*.AppImage
```

Alternatively, if you do not have access to the `fuse` kernel module or wish to access docs and licensing information:

```sh
chmod +x ./haldanoti*.AppImage
./haldanoti*.AppImage --appimage-extract
mv squashfs-root haldanoti

./haldanoti/AppRun

# Docs and licensing information can be found in:
# ./haldanoti/usr/share/doc/
# ./haldanoti/usr/share/haldanoti/
```

#### DEB

Built on Debian stable.

```sh
apt install ./haldanoti*.deb
```

#### RPM

Built on Fedora latest.

```sh
dnf install ./haldanoti*.rpm
```

### Source

#### Requirements

GCC supporting C++20 required.

Debian:

```sh
apt install         \
    build-essential \
    cmake           \
    git             \
    make            \
    libx11-dev      \
    libxrandr-dev   \
    libxcursor-dev  \
    libxi-dev       \
    libudev-dev     \
    libgl-dev       \
    libmbedtls-dev  \
    libssh2-1-dev   \
    libfreetype-dev \
    libharfbuzz-dev \
    libvorbis-dev   \
    libflac-dev
```

RPM (Fedora):

```sh
dnf install          \
    gcc-c++          \
    cmake            \
    git              \
    make             \
    libXcursor-devel \
    libXrandr-devel  \
    libXi-devel      \
    mesa-libGL-devel \
    systemd-devel    \
    mbedtls-devel    \
    libssh2-devel    \
    harfbuzz-devel   \
    freetype-devel   \
    libvorbis-devel  \
    flac-devel
```

#### Build and install

Run the following commands:

```sh
git clone https://github.com/Zedran/haldanoti.git
cd haldanoti

mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release -DHALDANOTI_SET_TC_FLAGS=ON ..
make -j$(nproc)

sudo make install
```

#### Uninstall

To uninstall the application, run the following inside the `/build/` directory:

```sh
sudo make uninstall
```

## Windows

### Installer

Download Windows installer from the most recent [release](https://github.com/Zedran/haldanoti/releases/latest) and run it. You will be warned that the file is unsigned and therefore cannot be trusted - this is expected.

### Source

#### Requirements

* [CMake](https://cmake.org/download)
* [Git](https://git-scm.com/install/windows)
* [MSVC](https://learn.microsoft.com/en-us/cpp/overview/acquire-msvc) with C++20 support.

#### Build and install

Run the following commands:

```bat
git clone https://github.com/Zedran/haldanoti.git
cd haldanoti

mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release -DHALDANOTI_SET_TC_FLAGS=ON ..
cmake --build . --target install --config Release --parallel %NUMBER_OF_PROCESSORS%
```

#### Uninstall

To uninstall the application, run the following inside the `/build/` directory:

```bat
cmake --build . --target uninstall
```
