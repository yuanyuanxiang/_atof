#include "_atof.h"
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#ifdef _DEBUG
// 随机数个数
#define NUMS 100
// 循环次数
#define TIMES 100
#else
#define NUMS 10000
#define TIMES 10000
#endif

typedef char str20[20];

int main()
{
	assert(NUMS <= 1e8);
	srand(time(NULL));
	// 生成随机浮点数
	str20 p[NUMS];
	for (int i = 0; i < NUMS; ++i)
	{
		double d = rand() / (double)(RAND_MAX + 1);
		sprintf_s(p[i], "%.17f", d);
	}
	double _s[NUMS] = {0}, s[NUMS] = {0};
	// _atof
	clock_t t = clock();
	for (int n = 0; n < TIMES; ++n)
	{
		for (int i = 0; i < NUMS; ++i)
			_s[i] = _atof(p[i]);
	}
	int tm1 = t = clock() - t;
	printf("_atof using time: %dms\n", t);
	// atof
	t = clock();
	for (int n = 0; n < TIMES; ++n)
	{
		for (int i = 0; i < NUMS; ++i)
			s[i] = atof(p[i]);
	}
	int tm2 = t = clock() - t;
	printf("atof using time: %dms\n", t);

	// 比较差异
	for (int i = 0; i < NUMS; ++i)
	{
		if(1e-15 < _s[i] - s[i])
			printf("_atof[%d]= %.7f, atof[d]= %.7f\n", _s[i], s[i]);
	}
	printf("speed up: %f\n", 1.0 * tm2 / tm1);

	system("PAUSE");

	return 0;
}
