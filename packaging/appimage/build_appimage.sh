#!/bin/sh

set -e

arch="$(uname -m)"

aic_tag="continuous"

aic="linuxdeploy-$arch.AppImage"

url="https://github.com/linuxdeploy/linuxdeploy/releases/download/$aic_tag/linuxdeploy-$arch.AppImage"

appdir="AppDir"

if [ ! -f "./$aic" ]; then
    if command -v curl > /dev/null 2>&1; then
        curl -sS -L -o "$aic" "$url"
    elif command -v wget > /dev/null 2>&1; then
        echo "curl not found"
        wget -qO "$aic" "$url"
    else
        echo "wget not found"
        echo "download utilities missing"
        exit 1
    fi
    chmod +x "./$aic"
fi

if [ ! -c /dev/fuse ] || [ ! -r /dev/fuse ] || [ ! -w /dev/fuse ]; then
    echo "fuse not available - extracting linuxdeploy"
    "./$aic" --appimage-extract
    aic="squashfs-root/AppRun"
fi

cmake -DCMAKE_INSTALL_PREFIX=/usr \
    -DCMAKE_BUILD_TYPE=Release    \
    -DHALDANOTI_SET_TC_FLAGS=ON   \
    -DHALDANOTI_APPIMAGE=ON ..

make -j"$(nproc)"

make install DESTDIR="$appdir"

"./$aic" --appdir "$appdir"                             \
    --desktop-file "./platform/linux/haldanoti.desktop" \
    --icon-file "../assets/haldanoti.svg"               \
    --output appimage

mv "Haldanóti-$arch.AppImage" "haldanoti-$arch.AppImage"
