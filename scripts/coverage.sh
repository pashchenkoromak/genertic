root_path=$PWD

rm -rf ./bin
mkdir -p bin && cd bin

conan install .. -s compiler.libcxx=libstdc++11

cmake .. -B"$BUILD_DIR" -DCOVERAGE_ENABLE=ON && cmake --build . -- -j `nproc`

lcov --directory $PWD --zerocounters --no-external
lcov -c -i -d $PWD --output-file app_base.info

./bin/actor_tests

lcov -c -d $PWD -o tests.info
lcov -a app_base.info -a tests.info -o tests_total.info
lcov --extract tests_total.info $root_path/actor/include/* $root_path/actor/src/* -o tests_total_filtered.info

genhtml -o report tests_total_filtered.info
