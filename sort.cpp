/**
implement sort algorithm
*/
#include <iostream>
#include <malloc.h>

using namespace std;
//dumparray
template<typename Tp>
void dump(Tp *array, int len)
{
    for(int i=0; i<len; i++)
    {
        cout<<array[i]<<",";
    }
    cout<<endl;
}


//bubbling sort
template <typename Tp>
void bubble(Tp *array, int len)
{
    int tmp;
    for(int i=len-1; i>0; i--)
    {
        for(int j=0; j<i; j++)
        {
            if(array[j]>=array[j+1])
            {
                tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
            }
        }
    }
}

//select algorithm
template<typename Tp>
void select(Tp *array, int len)
{
    int min,tmp;
    for(int i=0; i<len-1; i++)
    {
        min = i;
        for(int j=i+1; j<len; j++)
        {
            if(array[min] >= array[j])
            {
                min = j;
            }
        }
        tmp = array[i];
        array[i] = array[min];
        array[min] = tmp;
    }
}

//insert algorithm
template<typename Tp>
void insert(Tp *array, int len)
{
    int j;
    for(int i=1; i<len; i++)
    {
        for(j=0; j<i; j++)
        {
            if(array[j] >= array[i])
                break;
        }
        if(j<i)
        {
            int tmp = array[i];
            //容易出错的部分
            for(int k=i-1; k>=j; k--)
            {
                array[k+1] = array[k];
            }
            array[j] = tmp;
        }
    }
}

//quick sort
template<typename Tp>
int partation(Tp *array, int start, int end)
{
    int pivot = array[start];
    while(start < end)
    {
        while(start<end && array[end] >= pivot)
            end--;
        if(start<end)
            array[start++] = array[end];
        while(start<end && array[start] <= pivot)
            start++;
        if(start<end)
            array[end--] = array[start];
    }
    array[start] = pivot;
    return start;
}

template<typename Tp>
void quicksort(Tp *array, int start, int end)
{
    int index;
    if(start < end )
    {
        index = partation(array, start, end);
        if (index > start)
            quicksort(array, start, index-1);
        if (index < end)
            quicksort(array, index+1, end);
    }


}

//归并排序
template<typename Tp>
void merge(Tp *array, int start, int end, int start1, int end1)
{
    Tp *tmp = (Tp *) malloc(sizeof(Tp)*(end1-start+1));
    int pi=start,pj=start1, pk=0;
    while(pi<=end && pj<=end1)
    {
        if(array[pi]<array[pj])
        {
            tmp[pk++] = array[pi++];
        } else
        {
            tmp[pk++] = array[pj++];
        }
    }
    for(int i=pi; i<=end; i++)
    {
        tmp[pk++] = array[i];
    }
    for(int i=pj; i<=end1; i++)
    {
        tmp[pk++] = array[i];
    }
    for(int i=0; i<pk; i++)
    {
        array[start++] = tmp[i];
    }
}
template<typename Tp>
void mergesort(Tp *array, int len)
{
    for(int i=1; i<len; i*=2)
    {
        for(int j=0; j<len; j+=2*i)
        {
            merge(array, j, j+i-1, j+i, j+2*i-1);
        }
    }
}

template <typename Tp>
void swap(Tp *a, Tp *b)
{
    Tp t = *a;
    *a = *b;
    *b = t;
}
//Heap Sort
template<typename Tp>
void bigHeap(Tp *a, int start, int len)
{
    int max;
    int temp = a[start];
    int j = 2 * start + 1;
    while(j<len)
    {
        if((j+1) < len && a[j+1]>=a[j])
            j++;
        if(a[j] <= temp)
            break;
        a[start] = a[j];
        start = j;
        j = 2*start+1;
    }
    a[start] = temp;
}
template<typename Tp>
void buildBigHeap(Tp *array, int len)
{
   for(int i=len/2-1; i>=0; i--)
   {
       bigHeap(array, i, len);
   }
}
template<typename Tp>
void buildSmallHeap(Tp *array, int len)
{

}

template<typename Tp>
void heapSort(Tp *array, int len)
{
    buildBigHeap(array, len);
    for(int i=len-1; i >=1; i--)
    {
        swap(&array[i], &array[0]);
        bigHeap(array, 0, i);
    }
}

//bucket sort
template <typename Tp>
struct BucketNode
{
    Tp value;
    struct BucketNode *next;
};
template <typename Tp>
void addToBucket(BucketNode<Tp> *bucket,Tp item)
{
    BucketNode<Tp> *pCur=NULL, *pPre=NULL;
    pCur = bucket->next;
    pPre = bucket;
    while(pCur)
    {
        if(pCur->value <= item)
        {
            pPre = pCur;
            pCur = pCur->next;
        } else
        {
            break;
        }
    }
    BucketNode<Tp> *node = (BucketNode<Tp> *) malloc(sizeof(BucketNode<Tp>));
    node->value = item;
    node->next = pPre->next;
    pPre->next = node;
}
template<typename Tp>
void bucketSort(Tp *array, int len)
{
    //tricky here
    int bucket_num = 3;
    int min = 0, max = 9;
    int ind = (max-min+1)/bucket_num;
    BucketNode<Tp> *bucket[bucket_num];
    for(int i=0; i<bucket_num; i++)
    {
        bucket[i] = (BucketNode<Tp> *)malloc(sizeof(BucketNode<Tp>));
        bucket[i]->value = i;
        bucket[i]->next = NULL;
    }
    int index;
    for(int i=0; i<len; i++)
    {
        index = (array[i]-min+1)/ind;
        if(index >= bucket_num)
            index = bucket_num-1;
        addToBucket((bucket[index]), array[i]);
    }
    BucketNode<Tp> *ptr = NULL;
    for(int i=0; i<bucket_num; i++)
    {
        ptr = bucket[i]->next;
        while(ptr)
        {
            cout<<ptr->value<<",";
            ptr = ptr->next;
        }
    }
}

int main()
{
    //int array[] = {1,3,2,0};
    int array[] = {1,3,2,0,6,9,7,3,2};
    //bubble(array, 9);
    //select(array, 9);
    //insert(array, 9);
    //quicksort(array, 0, 8);
    //mergesort(array, 9);
    //heapSort(array, 9);
    dump(array, 9);
    bucketSort(array, 9);
    return 0;
}
