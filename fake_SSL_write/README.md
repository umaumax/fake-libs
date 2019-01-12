# fake SSL_write

this fake lib creates `SSL_write.log`

## how to use
### mac
```
LIBFAKE_OPEN=~/local/lib/libfake_SSL_write.dylib
DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES=$LIBFAKE_OPEN wget https://www.google.com
```

### linux
```
LIBFAKE_OPEN=~/local/lib/libfake_SSL_write.so
LD_PRELOAD=$LIBFAKE_OPEN wget https://www.google.com
```

## FYI
* [Function Hooking Part I: Hooking Shared Library Function Calls in Linux]( https://blog.netspi.com/function-hooking-part-i-hooking-shared-library-function-calls-in-linux/ )
