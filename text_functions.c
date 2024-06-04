#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#ifdef _WIN32

    #include <windows.h>

#endif

#if defined (__unix__)
    #include <time.h>
#endif

#include "text_functions.h"

// resets the colours and formatting of text
#define ANSI_COLOUR_RESET "\x1b[0m"



// runs one loop of a rotational loading sequence
// rotation_time is time between rotation phases
// rotation_time in milliseconds
void rotation_loading(int rotation_time) {
    for (int i = 1; i < 9; i++) {
            #ifdef _WIN32

            Sleep(rotation_time);

            #endif

            #ifdef __unix__

            nanosleep(rotation_time * 1000000);

            #endif

            if (i % 4 == 0 && i % 3 != 0) {
                printf("/\r");
            }
            else if (i % 2 == 0 || i % 6 == 0) {
                printf("\\\r");
            }
            else if (i % 3 == 0 || i == 7 || i == 0) {
                printf("|\r");
            }
            else {
                printf("-\r");
            }
            printf(ANSI_COLOUR_RESET);
        }
}


// function terminates at first non-integer character
// captures integer value from string input
// str_len must include the null terminator
int str_to_int(char *str, int str_len) {
    int input_string[str_len - 1];
    int return_number = 0;
    int sign = 0;

    if (str_len - 1 > strlen(str)) {
        // protects from errors due to not having the right amount of digits
        // add one because str_len includes the null character, but strlen() doesn't
        str_len = strlen(str) + 1;
    }
    
    for (int i = 0; i < str_len - 1; i++) {
        if (sign == 0) {
            input_string[i] = input_string[i] == 45 ? sign = 1 : str[i] - 48; // converts each value to an integer by subtracting the value of 0 in ASCII
        }
        else {
            input_string[i] = str[i - 1] - 48; // converts each value to an integer by subtracting the value of 0 in ASCII
        }
    }

    for (int j = 0; j < str_len - 1; j++) {
        if (sign == 0) {
            return_number += input_string[j] * pow(10, str_len - 2 - j);
        }
        else {
            return_number += input_string[j] * pow(10, str_len - 3 - j);
        }

    }


    /*
       *********************************************************************************************************************
       * when return_number is a 3 digit number, it is one less than it should be for some reason, so it is corrected here *
       * if someone could fix this more elegantly, they would be awesome                                                   *
       *********************************************************************************************************************
    */
    return_number = (return_number < 1000 && return_number > 99) ? return_number + 1 : return_number;
    return_number = sign == 1 ? return_number * -1 : return_number;

    return return_number;
}


char *int_to_str(int input) {
    int number_of_digits = 0, temp = input, i = 0, sign = 0; // 0 means positive, 1 means negative
    static char *out_str;

    if (input == 0) {
        return "0";
    }

    if (temp * -1 > 0) {
        sign = 1;
    }

    while (temp > 0) {
        temp /= 10;
        number_of_digits++;
    }

    out_str = sign == 1 ? malloc(sizeof(char) * (number_of_digits + 2)) : malloc(sizeof(char) * (number_of_digits + 1));

    if (out_str == NULL) {
        fprintf(stderr, "Error in int_to_str(): malloc() failed to allocate memory\n");

        return NULL;
    }

    if (sign == 1) {
        out_str[0] = 45;
        i++;
    }

    while(i < number_of_digits) {
        if (sign == 0) {
            out_str[number_of_digits - i - 1] = (input % 10) + 48;
        }
        else {
            out_str[number_of_digits - i] = (input % 10) + 48;
        }
        // printf("Out str->%s\n", out_str[i]);
        input /= 10;

        i++;
    }

    out_str[number_of_digits] = '\0';

    // printf("Out str->%s\n", out_str);

    // for (int i = 0; i < number_of_digits; i++) {
    //     output[i] = out_str[i];
    // }

    return out_str;
}


// ! Works
// char *int_to_str(int input) {
//     int number_of_digits = 0, temp = input, i = 0, sign = 0; // 0 means positive, 1 means negative
//     static char *out_str;

//     if (input == 0) {
//         return "0";
//     }

//     if (temp * -1 > 0) {
//         sign = 1;
//     }

//     while (temp > 0) {
//         temp /= 10;
//         number_of_digits++;
//     }

//     printf("Number of digits->%d\n", number_of_digits);

//     out_str = sign == 1 ? malloc(sizeof(char) * (number_of_digits + 2)) : malloc(sizeof(char) * (number_of_digits + 1));

//     if (out_str == NULL) {
//         fprintf(stderr, "Error in int_to_str(): malloc() failed to allocate memory\n");

