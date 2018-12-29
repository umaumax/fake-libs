# fake hosts

## how to use
### mac
```
LIBFAKE_HOSTS=~/local/lib/libfake_hosts.dylib
DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES=$LIBFAKE_HOSTS FAKE_HOSTS_FILEPATH=./.hosts ping www.google.com
```

### linux
```
sudo LIBFAKE_HOSTS=~/local/lib/libfake_hosts.so LD_PRELOAD=$LIBFAKE_HOSTS FAKE_HOSTS_FILEPATH=./.hosts ping www.google.com
```

```
fakeroot
LIBFAKE_HOSTS=~/local/lib/libfake_hosts.so
LD_PRELOAD=$LIBFAKE_HOSTS FAKE_HOSTS_FILEPATH=./.hosts ping www.google.com
```

### LD_PRELOAD with setuid/setgid
* [謎の処理系 SunOS 4\.1\.4 with Linux/FreeBSD]( http://www15.big.or.jp/~yamamori/sun/sunos4/dns.html )
  * linuxでの`ping`ではなぜか`LD_PRELOAD`でしていしていても`gethostname2`が呼ばれない
  * 自分でcompileした`gethostbyname2`は正常に動作する
  * そもそも，`ping`に`LD_DEBUG=files`が効かない
  * つまり，もともと`root`になっていれば，問題なく動作する

```
$ ls -l /bin/ping
-rwsr-xr-x 1 root root 44168 May  8  2014 /bin/ping
```

### LD_PRELOAD with PIE binrary
[linux \- ltrace doesn't work on some binaries \- Stack Overflow]( https://stackoverflow.com/questions/12899644/ltrace-doesnt-work-on-some-binaries )
> The reason why ltrace can't trace httpd is because ltrace does not support PIE executable. 

```
$ hardening-check /usr/bin/curl
/usr/bin/curl:
 Position Independent Executable: yes
 Stack protected: yes
 Fortify Source functions: yes (some protected functions found)
 Read-only relocations: yes
 Immediate binding: yes
```

`wget` is alos `PIE`

* PIE binaryの場合は`ltrace`が無効化されるが，`nm -D`で`U`のシンボルの置換は可能

----

## FYI
* use `nss_wrapper` for only linux
  * [/lib/x86\_64\-linux\-gnu/libnss\_files\.so\.2]( https://unix.stackexchange.com/questions/57459/how-can-i-override-the-etc-hosts-file-at-user-level )
  * [cwrap \- nss\_wrapper]( https://cwrap.org/nss_wrapper.html )
* `gethostbyname2`は名前解決の初回のみ呼ばれ，それ以降はcacheされるため，プロセスの途中でファイルを変更しても効果がない
