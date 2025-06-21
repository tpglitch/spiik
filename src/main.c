#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Check if two-character sequence sounds like "ee"
int is_ee_sound(const char *s) {
    return (!strncmp(s, "ee", 2) || !strncmp(s, "EE", 2) ||
            !strncmp(s, "Ee", 2) || !strncmp(s, "eE", 2) ||
            !strncmp(s, "ea", 2) || !strncmp(s, "EA", 2) ||
            !strncmp(s, "Ea", 2) || !strncmp(s, "eA", 2));
}

void to_wii_speak(const char *input, char *output) {
    int i = 0, j = 0;
    int first_capital = isupper(input[0]);

    while (input[i]) {
        if (input[i + 1] && is_ee_sound(&input[i])) {
            // Replace with "ii", capital if first letter
            if (j == 0 && first_capital)
                output[j++] = 'I';
            else
                output[j++] = 'i';
            output[j++] = 'i';
            i += 2; // Skip "ee"/"ea"
        } else {
            // Copy single character
            if (j == 0 && first_capital)
                output[j++] = toupper(input[i++]);
            else
                output[j++] = tolower(input[i++]);
        }
    }
    output[j] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <word>\n", argv[0]);
        return 1;
    }

    const char *input = argv[1];
    char output[1024];
    to_wii_speak(input, output);

    printf("%s -> %s\n", input, output);
    return 0;
}
