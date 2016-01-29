.PHONY: all clean distclean


COMPILER ?= "g++"

all: build/Makefile
	@make -j -C build
	@mkdir -p bin
	@cp build/monoRenderer bin

build/Makefile: CMakeLists.txt
	@mkdir -p build
	@cd build; cmake -D CMAKE_CXX_COMPILER=$(COMPILER) ..

clean:
	rm -rf build/* bin/* contrib/*

distclean:
	rm -rf build imgui.ini contrib dl bin
