gcc -falign=8 -Ofast -march=skylake -mtune=skylake -funroll-loops -fopt-info -fopt-info-vec-missed -fPIC -o native2.so -shared native2.cpp
g++ -Ofast -march=skylake -mtune=skylake -funroll-loops -fopt-info -fopt-info-vec-missed -fPIC -o native3.so -shared native3.cpp
g++ -Ofast -march=skylake -mtune=skylake -funroll-loops -fopt-info -fopt-info-vec-missed -fPIC -o native4.so -shared native4.cpp
g++ -Ofast -march=skylake -mtune=skylake -funroll-loops -fopt-info -fopt-info-vec-missed -fPIC -o native5.so -shared native5.cpp
