# WARNING!!!
# This deletes the build directory and creates a new one from scratch!

rm -rf build
mkdir build
cd build
cmake ..
make