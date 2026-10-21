#!/bin/sh

set -e

if [ "$1" = "--build-deps" ]; then
    dnf install -y rpmdevtools rpmlint
fi

WD=$(pwd)/rpmbuild

for d in BUILD BUILDROOT RPMS SOURCES SPECS SRPMS; do
    mkdir -p "$WD/$d"
done

VERSION=$(git describe --tags | sed 's/v//')

git -C .. archive                            \
    --format=tar.gz                          \
    --prefix="haldanoti-$VERSION/"             \
    -o "$WD/SOURCES/haldanoti-$VERSION.tar.gz" \
    HEAD

sed "s/@VERSION@/$VERSION/" "$(dirname "$0")/haldanoti.spec.in" > "$WD/SPECS/haldanoti.spec"

if [ "$1" = "--build-deps" ]; then
    dnf builddep -y "$WD/SPECS/haldanoti.spec"
fi

rpmbuild --define "_topdir $WD" -ba "$WD/SPECS/haldanoti.spec"
