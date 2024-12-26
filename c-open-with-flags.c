#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compile with: gcc -o copen c-open-with-flags.c

int main(int argc, char *argv[]) {
    FILE *file;
    char ch;
    int line_count = 0, char_count = 0, column_count = 0, max_column = 0;
    long file_size;
    float bits, kilobytes, megabytes;
    int print_stats = 0;

    // Check if a filename is provided
    if (argc < 2) {
        printf("Usage: %s [-s] <filename>\n", argv[0]);
        return 1;
    }

    // Check for -s flag for stats
    if (argc > 2 && strcmp(argv[1], "-s") == 0) {
        print_stats = 1;  // Set flag to print stats
    }

    // Open the file in read mode
    file = fopen(argv[argc - 1], "r");
    if (file == NULL) {
        printf("Error: Could not open file %s.\n", argv[argc - 1]);
        return 1;
    }

    // Count lines, characters, and maximum columns
    while ((ch = fgetc(file)) != EOF) {
        char_count++;
        column_count++;
        if (ch == '\n') {
            line_count++;
            if (column_count > max_column) {
                max_column = column_count - 1; // Exclude newline from column count
            }
            column_count = 0; // Reset for next line
        }
    }

    // If the file doesn't end with a newline
    if (column_count > max_column) {
        max_column = column_count;
    }
    if (char_count > 0) {
        line_count++;
    }

    // Calculate file size in bits, bytes, kilobytes, and megabytes
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    bits = file_size * 8;
    kilobytes = file_size / 1024.0;
    megabytes = kilobytes / 1024.0;

    // Reset the file pointer to the beginning of the file
    rewind(file);


    // Print the content of the file
    printf("\n");
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    // Print stats if the flag is set
    if (print_stats) {
        printf("\n");
        printf("\033[38;5;240m"); // Set text color to a gray color close to #505050
        printf("Chars: %d • Lines: %d • Columns: %d • Bits: %.0f • Bytes: %ld • Kilobytes: %.2f • Megabytes: %.5f\n",
               char_count, line_count, max_column, bits, file_size, kilobytes, megabytes);
        printf("\033[0m"); // Reset text color
    }

    // Close the file
    fclose(file);
    printf("\n");
    return 0;
}

