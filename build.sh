#!/usr/bin/env bash
set -e	# Stop on error
cd "$(dirname "$0")"

if pwd | grep -q " "; then
	echo "You have cloned the source directory into a path with spaces"
	echo "This will break a lot of thirdparty build scripts"
	echo "Please move the source directory somewhere without a space in the path"
	exit 1
fi

# Defaults
CF_SUPPRESSION="-w"
MAKE_SRT="NO_CHROOT=1 STEAM_RUNTIME_PATH="
MAKE_CFG="CFG=release"
MAKE_VERBOSE=''
VPC_FLAGS="/define:LTCG /define:CERT"
CORES=$(nproc)

while [[ ${1:0:1} == '-' ]]; do
	case "${1}" in
		"-v")
			CF_SUPPRESSION=""
		;;
		"-vv")
			CF_SUPPRESSION=""
			MAKE_VERBOSE=1
		;;
		"-d")
			VPC_FLAGS="/no_ceg /nofpo"
		;;
		"-dd")
			VPC_FLAGS="/no_ceg /nofpo"
			MAKE_CFG="CFG=debug"
		;;
		"-c")
			shift
			if [[ $1 == ?(-)+([[:digit:]]) ]]; then
				CORES=$1
			else
				echo "Not a number: ${1}"
				exit 1
			fi
		;;
		"-r")
			MAKE_SRT=''
		;;
		*)
			echo "Unknown flag ${1}"
			exit 1
		;;
	esac
	shift
done

if [[ ! -f ./thirdparty/gperftools-2.0/.libs/libtcmalloc_minimal.so ]]; then
	cd ./thirdparty/gperftools-2.0
	aclocal
	automake --add-missing
	autoconf
	chmod u+x configure
	./configure --enable-frame-pointers "CFLAGS=-m32 ${CF_SUPPRESSION}" "CXXFLAGS=-m32 ${CF_SUPPRESSION}" "LDFLAGS=-m32"
	make "-j$CORES"
	cd ../..
fi

if [[ ! -f ./thirdparty/protobuf-2.5.0/src/.libs/libprotobuf.a ]]; then
	cd ./thirdparty/protobuf-2.5.0
	aclocal
	automake --add-missing
	autoconf
	chmod u+x configure
	./configure "CFLAGS=-m32 ${CF_SUPPRESSION} -D_GLIBCXX_USE_CXX11_ABI=0" \
		"CXXFLAGS=-m32 ${CF_SUPPRESSION} -D_GLIBCXX_USE_CXX11_ABI=0" "LDFLAGS=-m32" --enable-shared=no
	make "-j$CORES"
	cd ../..
fi

if [ ! -f ./thirdparty/libedit-3.1/src/.libs/libedit.so ]; then
	cd ./thirdparty/libedit-3.1
	aclocal
	automake --add-missing
	autoconf
	chmod u+x ./configure
	./configure "CFLAGS=-m32 ${CF_SUPPRESSION}" "CXXFLAGS=-m32 ${CF_SUPPRESSION}" "LDFLAGS=-m32"
	make "-j$CORES"
	cd ../..
fi

if [ ! -f ./devtools/bin/vpc_linux ]; then
	cd ./external/vpc/utils/vpc
	make "-j$CORES"
	cd ../../../..
fi

# shellcheck disable=SC2086   # we want arguments to be split
devtools/bin/vpc /define:WORKSHOP_IMPORT_DISABLE /define:SIXENSE_DISABLE /define:NO_X360_XDK \
				/define:RAD_TELEMETRY_DISABLED /define:DISABLE_ETW /retail /tf ${VPC_FLAGS} +game /mksln games

export VALVE_NO_AUTO_P4=1

CFLAGS="${CF_SUPPRESSION}" CXXFLAGS="${CF_SUPPRESSION}" make ${MAKE_SRT} MAKE_VERBOSE="${MAKE_VERBOSE}" ${MAKE_CFG} \
		MAKE_JOBS="$CORES" -f games.mak "$@"
