#include "Eveluation.h"
#include "time.h"
#include "DDZMoveManager.h"

CEveluation::CEveluation() 
{

}

CEveluation::~CEveluation() 
{

}

/**
*   初始化玩家隶属度表
*/
void CEveluation::initMembership()
{
	for(size_t i=0;i<54;i++)  //初始化玩家p1隶属度表
	{
		Player::p1_Membership[i]=0.5;
	}

	for(size_t i=0;i<54;i++)  //初始化玩家p2隶属度表
	{
		Player::p2_Membership[i]=0.5;
	}
}


/**
* 根据我方手中牌将玩家p1、p2隶属度表更新
*/
void CEveluation::ClearedByDealCards()
{
	for(size_t i=0;i<Player::p3_cardsList.size();i++)
	{
		int value = Player::p3_cardsList[i];
		Player::p1_Membership[value]=0;
		Player::p2_Membership[value]=0;
	}
}
/**
* 根据3张底牌将玩家p1、p2隶属度表更新
* @leftCards 3张底牌
*/
void CEveluation::ClearedByLeftCards(vector<unsigned> leftCards)
{
	if(Player::p3_IsLandlord)    // 我方抓牌
	{
		for(size_t i=0;i<leftCards.size();i++)
		{
			Player::p1_Membership[leftCards.at(i)]=0;//抓牌隶属度清零
			Player::p2_Membership[leftCards.at(i)]=0;//抓牌隶属度清零
		}
	}
	else if(Player::p2_IsLandlord)// 玩家p2抓牌
	{
		for(size_t i=0;i<leftCards.size();i++)
		{
			Player::p1_Membership[leftCards.at(i)]=0;//抓牌隶属度清零
			Player::p2_Membership[leftCards.at(i)]=1;//抓牌隶属度为1.0
		}
	}
	else					// 玩家p1抓牌
	{
		for(size_t i=0;i<leftCards.size();i++)
		{
			Player::p1_Membership[leftCards.at(i)]=1;//抓牌隶属度为1.0
			Player::p2_Membership[leftCards.at(i)]=0;//抓牌隶属度清零
		}
	}
}

/**
*  玩家出牌，将隶属度表更新
* @playerCards 出牌
*/
void CEveluation::ClearedByPlayCards(vector<unsigned> playCards)
{

	for(size_t i=0;i<playCards.size();i++)
	{
		Player::p1_Membership[playCards.at(i)]=0;
		Player::p2_Membership[playCards.at(i)]=0;
	}
}

