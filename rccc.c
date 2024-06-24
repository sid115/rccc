#include <stdio.h>
#include <math.h>
#include <string.h>

#define NUM_COLORS 12            // Number of color codes
#define COLOR_NAME_MAX_LENGTH 10 // Max length of color name
#define INVALID -1               // Used to indicate invalid value

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
    if (argc != 5 && argc != 6) {
        printf("Usage: %s <color1> <color2> <color3> <color4> [<color5>]\n", argv[0]);
        return 1;
    }

    // Initialize variables
    int firstBand, secondBand, thirdBand = 0, exponent;
    float tolerance;
    int resistanceValue;

    // Retrieve colors and validate
    Color *color1 = getColor(argv[1]);
    Color *color2 = getColor(argv[2]);
    Color *color3 = getColor(argv[3]);
    Color *color4 = getColor(argv[4]);
    Color *color5 = (argc == 6) ? getColor(argv[5]) : NULL;

    if (!color1 || !color2 || !color3 || !color4 || (argc == 6 && !color5)) {
        printf("Invalid color code input.\n");
        return 1;
    }

    // Calculate resistance value
    firstBand = color1->value;
    secondBand = color2->value;

    if (argc == 5) { // 4-band resistor
        exponent = color3->exponent;
        tolerance = color4->tolerance;

        resistanceValue = (firstBand * 10 + secondBand) * (int)pow(10, exponent);

    } else { // 5-band resistor
        thirdBand = color3->value;
        exponent = color4->exponent;
        tolerance = color5->tolerance;

        resistanceValue = (firstBand * 100 + secondBand * 10 + thirdBand) * (int)pow(10, exponent);
    }

    // Print resistance value
    printf("Resistance: %d Ω ±%.2f%%\n", resistanceValue, tolerance);

    return 0;
}
