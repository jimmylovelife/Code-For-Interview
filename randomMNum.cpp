/**
 * ���ȡM����
 */
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

//�ⷨ-�� ���������ķ���
//N������ѡ��M��Ҫ��֤ÿ��������M/N�ĸ���
//��һ��ѡ�еĸ���ΪM/N
//��������µ�N-1����ѡM-1����ÿһ��ѡ�еĸ��� M-1/N-1
//�����һ��ûѡ�У� ��ÿһ���ĸ���ΪM/N-1
//��������Ϊ N/M * (N-1)/(M-1) + (1-N/M) * N/(M-1) = M/N
//��������ⷨ�����⣬���ǵ�N�Ƚ�С��ʱ���п���ûѡ��M�����Ѿ�����
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

//�ⷨ���� ������
//��N��Ԫ�ص����� ���������˳��ȡǰM����Ȼ���������
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
