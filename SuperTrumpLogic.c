#include <stdio.h>
#include <string.h>

// Card structure
typedef struct {
    char code[4];
    char name[50];
    unsigned long int population;
    float area;
    float gdp;
    int touristSpots;
    float density;
    float gdpPerCapita;
} Card;

// Calculates derived attributes
void calculateAttributes(Card *c) {
    c->density = c->area > 0 ? (float)c->population / c->area : 0;
    c->gdpPerCapita = c->population > 0 ? c->gdp / c->population : 0;
}

// Display attribute menu
void showMenu(int skip) {
    printf("\nChoose an attribute to compare:\n");
    if (skip != 1) printf("1 - Population\n");
    if (skip != 2) printf("2 - Area\n");
    if (skip != 3) printf("3 - GDP\n");
    if (skip != 4) printf("4 - Tourist Spots\n");
    if (skip != 5) printf("5 - Population Density\n");
    if (skip != 6) printf("6 - GDP per Capita\n");
    printf("Your choice: ");
}

// Get attribute value from a card
float getValue(Card c, int option) {
    switch(option) {
        case 1: return (float)c.population;
        case 2: return c.area;
        case 3: return c.gdp;
        case 4: return (float)c.touristSpots;
        case 5: return c.density;
        case 6: return c.gdpPerCapita;
        default: return -1;
    }
}

// Show attribute name
void attributeName(int option) {
    switch(option) {
        case 1: printf("Population"); break;
        case 2: printf("Area"); break;
        case 3: printf("GDP"); break;
        case 4: printf("Tourist Spots"); break;
        case 5: printf("Population Density"); break;
        case 6: printf("GDP per Capita"); break;
    }
}

// Register a card (user input)
void registerCard(Card *c, int number) {
    printf("\n--- Register Card %d ---\n", number);
    printf("Code (e.g., A01): ");
    scanf(" %3s", c->code);
    printf("Country name: ");
    scanf(" %[^\n]", c->name);
    printf("Population (numbers only): ");
    scanf("%lu", &c->population);
    printf("Area in km²: ");
    scanf("%f", &c->area);
    printf("GDP in trillion USD: ");
    scanf("%f", &c->gdp);
    printf("Number of tourist spots: ");
    scanf("%d", &c->touristSpots);
    calculateAttributes(c);
}

int main() {
    Card c1, c2;
    int choice1, choice2;

    // Register both cards
    registerCard(&c1, 1);
    registerCard(&c2, 2);

    // Choose two different attributes
    showMenu(0);
    scanf("%d", &choice1);

    do {
        showMenu(choice1);
        scanf("%d", &choice2);
        if (choice2 == choice1)
            printf("You've already selected that attribute. Choose another.\n");
    } while (choice2 == choice1);

    // Get attribute values
    float val1_c1 = getValue(c1, choice1);
    float val1_c2 = getValue(c2, choice1);
    float val2_c1 = getValue(c1, choice2);
    float val2_c2 = getValue(c2, choice2);

    // Determine winners
    int w1 = (choice1 == 5) ? (val1_c1 < val1_c2) : (val1_c1 > val1_c2);
    int w2 = (choice2 == 5) ? (val2_c1 < val2_c2) : (val2_c1 > val2_c2);

    float sum1 = val1_c1 + val2_c1;
    float sum2 = val1_c2 + val2_c2;

    // Final result
    printf("\n--- FINAL RESULT ---\n");
    printf("Card 1: %s\n", c1.name);
    printf("Card 2: %s\n\n", c2.name);

    printf("Attribute 1: ");
    attributeName(choice1);
    printf("\n  %s: %.2f\n  %s: %.2f\n", c1.name, val1_c1, c2.name, val1_c2);
    printf("Winner: %s\n\n", w1 ? c1.name : c2.name);

    printf("Attribute 2: ");
    attributeName(choice2);
    printf("\n  %s: %.2f\n  %s: %.2f\n", c1.name, val2_c1, c2.name, val2_c2);
    printf("Winner: %s\n\n", w2 ? c1.name : c2.name);

    printf("Sum of selected attributes:\n");
    printf("  %s: %.2f\n", c1.name, sum1);
    printf("  %s: %.2f\n", c2.name, sum2);

    if (sum1 == sum2)
        printf("Final result: It's a draw!\n");
    else
        printf("Final result: %s wins the round!\n", (sum1 > sum2) ? c1.name : c2.name);

    return 0;
}
