g++ -Ofast -march=skylake -fopenmp -frename-registers -funroll-loops -fopt-info -fopt-info-vec-missed -static-libgcc -static-libstdc++ -fPIC -o native.so -shared native.cpp
