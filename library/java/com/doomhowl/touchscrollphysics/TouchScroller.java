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
     * Creates a new TouchScroller with default configuration.
     * Default values:
     * - 25 total cells
     * - 800.0f view size (WIDTH from demo)
     * - 150.0f cell size (HEIGHT/4 from demo)
     * - 400.0f gutter size (WIDTH/2 from demo)
     * - true for dip to closest cell
     * - 10.0f dip max speed
     * - 0.1f dip snappiness
     */
    public TouchScroller() {
        this(25, 800.0f, 150.0f, 400.0f, true, 10.0f, 0.1f);
    }

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
        // Create native handle
        nativeHandle = nativeCreate(totalCells, viewSize, cellSize, gutterSize,
                dipToClosestCell, dipMaxSpeed, dipSnappiness);
    }

    // --- Getter and Setter methods ---

    /**
     * Gets the total number of cells.
     * 
     * @return The total number of cells
     */
    public int getTotalCells() {
        return nativeGetTotalCells(nativeHandle);
    }

    /**
     * Sets the total number of cells.
     * 
     * @param totalCells The total number of cells
     */
    public void setTotalCells(int totalCells) {
        nativeSetTotalCells(nativeHandle, totalCells);
    }

    /**
     * Gets the view size.
     * 
     * @return The view size
     */
    public float getViewSize() {
        return nativeGetViewSize(nativeHandle);
    }

    /**
     * Sets the view size.
     * 
     * @param viewSize The view size
     */
    public void setViewSize(float viewSize) {
        nativeSetViewSize(nativeHandle, viewSize);
    }

    /**
     * Gets the cell size.
     * 
     * @return The cell size
     */
    public float getCellSize() {
        return nativeGetCellSize(nativeHandle);
    }

    /**
     * Sets the cell size.
     * 
     * @param cellSize The cell size
     */
    public void setCellSize(float cellSize) {
        nativeSetCellSize(nativeHandle, cellSize);
    }

    /**
     * Gets the gutter size.
     * 
     * @return The gutter size
     */
    public float getGutterSize() {
        return nativeGetGutterSize(nativeHandle);
    }

    /**
     * Sets the gutter size.
     * 
     * @param gutterSize The gutter size
     */
    public void setGutterSize(float gutterSize) {
        nativeSetGutterSize(nativeHandle, gutterSize);
    }

    /**
     * Checks if the scroller is configured to dip to the closest cell.
     * 
     * @return true if the scroller dips to the closest cell, false otherwise
     */
    public boolean isDipToClosestCell() {
        return nativeGetDipToClosestCell(nativeHandle);
    }

    /**
     * Sets whether the scroller should dip to the closest cell.
     * 
     * @param dipToClosestCell Whether to dip to the closest cell
     */
    public void setDipToClosestCell(boolean dipToClosestCell) {
        nativeSetDipToClosestCell(nativeHandle, dipToClosestCell);
    }

    /**
     * Gets the maximum speed for dipping.
     * 
     * @return The maximum dip speed
     */
    public float getDipMaxSpeed() {
        return nativeGetDipMaxSpeed(nativeHandle);
    }

    /**
     * Sets the maximum speed for dipping.
     * 
     * @param dipMaxSpeed The maximum dip speed
     */
    public void setDipMaxSpeed(float dipMaxSpeed) {
        nativeSetDipMaxSpeed(nativeHandle, dipMaxSpeed);
    }

    /**
     * Gets the dip snappiness.
     * 
     * @return The dip snappiness
     */
    public float getDipSnappiness() {
        return nativeGetDipSnappiness(nativeHandle);
    }

    /**
     * Sets the dip snappiness.
     * 
     * @param dipSnappiness The dip snappiness
     */
    public void setDipSnappiness(float dipSnappiness) {
        nativeSetDipSnappiness(nativeHandle, dipSnappiness);
    }

    // --- End of Getter and Setter methods ---

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

    private native void nativeSetTotalCells(long handle, int totalCells);

    private native void nativeSetViewSize(long handle, float viewSize);

    private native void nativeSetCellSize(long handle, float cellSize);

    private native void nativeSetGutterSize(long handle, float gutterSize);

    private native void nativeSetDipToClosestCell(long handle, boolean dipToClosestCell);

    private native void nativeSetDipMaxSpeed(long handle, float dipMaxSpeed);

    private native void nativeSetDipSnappiness(long handle, float dipSnappiness);

    private native int nativeGetTotalCells(long handle);

    private native float nativeGetViewSize(long handle);

    private native float nativeGetCellSize(long handle);

    private native float nativeGetGutterSize(long handle);

    private native boolean nativeGetDipToClosestCell(long handle);

    private native float nativeGetDipMaxSpeed(long handle);

    private native float nativeGetDipSnappiness(long handle);
}