/**
*  更新剩余牌型表
*  @list 已出的牌
*/
void CEveluation::RefreshRemaining(vector<unsigned> list)
{
	for(size_t i=0;i<list.size();i++)
	{
		if(list[i]==53)
		{
			if(Player::remaining[14]!=0)
			{
				Player::remaining[14]--;// 大王特殊处理
			}
		}
		else
		{
			if(Player::remaining[list.at(i)/4]!=0)
			{
				Player::remaining[list.at(i)/4]--;
			}
		}
	}
}
/**
*  根据走步猜测其他牌隶属度，还需更改
*  @whoseGo 轮到谁走步  @cardsType 出牌类型  @playCards 出牌
*/
void CEveluation::UpdateByPlayCards(int whoseGo,int cardsType,vector<unsigned> playCards)
{
	DDZPlayer *play = new DDZPlayer();
	
	switch(cardsType)
	{
	case ROCKET:
		break;
	case ZHADAN:
		break;
	case SINGLE:
		{
			unsigned singleValue = playCards.at(0);
			if (singleValue == X)
			{
				if (whoseGo == 1)
				{
					if (Player::p1_Membership[D] != 0)
					{
						Player::p1_Membership[D]-=0.1;
					}
					if (Player::p2_Membership[D] != 0)
					{
						Player::p2_Membership[D]+=0.1;
					}
				}
				else if (whoseGo == 2)
				{
					if (Player::p1_Membership[D] != 0)
					{
						Player::p1_Membership[D] += 0.1;
					}
					if (Player::p2_Membership[D] != 0)
					{
						Player::p2_Membership[D] -= 0.1;
					}
				}
			}
			else if (singleValue == D)
			{
				if (whoseGo == 1)
				{
					if (Player::p1_Membership[X] != 0)
					{
						Player::p1_Membership[X] -= 0.1;
					}
					if (Player::p2_Membership[X] != 0)
					{
						Player::p2_Membership[X] += 0.1;
					}
				}
				else if (whoseGo == 2)
				{
					if (Player::p1_Membership[X] != 0)
					{
						Player::p1_Membership[X] += 0.1;
					}
					if (Player::p2_Membership[X] != 0)
					{
						Player::p2_Membership[X] -= 0.1;
					}
				}
			}
			else
			{
				for (size_t i = 4 * singleValue; i<4 * singleValue + 4; i++)
				{
					if (whoseGo == 1)
					{
						if (Player::p1_Membership[i] != 0)
						{
							Player::p1_Membership[i] -= 0.1;
						}

						if (Player::p2_Membership[i] != 0)
						{
							Player::p2_Membership[i] += 0.1;
						}

					}
					else if (whoseGo == 2)
					{
						if (Player::p1_Membership[i] != 0)
						{
							Player::p1_Membership[i] += 0.1;
						}

						if (Player::p2_Membership[i] != 0)
						{
							Player::p2_Membership[i] -= 0.1;
						}
					}
				}
			}
			
			break;
		}
	case COUPLE:
		{
			unsigned coupleValue = playCards.at(0);
			for (size_t i = 4 * coupleValue; i<4 * coupleValue + 4; i++)
			{
				if(whoseGo==1)
				{
					if(Player::p1_Membership[i]!=0)
					{
						Player::p1_Membership[i] -= 0.1;
					}

					if(Player::p2_Membership[i]!=0)
					{
						Player::p2_Membership[i] += 0.1;
					}

				}
				else if(whoseGo==2)
				{
					if(Player::p1_Membership[i]!=0)
					{
						Player::p1_Membership[i] += 0.1;
					}

					if(Player::p2_Membership[i]!=0)
					{
						Player::p2_Membership[i] -= 0.1;
					}
				}
			}
			break;
		}
	case SANTIAO:
		{	
			unsigned SanTiaoValue = playCards.at(0);
			for (size_t i = 4 * SanTiaoValue; i<4 * SanTiaoValue + 4; i++)
			{
				if(whoseGo==1)
				{
					if(Player::p1_Membership[i]!=0)
					{
						Player::p1_Membership[i]=0;
					}

					if(Player::p2_Membership[i]!=0)
					{
						Player::p2_Membership[i]=1;
					}

				}
				else if(whoseGo==2)
				{
					if(Player::p1_Membership[i]!=0)
					{
						Player::p1_Membership[i]=1;
					}

					if(Player::p2_Membership[i]!=0)
					{
						Player::p2_Membership[i]=0;
					}
				}
			}
		break;
		}
	case THREE_ONE:
		{

			vector<unsigned> Three_OneInfo = play->getThree_OneValue(playCards);

			unsigned SanTiaoValue = Three_OneInfo.at(0);//三带一 三条牌面值
			unsigned SanTiao_One = Three_OneInfo.at(2);//三带一 带牌牌面值

			for (size_t i = 4 * SanTiaoValue; i<4 * SanTiaoValue + 4; i++)
			{
				if(whoseGo==1)// 玩家一方打出三带一，若我方手中无三条剩余的一张，则另一张几乎在另一玩家手中
				{
					if(Player::p1_Membership[i]!=0)
					{
						Player::p1_Membership[i]=0;
					}

					if(Player::p2_Membership[i]!=0)
					{
						Player::p2_Membership[i]=1;
					}

				}
				else if(whoseGo==2)
				{
					if(Player::p1_Membership[i]!=0)
					{
						Player::p1_Membership[i]=1;
					}

					if(Player::p2_Membership[i]!=0)
					{
						Player::p2_Membership[i]=0;
					}
				}
			}

			for (size_t i = 4 * SanTiao_One; i<4 * SanTiao_One + 4; i++)
			{
				if(whoseGo==1)// 更改带牌隶属度
				{
					if(Player::p1_Membership[i]!=0)
					{
						Player::p1_Membership[i] -= 0.1;
					}

					if(Player::p2_Membership[i]!=0)
					{
						Player::p2_Membership[i] += 0.1;
					}

				}
				else if(whoseGo==2)
				{
					if(Player::p1_Membership[i]!=0)
					{
						Player::p1_Membership[i] += 0.1;
					}

					if(Player::p2_Membership[i]!=0)
					{
						Player::p2_Membership[i] -= 0.1;
					}
				}
			}
		break;
		}
	case THREE_TWO:
		{
			vector<unsigned> Three_TwoInfo = play->getThree_TwoValue(playCards);

			unsigned SanTiaoValue = Three_TwoInfo.at(0);//三带一 三条牌面值
			unsigned SanTiao_Two = Three_TwoInfo.at(2);//三带一 对牌牌面值

			for (size_t i = 4 * SanTiaoValue; i<4 * SanTiaoValue + 4; i++)
			{
				if(whoseGo==1)// 玩家一方打出三带一，若我方手中无三条剩余的一张，则另一张几乎在另一玩家手中
				{
					if(Player::p1_Membership[i]!=0)
					{
						Player::p1_Membership[i]=0;
					}

					if(Player::p2_Membership[i]!=0)
					{
						Player::p2_Membership[i]=1;
					}

				}
				else if(whoseGo==2)
				{
					if(Player::p1_Membership[i]!=0)
					{
						Player::p1_Membership[i]=1;
					}

					if(Player::p2_Membership[i]!=0)
					{
						Player::p2_Membership[i]=0;
					}
				}
			}

			for (size_t i = 4 * SanTiao_Two; i<4 * SanTiao_Two + 4; i++)
			{
				if(whoseGo==1)// 更改带牌隶属度
				{
					if(Player::p1_Membership[i]!=0)
					{
						Player::p1_Membership[i] -= 0.1;
					}

					if(Player::p2_Membership[i]!=0)
					{
						Player::p2_Membership[i] += 0.1;
					}

				}
				else if(whoseGo==2)
				{
					if(Player::p1_Membership[i]!=0)
					{
						Player::p1_Membership[i] += 0.1;
					}

					if(Player::p2_Membership[i]!=0)
					{
						Player::p2_Membership[i] -= 0.1;
					}
				}
			}
		break;
		}
	case SINGLEJUNKO:
		{
			vector<unsigned> singleJunkoInfo = play->getSingleJunkoValue(playCards);

			unsigned startJunkoValue = singleJunkoInfo.at(0);
			unsigned endJunkoValue = singleJunkoInfo.at(1);

			for(size_t k=startJunkoValue;k<=endJunkoValue;k++)
			{
				for (size_t i = 4 * k; i<4 * k + 4; i++)
				{
					if(whoseGo==1)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i] -= 0.1;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i] += 0.1;
						}

					}
					else if(whoseGo==2)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i] += 0.1;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i] -= 0.1;
						}
					}
				}
			}
		
		break;
		}
	case DUALJUNKO:
		{
			vector<unsigned> DualJunkoInfo = play->getDualJunkoValue(playCards);

			unsigned startJunkoValue = DualJunkoInfo.at(0);
			unsigned endJunkoValue = DualJunkoInfo.at(1);

			for(size_t k=startJunkoValue;k<=endJunkoValue;k++)
			{
				for (size_t i = 4 * k; i<4 * k + 4; i++)
				{
					if(whoseGo==1)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i] -= 0.1;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i] += 0.1;
						}

					}
					else if(whoseGo==2)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i] += 0.1;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i] -= 0.1;
						}
					}
				}
			}
		
		break;
		}
	case THREEJUNKO:
		{
			vector<unsigned> ThreeJunkoInfo = play->getThree_ShunValue(playCards);

			unsigned startJunkoValue = ThreeJunkoInfo.at(0);
			unsigned endJunkoValue = ThreeJunkoInfo.at(1);

			for(size_t k=startJunkoValue;k<=endJunkoValue;k++)
			{
				for (size_t i = 4 * k; i<4 * k + 4; i++)
				{
					if(whoseGo==1)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i]=0;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i]=1;
						}

					}
					else if(whoseGo==2)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i]=1;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i]=0;
						}
					}
				}
			}
		
		break;
		}
	case THREEJUNKO_ONE:
		{
			vector<unsigned> ThreeJunko_OneInfo = play->getThree_OneValue(playCards);

			unsigned startJunkoValue = ThreeJunko_OneInfo.at(0);
			unsigned endJunkoValue = ThreeJunko_OneInfo.at(1);

			for(size_t k=startJunkoValue;k<=endJunkoValue;k++)
			{
				for (size_t i = 4 * k; i<4 * k + 4; i++)
				{
					if(whoseGo==1)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i]=0;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i]=1;
						}

					}
					else if(whoseGo==2)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i]=1;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i]=0;
						}
					}
				}
			}

			for(size_t k=2;k<ThreeJunko_OneInfo.size();k++)
			{
				for (size_t i = 4 * (ThreeJunko_OneInfo.at(k)); 
					i<4 * (ThreeJunko_OneInfo.at(k)) + 4; i++)
				{
					if(whoseGo==1)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i] -= 0.1;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i] += 0.1;
						}

					}
					else if(whoseGo==2)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i] += 0.1;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i] -= 0.1;
						}
					}
				}
			}
		
		break;
		}
	case THREEJUNKO_TWO:
		{
			vector<unsigned> ThreeJunko_TwoInfo = play->getThree_TwoValue(playCards);

			unsigned startJunkoValue = ThreeJunko_TwoInfo.at(0);
			unsigned endJunkoValue = ThreeJunko_TwoInfo.at(1);

			for(size_t k=startJunkoValue;k<=endJunkoValue;k++)
			{
				for (size_t i = 4 * k; i<4 * k + 4; i++)
				{
					if(whoseGo==1)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i]=0;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i]=1;
						}

					}
					else if(whoseGo==2)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i]=1;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i]=0;
						}
					}
				}
			}

			for(size_t k=2;k<ThreeJunko_TwoInfo.size();k++)// 带牌信息更新
			{
				for (size_t i = 4 * (ThreeJunko_TwoInfo.at(k)); 
					i<4 * (ThreeJunko_TwoInfo.at(k)) + 4; i++)
				{
					if(whoseGo==1)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i]=0;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i]=1;
						}

					}
					else if(whoseGo==2)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i]=1;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i]=0;
						}
					}
				}
			}
		
		break;
		}
	case FOUR_TWO:
		{
			vector<unsigned> four_TwoInfo = play->getFour_TwoValue(playCards);

			for(size_t k=1;k<four_TwoInfo.size();k++)// 带牌信息更新
			{
				for (size_t i = 4 * (four_TwoInfo.at(k)); i<4 * (four_TwoInfo.at(k)) + 4; i++)
				{
					if(whoseGo==1)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i] -= 0.1;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i] += 0.1;
						}

					}
					else if(whoseGo==2)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i] += 0.1;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i] -= 0.1;
						}
					}
				}
			}


			break;
		}
	case FOUR_TWO_COUPLE:
		{
		vector<unsigned> four_TwoCoupleInfo = play->getFour_TwoCoupleValue(playCards);

			for(size_t k=1;k<four_TwoCoupleInfo.size();k++)// 带牌信息更新
			{
				for (size_t i = 4 * (four_TwoCoupleInfo.at(k)); 
					i<4 * (four_TwoCoupleInfo.at(k)) + 4; i++)
				{
					if(whoseGo==1)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i] -= 0.1;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i] += 0.1;
						}

					}
					else if(whoseGo==2)
					{
						if(Player::p1_Membership[i]!=0)
						{
							Player::p1_Membership[i] += 0.1;
						}

						if(Player::p2_Membership[i]!=0)
						{
							Player::p2_Membership[i] -= 0.1;
						}
					}
				}
			}
		break;
		}
	}


	delete(play);
	play = NULL;
}

