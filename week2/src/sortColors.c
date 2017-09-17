#include <stdio.h>
#include <malloc.h>

/*void sortColors(int* nums, int numsSize) {
    int b[3] = {0};
    int i;
    for (i = 0; i < numsSize; i++)
    	b[nums[i]]++;
    for (i = 0; i < b[0]; i++)
    	nums[i] = 0;
    for (i = b[0]; i < b[0] + b[1]; i++)
    	nums[i] = 1;
    for (i = b[0] + b[1]; i < numsSize; i++)
    	nums[i] = 2;
}*/


int partition(int arr[], int low, int high) {
	int key = arr[low];
	while (low < high) {
		while (low < high && key <= arr[high])
			high--;
		if (low < high) {
			arr[low] = arr[high];
			low++;
		}
		while (low < high && key >= arr[low])
			low++;
		if (low < high) {
			arr[high] = arr[low];
			high--;
		}
	}
	arr[low] = key;
	return low;
}

void quickSort(int arr[], int start, int end) {
	int pos;
	if (start < end) {
		pos = partition(arr, start, end);
		quickSort(arr, start, pos - 1);
		quickSort(arr, pos + 1, end);
	}
	return;
}


// use quickSort
void sortColors(int* nums, int numsSize) {
	quickSort(nums, 0, numsSize - 1);
}

int main()
{
	int* nums, i;
	int numsSize;
	scanf("%d", &numsSize);
	if (numsSize <= 0)
		return 0;
	nums = (int*)malloc(numsSize * sizeof(int));
	for (i = 0; i < numsSize; i++)
		scanf("%d", &nums[i]);
	sortColors(nums, numsSize);

	printf("bp\n");

	for (i = 0; i < numsSize; i++)
		printf("%d ", nums[i]);
	free(nums);
	return 0;
}