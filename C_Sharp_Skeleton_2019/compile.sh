g++ -Ofast -march=skylake -frename-registers -funroll-loops -fopt-info -fopt-info-vec-missed -fPIC -o native.so -shared native.cpp
