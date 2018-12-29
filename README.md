# fake libs

## how to build
```
mkdir -p ~/local/
mkdir -p build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=~/local/
make install
```

## FYI
* `RTLD_NEXT` is GNU extension
