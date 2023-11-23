/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() {
}

void main() {
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'L';
    *(video_memory + 2) = 'O';
    *(video_memory + 4) = 'G';
    *(video_memory + 6) = 'R';
    *(video_memory + 8) = 'E';
    *(video_memory + 10) = 'S';
    // What should I do Here?

    // 1. IO operation
    // 2. Single System Intereaction
    // 3. Multi-Task-Control=>(Virtual Memory and Paging, and task switching)

    // Advance: File System
    // Advance: Network
    // Advance: GUI
}   
