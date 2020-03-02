sh ./clean.sh
premake5 gmake2
make config=release_l64
./bin/Release/mkpixel
