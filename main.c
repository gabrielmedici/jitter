#include "stdio.h"
#include "Windows.h"

unsigned char instructions[] = {
    //  push   ebp
    0x55,
    //  mov    ebp,esp
    0x8b, 0xec,
    //  mov    eax,DWORD PTR [ebp+0x8]
    0x8b, 0x45, 0x08,
    //  add    eax,DWORD PTR [ebp+0xc]
    0x03, 0x45, 0x0c,
    //  pop    ebp
    0x5d,
    //  ret
    0xc3
};

typedef int (*add)(int, int);

void main() {

    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);
    DWORD page_size = system_info.dwPageSize;

    LPVOID buffer = VirtualAlloc(NULL, page_size, MEM_COMMIT, PAGE_READWRITE);

    memcpy(buffer, instructions, sizeof(instructions) / sizeof(instructions[0]));

    DWORD dummy;
    VirtualProtect(buffer, sizeof(instructions), PAGE_EXECUTE_READ, &dummy);

    add lol = buffer;
    int result = lol(5, 8);

    printf("Result: %d", result);
}