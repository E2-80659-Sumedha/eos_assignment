#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

typedef struct array
{
    int size;
    int *arr;
    
}arr_t;

void swap(int *p, int *q)
{
    int temp = *p;
    *p = *q;
    *q = temp;
}

void *bubble_sort_array(void *param)
{
    arr_t *a = (arr_t *)param;
    for(int i =0; i<a->size-1; i++)
    {
        for(int j=0; j<a->size-1-i; j++)
        {
            if(a->arr[j] > a->arr[j+1])
            {
                swap(&a->arr[j], &a->arr[j+1]);
            }
        }
    }
    pthread_exit(a->arr);
}

int main(void)
{
    int ret;
    arr_t a;
    printf("Enter the size of array: ");
    scanf("%d", &a.size);
    a.arr = (int *)malloc(a.size * sizeof(int));
    
    printf("\nEnter array element: ");
    for(int i=0; i<a.size; i++)
    {
        scanf("%d", &a.arr[i]);
    }

    pthread_t th;
    ret = pthread_create(&th, NULL, bubble_sort_array, &a);
    if(ret != 0)
    {
        perror("pthread_create() failed\n");
        _exit(1);
    }

    printf("\nmain waiting for thread complete-----\n");
    pthread_join(th, (void**)&(a.arr));
    int *arr1 = (int *)a.arr;

    printf("\nSorted array: \n");
    for(int i=0; i<a.size; i++)
    {
        printf("%d  ", arr1[i]);
    }
    printf("\n");
    free(a.arr);
    return 0;
}