// Extra Credit 4:
// - find out how to compute a struct's size based on how struct
// packing work
// - assume 64-bit CPU arch
// - means CPU can read 8 bytes at a time

#include <stdio.h>

// this directive removes ALL padding in structs no matter what
#pragma pack(1)

// should take 8 + 1 + 7 + 8 = 24 bytes in memory
struct MyStruct {
    char *my_char_ptr;      // 8 bytes
    char my_char;           // 1 byte
                            // 7 bytes (padding btwn `char` & `long)
    long my_long;           // 8 bytes
};

// should take 8 + 8 + 1 bytes in memory
// actually takes 24 bytes in memory b/c of compiler??
struct MyStruct2 {
    char *my_char_ptr;      // 8 bytes
    long my_long;           // 8 bytes
    char my_char;           // 1 byte
};

int main(int argc, char *argv[])
{
    printf("struct MyStruct expected size: 24 bytes\n");
    printf(
        "struct MyStruct real size: %ld bytes\n",
        sizeof(struct MyStruct)
    );

    printf("struct MyStruct2 expected size: 17 bytes\n");
    printf(
        "struct MyStruct2 real size: %ld bytes\n",
        sizeof(struct MyStruct2)
    );

    return 0;
}
