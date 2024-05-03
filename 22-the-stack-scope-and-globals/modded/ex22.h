#ifndef _ex22_h
#define _ex22_h

/*
`extern`: This keyword is a way to tell the compiler "the
variable exists, but it's in another 'external' location."
Typically this means that one .c file is going to use a
variable that's been defined in another .c file. In this case,
we're saying `ex22.c` has a variable `THE_SIZE` that will be
accessed from `ex22_main.c`.
*/
// makes THE_SIZE in ex22.c available to other .c files
extern int THE_SIZE;

// gets and sets an internal static variable in ex22.c
int get_age();
void set_age(int age);

// updates a static variable that's inside update_ratio
double update_ratio(double ratio);

void print_size();

#endif
