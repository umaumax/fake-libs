# fake hosts

## how to use
### mac
```
LIBFAKE_HOSTS=~/local/lib/libfake_hosts.dylib
DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES=$LIBFAKE_HOSTS FAKE_HOSTS_FILEPATH=./.hosts ping www.google.com
```

### linux
```
LIBFAKE_HOSTS=~/local/lib/libfake_hosts.dylib
LD_PRELOAD=$LIBFAKE_HOSTS FAKE_HOSTS_FILEPATH=./.hosts ping www.google.com
```

## FYI
`gethostname2`は名前解決の初回のみ呼ばれ，それ以降はcacheされるため，プロセスの途中でファイルを変更しても効果がない
