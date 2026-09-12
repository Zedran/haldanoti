cmake -DCMAKE_BUILD_TYPE=Release -DMM_SET_TC_FLAGS=ON -DCPACK_GENERATOR=NSIS ..
cmake --build . --config Release --parallel %NUMBER_OF_PROCESSORS%
cpack
