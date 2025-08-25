#include <stdio.h>
#include <stdlib.h>

// A structure to represent an activity
typedef struct {
    int start;
    int finish;
} Activity;

// Comparison function to sort activities based on their finish times
int compareActivities(const void* a, const void* b) {
    Activity* activityA = (Activity*)a;
    Activity* activityB = (Activity*)b;
    return activityA->finish - activityB->finish;
}

// Function to solve the activity selection problem
void activitySelection(Activity activities[], int n) {
    // Sort activities based on finish times
    qsort(activities, n, sizeof(Activity), compareActivities);

    printf("Following activities are selected:\n");

    // The first activity in the sorted array is always selected
    int i = 0;
    printf("Activity %d: (%d, %d)\n", i, activities[i].start, activities[i].finish);

    // Consider the rest of the activities
    for (int j = 1; j < n; j++) {
        // If this activity has a start time greater than or equal to
        // the finish time of the previously selected activity, then select it
        if (activities[j].start >= activities[i].finish) {
            printf("Activity %d: (%d, %d)\n", j, activities[j].start, activities[j].finish);
            i = j;
        }
    }
}

int main() {
    Activity activities[] = {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 8}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 13}, {12, 14}};
    int n = sizeof(activities) / sizeof(activities[0]);

    activitySelection(activities, n);

    return 0;
}
