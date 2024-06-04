#ifndef TEXT_FUNCTIONS

    #define TEXT_FUNCTIONS

    typedef enum {
        CHARACTER = 'c',
        INTEGER = 'i',
        STRING = 's',
    } types;

    void rotation_loading(int rotation_time);
    void printc(char *string, int foreground_colour, int background_colour);
    void create_progress_bar(int size, int foreground_colour, int background_colour);
    void move_progress_bar(int foreground_colour, int background_colour);
    int read_line(void *out, int n, types out_type);
    int str_to_int(char *str, int str_len);
    char *int_to_str(int input);
    void print(char *str, ...);

#endif