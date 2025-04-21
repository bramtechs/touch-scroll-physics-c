# Touch Scroll Physics - Java Bindings

This module provides Java bindings for the TouchScrollPhysics C library, making it easy to use the smooth scrolling physics in Java applications.

## Features

- Full access to all TouchScroller functionality
- Clean, object-oriented Java API
- Memory management handled automatically
- Includes a Swing demo application

## Building the Library

### Prerequisites

- JDK 8 or higher
- CMake 3.12 or higher
- C compiler (GCC, Clang, MSVC)

### Build Steps

1. Make sure the parent C library is built first (or will be built as part of this process)

2. From the root of the project, run:

```bash
# Configure CMake to include Java bindings
cmake -S . -B build -DTSCROLL_BUILD_JAVA=ON

# Build everything
cmake --build build
```

This will compile:

- The native C library
- The JNI native library
- The Java classes
- A JAR file containing all Java classes

The compiled libraries and JAR file will be placed in `library/java/build/libs/`.

## Usage

### Including in Your Project

1. Add the JAR file to your Java project's classpath:

   - `touch-scroll-physics.jar`

2. Make sure the native libraries are in your library path:
   - `libtouchscrollphysics.so` (Linux)
   - `libtouchscrollphysics.dylib` (macOS)
   - `touchscrollphysics.dll` (Windows)
   - `libtouchscrollphysics_jni.so` (Linux)
   - `libtouchscrollphysics_jni.dylib` (macOS)
   - `touchscrollphysics_jni.dll` (Windows)

### Example Code

```java
import com.doomhowl.touchscrollphysics.TouchScroller;

// Create a new TouchScroller
TouchScroller scroller = new TouchScroller(
    25,        // totalCells
    800.0f,    // viewSize
    150.0f,    // cellSize
    400.0f,    // gutterSize
    true,      // dipToClosestCell
    10.0f,     // dipMaxSpeed
    0.1f       // dipSnappiness
);

// In your game/animation loop
public void update() {
    // Update physics (pass milliseconds since last frame)
    scroller.update(16.0f);  // For 60 FPS

    // Get the current scroll position
    float offset = scroller.getOffset();

    // Render your content at the offset
    // ...
}

// Handle user input
public void onTouchDown(float x) {
    scroller.start(x);
}

public void onTouchMove(float x) {
    scroller.move(x);
}

public void onTouchUp(float x) {
    scroller.end(x);
}

// Clean up when done
public void dispose() {
    scroller.dispose();
}
```

## Running the Demo

The project includes a Swing-based demo application that shows how to use the TouchScroller class:

```bash
# Run from the build directory
java -Djava.library.path=./library/java/build/libs -cp ./library/java/build/libs/touch-scroll-physics.jar com.doomhowl.touchscrollphysics.TouchScrollerDemo
```

The demo shows a horizontally scrollable list of colored cells. Drag with your mouse to scroll.

## Using in Other Projects

When using the TouchScrollPhysics library in other projects, you can now properly see variable names and source code in your IDE by including both JARs:

1. `touch-scroll-physics-lib.jar` - The main library JAR with compiled classes and debug information
2. `touch-scroll-physics-lib-sources.jar` - The source JAR with original Java source files

### Maven Example

```xml
<dependency>
  <groupId>com.doomhowl</groupId>
  <artifactId>touch-scroll-physics</artifactId>
  <version>0.0.1</version>
  <scope>system</scope>
  <systemPath>/path/to/touch-scroll-physics-lib.jar</systemPath>
</dependency>
```

Then manually attach the sources JAR in your IDE:

- **IntelliJ IDEA**: Right-click on the JAR in the Project view → "Add as Library..." → Choose "Sources" for the sources JAR
- **Eclipse**: Right-click on the JAR in the Package Explorer → "Properties" → "Java Source Attachment" → Select the sources JAR
- **VS Code**: Add to your `.classpath` file or configure in your Java extension settings

### Gradle Example

```groovy
dependencies {
    implementation files('/path/to/touch-scroll-physics-lib.jar')
}
```

For the sources, add this to your `settings.gradle`:

```groovy
sourceAttachmentPattern = '/path/to/touch-scroll-physics-lib-sources.jar'
```

## Building with Debug Information

The library is now configured to compile with full debug information (`-g` flag) and create a sources JAR. To build:

```bash
# Build only the Java bindings
make java

# Or build everything including demos
make build
```

The JARs will be located at:

- `library/java/build/libs/touch-scroll-physics-lib.jar`
- `library/java/build/libs/touch-scroll-physics-lib-sources.jar`