void CEveluation::UpdateFewCards(int whoseGo)
{
	int cardsType=Player::lastMove.cardsType;
	if(whoseGo!=1||whoseGo!=2||whoseGo!=3)
	{
		return ;
	}
	else if(whoseGo==1)
	{
		Player::p1_fewCards[cardsType]=1;
	}
	else if(whoseGo==2)
	{
		Player::p2_fewCards[cardsType]=1;
	}
}

void CEveluation::UpdateManyCards(int whoseGo)
{
	int cardsType=Player::firstMove.cardsType;
	if(whoseGo!=1||whoseGo!=2||whoseGo!=3)
	{
		return ;
	}
	else if(whoseGo==1&&Player::firstPlayer==1)
	{
		Player::p1_manyCards[cardsType]=1;
	}
	else if(whoseGo==2&&Player::firstPlayer==2)
	{
		Player::p2_manyCards[cardsType]=1;
	}
}

/**
*   蒙特卡罗随机
*   斗地主悲观模拟菜单
*   根据剩余棋子表和斗地主隶属度表产生一个玩家的模拟持有牌，则剩余棋子即为另一玩家
*   备注：这里玩家模拟方选择也可随机。。
*/
void CEveluation::NegativeSimulatedMenu()
{
	srand(time(NULL));

	//初始化玩家1、2牌面，全清零进行模拟
	init_p1_p2_EachCardNum();


	int whoseRand=rand()%10;

	double tmp_Membership[54];
	int cardsNum=0;   // 随机菜单需要产生的随机牌张数???

	if(whoseRand<5) // 随机数为0-4，随机生成玩家1模拟牌面
	{
		memcpy(tmp_Membership,Player::p1_Membership,sizeof(tmp_Membership));
		cardsNum = Player::p1_cardsNum;

		while(cardsNum)// 直到随机完玩家手中牌，循环结束
		{
			for(size_t i=0;i<54;i++) // 牌面随机模拟正式开始
			{
				double randNum = (double)(rand()%100)/100.00;// 产生一个0.00->1.00的随机数
				int value = getValue(i);
				
				if (randNum < tmp_Membership[value] && cardsNum != 0
					&& Player::p1_EachCardNum[value] < Player::remaining[value])
				{
					Player::p1_EachCardNum[value]++;
					cardsNum--;
				}
				
			}
		}

		for(size_t i=0;i<15;i++)
		{
			Player::p2_EachCardNum[i] = Player::remaining[i] - Player::p1_EachCardNum[i];//根据玩家1的随机牌及牌型剩余表得到玩家2的牌
		}
	}
	else			// 随机数为5-9，随机生成玩家2模拟牌面
	{
		memcpy(tmp_Membership, Player::p2_Membership, sizeof(tmp_Membership));
		cardsNum = Player::p2_cardsNum;

		while(cardsNum)
		{
			for(size_t i=0;i<54;i++) // 牌面随机模拟正式开始
			{
				double randNum = (double)(rand()%100)/100.00;// 产生一个0.00->1.00的随机数
		
				int value = getValue(i);
				
				if (randNum < tmp_Membership[i] && cardsNum != 0
					&& Player::p2_EachCardNum[value] < Player::remaining[value])
				{
					Player::p2_EachCardNum[value]++;
					cardsNum--;
				}
			}
		}

		for(size_t i=0;i<15;i++)
		{
			Player::p1_EachCardNum[i] = Player::remaining[i] - Player::p2_EachCardNum[i];//根据玩家2的随机牌及牌型剩余表得到玩家1的牌
		}
	}	
}

