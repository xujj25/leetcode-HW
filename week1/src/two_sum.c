#include <stdio.h>
#include <malloc.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target) {
    int* result = (int*)malloc(2 * sizeof(int));

    int i, j;
    for (i = 0; i < numsSize; i++) {
    	for (j = 0; j < numsSize; j++) {
    		if (i == j) continue;
    		if (nums[i] + nums[j] == target) {
    			if (i < j) {
    				result[0] = i;
    				result[1] = j;
    			} else {
    				result[0] = j;
    				result[1] = i;
    			}
    			return result;
    		}
    	}
    }
    return result;
}

int main(void)
{
	int nums[3] = {3, 2, 4};
	int *result = twoSum(nums, 3, 6);
	printf("result:[%d, %d]\n", result[0], result[1]);
	return 0;
}