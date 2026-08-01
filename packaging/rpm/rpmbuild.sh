#!/bin/sh

set -e

if [ "$1" != "--local" ]; then
    dnf install -y git rpmdevtools rpmlint
fi

WD=$(pwd)/rpmbuild

mkdir -p "$WD"/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}

VERSION=$(git describe --tags | sed 's/v//')

git -C .. archive                       \
    --format=tar.gz                     \
    --prefix=mm-$VERSION/               \
    -o "$WD/SOURCES/mm-$VERSION.tar.gz" \
    HEAD

sed "s/@VERSION@/$VERSION/" ../packaging/rpm/mm.spec.in > "$WD/SPECS/mm.spec"

if [ "$1" != "--local" ]; then
    dnf builddep -y "$WD/SPECS/mm.spec"
fi

rpmbuild --define "_topdir $WD" -ba "$WD/SPECS/mm.spec"