/**
*	斗地主乐观模拟菜单
*	当玩家某张牌持有的概率大于0.5，
*   则认为一定存在于该玩家手中。
*	若小于或等于0.5，则需要模拟
*/
void CEveluation::PositiveSimulatedMenu()
{
	srand(time(NULL));
	
	//初始化玩家1、2牌面，全清零进行模拟
	init_p1_p2_EachCardNum(); 
	int p1_cardsNum = Player::p1_cardsNum;
	int p2_cardsNum = Player::p2_cardsNum;
	unsigned remaining[15]={ 0 };
	memcpy(remaining, Player::remaining, sizeof(Player::remaining));
	int randNum = 0;
	for (int i = 0; i < 54; i++)
	{
		int value = getValue(i);
		if (Player::p1_Membership[i] > 0.5 && p1_cardsNum > 0 && remaining[value]>0)
		{
			Player::p1_EachCardNum[value]++;
			p1_cardsNum--;
			remaining[value]--;
		}
		else if (Player::p1_Membership[i] < 0.5 && Player::p1_Membership[i] > 0 
				 && p2_cardsNum > 0 && remaining[value]>0)
		{
			Player::p2_EachCardNum[value]++;
			p2_cardsNum--;
			remaining[value]--;
		}
		else if (Player::p1_Membership[i] == 0.5)
		{
			randNum = rand() % 2;

			if (randNum)
			{
				if (p1_cardsNum && remaining[value]>0)
				{
					Player::p1_EachCardNum[value]++;
					p1_cardsNum--;
					remaining[value]--;
				}
				else if (p2_cardsNum && remaining[value]>0)
				{
					Player::p2_EachCardNum[value]++;
					p2_cardsNum--;
					remaining[value]--;
				}
				
			}
			else
			{
				if (p2_cardsNum && remaining[value]>0)
				{
					Player::p2_EachCardNum[value]++;
					p2_cardsNum--;
					remaining[value]--;
				}
				else if (p1_cardsNum && remaining[value]>0)
				{
					Player::p1_EachCardNum[value]++;
					p1_cardsNum--;
					remaining[value]--;
				}
			}
		}
	}

	if (p1_cardsNum)
	{
		for (size_t j = 0; j<15; j++)
		{
			if (remaining[j] > 0)
			{
				if (p1_cardsNum > remaining[j])
				{
					Player::p1_EachCardNum[j] += remaining[j];
					p1_cardsNum-= remaining[j];
					remaining[j]=0;
				}	
				else
				{
					Player::p1_EachCardNum[j] += p1_cardsNum;
					remaining[j]-=p1_cardsNum;
					p1_cardsNum = 0;
				}
			}
		}
	}

	if (p2_cardsNum)
	{
		for (size_t j = 0; j<15; j++)
		{
			Player::p2_EachCardNum[j] += remaining[j];//玩家2差的牌等于剩余牌
		}
	}

	//int p1_cardsNum = Player::p1_cardsNum;
	//int p2_cardsNum = Player::p2_cardsNum;
	//
	//unsigned remaining[15];
	//memcpy(remaining, Player::remaining, sizeof(remaining));
	//double gailv = 0.5;
	//for (int i = 0; i < 54; i++)
	//{
	//	if (Player::p1_Membership[i] > gailv)// 依次取概率大于0.5的作为玩家1手中牌
	//	{
	//		handleMoreThanHalf(i, &p1_cardsNum, remaining, 1);
	//	}
	//}
	//for (int i = 0; i < 54; i++)
	//{
	//	if (Player::p2_Membership[i] > gailv)// 依次取概率大于0.5的作为玩家2手中牌
	//	{
	//		handleMoreThanHalf(i, &p2_cardsNum, remaining, 2);
	//	}
	//}
	//while (p1_cardsNum && gailv > 0)
	//{
	//	gailv -= 0.1;
	//	for (int i = 0; i < 54; i++)
	//	{
	//		if (Player::p1_Membership[i] > gailv)// 依次取概率的大的作为玩家1手中牌
	//		{
	//			handleMoreThanHalf(i, &p1_cardsNum, remaining, 1);
	//		}
	//	}
	//	
	//}

	//gailv = 0.5;
	//while (p2_cardsNum && gailv > 0)
	//{
	//	gailv -= 0.1;
	//	for (int i = 0; i < 54; i++)
	//	{
	//		if (Player::p2_Membership[i] > gailv)// 依次取概率的大的作为玩家1手中牌
	//		{
	//			handleMoreThanHalf(i, &p2_cardsNum, remaining, 2);
	//		}
	//	}
	//	
	//}
	

	//int index = 0;
	//int count = 0;//只随机三轮，防止出现死循环
	//double randNum;
	//while (p1_cardsNum && count < 1)
	//{
	//	if (index > 53)
	//	{
	//		index = 0;
	//		count++;
	//		break;
	//	}
	//	if (Player::p1_Membership[index] > 0.5 || Player::p1_Membership[index]<=0)
	//	{
	//		index++;//大于0.5的已经被模拟，直接跳过,等于零不模拟
	//	}
	//	else
	//	{
	//		randNum = (double)(rand() % 100) / 100.00;
	//		handleNotMoreThanHalf(index, randNum, &p1_cardsNum, remaining, 1);
	//		index++;
	//	}
	//}

	//index = 0;
	//count = 0;//只随机三轮，防止出现死循环
	//while (p2_cardsNum && count < 1)
	//{
	//	if (index > 53)
	//	{
	//		index = 0;
	//		count++;
	//		break;
	//	}
	//	if (Player::p2_Membership[index] > 0.5 || Player::p2_Membership[index] <= 0)
	//	{
	//		index++;//大于0.5的已经被模拟，直接跳过,等于零不模拟
	//	}
	//	else
	//	{
	//		randNum = (double)(rand() % 100) / 100.00;
	//		handleNotMoreThanHalf(index, randNum, &p2_cardsNum, remaining, 1);
	//		index++;
	//	}
	//}
	//
	//if (p1_cardsNum)
	//{
	//	for (size_t j = 0; j<15; j++)
	//	{
	//		if (remaining[j] > 0)
	//		{
	//			if (p1_cardsNum > remaining[j])
	//			{
	//				Player::p1_EachCardNum[j] += remaining[j];
	//				p1_cardsNum-= remaining[j];
	//				remaining[j]=0;
	//			}	
	//			else
	//			{
	//				Player::p1_EachCardNum[j] += p1_cardsNum;
	//				remaining[j]-=p1_cardsNum;
	//				p1_cardsNum = 0;
	//			}
	//		}
	//	}
	//}

	//if (p2_cardsNum)
	//{
	//	for (size_t j = 0; j<15; j++)
	//	{
	//		Player::p2_EachCardNum[j] += remaining[j];//玩家2差的牌等于剩余牌
	//	}
	//}
	//
	
	
	//for (int i = 0; i < 54; i++)
	//{
	//	if (Player::p1_Membership[i] > 0.5)//当概率大于0.5，则确定持有该牌
	//	{
	//		handleMoreThanHalf(i, &p1_cardsNum, remaining, 1);
	//	}
	//}

	//for (int i = 0; i<54; i++)
	//{
	//	if (Player::p2_Membership[i]>0.5)
	//	{
	//		handleMoreThanHalf(i, &p2_cardsNum, remaining, 2);
	//	}
	//}

	//for (int i = 0; i<15; i++)
	//{
	//	Player::p1_EachCardAndRemaining[i] = remaining[i] + Player::p1_EachCardNum[i];
	//	Player::p2_EachCardAndRemaining[i] = remaining[i] + Player::p2_EachCardNum[i];
	//}
	//int index = 0;
	//while (p1_cardsNum)
	//{
	//	if (index > 53)
	//	{
	//		index = 0;
	//	}
	//	if (Player::p1_Membership[index] > 0.5 || Player::p1_Membership[index]<=0)
	//	{
	//		index++;//大于0.5的已经被模拟，直接跳过,等于零不模拟
	//	}
	//	else
	//	{
	//		double randNum = (double)(rand() % 100) / 100.00;
	//		handleNotMoreThanHalf(index, randNum, &p1_cardsNum, remaining, 1);
	//		index++;
	//	}
	//}

	//for (size_t j = 0; j<15; j++)
	//{
	//	Player::p2_EachCardNum[j] += remaining[j];//p2手中牌=模拟后剩余牌+本身已经确定的牌
	//}

}

