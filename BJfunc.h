#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<conio.h>
#include <math.h>

//#define Q 10;
//#define K 10;
//#define J 10;

//��ȡ�����Ƶ��б�
typedef struct pcCard {
	int pcPoint;
	struct Node* NODE;
}PCCARD;

//��ȡ����Ƶ��б�
typedef struct plCard {
	int plPoint;
	struct Node* NODE;
}PLCARD;

void Title();
void Card(char* plc, char* pcc);
int A(char randomPC, char sumPC);
int Char(char random, int sum);
void pcChoose(char* plc, char* pcc);
void pcNext(char* plc);
double Randn(double mu, double sigma);
void Print(char* plc, char* pcc);
int Calculate(char* pcard);
void Judge(char* plc, char* pcc);
void JudgePoint(int pcSum, int plSum);