g++ -Ofast -march=skylake -frename-registers -funroll-loops -fPIC -o native2.so -shared native2.cpp
g++ -Ofast -march=skylake -frename-registers -funroll-loops -fPIC -o native3.so -shared native3.cpp
g++ -Ofast -march=skylake -frename-registers -funroll-loops -fPIC -o native4.so -shared native4.cpp
g++ -Ofast -march=skylake -frename-registers -funroll-loops -fPIC -o native5.so -shared native5.cpp