/**
*	处理p1概率大于0.5的牌
*	@i 牌的下标
*   @cardsNum 玩家手中牌数量
*   @who  哪个玩家
*/
void CEveluation::handleMoreThanHalf(int i, int *cardsNum, unsigned *remaining, int who)
{
	int value = getValue(i);

	if (who == 1 && (*cardsNum) > 0 &&
		Player::p1_EachCardNum[value]<remaining[value])
	{
		Player::p1_EachCardNum[value]++;
		remaining[value]--;
		(*cardsNum)--;
	}
	else if (who == 2 && (*cardsNum)> 0 &&
			 Player::p2_EachCardNum[value] < remaining[value])
	{
		Player::p2_EachCardNum[value]++;
		remaining[value]--;
		(*cardsNum)--;
	}
}

/**
*	处理p1概率不超过0.5的牌
*   随机数不好控制，舍弃此方法模拟
*/
void CEveluation::handleNotMoreThanHalf(int i, double randNum, int *cardsNum, unsigned *remaining, int who)
{
	int value = getValue(i);
	if (who == 1 && Player::p1_EachCardNum[value] < remaining[value]
		&& randNum < Player::p1_Membership[i] && (*cardsNum)>0)
	{
		Player::p1_EachCardNum[value]++;
		remaining[value]--;
		(*cardsNum)--;
	}
	else if (who == 2 && Player::p2_EachCardNum[value] < remaining[value]
			 && randNum < Player::p2_Membership[i] && (*cardsNum) > 0)
	{
		Player::p2_EachCardNum[value]++;
		remaining[value]--;
		(*cardsNum)--;
	}
}

