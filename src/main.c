#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Check if two-character sequence sounds like "ee"
int is_ee_sound(const char *s) {
    return (!strncmp(s, "ee", 2) || !strncmp(s, "EE", 2) ||
            !strncmp(s, "Ee", 2) || !strncmp(s, "eE", 2) ||
            !strncmp(s, "ea", 2) || !strncmp(s, "EA", 2) ||
            !strncmp(s, "Ea", 2) || !strncmp(s, "eA", 2) ||
            !strncmp(s, "ey", 2) || !strncmp(s, "EY", 2) ||
            !strncmp(s, "Ey", 2) || !strncmp(s, "eY", 2) ||
            !strncmp(s, "ie", 2) || !strncmp(s, "IE", 2) ||
            !strncmp(s, "Ie", 2) || !strncmp(s, "iE", 2) ||
            !strncmp(s, "ei", 2) || !strncmp(s, "EI", 2) ||
            !strncmp(s, "Ei", 2) || !strncmp(s, "eI", 2) ||
            !strncmp(s, "eo", 2) || !strncmp(s, "EO", 2) ||
            !strncmp(s, "Eo", 2) || !strncmp(s, "eO", 2) ||
            !strncmp(s, "oe", 2) || !strncmp(s, "OE", 2) ||
            !strncmp(s, "Oe", 2) || !strncmp(s, "oE", 2));
}

void to_wii_speak(const char *input, char *output) {
    int i = 0, j = 0;
    int first_capital = isupper(input[0]);
    int len = strlen(input);
    while (input[i]) {
        // Handle two-letter ee sounds
        if (input[i + 1] && is_ee_sound(&input[i])) {
            if (j == 0 && first_capital)
                output[j++] = 'I';
            else
                output[j++] = 'i';
            output[j++] = 'i';
            i += 2;
        // Handle 'y' at the end of a word (happy, funny)
        } else if (input[i] == 'y' || input[i] == 'Y') {
            if (i == len - 1) {
                if (j == 0 && first_capital)
                    output[j++] = 'I';
                else
                    output[j++] = 'i';
                output[j++] = 'i';
                i++;
            } else {
                if (j == 0 && first_capital)
                    output[j++] = toupper(input[i++]);
                else
                    output[j++] = tolower(input[i++]);
            }
        // Handle 'e' at the end of a word (me, he, she, we, be)
        } else if ((input[i] == 'e' || input[i] == 'E') && i == len - 1) {
            if (j == 0 && first_capital)
                output[j++] = 'I';
            else
                output[j++] = 'i';
            output[j++] = 'i';
            i++;
        // Handle single 'i' in special words (machine, ski)
        } else if ((input[i] == 'i' || input[i] == 'I') &&
                   (i == 0 || !isalpha(input[i-1])) &&
                   (strncmp(&input[i], "ine", 3) == 0 || strncmp(&input[i], "i", 1) == 0)) {
            // This is a best-effort guess, not perfect
            if (j == 0 && first_capital)
                output[j++] = 'I';
            else
                output[j++] = 'i';
            output[j++] = 'i';
            i++;
        } else {
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
