#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define NUM_COLORS 12                            // Number of color codes
#define COLOR_NAME_MAX_LENGTH 10                 // Max length of color name
#define INVALID -1                               // Used to indicate invalid value
#define MAX_ARGS 6                               // Max number of input arguments
#define NUM_ARGS_4_BANDS (MAX_ARGS - 1)          // Number of input arguments for 4-band resistor
#define NUM_ARGS_5_BANDS (MAX_ARGS)              // Number of input arguments for 5-band resistor
#define MAX_VALUE_BANDS 3                        // Max number of value bands (5-band resistor has 3 value bands)
#define NUM_VALUE_BANDS (argc - MAX_VALUE_BANDS) // Number of value bands

// Error messages
#define ERR_INVALID_COLOR "Invalid color code input: %s\n"
#define ERR_INVALID_VALUE_BAND "Invalid color code input for value band: %s\n"
#define ERR_INVALID_TOLERANCE "Invalid color code input for tolerance: %s\n"
#define ERR_USAGE "Usage: %s <color1> <color2> <color3> <color4> [<color5>]\n"

// Color structure
typedef struct {
    char name[COLOR_NAME_MAX_LENGTH]; // Color name
    int value;                        // Value as digit
    int exponent;                     // Multiplier as exponent of base 10
    float tolerance;                  // Tolerance in %
} Color;

// Array of color codes
Color colors[NUM_COLORS] = {
/*   Name        Value Exp  Tolerance */
    {"black",        0,  0, INVALID},
    {"brown",        1,  1, 1},
    {"red",          2,  2, 2},
    {"orange",       3,  3, INVALID},
    {"yellow",       4,  4, INVALID},
    {"green",        5,  5, 0.5},
    {"blue",         6,  6, 0.25},
    {"violet",       7,  7, 0.1},
    {"grey",         8,  8, 0.05},
    {"white",        9,  9, INVALID},
    {"gold",   INVALID, -1, 5},
    {"silver", INVALID, -2, 10}
};

// Function to convert color name to color structure
Color* getColor(const char* color) {
    for (int i = 0; i < NUM_COLORS; i++) {
        if (strncmp(colors[i].name, color, COLOR_NAME_MAX_LENGTH) == 0) {
            return &colors[i];
        }
    }
    return NULL;
}

// Main function
int main(int argc, char *argv[]) {
    // Check input arguments
    if (argc != NUM_ARGS_4_BANDS && argc != NUM_ARGS_5_BANDS) {
        printf(ERR_USAGE, argv[0]);
        return EXIT_FAILURE;
    }

    // Initialize variables
    int values[MAX_VALUE_BANDS] = { INVALID };
    int exponent;
    float tolerance = INVALID;
    int resistanceValue;

    // Retrieve colors and validate
    Color *colors[MAX_ARGS] = { NULL };
    for (int i = 1; i < argc; ++i) {
        colors[i - 1] = getColor(argv[i]);
        if (colors[i - 1] == NULL) {
            printf(ERR_INVALID_COLOR, argv[i]);
            return EXIT_FAILURE;
        }
    }

    // Assign values, exponent, and tolerance
    values[0] = colors[0]->value;
    values[1] = colors[1]->value;
    values[2] = argc == MAX_ARGS ? colors[2]->value : INVALID;
    exponent = colors[argc - 3]->exponent;
    tolerance = colors[argc - 2]->tolerance;

    // Check if value bands are invalid
    for (int i = 0; i < NUM_VALUE_BANDS; i++) {
        if (values[i] == INVALID) {
            printf(ERR_INVALID_VALUE_BAND, argv[i + 1]);
            return EXIT_FAILURE;
        }
    }

    // Check if tolerance is invalid
    if (tolerance == INVALID) {
        printf(ERR_INVALID_TOLERANCE, argv[argc - 1]);
        return EXIT_FAILURE;
    }

    // Calculate resistance value
    if (argc == NUM_ARGS_4_BANDS) { // 4-band resistor
        resistanceValue = (values[0] * 10 + values[1]) * (int)pow(10, exponent);

    } else { // 5-band resistor
        resistanceValue = (values[0] * 100 + values[1] * 10 + values[2]) * (int)pow(10, exponent);
    }

    // Print resistance value
    printf("%d Ω ±%.2f%%\n", resistanceValue, tolerance);

    return EXIT_SUCCESS;
}
