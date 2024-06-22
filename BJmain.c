#include "BJfunc.h"
// 注释标准：建议在语句上下添加注释，不要在语句内部添加注释

int main()
{

	srand((unsigned)time(NULL)); // 随机种子

	char PLcard[6] = {'0'}; // 初始化玩家的牌组//可以直接malloc
	char PCcard[6] = {'0'}; // 初始化pc的牌组//同上
	// 没用，数组名就是指针
	char *plc = PLcard;
	char *pcc = PCcard;

	// 电脑牌表的指针
	// PCCARD nodePC;
	// PCCARD* headPC = &nodePC;
	// headPC->NODE = NULL;
	// 玩家排表的指针
	// PLCARD nodePL;
	// PLCARD* headPL = &nodePL;
	// headPL->NODE = NULL;

	Title();
	printf("\n连赢局数：%c\n", PLcard[6]);
	char cho = _getch();
	switch (cho)
	{
	case '1':
		system("cls");
		Card(plc, pcc);
		pcChoose(plc, pcc);
		break;
	default:
		exit(1);
		break;
	}

	return 0;
}

// 标题
void Title()
{
	printf("\tBlack Jack\n");
	printf("玩法介绍：https://baike.baidu.com/item/21点\n");
	printf("1.开始游玩\n");
	printf("q.离开\n");
}

// 初始发牌
void Card(char *plc, char *pcc)
{

	double mu = 18.0;	// 均值
	double sigma = 3.0; // 标准差

	// 错误的决定。
	char card[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'K', 'Q', 'J'}; // 牌的面额//申请13个空间，但是只有12个有效字符
	int sumPC = 0;																  // 电脑点数
	int sumPL = 0;																  // 玩家点数

	// pc初始抽i张
	printf("\n对方的牌：");
	// int i = rand() % 3 + 2;		//i的范围是2-5
	int i = 0;					  // 初始i
	int point = Randn(mu, sigma); // 随机一个点数
	int Sum = 0;
	while (1)
	{

		int randomIndex = rand() % (sizeof(card) - 1); // 电脑随机card，减1是去掉\0
		char randomPC = card[randomIndex];
		if ((point - sumPC) <= 10)
		{
			Sum = Char(randomPC, sumPC);
			if (Sum > 10)
			{ // 判断卡的点数是否超了
				while (1)
				{
					randomIndex = rand() % (sizeof(card) - 1);
					randomPC = card[randomIndex];
					Sum = Char(randomPC, sumPC);
					if (Sum <= (point - sumPC))
					{
						break;
					}
				} // 当大于10时，就一直循环抽，直到小于10
			}
		}
		pcc[i] = randomPC;
		if (i > 0)
		{
			printf("\t？");
		}
		else
		{
			printf("\t%c", randomPC);
		}
		i++;
		Sum = Char(randomPC, sumPC); // 转化为数字
		sumPC += Sum;

		if ((point - sumPC) <= 0 || i == 5)
		{ // 随机点数耗尽时，停止
			break;
		}

		//	i--;
	}
	// printf("点数：%d\n", sumPC);
	printf("\n");

	// player初始抽2张
	printf("  你的牌：");
	int j = 0;
	while (j < 2)
	{

		int randomIndex = rand() % (sizeof(card) - 1); // 电脑随机card，减1是去掉\0
		char randomPL = card[randomIndex];
		// PLcard[j-1]= card[randomIndex];		//将玩家的牌存到玩家牌组中
		plc[j] = randomPL;
		j++;
		printf("\t%c", randomPL);
		randomPL = Char(randomPL, sumPL);
		sumPL += randomPL;
	}
	printf("\n  点数：%d\n", sumPL);
}

// 是否继续
void pcChoose(char *plc, char *pcc)
{
	if (plc[4] != '\0')
	{
		printf("结束（n）\n");
		char end = _getch();
		switch (end)
		{
		default:
			system("cls");
			Judge(plc, pcc);
			system("pause");
			break;
		}
	}
	else
	{
		printf("再抽一张牌（y/n）\n");
		char next = _getch();
		switch (next)
		{
		case 'y':
			system("cls");
			pcNext(plc);
			Print(plc, pcc);
			break;
		default:
			system("cls");
			Judge(plc, pcc);
			system("pause");
			break;
		}
	}
}

