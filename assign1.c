#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define SIZE 10

void swap(int *p, int *q)
{
    int temp = *p;
    *p = *q;
    *q = temp;
}

void *sort_array(void *param)
{
    int *arr = (int *)param;

    for(int i =0; i<SIZE-1; i++)
    {
        for(int j=i+1; j<SIZE-1; j++)
        {
            if(arr[i] > arr[j])
            swap(&arr[i], &arr[j]);
        }
    }
    //return arr;
    //Or,
    pthread_exit(arr);
}

int main()
{
    int arr[SIZE];
    int *arr2 ;
    printf("Enter the 10 array elements:\n");
    for(int i=0; i<10; i++)
    {
        scanf("%d", &arr[i]);
    }

    int ret;
    pthread_t th;
    ret = pthread_create(&th, NULL, sort_array, arr);
    if(ret != 0)
    {
        perror("pthread_create is failed()!\n");
        _exit(1);
    }

    printf("\nmain waiting for thread complete\n");
    pthread_join(th, (void**)&arr2);
    arr2 = (int *)arr2;

    printf("Sorted array is :\n");
    for(int i =0; i<SIZE; i++)
    {
        printf("%d  ", arr2[i]);
    }
    return 0;
}