#!/usr/bin/env bash
set -e  # Stop on error

CORES=`nproc`
if [ ! -f ./thirdparty/gperftools-2.0/built ]; then
	cd ./thirdparty/gperftools-2.0
	bash ./autogen.sh
	./configure --enable-frame-pointers --host=i686-pc-linux-gnu "CFLAGS=-m32" "CXXFLAGS=-m32" "LDFLAGS=-m32"
	make -j $CORES
	cd ../..
	touch ./thirdparty/gperftools-2.0/built
fi

if [ ! -f ./thirdparty/protobuf-2.5.0/built ]; then
	cd ./thirdparty/protobuf-2.5.0
	bash ./autogen.sh
	bash ./configure --host=i686-pc-linux-gnu "CFLAGS=-m32" "CXXFLAGS=-m32" "LDFLAGS=-m32"
	make -j $CORES
	cd ../..
	touch ./thirdparty/protobuf-2.5.0/built
fi

if [ ! -f ./games.mak ]; then
	bash ./creategameprojects.sh
fi

export VALVE_NO_AUTO_P4=1
if [[ $1 == -v ]]; then
  # Debug mode
  make -f games.mak NO_CHROOT=1 MAKE_JOBS=1 MAKE_VERBOSE=1 "${@:2}"
else
  make -f games.mak NO_CHROOT=1 "$@"
fi
