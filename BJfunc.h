#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<conio.h>
#include <math.h>

//#define Q 10;
//#define K 10;
//#define J 10;

//存取电脑牌的列表
typedef struct pcCard {
	int pcPoint;
	struct Node* NODE;
}PCCARD;

//存取玩家牌的列表
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