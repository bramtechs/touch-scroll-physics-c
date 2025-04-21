# Touch Scroll Physics Java Demo

This is a Java demonstration of the Touch Scroll Physics library.

## Building

To build the Java demo:

1. First build the main library with Java bindings enabled:

   ```
   mkdir build && cd build
   cmake -DTSCROLL_BUILD_JAVA=ON -DTSCROLL_BUILD_DEMOS=ON ..
   make
   ```

2. The fat JAR (containing all Java dependencies) will be created in `demo/java/build/libs/touch-scroll-physics-demo.jar`

## Running

To run the demo:

```
java -Djava.library.path=/path/to/jni/library -jar demo/java/build/libs/touch-scroll-physics-demo.jar
```

The JNI library path would typically be one of these locations depending on your OS:

- Linux: `library/java/build/libs/` or `install/lib/`
- macOS: `library/java/build/libs/` or `install/lib/`
- Windows: `library/java/build/libs/` or `install/bin/`

Example on macOS:

```
java -Djava.library.path=library/java/build/libs -jar demo/java/build/libs/touch-scroll-physics-demo.jar
```

## Features

The demo demonstrates the core features of the Touch Scroll Physics library:

- Smooth scrolling with physics
- Cell-based scrolling with snap points
- Visual feedback on cell visibility

## Controls

- Click and drag to scroll the cells
- Release to let physics take over
- The green/red cell shows visibility detection in action
