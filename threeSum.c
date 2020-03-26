// 第15题 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，
// 使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

// 给定数组 nums = [-1, 0, 1, 2, -1, -4]，

// 满足要求的三元组集合为：
// [
//   [-1, 0, 1],
//   [-1, -1, 2]
// ]

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *pd1, const void *pd2)
{
    return *(int*)pd1 - *(int*)pd2;
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    qsort(nums, numsSize, sizeof(int), cmp);

    for (int i = 0; i < numsSize; i++)
    {

        if (nums[i] == nums[i-1]) continue;     //去重
        if (nums[i] > 0) break;                 //直接停止，防止做无用功

        for (int j = i + 1; j < numsSize; j++)
        {
            if (nums[i] + nums[j] > 0) break;   //直接停止，防止做无用功

            for (int k = numsSize -1 ; k > j; k--)
            {
                if (0 == (nums[i] + nums[j] + nums[k]))
                {
                    printf("zero %d, %d, %d \n", nums[i], nums[j], nums[k]);
                    break;
                }
            }
        }
    }
}


int main()
{
    int nums[] = {-1, 0, 1, 2, -1, -4};
    int returnSize = 0;
    int *returnColumnSizes = NULL;
    
    threeSum(nums, sizeof(nums) / sizeof(int), &returnSize, &returnColumnSizes);

    return 0;

}