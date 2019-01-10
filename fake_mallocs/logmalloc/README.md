# logmalloc

only output log

* `malloc`
* `free`
* no `calloc` ...

Ubuntu: OK
Mac: NG

## how to build
```
$ ninja
```

## DEBUG NOTE of Mac OS X
```
$ lldb wget
env DYLD_FORCE_FLAT_NAMESPACE=1
env DYLD_INSERT_LIBRARIES=./liblogmalloc.so
r
# <c-c>
bt
```

```
* thread #1, queue = 'com.apple.main-thread', stop reason = signal SIGSTOP
  * frame #0: 0x00000001000ad77a dyld`__ulock_wait + 10
    frame #1: 0x00000001000a8b36 dyld`_os_nospin_lock_lock_slow + 112
    frame #2: 0x0000000100086d35 dyld`dyld::imageCount() + 22
    frame #3: 0x000000010008c903 dyld`ImageLoader::findExportedSymbolInDependentImages(char const*, ImageLoader::LinkContext const&, ImageLoader const**) const + 39
    frame #4: 0x000000010008a6c5 dyld`dlsym + 624
    frame #5: 0x00007fff74100e5d libdyld.dylib`dlsym + 103
    frame #6: 0x000000010011aed8 liblogmalloc.so`::malloc(sz=32) at logmalloc.cpp:37
    frame #7: 0x00007fff734d4b66 libobjc.A.dylib`NXCreateHashTableFromZone + 268
    frame #8: 0x00007fff734d4a51 libobjc.A.dylib`NXCreateHashTable + 47
    frame #9: 0x00007fff734d4951 libobjc.A.dylib`NXCreateMapTableFromZone + 79
    frame #10: 0x00007fff734d48fb libobjc.A.dylib`NXCreateMapTable + 39
    frame #11: 0x00007fff734d3bfd libobjc.A.dylib`_read_images + 442
    frame #12: 0x00007fff734d2ac5 libobjc.A.dylib`map_images_nolock + 1154
    frame #13: 0x00007fff734e57db libobjc.A.dylib`map_images + 43
    frame #14: 0x0000000100080c65 dyld`dyld::notifyBatchPartial(dyld_image_states, bool, char const* (*)(dyld_image_states, unsigned int, dyld_image_info const*), bool, bool) + 1071
    frame #15: 0x0000000100080e3a dyld`dyld::registerObjCNotifiers(void (*)(unsigned int, char const* const*, mach_header const* const*), void (*)(char const*, mach_header const*), void (*)(char const*, mach_header const*)) + 57
    frame #16: 0x00007fff7410171e libdyld.dylib`_dyld_objc_notify_register + 113
    frame #17: 0x00007fff734d2076 libobjc.A.dylib`_objc_init + 117
    frame #18: 0x00007fff740c5b35 libdispatch.dylib`_os_object_init + 13
    frame #19: 0x00007fff740c5b1c libdispatch.dylib`libdispatch_init + 276
    frame #20: 0x00007fff71e199c3 libSystem.B.dylib`libSystem_initializer + 121
    frame #21: 0x0000000100092ac6 dyld`ImageLoaderMachO::doModInitFunctions(ImageLoader::LinkContext const&) + 420
    frame #22: 0x0000000100092cf6 dyld`ImageLoaderMachO::doInitialization(ImageLoader::LinkContext const&) + 40
    frame #23: 0x000000010008e218 dyld`ImageLoader::recursiveInitialization(ImageLoader::LinkContext const&, unsigned int, char const*, ImageLoader::InitializerTimingList&, ImageLoader::UninitedUpwards&) + 330
    frame #24: 0x000000010008e1ab dyld`ImageLoader::recursiveInitialization(ImageLoader::LinkContext const&, unsigned int, char const*, ImageLoader::InitializerTimingList&, ImageLoader::UninitedUpwards&) + 221
    frame #25: 0x000000010008d34e dyld`ImageLoader::processInitializers(ImageLoader::LinkContext const&, unsigned int, ImageLoader::InitializerTimingList&, ImageLoader::UninitedUpwards&) + 134
    frame #26: 0x000000010008d3e2 dyld`ImageLoader::runInitializers(ImageLoader::LinkContext const&, ImageLoader::InitializerTimingList&) + 74
    frame #27: 0x000000010007e521 dyld`dyld::initializeMainExecutable() + 126
    frame #28: 0x0000000100083239 dyld`dyld::_main(macho_header const*, unsigned long, int, char const**, char const**, char const**, unsigned long*) + 7242
    frame #29: 0x000000010007d3d4 dyld`dyldbootstrap::start(macho_header const*, int, char const**, long, macho_header const*, unsigned long*) + 453
    frame #30: 0x000000010007d1d2 dyld`_dyld_start + 54
```
