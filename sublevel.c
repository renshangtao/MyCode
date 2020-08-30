#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    
    /*  
        解法：
        数组的每一个元素存在两种状态，0：不选，1：选择。
        数组的子集个数为：numsSize个数的数组，其子集个数为pow(2, numsSize)
        所以只需要遍历从0到pow(2, numsSize)-1的所有数字中1个个数即可得出每个子集中元素的个数
    */
    int **arr;
    int *parr;
    *returnSize = pow(2, numsSize);
    
    /* 先申请一个空的二维数组，后续根据需要申请第二维 */
    arr = (int**)malloc(sizeof(int *) * (*returnSize));
    
    /* 传进来的是指针，所以要用两层指针 */
    *returnColumnSizes = (int *)malloc(sizeof(int) * (*returnSize));
    //parr = (int *)malloc(sizeof(int) * (*returnSize));
    
    
    int i = 0;
    int j = 0;
    int k = 0;
    int count = 0;
    int m = 0;
    
    for (; i < *returnSize; i++)
    {
        m = i;
        count = 0;
        
        while(m)
        {
            m &= (m - 1);
            count++;
        }
        

        arr[i] = (int *)malloc(sizeof(int) * count);
        (*returnColumnSizes)[i] = count;

        for (j = 0, k = 0; j < 31; j++)
        {
            if (i & (1 << j))
            {
                arr[i][k++] = nums[j];
            }
        }
    }
    
    return arr;
    
}

int main(void)
{
    int a[3] = {1,2,3};
    int rowSize;
    int *pcloumSize;
    int **arr;
    int i = 0;
    int j = 0;

    arr = subsets(a, 3, &rowSize, &pcloumSize);

    printf("rowSize = %d.\n", rowSize);
    
    for (; i < rowSize; i++)
    {
        printf("%d ", pcloumSize[i]);
    }

    printf("\n");

    for (i = 0; i < rowSize; i++)
    {
        for (j = 0; j < pcloumSize[i]; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}