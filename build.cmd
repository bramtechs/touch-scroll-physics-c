cmake -S . -B build -DTSCROLL_BUILD_DEMOS=ON -DTSCROLL_DOWNLOAD_RAYLIB=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
