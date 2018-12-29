# fake open

## how to use
### mac
```
LIBFAKE_OPEN=~/local/lib/libfake_open.dylib
DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES=$LIBFAKE_OPEN FAKE_OPENRC_FILEPATH=./.openrc head /dev/random | LC_CTYPE=C tr -dc 0-9 | head -c 13 ; echo ''
```

### linux
```
LIBFAKE_OPEN=~/local/lib/libfake_open.so
LD_PRELOAD=$LIBFAKE_OPEN FAKE_OPENRC_FILEPATH=./.openrc head /dev/random | LC_CTYPE=C tr -dc 0-9 | head -c 13 ; echo ''
```

## FYI
* `create`には対応していない
* `/etc/hosts`はsystem callを利用しているので置換はできない
