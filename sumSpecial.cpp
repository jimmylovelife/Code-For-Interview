/**
 * �� 1+2+...+n
 * Ҫ����ʹ�ó˳�����for��while��if��else��switch��case�ȹؼ����Լ������ж���䣨A?B:C��
 */

#include <stdio.h>

//�ⷨһ�� ����ѭ���õݹ���
//������ڵݹ�������������ж����

int sum(int end) {
	int s=0;
	(end) && (s=sum(end-1));
	return s+end;	
}

//�ⷨ��������Ĺ��캯�������
class SumSpe {
public:
	SumSpe() {
		++n;
		sum += n;
	}
	static int getSum() {
		return sum;
	}
private:
	static int n;
	static int sum;
};

int SumSpe::n = 0;
int SumSpe::sum = 0;
static int sumResult(const int n) {
	SumSpe *spe = new SumSpe[n];
	return SumSpe::getSum();
}
int main() {
	printf("digui %d\n", sum(100));
	printf("lei %d\n", sumResult(100));
	return 0;
}
