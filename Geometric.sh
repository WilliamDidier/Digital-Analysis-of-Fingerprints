cd build
make Test_geom
make Test_geom_advanced
echo $''
echo $' ____            _                                        _        _        _            _       '
echo $'|  _ \\          (_)                                      | |      (_)      | |          | |      '
echo $'| |_) | __ _ ___ _  ___    __ _  ___  ___  _ __ ___   ___| |_ _ __ _  ___  | |_ ___  ___| |_ ___ '
echo $'|  _ < / _` / __| |/ __|  / _` |/ _ \\/ _ \\| \'_ ` _ \\ / _ \\ __| \'__| |/ __| | __/ _ \\/ __| __/ __|'
echo $' | |_) | (_| \\__ \\ | (__  | (_| |  __/ (_) | | | | | |  __/ |_| |  | | (__  | ||  __/\\__ \\ |_\\__ \\'
echo $'|____/ \\__,_|___/_|\\___|  \\__, |\\___|\\___/|_| |_| |_|\\___|\\__|_|  |_|\\___|  \\__\\___||___/\\__|___/'
echo $'                           __/ |                                                                 '
echo $'                          |___/                                                                  '
./tests/Test_geom $1
./tests/Test_geom_advanced $1
