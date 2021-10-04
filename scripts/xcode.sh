rm -rf build && mkdir build && pushd build
cmake -G Xcode .. && open arithmetic-evaluator.xcodeproj
