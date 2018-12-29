# fake hostname

## how to use
### mac
```
LIBFAKE_HOSTNAME=~/local/lib/libfake_hostname.dylib
DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES=$LIBFAKE_HOSTNAME FAKE_HOSTNAME=fake_hostname hostname
```

### linux
```
LIBFAKE_HOSTNAME=~/local/lib/libfake_hostname.so
LD_PRELOAD=$LIBFAKE_HOSTNAME FAKE_HOSTNAME=fake_hostname hostname
```