//         return NULL;
//     }

//     if (sign == 1) {
//         out_str[0] = 45;
//         i++;
//     }

//     while(i < number_of_digits) {
//         printf("loop not issue\n");
//         out_str[number_of_digits - i - 1] = (input % 10) + 48;
//         // printf("Out str->%s\n", out_str[i]);
//         input /= 10;

//         i++;
//     }

//     out_str[number_of_digits] = '\0';

//     for (int j = 0; j < number_of_digits; j++) {
//         printf("out_str[%d] = %c\n", j, out_str[j]);
//     }

//     // printf("Out str->%s\n", out_str);

//     // for (int i = 0; i < number_of_digits; i++) {
//     //     output[i] = out_str[i];
//     // }

//     return out_str;
// }


// reads a string from input and stores it in string of size n
// ensures no buffer overflow
void input_capture(char *str, int n) {
    int i = 0;
    int ch; // ch has int type as getchar() returns an integer value

    while ((ch = getchar()) != '\n') { // \n must be in single quotes so its a string literal not a string
        if (i < n - 1) { // ensures that string is not longer than array it is stored in
            str[i] = ch;
            i++;
        }
    }

    // terminates string with a null character to prevent against buffer overflow
    // unlike some input functions...
    // lookin' at you scanf()

    str[i] = '\0';
}


void print(char *str, ...) {
    int format_specifier = 0;
    int arguments_fetched = -1;
    char *temp;

    /* Declare a variable of type va_list. */
    va_list argptr;

    /* Initialize that variable.. */
    va_start (argptr, str);

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != 37 && format_specifier != 1) {
            putc(str[i], stdout);
        }
        else if (str[i] == 37) { // 37 is the '%' character
            format_specifier = 1;

            continue;
        }
        else if (format_specifier = 1) {
            arguments_fetched += 1;

            format_specifier = 0;

            switch (str[i]) {
                case 'd':
                    temp = int_to_str(va_arg(argptr, int));

                    for (int j = 0; j < strlen(temp); j++) {
                        putc(temp[j], stdout);
                    }

                    break;

                default:
                    printf("u fucking suck\n");
                    break;
            }
        }
    }
}


// captures input using the input_capture() function
// and converts the value to the desired output type
// void *out is pointer to the output variable
// int n is the length of the input string, including the null character
// that will be added
// types out_type is the type of the output variable:
// INTEGER, STRING or CHARACTER
int read_line(void *out, int n, types out_type) {
    char *str;

    switch (out_type) {
        case STRING:

            str = (char *) out;

            input_capture(str, n);

            *((char *) out) = *str;
            
            break;

        case CHARACTER:

            *((char *) out) = (char) getchar();

            break;

        case INTEGER:

            str = (char *) out;

            input_capture(str, n);

            *((int *) out) = str_to_int(str, n);

            break;

        default:

            fprintf(stderr, "Error in read_line(): invalid output type\nChoose from:\nString: s\nCharacter: c\nInteger: i\n");

            return -1;

            break;
    }

    return 1;
}


// "print in colour", kinda self-explanatory
// prints a string to stdout in your desired colours
// if 0 is passed to foreground_colour and background_colour,
// then this will print in normal colours
void printc(char *string, int foreground_colour, int background_colour) {
    foreground_colour = (foreground_colour > 255 || foreground_colour < 0) ? 0 : foreground_colour;
    background_colour = (background_colour > 255 || background_colour < 0) ? 0 : background_colour;

    // printf("%s\n", string);

    for (int i = 0; i < ((sizeof(string) - 1) / sizeof(string[0])); i++) {
        if (string[i] <= 31 && string[i] > 0) {
            print(ANSI_COLOUR_RESET);
            putc(string[i], stdout);
        }
        else if (string[i] == 0) {
            break;
        }
        else {
            print("\x1b[38;5;%dm\x1b[48;5;%dm", foreground_colour, background_colour);
            // printf("\x1b[48;5;%dm", background_colour);
            putc(string[i], stdout);
        }
    }
    
    print(ANSI_COLOUR_RESET);
}


// size in number of ░ (ASCII 176) characters
void create_progress_bar(int size, int foreground_colour, int background_colour) {
    for (int i = 0; i < size; i++) {
        printc("\xb0", foreground_colour, background_colour);
    }
    print("\r");
}

// prints a ▓ (ASCII 178) character in desired colours
void move_progress_bar(int foreground_colour, int background_colour) {
    printc("\xb2", foreground_colour, background_colour);
}