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
* `less`はsystem callの`open`を利用している
* `/etc/hosts`はsystem callを利用しているので置換はできない
* macの場合には`dlsym`内でopen系(not system call)を利用するため，分岐処理あり
