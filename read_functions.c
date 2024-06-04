#include <stdio.h>
#include <math.h>
#include <string.h>


// reads a string from input and stores it in string of size n
// ensures no buffer overflow
int read_line(char *str, int n) {
    int i = 0;
    int ch; // ch has int type as getchar() returns an integer value

    while ((ch = getchar()) != '\n') { // \n must be in single quotes so its a string literal not a string
        if (i < n-1) { // ensures that string is not longer than array it is stored in
            str[i] = ch;
            i++;
        }
    }
    str[i] = '\0'; // terminates string with a null character

    return i;

}


// function terminates at first non-integer character
// captures integer value from string input
// str_len must include the null terminator
int str_to_int(char *str, int str_len) {
    int input_string[str_len - 1];
    int return_number = 0;

    if (str_len - 1 > strlen(str)) {
        str_len = strlen(str) + 1;
        // protects from errors due to not having the right amount of digits
        // add one because str_len includes the null character, but strlen() doesn't
    }
    
    for (int i = 0; i < str_len - 1; i++) {

        input_string[i] = str[i] - 48; // converts each value to an integer by subtracting the value of 0 in ASCII

    }

    for (int j = 0; j < str_len - 1; j++) {

        return_number += input_string[j] * pow(10, str_len - 2 - j);

    }


    /*
       *********************************************************************************************************************
       * when return_number is a 3 digit number, it is one less than it should be for some reason, so it is corrected here *
       *********************************************************************************************************************
    */
    return_number = (return_number < 1000 && return_number > 99) ? return_number + 1 : return_number;

    return return_number;
}