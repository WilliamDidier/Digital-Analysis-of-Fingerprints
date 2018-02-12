cd build
make Test_geom
make Test_geom_advanced
./tests/Test_geom $1
./tests/Test_geom_advanced $1
