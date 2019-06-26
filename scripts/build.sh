rm -rf ./bin
mkdir -p bin && cd bin

conan install .. -s compiler.libcxx=libstdc++11

cmake .. && cmake --build . -j `nproc` 