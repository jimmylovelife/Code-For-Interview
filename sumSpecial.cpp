/**
 * 求 1+2+...+n
 * 要求不能使用乘除法、for、while、if、else、switch、case等关键字以及条件判断语句（A?B:C）
 */

#include <stdio.h>

//解法一： 不用循环用递归解决
//巧妙处在于递归结束条件不用判断语句

int sum(int end) {
	int s=0;
	(end) && (s=sum(end-1));
	return s+end;	
}

//解法二利用类的构造函数来解决
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
