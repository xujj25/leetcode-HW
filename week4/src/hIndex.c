#include <stdio.h>
#include <malloc.h>

typedef struct range {
    int start, end;
} range;

range new_range(int s, int e) {
    range r;
    r.start = s;
    r.end = e;
    return r;
}

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(int arr[], int size) {
    if (size <= 1)
        return;

    range rangeStack[size], tempRange;
    int pos = 0, mid, left, right;
    rangeStack[pos++] = new_range(0, size - 1);
    while (pos) {
        tempRange = rangeStack[--pos];
        if (tempRange.start >= tempRange.end)
            continue;
        left = tempRange.start;
        right = tempRange.end - 1;
        mid = arr[tempRange.end];
        while (left < right) {
            while (arr[left] < mid && left < right)
                left++;
            while (arr[right] >= mid && left < right)
                right--;
            swap(&arr[left], &arr[right]);
        }
        if (arr[left] >= arr[tempRange.end])
            swap(&arr[left], &arr[tempRange.end]);
        else
            left++;
        rangeStack[pos++] = new_range(tempRange.start, left - 1);
        rangeStack[pos++] = new_range(left + 1, tempRange.end);
    }
}

int hIndex(int* citations, int citationsSize) {
    if (citationsSize <= 0)
        return 0;
    int i;
    quickSort(citations, citationsSize);
    for (i = citationsSize - 1; i >= 0; i--) {
        if (citations[i] >= citationsSize - i) {
            if (i == 0) {
                return citationsSize;                
            } else if (citations[i - 1] <= citationsSize - i) {
                return citationsSize - i;
            }
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    int size, i;
    int *arr;
    scanf("%d", &size);
    if (size <= 0)
        return -1;
    arr = (int*)malloc(size * sizeof(int));
    for (i = 0; i < size; i++)
        scanf("%d", &arr[i]);
    printf("%d\n", hIndex(arr, size));
    return 0;
}