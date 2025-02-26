#include <stdio.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} VariantType;

/*
You find this in many implementations of dynamic languages. The
language will define some base variant type with tags for all the
base types of the language, and then usually there's a generic
object tag for the types you can create. The advantage of doing
this is that the `Variant` only takes up as much space as the
`VariantType type` tag and the largest member of the union. This is
because C is layering each element of the `Variant.data` union
together, so they overlap. To do that, C sizes the union big enough
to hold the largest element.
*/
struct Variant {
    VariantType type;
    union {
        int as_integer;
        float as_float;
        char *as_string;
    } data;
};

typedef struct Variant Variant;

void Variant_print(Variant *var)
{
    switch (var->type) {
        case TYPE_INT:
            printf("INT: %d\n", var->data.as_integer);
            break;
        case TYPE_FLOAT:
            printf("FLOAT: %f\n", var->data.as_float);
            break;
        case TYPE_STRING:
            printf("STRING: %s\n", var->data.as_string);
            break;
        default:
            printf("UNKNOWN TYPE: %d\n", var->type);
    }
}

int main(int argc, char *argv[])
{
    Variant a_int = { .type = TYPE_INT, .data.as_integer = 100 };
    Variant a_float = {
        .type = TYPE_FLOAT, .data.as_float = 100.34
    };
    Variant a_string = {
        .type = TYPE_STRING, .data.as_string = "YO DUDE!"
    };

    Variant_print(&a_int);
    Variant_print(&a_float);
    Variant_print(&a_string);

    // here's how you access them
    a_int.data.as_integer = 200;
    a_float.data.as_float = 2.345;
    a_string.data.as_string = "Hi there.";

    Variant_print(&a_int);
    Variant_print(&a_float);
    Variant_print(&a_string);

    return 0;
}