void CEveluation::handle1(int value, int *cardsNum, int who)
{
	if (who == 1 && (*cardsNum) > 0 &&
			Player::p1_EachCardNum[value]<Player::remaining[value])
	{
		Player::p1_EachCardNum[value]++;
		(*cardsNum)--;
	}
	else if (who == 2 && (*cardsNum )> 0 && 
				Player::p2_EachCardNum[value] < Player::remaining[value])
	{
		Player::p2_EachCardNum[value]++;
		(*cardsNum)--;
	}
}

void CEveluation::handle2(int value, int i, double randNum, int *cardsNum, unsigned *remaining, int who)
{
	if (Player::p1_EachCardNum[value] < Player::remaining[value]
		&& randNum < Player::p1_Membership[i])
	{
		Player::p1_EachCardNum[value]++;
		(*cardsNum)--;
	}
}



int CEveluation::getValue(int i)
{
	return i == 53 ? 14 : (i / 4);
}




void CEveluation::init_p1_p2_EachCardNum()
{
	for (int i = 0; i < 15; i++)
	{
		Player::p1_EachCardNum[i] = 0;
		Player::p2_EachCardNum[i] = 0;
	}
}



/*    AI Pass策略   */
int CEveluation::IsAiPass()
{
	if(Player::p2_IsLandlord)		 //  上家为地主
	{
		if(Player::lastPlayer==1)	 //  出牌者为下家
		{
			return 1;
		}
	}

	if(Player::p1_IsLandlord)
	{
		if(Player::p1_general.size()>0 && Player::p1_general[Player::p1_general.size()-1].cardsType==-1 
			&& Player::lastPlayer == 2 && Player::firstPlayer ==3)
		{
			return 1;
		}
	}

	return 0;
}

