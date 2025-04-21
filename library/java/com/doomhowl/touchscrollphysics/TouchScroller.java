package com.doomhowl.touchscrollphysics;

/**
 * Java bindings for the TouchScrollPhysics C library.
 * Provides a smooth touch-based scrolling physics implementation.
 */
public class TouchScroller implements AutoCloseable {
    static {
        NativeLibLoader.loadTouchScrollPhysicsLibrary();
    }

    // Pointer to the native TouchScroller instance
    private long nativeHandle;

    /**
     * Creates a new TouchScroller with the specified configuration.
     *
     * @param totalCells       Total number of cells in the scroller
     * @param viewSize         Size of the visible view area
     * @param cellSize         Size of each cell
     * @param gutterSize       Size of the gutter (overscroll area)
     * @param dipToClosestCell Whether to snap to the closest cell
     * @param dipMaxSpeed      Maximum speed for dipping (recommended: 10.0f)
     * @param dipSnappiness    How snappy the dipping is (recommended: 0.1f)
     */
    public TouchScroller(int totalCells, float viewSize, float cellSize, float gutterSize,
            boolean dipToClosestCell, float dipMaxSpeed, float dipSnappiness) {
        nativeHandle = nativeCreate(totalCells, viewSize, cellSize, gutterSize,
                dipToClosestCell, dipMaxSpeed, dipSnappiness);
    }

    /**
     * Updates the physics simulation.
     *
     * @param dtInMillis Time delta in milliseconds
     */
    public void update(float dtInMillis) {
        nativeUpdate(nativeHandle, dtInMillis);
    }

    /**
     * Starts a touch interaction at the given offset.
     *
     * @param offset Starting position of the touch
     */
    public void start(float offset) {
        nativeStart(nativeHandle, offset);
    }

    /**
     * Updates touch position during an interaction.
     *
     * @param offset Current position of the touch
     */
    public void move(float offset) {
        nativeMove(nativeHandle, offset);
    }

    /**
     * Ends a touch interaction at the given offset.
     *
     * @param offset Final position of the touch
     */
    public void end(float offset) {
        nativeEnd(nativeHandle, offset);
    }

    /**
     * Checks if a range is visible within the current view.
     *
     * @param startOffset Start of the range to check
     * @param endOffset   End of the range to check
     * @return true if the range is visible, false otherwise
     */
    public boolean isVisible(float startOffset, float endOffset) {
        return nativeIsVisible(nativeHandle, startOffset, endOffset);
    }

    /**
     * Gets the current scroll offset.
     *
     * @return Current scroll offset
     */
    public float getOffset() {
        return nativeGetOffset(nativeHandle);
    }

    /**
     * Releases native resources. Should be called when the scroller is no longer
     * needed.
     */
    public void dispose() {
        if (nativeHandle != 0) {
            nativeDispose(nativeHandle);
            nativeHandle = 0;
        }
    }

    @Override
    public void close() {
        dispose();
    }

    // Native methods
    private native long nativeCreate(int totalCells, float viewSize, float cellSize, float gutterSize,
            boolean dipToClosestCell, float dipMaxSpeed, float dipSnappiness);

    private native void nativeUpdate(long handle, float dtInMillis);

    private native void nativeStart(long handle, float offset);

    private native void nativeMove(long handle, float offset);

    private native void nativeEnd(long handle, float offset);

    private native boolean nativeIsVisible(long handle, float startOffset, float endOffset);

    private native float nativeGetOffset(long handle);

    private native void nativeDispose(long handle);
}