package com.doomhowl.touchscrollphysics;

import java.io.*;
import java.nio.file.*;

/**
 * Helper class for loading native libraries from within JAR files.
 */
public class NativeLibLoader {

    /**
     * Loads the touch scroll physics JNI library.
     * This method will try to extract the library from the JAR file if needed.
     */
    public static void loadTouchScrollPhysicsLibrary() {
        try {
            // Try simple load first (in case library is already in path)
            System.loadLibrary("touch_scroll_physics_jni");
        } catch (UnsatisfiedLinkError e) {
            // If not found, try to extract from JAR and load
            try {
                // Detect OS and architecture
                String os = System.getProperty("os.name").toLowerCase();
                String arch = System.getProperty("os.arch").toLowerCase();

                // Determine native library path and name
                String libraryPath;
                String libraryName;

                if (os.contains("mac") || os.contains("darwin")) {
                    if (arch.contains("aarch64") || arch.contains("arm64")) {
                        libraryPath = "native/macos/arm64/libtouch_scroll_physics_jni.dylib";
                    } else {
                        libraryPath = "native/macos/x86_64/libtouch_scroll_physics_jni.dylib";
                    }
                    libraryName = "libtouch_scroll_physics_jni.dylib";
                } else if (os.contains("windows")) {
                    // Add Windows support if needed
                    libraryPath = "native/windows/touch_scroll_physics_jni.dll";
                    libraryName = "touch_scroll_physics_jni.dll";
                } else {
                    // Linux/Unix
                    libraryPath = "native/linux/libtouch_scroll_physics_jni.so";
                    libraryName = "libtouch_scroll_physics_jni.so";
                }

                // Create temp directory for native libraries if it doesn't exist
                String tempDir = System.getProperty("java.io.tmpdir");
                File nativeLibDir = new File(tempDir, "touch_scroll_physics_native_" + System.nanoTime());
                nativeLibDir.mkdirs();
                nativeLibDir.deleteOnExit();

                // Extract library to temp directory
                File nativeLibFile = new File(nativeLibDir, libraryName);
                try (InputStream in = NativeLibLoader.class.getClassLoader().getResourceAsStream(libraryPath)) {
                    if (in == null) {
                        throw new FileNotFoundException("Native library not found in JAR: " + libraryPath);
                    }

                    Files.copy(in, nativeLibFile.toPath(), StandardCopyOption.REPLACE_EXISTING);
                }

                // Set executable permission
                nativeLibFile.setExecutable(true);

                // Load the extracted library
                System.load(nativeLibFile.getAbsolutePath());
            } catch (IOException ex) {
                throw new RuntimeException("Failed to load native library", ex);
            }
        }
    }
}