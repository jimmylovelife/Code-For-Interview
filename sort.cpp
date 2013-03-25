/**
implement sort algorithm
*/
#include <iostream>
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

//TODO Other sort algorithm
int main()
{
    //int array[] = {1,3,2,0};
    int array[] = {1,3,2,0,6,9,7,3,2};
    //bubble(array, 9);
    //select(array, 9);
    insert(array, 9);
    //quicksort(array, 0, 8);
    dump(array, 9);
    return 0;
}
