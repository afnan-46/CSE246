#include <stdio.h>
#include <stdlib.h>

// A structure to represent an item with its value and weight
typedef struct {
    int value;
    int weight;
} Item;

// Comparison function to sort items based on their value-to-weight ratio
int compareItems(const void* a, const void* b) {
    double ratio_a = (double)((Item*)a)->value / ((Item*)a)->weight;
    double ratio_b = (double)((Item*)b)->value / ((Item*)b)->weight;
    
    if (ratio_a < ratio_b) return 1;
    if (ratio_a > ratio_b) return -1;
    return 0;
}

// Main function to solve the fractional knapsack problem
double fractionalKnapsack(int W, Item items[], int n) {
    // Sort items in descending order of value-to-weight ratio
    qsort(items, n, sizeof(Item), compareItems);

    double total_value = 0.0;
    int current_weight = 0;

    // Loop through all items
    for (int i = 0; i < n; i++) {
        // If the current item can be taken as a whole
        if (current_weight + items[i].weight <= W) {
            current_weight += items[i].weight;
            total_value += items[i].value;
        } else {
            // If we can only take a fraction of the item
            int remaining_weight = W - current_weight;
            total_value += (double)items[i].value * ((double)remaining_weight / items[i].weight);
            break; // The knapsack is now full
        }
    }

    return total_value;
}

int main() {
    int W = 50; // Knapsack capacity
    Item items[] = {{60, 10}, {100, 20}, {120, 30}};
    int n = sizeof(items) / sizeof(items[0]);

    double max_value = fractionalKnapsack(W, items, n);

    printf("Maximum value we can obtain = %.2f\n", max_value);

    return 0;
}
