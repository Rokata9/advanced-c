#include <stdio.h>

int main() {
    int arr_size;

    printf("Enter amount of numbers: ");
    scanf("%d", &arr_size);

    int nums[arr_size];
    
    for (int i = 0; i < arr_size; i++) {
        printf("Number #%d: ", i+1);
        scanf("%d", &nums[i]);
    }

    int sum = 0;

    for (int i = 0; i < arr_size; i++) {
        sum += nums[i]; 
    }

    printf("Sum is %d\n", sum);
}
