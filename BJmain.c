#include "BJfunc.h"
// ע�ͱ�׼������������������ע�ͣ���Ҫ������ڲ����ע��

int main()
{

	srand((unsigned)time(NULL)); // �������

	char PLcard[6] = {'0'}; // ��ʼ����ҵ�����//����ֱ��malloc
	char PCcard[6] = {'0'}; // ��ʼ��pc������//ͬ��
	// û�ã�����������ָ��
	char *plc = PLcard;
	char *pcc = PCcard;

	// �����Ʊ��ָ��
	// PCCARD nodePC;
	// PCCARD* headPC = &nodePC;
	// headPC->NODE = NULL;
	// ����ű��ָ��
	// PLCARD nodePL;
	// PLCARD* headPL = &nodePL;
	// headPL->NODE = NULL;

	Title();
	printf("\n��Ӯ������%c\n", PLcard[6]);
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

// ����
void Title()
{
	printf("\tBlack Jack\n");
	printf("�淨���ܣ�https://baike.baidu.com/item/21��\n");
	printf("1.��ʼ����\n");
	printf("q.�뿪\n");
}

// ��ʼ����
void Card(char *plc, char *pcc)
{

	double mu = 18.0;	// ��ֵ
	double sigma = 3.0; // ��׼��

	// ����ľ�����
	char card[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'K', 'Q', 'J'}; // �Ƶ����//����13���ռ䣬����ֻ��12����Ч�ַ�
	int sumPC = 0;																  // ���Ե���
	int sumPL = 0;																  // ��ҵ���

	// pc��ʼ��i��
	printf("\n�Է����ƣ�");
	// int i = rand() % 3 + 2;		//i�ķ�Χ��2-5
	int i = 0;					  // ��ʼi
	int point = Randn(mu, sigma); // ���һ������
	int Sum = 0;
	while (1)
	{

		int randomIndex = rand() % (sizeof(card) - 1); // �������card����1��ȥ��\0
		char randomPC = card[randomIndex];
		if ((point - sumPC) <= 10)
		{
			Sum = Char(randomPC, sumPC);
			if (Sum > 10)
			{ // �жϿ��ĵ����Ƿ���
				while (1)
				{
					randomIndex = rand() % (sizeof(card) - 1);
					randomPC = card[randomIndex];
					Sum = Char(randomPC, sumPC);
					if (Sum <= (point - sumPC))
					{
						break;
					}
				} // ������10ʱ����һֱѭ���飬ֱ��С��10
			}
		}
		pcc[i] = randomPC;
		if (i > 0)
		{
			printf("\t��");
		}
		else
		{
			printf("\t%c", randomPC);
		}
		i++;
		Sum = Char(randomPC, sumPC); // ת��Ϊ����
		sumPC += Sum;

		if ((point - sumPC) <= 0 || i == 5)
		{ // ��������ľ�ʱ��ֹͣ
			break;
		}

		//	i--;
	}
	// printf("������%d\n", sumPC);
	printf("\n");

	// player��ʼ��2��
	printf("  ����ƣ�");
	int j = 0;
	while (j < 2)
	{

		int randomIndex = rand() % (sizeof(card) - 1); // �������card����1��ȥ��\0
		char randomPL = card[randomIndex];
		// PLcard[j-1]= card[randomIndex];		//����ҵ��ƴ浽���������
		plc[j] = randomPL;
		j++;
		printf("\t%c", randomPL);
		randomPL = Char(randomPL, sumPL);
		sumPL += randomPL;
	}
	printf("\n  ������%d\n", sumPL);
}

// �Ƿ����
void pcChoose(char *plc, char *pcc)
{
	if (plc[4] != '\0')
	{
		printf("������n��\n");
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
		printf("�ٳ�һ���ƣ�y/n��\n");
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

// ������ĳ���
void pcNext(char *plc)
{
	char card[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'K', 'Q', 'J'}; // ��������
	int i = 0;
	// �ҵ����һ���ƣ�������strlen
	while (plc[i] != '\0')
	{
		i++;
	}
	int randomIndex = rand() % (sizeof(card) - 1); // �������card����1��ȥ��\0
	char randomPL = card[randomIndex];
	plc[i] = randomPL; // ����
}

// ��ʾ˫������
void Print(char *plc, char *pcc)
{
	int i = 0;
	int j = 0;
	int sum = 0;
	printf("\n�Է����ƣ�");
	while (pcc[i] != '\0')
	{
		if (i > 0)
		{
			printf("\t��"); // ���Ե�һ���ƺ󣬽�����ʾ
		}
		else
		{
			printf("\t%c", pcc[0]);
		}
		i++;
	}
	printf("\n  ����ƣ�");
	while (plc[j] != '\0')
	{
		printf("\t%c", plc[j]);
		j++;
	}
	sum = Calculate(plc);
	printf("\n  ������%d\n", sum);
	pcChoose(plc, pcc); // �ٴ�ת��ѯ���Ƿ��ȡ
}

// ����
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

// ����
void Judge(char *plc, char *pcc)
{
	int i = 0, j = 0;
	int pcSum = Calculate(pcc);
	int plSum = Calculate(plc);
	printf("\n�Է����ƣ�");
	while (pcc[i] != '\0')
	{
		printf("\t%c", pcc[i]);
		i++;
	}
	printf("\n  ����ƣ�");
	while (plc[j] != '\0')
	{
		printf("\t%c", plc[j]);
		j++;
	}
	printf("\n\tׯ�ҵ�����%d\n", pcSum);
	printf("\t��ĵ�����%d\n", plSum);

	JudgePoint(pcSum, plSum);

	printf("\n�밴���������");
	char again = _getch();
	switch (again)
	{
	default:
		system("cls");
		main();
		break;
	}
}

// ��ֵ�Ƚ�
void JudgePoint(int pcSum, int plSum)
{
	int com = plSum - pcSum; // ���߷ֲ�
	
	if (com > 0)
	{
		printf("��Ӯ�ˣ�\n");
	}
	else if (com < 0)
	{
		printf("�����ˣ�\n");
	}
	else
	{
		printf("ƽ�֣�\n");
	}
}

// �ַ�ת��
int Char(char random, int sum)
{
	// �˴�aû�����壬ɾ��

	switch (random)
	{
		// ��ע�⣬�����case 81��case 75���ظ��ģ����Ժϲ�
		// ͬʱ���Ƹ���룬ʹ���������
	case 'J':
		// ����ֱ��ʹ���ַ�������Ҫʹ��ASCII��
	case 'Q':
		// ����break������case�ϲ�
	case 'K':
		return 10;
		break;
	case 'A'://ԭ������
		int a = A(random, sum);
		return a;
		break;
	default:
		random -= 48;
		return random;
		break;
	}
}

// �ж�A
int A(char random, char sum)
{
	// �������淶�����Ը�ΪisA
	// ���£�����ֱ�ӷ��ر��ʽ 
	return (sum + 11) > 21 ? 1 : 11;
	//��Ԫ�����
}

// ��̬�ֲ�,ΪʲôҪ�����������
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
	int re = trunc(mu + sigma * U1 * Z); // С��ȡ��
	return re;
}
