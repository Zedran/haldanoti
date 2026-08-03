#!/bin/sh

set -e

if [ "$1" == "--build-deps" ]; then
    apt install -y debmake
fi

OWD=$(pwd)

WD=$(pwd)/debian

mkdir -p "$WD"

VERSION=$(git describe --tags | sed 's/v//')

ROOT=$(git rev-parse --show-toplevel)

git -C .. archive                       \
    --format=tar.gz                     \
    --prefix="mm_$VERSION/"             \
    -o "$WD/mm_$VERSION.tar.gz"         \
    HEAD

DEB_DIR="$WD/mm_$VERSION/debian"
mkdir -p "$DEB_DIR"

cp "$WD/mm_$VERSION.tar.gz" "$WD/mm_$VERSION.orig.tar.gz"

sed "s/@VERSION@/$VERSION/" "$(dirname "$0")/rules.in" > "$DEB_DIR/rules"
chmod +x "$DEB_DIR/rules"

{
    cat "$(dirname "$0")/copyright.in"
    echo
    echo "License:   AGPL-3.0-only"
    cat "$ROOT/LICENSE"
    echo
    echo "License:   OFL-1.1"
    cat "$ROOT/docs/licenses/Inter.txt"
} >> "$DEB_DIR/copyright"

cp "$(dirname "$0")/control" "$DEB_DIR/control"

cd "$DEB_DIR/.."

export DEBEMAIL="17592740+Zedran@users.noreply.github.com"
export NAME="Zedran"

dch --create                  \
    --package mm              \
    --newversion "$VERSION-1" \
    "Automated build"         \

unset DEBEMAIL NAME

cd "$WD"

tar -xzf "mm_$VERSION.tar.gz"

cd "mm_$VERSION"

if [ "$1" == "--build-deps" ]; then
    yes | mk-build-deps -i -r debian/control
fi

debuild -us -uc -b

cd "$OWD"
