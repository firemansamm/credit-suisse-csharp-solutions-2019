g++ -Ofast -march=skylake -fopenmp -frename-registers -funroll-loops -fopt-info -fopt-info-vec-missed -fPIC -o native.so -shared native.cpp
