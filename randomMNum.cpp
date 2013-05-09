/**
 * 随机取M个数
 */
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

//解法-： 编程珠玑里的方法
//N个数理选族M个要保证每个数都是M/N的概率
//第一个选中的概率为M/N
//下面从生下的N-1个里选M-1个，每一个选中的概率 M-1/N-1
//如果第一个没选中， 则每一个的概率为M/N-1
//这样概率为 N/M * (N-1)/(M-1) + (1-N/M) * N/(M-1) = M/N
//下面这个解法有问题，就是当N比较小的时候有可能没选出M个就已经结束
void randomSelect(int m, int n) {
	srand(time(NULL));
	for(int i=0; i<n; i++) {
		if(rand()%(n-i) < m) {
			cout << i << endl;
			if (!(--m))
				break;
		}
	}
}

//解法二： 交换法
//含N个元素的数组 打算数组的顺序取前M个，然后输出即可
//
int array[100];
void swap(int ind1, int ind2) {
	int tmp = array[ind1];
	array[ind1] = array[ind2];
	array[ind2] = tmp;
}
void randomSwapSel(int m, int n) {
	srand(time(NULL));
	for (int j = 0; j<m; j++) {
		int k = rand()%n-j + j;
		swap(j, k);
	}
	for (int i=0; i<m; i++) {
		cout << array[i] <<endl;
	}
}
int main() {
	randomSelect(10,1000000000);
	for (int i=0; i<100; i++) {
		array[i] = i;
	}
	randomSwapSel(10, 100);	
	return 0;
}
