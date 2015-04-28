#ifndef define_h_
#define define_h_
#include<vector>
#include<set>

using namespace std;

#define MAX_Depth 120     //���ؿ������
#define AlphaBeta_Depth 3 // ��-��ģ�����
#define RANDTIME 100		   // ���ģ�����


#define PASS -1				// pass
#define INVALID 0 			//��Ч����
#define ROCKET 1			// ���
#define ZHADAN 2			// ը��
#define SINGLE 3			// ����
#define COUPLE 4			// ����
#define SANTIAO 5			// ����
#define THREE_ONE 6			// ������
#define THREE_TWO 7			// ����˫
#define SINGLEJUNKO 8		// ��˳
#define DUALJUNKO 9			// ˫˳
#define THREEJUNKO 10		// ��˳
#define THREEJUNKO_ONE 11   // ��˳����
#define THREEJUNKO_TWO 12   // ��˳��˫
#define FOUR_TWO 13         // �Ĵ���
#define FOUR_TWO_COUPLE 14  // �Ĵ�����

#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}//������鳤��

#define STATUS_MAX 1		//  ��ʤ��
#define STATUS_LARGE 2	//  ����
#define STATUS_MID 3		//  �е���
#define STATUS_SMALL 4   //  С��

// ���ÿ��߲�
#define NULL_MOVE(move) \
{ \
	vector<unsigned> list;\
	move.cards=list;\
	move.cardsType=-1;\
	move.score=0;\
}





typedef vector<unsigned> VECTORINT;

typedef struct _cardsmoves
{
	vector<unsigned> cards;
	int cardsType;
	int status;	  // ״̬
	int outWay;// ���Ʒ�ʽ
	int score;
}CARDSMOVE;//�߲�

typedef struct _comb
{
	vector<CARDSMOVE> moves;//һ���߲�
	int score;
}Comb;

typedef vector<Comb> CombsLib;


typedef struct _card
{
	int meihua;		 //  ÷��
	int fangkuai;	 //  ����
	int hongtao;	 //  ����
	int heitao;      //  ����
	int num;		 //  �Ƶ�����
	int value;		 //  ����ֵ
}CARD;

typedef struct _wang
{
	int small; // С��
	int big; // ����
	int num;//  �Ƶ�����
	int value;// ����ֵ
}WANG;

typedef struct _cardsInfo
{
	CARD a; // 3
	CARD b; // 4
	CARD c; // 5
	CARD d; // 6
	CARD e; // 7
	CARD f; // 8
	CARD g; // 9
	CARD h; // 10
	CARD i; // J
	CARD j; // Q
	CARD k; // K
	CARD l; // A
	CARD m; // 2
	WANG n; // ��
}CardsInfo;

#endif //define_h_