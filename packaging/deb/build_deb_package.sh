#!/bin/sh

set -e

if [ "$1" = "--build-deps" ]; then
    apt install -y debmake
fi

OWD=$(pwd)

WD=$(pwd)/debian

mkdir -p "$WD"

VERSION=$(git describe --tags | sed 's/v//')

PACKAGE_NAME="mm-game_$VERSION"

ROOT=$(git rev-parse --show-toplevel)

git -C .. archive                 \
    --format=tar.gz               \
    --prefix="$PACKAGE_NAME/"     \
    -o "$WD/$PACKAGE_NAME.tar.gz" \
    HEAD

DEB_DIR="$WD/$PACKAGE_NAME/debian"
mkdir -p "$DEB_DIR"

cp "$WD/$PACKAGE_NAME.tar.gz" "$WD/$PACKAGE_NAME.orig.tar.gz"

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
    --package mm-game         \
    --newversion "$VERSION-1" \
    "Automated build"         \

unset DEBEMAIL NAME

cd "$WD"

tar -xzf "$PACKAGE_NAME.tar.gz"

cd "$PACKAGE_NAME"

if [ "$1" = "--build-deps" ]; then
    yes | mk-build-deps -i -r debian/control
fi

debuild -us -uc -b

cd "$OWD"
