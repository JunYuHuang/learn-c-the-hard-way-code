#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define print_type(type_name, type) \
            printf( \
                "%s size: %ld byte(s)\n", \
                type_name, \
                sizeof(type) \
            )

void print_header(char *header)
{
    size_t header_length = strlen(header);
    char *dashes = malloc(header_length * sizeof(char));

    int i = 0;
    for (i = 0; i < header_length; i++) {
        dashes[i] = '=';
    }

    printf("// %s\n", dashes);
    printf("// %s\n", header);
    printf("// %s\n", dashes);

    free(dashes);
}

void print_desc(char *thing, char *desc)
{
    printf("'%s': %s\n", thing, desc);
}

int main(int argc, char *argv[])
{
    // DATA TYPES
    print_header("DATA TYPES");
    print_type("int", int);
    print_type("double", double);
    print_type("float", float);
    print_type("char", char);
    print_type("void", void);
    enum my_enum { ZERO, ONE };
    print_type("enum", ONE);
    printf("\n");

    // TYPE MODIFIERS
    print_header("TYPE MODIFIERS");
    print_type("unsigned int", unsigned int);
    print_type("signed int", signed int);
    print_type("long int", long int);
    print_type("short int", short int);
    printf("\n");

    // TYPE QUALIFIERS
    print_header("TYPE QUALIFIERS");
    print_desc("const", "var that CAN'T be changed");
    print_desc("volatile", "use to do weird stuff to vars");
    print_desc("register", "forces to keep var in a register");
    printf("\n");

    // (INT) TYPE SIZES
    print_header("(INT) TYPE SIZES");
    print_type("int8_t", int8_t);
    print_type("uint8_t", uint8_t);
    print_type("int16_t", int16_t);
    print_type("uint16_t", uint16_t);
    print_type("int32_t", int32_t);
    print_type("uint32_t", uint32_t);
    print_type("int64_t", int64_t);
    print_type("uint64_t", uint64_t);
    printf("\n");

    return 0;
}
