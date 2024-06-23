.PHONY: build
build:
	cmake -S . -B build -DTSCROLL_BUILD_DEMOS=ON -DCMAKE_BUILD_TYPE=Debug
	cmake --build build

run:
	./build/demo-cpp/TouchScrollPhysicsDemoCPP
