#include <stdio.h>
int binarySearch(int arr[], int size, int target) {
    int low = 0, high = size - 1; //low, high are the index
    while (low <= high) {
        int mid = low + (high - low) / 2; //mid is the index
        if (arr[mid] == target)
            return mid;  // Element found
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;  // Element not found
}
int main() {
    int n, target;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d elements in sorted order:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter the number to search: ");
    scanf("%d", &target);
    int result = binarySearch(arr, n, target);
    if (result != -1)
        printf("Element %d found at index %d\n", target, result);
    else
        printf("Element %d not found in the array\n", target);
    return 0;
}
