#!/bin/sh
cd "$(dirname "$0")" || exit

# Edit this if installed elsewhere
steam="$HOME/.steam/steam"

live_install="$steam/steamapps/common/Team Fortress 2"

if [ ! -d "$live_install" ]; then
	echo Failed to find TF2 at \'$live_install\'
	echo Did you move your steam library?
	echo If so, change the \`steam\` variable in \`link.sh\`
	exit 1
fi

ln -s "$live_install/hl2" 		"../game/hl2"
ln -s "$live_install/platform"	"../game/platform"
ln -s "$live_install/tf/maps"	"../game/tf/maps"
ln -s "$live_install/tf/"*.vpk	"../game/tf/"

echo If you get \'cp: cannot overwrite non-directory\', that\'s normal

cp -rn "$live_install/"*		"../game/"

rm -r ../game/tf/custom

cp game_clean/copy/bin/*.so ../game/bin/
cp -r game_clean/copy/tf/custom/ ../game/tf/custom