int CEveluation::GetCardsRightIfPass()
{
	int size = Player::cardsMoveRecords.size();

	if (Player::p1_IsLandlord)
	{
		if (Player::lastPlayer == 1)
			return -1;
		else
			return 0;
	
	}
	else if (Player::p2_IsLandlord)
	{
		if (Player::lastPlayer == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return -1;
	}
}

bool CEveluation::IsCurrentTeam(bool current_IsLandlord, int turn)
{
	if (current_IsLandlord)
	{
		return false;
	}
	else
	{
		if (turn == 1)
		{
			if (Player::p1_IsLandlord)
				return false;
			else
				return true;
		}
		else if (turn == 2)
		{
			if (Player::p2_IsLandlord)
				return false;
			else
				return true;
		}
		else if (turn == 0)
		{
			if (Player::p3_IsLandlord)
				return false;
			else
				return true;
		}
	}
}

/*
*	是否为此轮出牌发起者
*/
bool CEveluation::IsCardOriginator(int turn)
{
	return (Player::firstPlayer % 3) == turn ? true : false;
}

int CEveluation::EveluateMove(CARDSMOVE* move, int whoseGo)
{
	DDZPlayer *play = new DDZPlayer();
	int score=0;//估值
	int outWay = move->outWay;
	int cardsType = move->cardsType;
	vector<unsigned> current_cards = move->cards;
	int currentValue; // 当前走步牌面值
	int currentCardsNum, nextCardsNum, frontCardsNum; //当前玩家手中牌数量
	bool IsSplit = move->IsSplit;
	
	
	unsigned tmp_cards[15];
	unsigned next_cards[15];

	bool current_IsLandlord; // 当前是否为地主
	bool next_IsLandlord;     // 下家是否为地主
	bool front_IsLandLord;
	int turn = whoseGo % 3;


	if (cardsType != INVALID && cardsType != PASS)
	{
		currentValue = current_cards[0];
	}
	if(turn == 0)
	{
		memcpy(tmp_cards,Player::p3_EachCardNum,sizeof(tmp_cards));
		memcpy(next_cards,Player::p1_EachCardNum,sizeof(next_cards));

		currentCardsNum = Player::p3_cardsNum;
		current_IsLandlord=Player::p3_IsLandlord;
		next_IsLandlord=Player::p1_IsLandlord;
		front_IsLandLord=Player::p2_IsLandlord;

		nextCardsNum = Player::p1_cardsNum;
		frontCardsNum = Player::p2_cardsNum;
	}
	else if(turn == 2)
	{
		memcpy(tmp_cards,Player::p1_EachCardNum,sizeof(tmp_cards));
		memcpy(next_cards,Player::p2_EachCardNum,sizeof(next_cards));

		currentCardsNum = Player::p2_cardsNum;
		current_IsLandlord=Player::p1_IsLandlord;
		next_IsLandlord=Player::p2_IsLandlord;
		front_IsLandLord=Player::p3_IsLandlord;

		nextCardsNum = Player::p3_cardsNum;
		frontCardsNum = Player::p1_cardsNum;
	}
	else
	{
		memcpy(tmp_cards,Player::p2_EachCardNum,sizeof(tmp_cards));
		memcpy(next_cards,Player::p3_EachCardNum,sizeof(next_cards));

		currentCardsNum = Player::p1_cardsNum;
		current_IsLandlord=Player::p2_IsLandlord;
		next_IsLandlord=Player::p3_IsLandlord;
		front_IsLandLord=Player::p1_IsLandlord;

		nextCardsNum = Player::p2_cardsNum;
		frontCardsNum = Player::p3_cardsNum;
	}

	if (outWay)
	{
		if (currentValue >= Q)
		{
			score-=10000;
		}
	}

	if (IsSplit)
	{
		score-=200;//优先出非拆牌走步
	}
	
	if (currentCardsNum - current_cards.size() == 1)//打完剩下一张
	{
		score+=200;
	}

	if (currentCardsNum - current_cards.size() == 2)//打完剩下二张
	{
		score += 100;
	}
	if (((IsCardOriginator(turn) || (!current_IsLandlord && !next_IsLandlord)) && !outWay)
			&& cardsType != PASS)
	{
		score += (D - current_cards[0]) * 200;//自己主动出牌发起者，尽量走最小
	}
	else if (!IsCardOriginator(turn) && next_IsLandlord 
			&& cardsType != PASS && Player::firstPlayer == 1)//敌方主动出牌，且我方为顶家
	{
		switch (currentValue)//顶牌
		{
			case K: score += 50; break;
			case A: score += 40; break;	
			case Q: score += 30; break;
			case T: score += 20; break;
			case X: score += 10; break;
			case D: score += 5;  break;
		}
	}

	if (cardsType == SINGLEJUNKO || cardsType == DUALJUNKO || cardsType == THREEJUNKO
		|| cardsType == THREEJUNKO_ONE || cardsType == THREEJUNKO_TWO || cardsType == ZHADAN
		|| cardsType == FOUR_TWO || cardsType == FOUR_TWO_COUPLE)
	{
		if (IsCurrentTeam(current_IsLandlord, Player::lastPlayer))
			score-=1000;
	}
	else if (cardsType == SINGLE || cardsType == COUPLE || cardsType == SANTIAO
			 || cardsType == THREE_ONE || cardsType == THREE_TWO)
	{
		if (IsCurrentTeam(current_IsLandlord, Player::lastPlayer))
		{
			if (Player::lastMove.cardsType != INVALID)
			{
				int value = Player::lastMove.cards[0];
				if (value >= K)
				{
					score-=1000;//伙伴方出大牌我方不管
				}
			}
		}
	}

	
	if (currentCardsNum == current_cards.size())//非四带牌的能一手走完就走完
	{
		if (cardsType != FOUR_TWO || cardsType != FOUR_TWO_COUPLE)
		{
			score+=1000;
		}
	}

	

	switch (cardsType)
	{
		case PASS:
		{
				 int canGetRight = GetCardsRightIfPass();
				 if (canGetRight == 1)//pass获得牌权
				 {
					score+=100;
				 }
				 else if (canGetRight == -1)
				 {
					score-=100;
				 }


				 if (!IsCurrentTeam(current_IsLandlord, Player::lastPlayer))
				 {
					score-=500;
				 }
				 if (Player::p1_IsLandlord)
				 {
					 if (Player::p1_cardsNum == 1 || Player::p1_cardsNum == 2)
					 {
						 score -= 200;
					 }
					 else if (Player::p2_cardsNum == 1 || Player::p1_cardsNum == 2)
					 {
						 score += 200;
					 }
				 }
				 else  if (Player::p2_IsLandlord)
				 {
					 if (Player::p2_cardsNum == 1 || Player::p2_cardsNum == 2)
					 {
						 score -= 200;
					 }
					 else if (Player::p1_cardsNum == 1 || Player::p1_cardsNum == 2)
					 {
						 score += 200;
					 }
				 }
				 break;
			}
		case ROCKET:
		{
			score-=8000;
			break;
		}
		

		case ZHADAN:
		{
					score-=8000;
					
					break;
		}

		case SINGLE:
			{
					   if (outWay)
					   {
						   if (current_IsLandlord)
						   {
							   if (nextCardsNum == 1 || frontCardsNum == 1)
							   {
								   score -= 15000;
							   }
						   }
						   else
						   {
							   if (next_IsLandlord)
							   {
								   if (nextCardsNum == 1)
								   {
									   score -= 15000;
								   }
								   if (frontCardsNum == 1)
								   {
									   score += 500;
								   }
							   }
							   else
							   {
								   if (nextCardsNum == 1)
								   {
									   score += 500;
								   }
								   if (frontCardsNum == 1)
								   {
									   score -= 15000;
								   }
							   }
						   }
					   }
					 
					   if (turn == 0 && outWay)
					   {
						   score += (15 * (Player::OnHandCardsTypeNum[SINGLE]-1));
					   }
					   else
					   {
							score += 20;
					   }
					
			break;
		}

	case COUPLE:
		{
				   if (outWay)
				   {
					   if (current_IsLandlord)
					   {
						   if (nextCardsNum == 2 || frontCardsNum == 2)
						   {
							   score -= 15000;
						   }
					   }
					   else
					   {
						   if (next_IsLandlord)
						   {
							   if (nextCardsNum == 2)
							   {
								   score -= 15000;
							   }
							   if (frontCardsNum == 2)
							   {
								   score += 500;
							   }
						   }
						   else
						   {
							   if (nextCardsNum == 2)
							   {
								   score += 500;
							   }
							   if (frontCardsNum == 2)
							   {
								   score -= 15000;
							   }
						   }
					   }
				   }
				   
				   if (turn == 0 && outWay)
				   {
					   score += (10 * Player::OnHandCardsTypeNum[COUPLE]);
				   }
				   else
				   {
					   score += 10;
				   }
			break;
		}

	case SANTIAO:
		{
			int threeTiaoValue=play->getSanTiaoValue(current_cards);

		/*	if (currentValue == T && outWay)
			{
				score -= 10000;
			}*/

			if (turn == 0 && outWay)
			{
				score += (25 * (Player::OnHandCardsTypeNum[SANTIAO] - 1));
			}
			else
			{
				score += 25;
			}
			break;
		}

	case THREE_ONE:
		{
			vector<unsigned> cardsInfo = play->getThree_OneValue(current_cards);
			int threeTiaoValue=cardsInfo.at(0);

			if (turn == 0)
			{
				score += (30 * Player::OnHandCardsTypeNum[THREE_ONE]);
			}
			else
			{
				score += 30;
			}
			
			

			/*if (currentValue == T && outWay)
			{
				score -= 10000;
			}*/
		}
		break;

	case THREE_TWO:
		{
			vector<unsigned> cardsInfo = play->getThree_TwoValue(current_cards);
		
			int threeTiaoValue=cardsInfo.at(0);

		
			if (turn == 0)
			{
				score += (30 * Player::OnHandCardsTypeNum[THREE_TWO]);
			}
			else
			{
				score += 30;
			}
			
			

			/*if (currentValue == T && outWay)
			{
				score -= 10000;
			}*/
		}
		break;

	case SINGLEJUNKO:
		{
			vector<unsigned> cardsInfo = play->getSingleJunkoValue(current_cards);
			int startValue = cardsInfo.at(0);
			int endValue = cardsInfo.at(1);

			score += ((endValue - startValue + 1) * 200);//优先出长的单顺
		}
		break;

	case DUALJUNKO:
		{
			vector<unsigned> cardsInfo = play->getDualJunkoValue(current_cards);
			int startValue = cardsInfo.at(0);
			int endValue = cardsInfo.at(1);
			score += (endValue - startValue + 1) * 70;
		}
		break;

	case THREEJUNKO:
		{
			vector<unsigned> cardsInfo = play->getThree_ShunValue(current_cards);
			int startValue = cardsInfo.at(0);
			int endValue = cardsInfo.at(1);
			score += (endValue-startValue + 1)* 200;
		}
		break;

	case THREEJUNKO_ONE:
		{
			vector<unsigned> cardsInfo = play->getThree_OneValue(current_cards);
			int startValue = cardsInfo.at(0);
			int endValue = cardsInfo.at(1);
			int junkoNum = endValue-startValue+1;
			
			score += (endValue - startValue + 1) * 500;
		}
		break;

	case THREEJUNKO_TWO:
		{
			vector<unsigned> cardsInfo = play->getThree_TwoValue(current_cards);
			int startValue = cardsInfo.at(0);
			int endValue = cardsInfo.at(1);
			int junkoNum = endValue-startValue+1;
			 
			score += (endValue - startValue + 1) * 400;
		}
		break;

	case FOUR_TWO:
		{
			vector<unsigned> cardsInfo = play->getFour_TwoValue(current_cards);
			int FourValue = cardsInfo.at(0);

			score-=2000;
		}
		break;

	case FOUR_TWO_COUPLE:
		{
			vector<unsigned> cardsInfo = play->getFour_TwoCoupleValue(current_cards);
			int FourValue = cardsInfo.at(0);
			
			score-=2000;
		}
		break;
	}

	move->score=score;
	return score;
}

void CEveluation::EveluateMoves(vector<CARDSMOVE> *moves, int whoseGo)
{
	for (int i = moves->size() - 1; i >= 0; i--)
	{
		EveluateMove(&moves->at(i), whoseGo);
	}
}

/**
*	首攻
*/
CARDSMOVE CEveluation::firstAttack(vector<CARDSMOVE> moves)
{
	DDZMoveManager ddz_MM = DDZMoveManager();
	vector<CARDSMOVE> singles = ddz_MM.getType3Single(moves);
	vector<CARDSMOVE> couples = ddz_MM.getType4Couple(moves);
	vector<CARDSMOVE> santiaos = ddz_MM.getType5Santiao(moves);
	vector<CARDSMOVE> singleJunkos = ddz_MM.getType8SingleJunko(moves);
	CARDSMOVE m =CARDSMOVE();
	if (moves.size() > 0)
	{
		 m= moves[0];
	}
	else
	{
		NULL_MOVE(m);
	}

	if (singles.size() >= FA_Single)
	{
		return ddz_MM.getMinimumMove(singles, SINGLE);
	}

	if (couples.size() > FA_Couple)
	{
		return ddz_MM.getMinimumMove(couples, COUPLE);
	}

	if (santiaos.size() > FA_Santiao)
	{
		return ddz_MM.getMinimumMove(santiaos, SANTIAO);
	}

	if (singleJunkos.size() > 0)
	{
		return singleJunkos[0];
	}

	return m;
}