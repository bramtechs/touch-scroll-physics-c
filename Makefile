.PHONY: build
build:
	cmake -S . -B build -DTSCROLL_BUILD_DEMOS=ON -DTSCROLL_BUILD_JAVA=ON -DCMAKE_BUILD_TYPE=Debug
	cmake --build build

run:
	./build/demo-cpp/TouchScrollPhysicsDemoCPP

.PHONY: java
java:
	cmake -S . -B build -DTSCROLL_BUILD_JAVA=ON -DCMAKE_BUILD_TYPE=Debug
	cmake --build build
