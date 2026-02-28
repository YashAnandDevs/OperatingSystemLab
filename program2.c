#include <stdio.h>
int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int min = arr[0];
    int position = 0;
    for(int i = 1; i < n; i++) {
        if(arr[i] < min) {
            min = arr[i];
            position = i;
        }
    }
    printf("Smallest number: %d\n", min);
    printf("Position: %d\n", position + 1);
    return 0;
}