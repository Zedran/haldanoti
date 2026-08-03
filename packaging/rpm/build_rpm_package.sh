#!/bin/sh

set -e

if [ "$1" != "--build-deps" ]; then
    dnf install -y rpmdevtools rpmlint
fi

WD=$(pwd)/rpmbuild

for d in BUILD BUILDROOT RPMS SOURCES SPECS SRPMS; do
    mkdir -p "$WD/$d"
done

VERSION=$(git describe --tags | sed 's/v//')

git -C .. archive                            \
    --format=tar.gz                          \
    --prefix="mm-game-$VERSION/"             \
    -o "$WD/SOURCES/mm-game-$VERSION.tar.gz" \
    HEAD

sed "s/@VERSION@/$VERSION/" "$(dirname "$0")/mm-game.spec.in" > "$WD/SPECS/mm-game.spec"

if [ "$1" != "--build-deps" ]; then
    dnf builddep -y "$WD/SPECS/mm-game.spec"
fi

rpmbuild --define "_topdir $WD" -ba "$WD/SPECS/mm-game.spec"
