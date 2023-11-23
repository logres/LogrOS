/* Print a char on the screen at col , row , or at cursor position */
void print_char(char character, int col, int row, char attribute_byte)
{ /* Create a byte (char) pointer to the start of video memory */
    unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;
    /* If attribute byte is zero , assume the default style. */
    if (!attribute_byte)
    {
        attribute_byte = WHITE_ON_BLACK;
    }
    /* Get the video memory offset for the screen location */
    int offset;
    /* If col and row are non -negative , use them for offset. */
    if (col >= 0 && row >= 0)
    {
        offset = get_screen_offset(col, row);
        /* Otherwise , use the current cursor position. */
    }
    else
    {
        offset = get_cursor();
    }
    // If we see a newline character , set offset to the end of
    // current row , so it will be advanced to the first col
    // of the next row.
    if (character == '\n')
    {

        int rows = offset / (2 * MAX_COLS);
        offset = get_screen_offset(79, rows);
        // Otherwise , write the character and its attribute byte to
        // video memory at our calculated offset.
    }
    else
    {
        vidmem[offset] = character;
        vidmem[offset + 1] = attribute_byte;
    }
    // Update the offset to the next character cell , which is
    // two bytes ahead of the current cell.
    offset += 2;
    // Make scrolling adjustment , for when we reach the bottom
    // of the screen. offset = handle_scrolling(offset );
    // Update the cursor position on the screen device.
    set_cursor(offset);
}

int handle_scrolling(int cursor_offset)
{ // If the cursor is within the screen , return it unmodified.
    if (cursor_offset < MAX_ROWS * MAX_COLS * 2)
    {
        return cursor_offset;
    }
    /* Shuffle the rows back one. */ int i;
    for (i = 1; i < MAX_ROWS; i++)
    {
        memory_copy(get_screen_offset(0, i) + VIDEO_ADDRESS, get_screen_offset(0, i - 1) + VIDEO_ADDRESS, MAX_COLS * 2);
    }
    /* Blank the last line by setting all bytes to 0 */
    char *last_line = get_screen_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;
    for (i = 0; i < MAX_COLS * 2; i++)
    {
        last_line[i] = 0;
    }
    // Move the offset back one row , such that it is now on the last
    // row , rather than off the edge of the screen.
    cursor_offset -= 2 * MAX_COLS;
    // Return the updated cursor position.
    return cursor_offset;
}