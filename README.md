# fake libs

## how to build
```
mkdir -p ~/local/
mkdir -p build && cd build
# for Mac add below command before cmake
# OPENSSL_ROOT_DIR=/usr/local/opt/openssl \
cmake .. -DCMAKE_INSTALL_PREFIX=~/local/
make install
```

## FYI
* `RTLD_NEXT` is GNU extension
