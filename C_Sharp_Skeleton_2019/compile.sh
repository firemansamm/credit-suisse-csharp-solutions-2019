g++ -Ofast -march=skylake -mtune=skylake -funroll-loops -fopt-info -fopt-info-vec-missed -fPIC -o native.so -shared native.cpp
