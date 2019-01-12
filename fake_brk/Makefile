all: hook_brk.so malloc_test
	LD_PRELOAD=./hook_brk.so ./malloc_test

malloc_test: malloc_test.c
	gcc malloc_test.c -o malloc_test

hook_brk.so: hook_brk.cpp LibHook.h
	$(CXX) -fPIC -shared -o hook_brk.so hook_brk.cpp -std=c++0x -ldl
