Debug version:

mkdir Debug
cd Debug
cmake -DCMAKE_BUILD_TYPE=Debug ../src
cmake --build .

Release version:

mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ../src
cmake --build .