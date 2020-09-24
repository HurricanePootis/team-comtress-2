#!/bin/sh
set -e
cd "$(dirname "$0")"

# Edit this if installed elsewhere
steam="$HOME/.steam/steam"

live_install="$steam/steamapps/common/Team Fortress 2"

ln -s "$live_install/hl2" 		"../game/hl2"
ln -s "$live_install/platform"	"../game/platform"
ln -s "$live_install/tf/maps"	"../game/tf/maps"
ln -s "$live_install/tf/"*.vpk	"../game/tf/"

cp -rn "$live_install/"*		"../game/"
