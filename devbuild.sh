#!/usr/bin/env bash
set -e  # Stop on error

if [[ ! -v CORES ]]; then
  CORES=`nproc`
fi

if [ ! -f ./thirdparty/gperftools-2.0/.libs/libtcmalloc_minimal.so ]; then
	cd ./thirdparty/gperftools-2.0
  aclocal
  automake --add-missing
	autoconf
	./configure --enable-frame-pointers "CFLAGS=-m32" "CXXFLAGS=-m32" "LDFLAGS=-m32"
  make -j$CORES
	cd ../..
fi

if [ ! -f ./thirdparty/protobuf-2.5.0/src/.libs/libprotobuf.a ]; then
	cd ./thirdparty/protobuf-2.5.0
  aclocal
  automake --add-missing
	autoconf
	chmod u+x autogen.sh
	./configure "CFLAGS=-m32 -D_GLIBCXX_USE_CXX11_ABI=0" "CXXFLAGS=-m32 -D_GLIBCXX_USE_CXX11_ABI=0" "LDFLAGS=-m32" --enable-shared=no
	make -j$CORES
	cd ../..
fi

if [ ! -f ./thirdparty/libedit-3.1/src/.libs/libedit.so ]; then
	cd ./thirdparty/libedit-3.1
  aclocal
  automake --add-missing
	autoconf
	chmod u+x ./configure
	./configure "CFLAGS=-m32" "CXXFLAGS=-m32" "LDFLAGS=-m32"
	make -j$CORES
	cd ../..
fi

if [ ! -f ./devtools/bin/vpc2_linux ]; then
	cd ./thirdparty/vpc2
	make -j$CORES
	mv ./utils/vpc/obj/Linux/release/vpc ../../devtools/bin/vpc2_linux
	cd ../..
fi

if [ ! -f ./games.mak ]; then
	./creategameprojects_dev.sh
fi

export VALVE_NO_AUTO_P4=1
if [[ $1 == '-v' ]]; then
  make NO_CHROOT=1 MAKE_JOBS=1 MAKE_VERBOSE=1 -f games_dev.mak "${@:2}"
else
  make NO_CHROOT=1 MAKE_JOBS=$CORES -f games_dev.mak "${@:1}"
fi
