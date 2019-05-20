// for the arm 32-bit little endian assembly implementation
// but also something to note, pointers to data **should** be aligned by 4
// Returned key and taken keys are treated as 128bit big endian values in memory
void KeyScrambler(void* NormalKey, const void* KeyX, const void* KeyY);
