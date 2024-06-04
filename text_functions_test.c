#include <stdio.h>
#include <windows.h>

#include "text_functions.h"


int main() {
    int i = 0, j = 0;
    char str[4], temp[4];

    // print_f("hi%d\n", array);

    printf("data to store?\n");
    read_line((void *)(str), 4, 's');
    print("HI! %d\n", 3);


    printf("text colour?\n");
    read_line((void *)(&i), 4, 'i');
    printf("int2str->%s\n", int_to_str(i));

    printf("background colour?\n");
    read_line((void *)(&j), 4, 'i');

    printc("hi\n", i, j);

    create_progress_bar(20, i, j);

    for (int k = 0; k < 20; k++) {
        move_progress_bar(24, 0);
        Sleep(100);
    }

    printf("\n");

    for (int j = 0; j < 5; j++) {
        rotation_loading(200);
    }

    return 0;
}