// 继续后的抽牌
void pcNext(char *plc)
{
	char card[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'K', 'Q', 'J'}; // 参照上文
	int i = 0;
	// 找到最后一张牌，可以用strlen
	while (plc[i] != '\0')
	{
		i++;
	}
	int randomIndex = rand() % (sizeof(card) - 1); // 电脑随机card，减1是去掉\0
	char randomPL = card[randomIndex];
	plc[i] = randomPL; // 存牌
}

// 显示双方的牌
void Print(char *plc, char *pcc)
{
	int i = 0;
	int j = 0;
	int sum = 0;
	printf("\n对方的牌：");
	while (pcc[i] != '\0')
	{
		if (i > 0)
		{
			printf("\t？"); // 电脑第一张牌后，将不显示
		}
		else
		{
			printf("\t%c", pcc[0]);
		}
		i++;
	}
	printf("\n  你的牌：");
	while (plc[j] != '\0')
	{
		printf("\t%c", plc[j]);
		j++;
	}
	sum = Calculate(plc);
	printf("\n  点数：%d\n", sum);
	pcChoose(plc, pcc); // 再次转回询问是否抽取
}

// 计算
int Calculate(char *pcard)
{
	int i = 0;
	int sum = 0;
	while (pcard[i] != '\0')
	{
		int temp = Char(pcard[i], sum);
		sum += temp;
		i++;
	}
	return sum;
}

// 评分
void Judge(char *plc, char *pcc)
{
	int i = 0, j = 0;
	int pcSum = Calculate(pcc);
	int plSum = Calculate(plc);
	printf("\n对方的牌：");
	while (pcc[i] != '\0')
	{
		printf("\t%c", pcc[i]);
		i++;
	}
	printf("\n  你的牌：");
	while (plc[j] != '\0')
	{
		printf("\t%c", plc[j]);
		j++;
	}
	printf("\n\t庄家点数：%d\n", pcSum);
	printf("\t你的点数：%d\n", plSum);

	JudgePoint(pcSum, plSum);

	printf("\n请按任意键继续");
	char again = _getch();
	switch (again)
	{
	default:
		system("cls");
		main();
		break;
	}
}

// 数值比较
void JudgePoint(int pcSum, int plSum)
{
	int com = plSum - pcSum; // 两者分差
	
	if (com > 0)
	{
		printf("你赢了！\n");
	}
	else if (com < 0)
	{
		printf("你输了！\n");
	}
	else
	{
		printf("平局！\n");
	}
}

// 字符转换
int Char(char random, int sum)
{
	// 此处a没有意义，删除

	switch (random)
	{
		// 请注意，这里的case 81和case 75是重复的，可以合并
		// 同时请推格代码，使其更加美观
	case 'J':
		// 可以直接使用字符，不需要使用ASCII码
	case 'Q':
		// 不加break，三个case合并
	case 'K':
		return 10;
		break;
	case 'A'://原文忘了
		int a = A(random, sum);
		return a;
		break;
	default:
		random -= 48;
		return random;
		break;
	}
}

// 判断A
int A(char random, char sum)
{
	// 起名不规范，可以改为isA
	// 啰嗦，可以直接返回表达式 
	return (sum + 11) > 21 ? 1 : 11;
	//三元运算符
}

// 正态分布,为什么要用这个函数？
double Randn(double mu, double sigma)
{
	double U1, U2, W, Z;

	do
	{
		U1 = -1.0 + 2.0 * (double)rand() / RAND_MAX;
		U2 = -1.0 + 2.0 * (double)rand() / RAND_MAX;
		W = U1 * U1 + U2 * U2;
	} while (W >= 1.0);

	Z = sqrt(-2.0 * log(W) / W);
	int re = trunc(mu + sigma * U1 * Z); // 小数取整
	return re;
}
