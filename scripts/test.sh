popd
rm -rf build && mkdir build && pushd build
cmake .. && make && ./tests
