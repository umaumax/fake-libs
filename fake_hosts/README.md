# fake hosts

## how to use
### mac
```
LIBFAKE_HOSTS=~/local/lib/libfake_hosts.dylib
DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES=$LIBFAKE_HOSTS FAKE_HOSTS_FILEPATH=./.hosts ping www.google.com
```

### linux
linuxでは`gethostname2`が呼ばれない...
```
LIBFAKE_HOSTS=~/local/lib/libfake_hosts.so
LD_PRELOAD=$LIBFAKE_HOSTS FAKE_HOSTS_FILEPATH=./.hosts ping www.google.com
```

## FYI
* use `nss_wrapper` for only linux
  * [/lib/x86\_64\-linux\-gnu/libnss\_files\.so\.2]( https://unix.stackexchange.com/questions/57459/how-can-i-override-the-etc-hosts-file-at-user-level )
  * [cwrap \- nss\_wrapper]( https://cwrap.org/nss_wrapper.html )
* `gethostname2`は名前解決の初回のみ呼ばれ，それ以降はcacheされるため，プロセスの途中でファイルを変更しても効果がない
