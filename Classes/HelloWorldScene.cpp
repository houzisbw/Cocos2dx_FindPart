#include "HelloWorldScene.h"
#include "WelcomeScene.h"
#include "ModeSelectScene.h"
#include "SimpleAudioEngine.h"
#include "OptionScene.h"
using namespace CocosDenshion;

USING_NS_CC;
int HelloWorld::bestCombo = 0;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

int HelloWorld::count = 0;
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//back to main menu
	auto backToMenu = MenuItemImage::create("back.png", "back.png", CC_CALLBACK_1(HelloWorld::backToMainMenu, this));
	backToMenu->setScale(1.5);
	auto btm = Menu::create(backToMenu, NULL);
	btm->setPosition(100, visibleSize.height - 70);
	addChild(btm, 2);


	//log("%f",visibleSize.width);
	//log("%f", visibleSize.height);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	cardWidth = visibleSize.width / H_NUM - 20;
	cardHeight = visibleSize.height / V_NUM - 20;
	//log("%f  %f", visibleSize.width, visibleSize.height); //960 * 640
	//��ʼ��ͼƬ
	imageName[0] = "c.png";
	imageName[1] = "g.png";
	imageName[2] = "h.png";
	imageName[3] = "j.png";
	imageName[4] = "v.png";
	imageName[5] = "x.png";
	imageName[6] = "m.png";
	imageName[7] = "k.png";
	imageName[8] = "i.png";
	//��ʼ������.�����bgm����������ͻ������,�����쳣��������֪��Ϊɶ
	bgm = Sprite::create("stage1_bg.jpg");
	bgm->setPosition(0, 0);
	bgm->setAnchorPoint(Point(0, 0));
	addChild(bgm);

	pointArr = new PointArray();//��ʼ��
	pointArr->initWithCapacity(60);//�ռ��ʼ��

	cards = new Vector<Sprite*>();
	backCards = new Vector<Sprite*>();
	genAllPoints();
	addCard();   //��ӿ�Ƭ

	lastBCard = nullptr;
	thisBCard = nullptr;
	lastCard = nullptr;
	thisCard = nullptr;

	actionRunning = false;
	prophetStart = false;

	if (ModeSelectScene::level == 2 || ModeSelectScene::level == 3)
	{
		timerLabel = Label::createWithTTF("Arcade", "fonts/pirulenrg.ttf", 50);
		timerLabel->setColor(Color3B::WHITE);
		timerLabel->setAnchorPoint(Point(0, 0));//��ֹ���ֶ���
		timerLabel->setPosition(visibleSize.width - 220, visibleSize.height - 110);
		addChild(timerLabel);
		timerLabel->setString(StringUtils::format("%0.1f", 0.0)); //��ʼ��ʱ��

		//clock
		auto timeClock = Sprite::create("time_clock.png");
		timeClock->setAnchorPoint(Vec2(0, 0));
		timeClock->setScale(1.7);
		timeClock->setPosition(visibleSize.width - 340, visibleSize.height - 140);
		addChild(timeClock, 3);
	}
	//��ʾarcade��ĸ
	if (ModeSelectScene::level == 1)
	{
		auto arcade = Label::createWithTTF("Arcade", "fonts/Alien_Resurrection.ttf", 30);
		arcade->setPosition(visibleSize.width - 90, visibleSize.height - 90);
		arcade->setRotation(45);
		addChild(arcade);
	}
	//��ʾ��ʼ��ť,��֪ģʽ
	auto start = Sprite::create("left_t.png");
	start->setScale(2.0);
	if (ModeSelectScene::level == 3)
	{

		start->setPosition(visibleSize.width / 2 - 30, visibleSize.height - 80);
		addChild(start);
		auto st = ScaleBy::create(1, 2.0);
		auto seq = Sequence::create(st, st->reverse(), NULL);
		auto repeat = RepeatForever::create(seq);
		start->runAction(repeat);
	}
	//���¿�ʼ��Ϸ
	rg = MenuItemImage::create("refresh.png", "refresh.png", CC_CALLBACK_1(HelloWorld::restartGame, this));
	rg->setScale(1.5);
	auto rgt = Menu::create(rg, NULL);
	rgt->setPosition(190, visibleSize.height - 70);
	addChild(rgt, 2);
	
	timerRunning = false;
	isGameOver = false;

	prophetCount = 59;//����ÿ�ζ���ʼ��Ϊ50
	
	newBestLabel = Label::createWithTTF("5", "fonts/ethnocentricrg.ttf", 90);
	newBestLabel->setVisible(false);
	newBestLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(newBestLabel,4);
	
	prophetCountDown = Label::createWithTTF("8", "fonts/ethnocentricrg.ttf", 120);
	prophetCountDown->setPosition(visibleSize.width / 2-20, visibleSize.height - 70);
	prophetCountDown->setVisible(false);
	addChild(prophetCountDown,4);

	cong = Label::createWithTTF("CONgratulation", "fonts/Alien_Resurrection.ttf", 35);
	cong->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 80);
	cong->setVisible(false);
	addChild(cong);

	record = Label::createWithTTF("new   best  record", "fonts/Alien_Resurrection.ttf", 32);
	record->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 110);
	record->setVisible(false);
	addChild(record);

	t1 = Sprite::create("trophy.png");
	t1->setPosition(visibleSize.width / 2 - 250, visibleSize.height / 2);
	t1->setVisible(false);
	t1->setScale(2);
	addChild(t1);

	t2 = Sprite::create("trophy.png");
	t2->setPosition(visibleSize.width / 2 + 250, visibleSize.height / 2);
	t2->setVisible(false);
	t2->setScale(2);
	addChild(t2);

	//��֪ģʽcomboͼ��
	combo = Sprite::create("layer.png");
	combo->setPosition(visibleSize.width / 2-100, visibleSize.height-75);
	combo->setVisible(false);
	combo->setScale(1.5);
	addChild(combo);

	multiply = Sprite::create("cancel.png");
	multiply->setPosition(visibleSize.width / 2 - 40, visibleSize.height - 75);
	multiply->setVisible(false);
	multiply->setScale(1.5);
	addChild(multiply);

	comboCount = 0;//��ʼ��Ϊ0
	comboLabel = Label::createWithTTF("Arcade", "fonts/pirulenrg.ttf", 50);
	comboLabel->setColor(Color3B::WHITE);
	comboLabel->setPosition(visibleSize.width / 2+5, visibleSize.height - 75);
	addChild(comboLabel);
	comboLabel->setString(StringUtils::format("%d", comboCount)); 
	comboLabel->setVisible(false);





	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch *t, Event *e){


		Sprite *card;
		Sprite *bCard;
		if (ModeSelectScene::level == 1 || ModeSelectScene::level == 2)
		{
			if (actionRunning == false)//��֤�����ַ��ʳ�ͻ��ԭ����actionδ���ʱ���������Ƭ��ɵ�
				//�������濨Ƭ
			{
				for (auto it1 = backCards->begin(); it1 != backCards->end(); it1++)
				{
					bCard = *it1;
					if (bCard->getBoundingBox().containsPoint(t->getLocation()))
					{
						//��2,3��ģʽ���м�ʱ
						if (ModeSelectScene::level == 2 || ModeSelectScene::level == 3)
						{
							if (!timerRunning)
							{
								this->startTimer();//��ʼ��ʱ

							}
						}

						if (lastBCard == nullptr)//�����һ�ſ�ƬΪ��
						{
							log("11");
							lastBCard = bCard;
						}
						else
						{
							thisBCard = bCard;
						}

						if (bCard->isVisible() == true)
						{
							bCard->setVisible(false);
						}

						break;
					}
				}


				//�������濨Ƭ
				for (auto it = this->cards->begin(); it != this->cards->end(); it++)
				{
					card = *it;
					if (card->getBoundingBox().containsPoint(t->getLocation()))//cards������5��ͼƬ
					{

						if (card->isVisible() == false)//������ɼ�
						{
							log("22");
							card->setVisible(true);
						}

						if (lastCard == nullptr)
						{
							log("33");
							lastCard = card;
						}
						else
						{
							log("front");
							thisCard = card;
						}
						break;
					}
				}

				//���2�ſ�Ƭ��ͬ
				if (thisCard != nullptr&&thisBCard != nullptr)
				{

					if ((lastCard->getTag() != thisCard->getTag()) && (abs(this->thisCard->getTag() - this->lastCard->getTag()) != 9))
					{
						log("44");
						lastBCard->setVisible(true);
						lastCard->setVisible(false);
						thisCard->setVisible(true);
						thisBCard->setVisible(false);
						lastCard = thisCard;
						lastBCard = thisBCard;
					}
				}

				//���2�ſ�Ƭ��ͬ
				if (thisCard != nullptr&&thisBCard != nullptr)
				{
					if (abs(this->thisCard->getTag() - this->lastCard->getTag()) == 9)
					{

						//������ȥ��Ч
						if (OptionScene::isSoundOn == true)
						{
							SimpleAudioEngine::getInstance()->playEffect("scoring.ogg");
						}

						actionRunning = true;
						auto action_end1 = CallFunc::create([=](){

							//�����Ƴ���vector�е�Ԫ�أ����ǻ�����ʾ����Ļ��											
							this->cards->eraseObject(this->lastCard);
							this->backCards->eraseObject(this->lastBCard);


							//�������Ͱ�card����Ļ���Ƴ���				

							this->lastCard->removeFromParent();
							this->lastBCard->removeFromParent();


							//nullptr,����������

							lastCard = nullptr;
							lastBCard = nullptr;

							actionRunning = false;
						});
						auto action_end2 = CallFunc::create([=](){

							//�����Ƴ���vector�е�Ԫ�أ����ǻ�����ʾ����Ļ��							

							this->cards->eraseObject(this->thisCard);
							this->backCards->eraseObject(this->thisBCard);


							//�������Ͱ�card����Ļ���Ƴ���				

							this->thisCard->removeFromParent();
							this->thisBCard->removeFromParent();

							//nullptr,����������				
							thisBCard = nullptr;
							thisCard = nullptr;

							actionRunning = false;
						});
						//����,����2��node��ͬһ��anction������ֿ���
						auto st = FadeOut::create(1.0);
						auto st2 = FadeOut::create(1.0);

						auto seq1 = Sequence::create(st, action_end1, NULL);
						auto seq2 = Sequence::create(st2, action_end2, NULL);


						this->thisCard->runAction(seq2);
						this->lastCard->runAction(seq1);

					}
				}
			}
		}//end 1 and 2
		else if (ModeSelectScene::level == 3)
		{
		
			if (prophetCount == 0)//����������Ϊ������Ϸ��ʼʱ�ſ��Ե����Ƭ
			{
				if (actionRunning == false)//��֤�����ַ��ʳ�ͻ��ԭ����actionδ���ʱ���������Ƭ��ɵ�
					//�������濨Ƭ
				{
					for (auto it1 = backCards->begin(); it1 != backCards->end(); it1++)
					{
						bCard = *it1;
						if (bCard->getBoundingBox().containsPoint(t->getLocation()))
						{
							//��2,3��ģʽ���м�ʱ
							if (ModeSelectScene::level == 2 || ModeSelectScene::level == 3)
							{
								if (!timerRunning)
								{
									this->startTimer();//��ʼ��ʱ

								}
							}

							if (lastBCard == nullptr)//�����һ�ſ�ƬΪ��
							{
								log("11");
								lastBCard = bCard;
							}
							else
							{
								thisBCard = bCard;
							}

							if (bCard->isVisible() == true)
							{
								bCard->setVisible(false);
							}

							break;
						}
					}


					//�������濨Ƭ
					for (auto it = this->cards->begin(); it != this->cards->end(); it++)
					{
						card = *it;
						if (card->getBoundingBox().containsPoint(t->getLocation()))//cards������5��ͼƬ
						{

							if (card->isVisible() == false)//������ɼ�
							{
								log("22");
								card->setVisible(true);
							}

							if (lastCard == nullptr)
							{
								log("33");
								lastCard = card;
							}
							else
							{
								log("front");
								thisCard = card;
							}
							break;
						}
					}

					//���2�ſ�Ƭ��ͬ
					if (thisCard != nullptr&&thisBCard != nullptr)
					{

						if ((lastCard->getTag() != thisCard->getTag()) && (abs(this->thisCard->getTag() - this->lastCard->getTag()) != 9))
						{
							//����������0����Ϊ������˴���ķ���
							comboCount = 0;
							comboLabel->setString(StringUtils::format("%d", comboCount)); //��ʼ��ʱ��

							lastBCard->setVisible(true);
							lastCard->setVisible(false);
							thisCard->setVisible(true);
							thisBCard->setVisible(false);
							lastCard = thisCard;
							lastBCard = thisBCard;
						}
					}

					//���2�ſ�Ƭ��ͬ
					if (thisCard != nullptr&&thisBCard != nullptr)
					{
						if (abs(this->thisCard->getTag() - this->lastCard->getTag()) == 9)
						{
							
							Size visibleSize = Director::getInstance()->getVisibleSize();
							//����������1
							
							comboCount++;
							comboLabel->setString(StringUtils::format("%d", comboCount)); //��ʼ��ʱ��

							//����bestCombol,ÿһ�ֵ����combo
							if (comboCount >= bestCombo)
							{
								bestCombo = comboCount;
							}
							
							auto st6 = ScaleBy::create(0.3f, 2);
							auto seq6 = Sequence::create(st6, st6->reverse(), NULL);
							comboLabel->runAction(seq6);
							comboLabel->setColor(Color3B(255, 255, 0));
							this->scheduleOnce(SEL_SCHEDULE(&HelloWorld::resumeColor), 0.6f);
							
							//// ��ֵ����⣺�ڵ�����û���⣬����Ͼͳ���bug��������Ե�޹���ʧ��
							/*auto card_fly = Sprite::create("card1.png");
							card_fly->setScale(1.5);
							card_fly->setPosition(thisCard->getPosition());
							addChild(card_fly,4);
							vec_combo.pushBack(card_fly);
							//����
							auto mt = MoveTo::create(1.0f, Vec2(visibleSize.width / 2 - 100, visibleSize.height - 75));
							card_fly->runAction(mt);*/

								
							//������ȥ��Ч
							if (OptionScene::isSoundOn == true)
							{
								SimpleAudioEngine::getInstance()->playEffect("scoring.ogg");
							}

							actionRunning = true;
							auto action_end1 = CallFunc::create([=](){

								//�����Ƴ���vector�е�Ԫ�أ����ǻ�����ʾ����Ļ��											
								this->cards->eraseObject(this->lastCard);
								this->backCards->eraseObject(this->lastBCard);


								//�������Ͱ�card����Ļ���Ƴ���				

								this->lastCard->removeFromParent();
								this->lastBCard->removeFromParent();


								//nullptr,����������

								lastCard = nullptr;
								lastBCard = nullptr;

								actionRunning = false;
							});
							auto action_end2 = CallFunc::create([=](){

								//�����Ƴ���vector�е�Ԫ�أ����ǻ�����ʾ����Ļ��							

								this->cards->eraseObject(this->thisCard);
								this->backCards->eraseObject(this->thisBCard);


								//�������Ͱ�card����Ļ���Ƴ���				

								this->thisCard->removeFromParent();
								this->thisBCard->removeFromParent();

								//nullptr,����������				
								thisBCard = nullptr;
								thisCard = nullptr;

								actionRunning = false;
							});
							//����,����2��node��ͬһ��anction������ֿ���
							auto st = FadeOut::create(1.0);
							auto st2 = FadeOut::create(1.0);

							auto seq1 = Sequence::create(st, action_end1, NULL);
							auto seq2 = Sequence::create(st2, action_end2, NULL);


							this->thisCard->runAction(seq2);
							this->lastCard->runAction(seq1);

						}
					}
				}

			}
		}

			return false;
		};
	
		
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	
	//��Ϸ��ʼ������������֪ģʽ
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = [=](Touch *t, Event *e){
	 
		//���δ��ʼ��Ϸ
		if (prophetStart == false&&ModeSelectScene::level==3)
		{
			if (start->getBoundingBox().containsPoint(t->getLocation()))
			{
				prophetStart = true;
				start->removeFromParent();
				prophetInit();

			}
		}

		
		
		return false;
	
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);
	
	
	
	//�����Ϸ�Ƿ����
	this->schedule(SEL_SCHEDULE(&HelloWorld::isGameEnd), 1.0f);
	//�����֪ģʽ��Ϸǰ�Ĺ۲��Ƿ����
	this->schedule(SEL_SCHEDULE(&HelloWorld::isProphetWatchOver), 0.1f);
	//���combol label�Ƿ񵽴�Ŀ�ĵأ�Ȼ����ʧ
	//this->schedule(SEL_SCHEDULE(&HelloWorld::isComboLabelArrived), 0.1f);
	
    return true;
}
void 
HelloWorld::isComboLabelArrived(float dt)
{
	//��ʼ��Ϸ��
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (timerRunning)
	{
		for (int i = 0; i < vec_combo.size(); i++)
		{
			Sprite* s;
			s = vec_combo.at(i);
			if (s->getPosition() == Point(visibleSize.width / 2 - 100, visibleSize.height - 75))
			{
				s->removeFromParent();
				vec_combo.eraseObject(s);
				
				auto st = ScaleBy::create(0.3f, 2);
				auto seq = Sequence::create(st, st->reverse(), NULL);
				comboLabel->runAction(seq);
				comboLabel->setColor(Color3B(255, 255, 0));
				this->scheduleOnce(SEL_SCHEDULE(&HelloWorld::resumeColor), 0.6f);

			}
		}
	}
}
void 
HelloWorld::resumeColor(float dt)
{
	comboLabel->setColor(Color3B(255, 255, 255));
}
int HelloWorld::prophetCount = 59;//5����׼����

void 
HelloWorld::isProphetWatchOver(float dt)
{
	
	if (prophetStart == true)
	{
		prophetCountDown->setVisible(true);
		prophetCountDown->setString(StringUtils::format("%d", prophetCount / 10));
		prophetCountDown->setScale((double)(prophetCount%10)/10);
	
	}
	//�������˿�ʼ��ť
	if (prophetStart == true)
	{
		prophetCount--;
	}
	
	if (prophetCount <= 0)
	{
		for (auto it = cards->begin(); it != cards->end(); it++)
		{
			(*it)->setVisible(false);
		}
		for (auto it = backCards->begin(); it != backCards->end(); it++)
		{
			(*it)->setVisible(true);
		}
		prophetCount = 0;
		prophetCountDown->removeFromParent();
		//��ʾ��֪comboͼ��
		combo->setVisible(true);
		multiply->setVisible(true);
		comboLabel->setVisible(true);

		this->unschedule(SEL_SCHEDULE(&HelloWorld::isProphetWatchOver));
	}
	
}
void 
HelloWorld::prophetInit()
{
	//�ÿ�Ƭ������ʾ����������
	for (auto it = cards->begin(); it != cards->end(); it++)
	{
		(*it)->setVisible(true);
	}
	for (auto it = backCards->begin(); it != backCards->end(); it++)
	{
		(*it)->setVisible(false);
	}
	

}

double HelloWorld::timing[3] = { 0.0, 0.0, 0.0 };
double HelloWorld::prophet[3] = { 0.0, 0.0, 0.0 };

void
HelloWorld::isGameEnd(float dt)
{
	Size size = Director::getInstance()->getVisibleSize();
	if (this->cards->size() == 0)
	{
		
		if (ModeSelectScene::level == 1)
		{
			showInit();
			auto st = ScaleBy::create(0.6f, 1.3);
			auto seq = Sequence::create(st, st->reverse(), NULL);
			auto repeat = RepeatForever::create(seq);
			rg->runAction(repeat);
		}
		
				
		if (ModeSelectScene::level == 2 || ModeSelectScene::level == 3)
		{
			endTimer();

		}
			
		//��ʾ�¼�¼�������п�Ƭ��ʧ	
		if (ModeSelectScene::level == 2)//timingģʽ
		{
			
			//���¿�ʼ�Ķ���
			auto st = ScaleBy::create(0.6f, 1.3);
			auto seq = Sequence::create(st, st->reverse(), NULL);
			auto repeat = RepeatForever::create(seq);
			rg->runAction(repeat);		
			
			Size visibleSize = Director::getInstance()->getVisibleSize();
			auto tl = Label::createWithTTF("Arcade", "fonts/pirulenrg.ttf", 50);
			tl->setColor(Color3B::WHITE);
			tl->setAnchorPoint(Point(0, 0));//��ֹ���ֶ���
			tl->setPosition(visibleSize.width - 220, visibleSize.height - 110);
			addChild(tl);
			tl->setString(StringUtils::format("%0.1f", ((double)offset) / 1000000)); //��ʼ��ʱ��				  
			//������Ӧ�����ݼ�¼1,2,3��
			WelcomeScene::highestScoreTiming = UserDefault::getInstance()->getDoubleForKey("highestScoreTiming");
			WelcomeScene::SecondhighestScoreTiming = UserDefault::getInstance()->getDoubleForKey("SecondhighestScoreTiming");
			WelcomeScene::ThirdhighestScoreTiming = UserDefault::getInstance()->getDoubleForKey("ThirdhighestScoreTiming");
			timing[0] = WelcomeScene::highestScoreTiming;
			timing[1] = WelcomeScene::SecondhighestScoreTiming;
			timing[2] = WelcomeScene::ThirdhighestScoreTiming;
			char *temp[3] = { "highestScoreTiming", "SecondhighestScoreTiming", "ThirdhighestScoreTiming" };
			for (int i = 0; i < 3; i++)
			{
				if (((double)offset) / 1000 < timing[i]) //���¼�¼
				{
					//����i
					int t = i;
					//���º������ݣ����벽��
					for (int j = 2; j > t; j--)
					{
						UserDefault::getInstance()->setDoubleForKey(temp[j],UserDefault::getInstance()->getDoubleForKey(temp[j-1]));
					}
					
					UserDefault::getInstance()->setDoubleForKey(temp[i], offset / 1000);
					UserDefault::getInstance()->flush();//����©��

					break;//����ѭ������
				}
			}
			
			if (((double)offset) / 1000 <= WelcomeScene::highestScoreTiming)
			{
				
				newBestLabel->setString(StringUtils::format("%0.1f", ((double)offset) / 1000000));
				newBestLabel->setColor(Color3B::YELLOW);
				newBestLabel->setVisible(true);
				
				cong->setVisible(true);
				record->setVisible(true);
				t1->setVisible(true);
				t2->setVisible(true);
				
				//����
				auto st = ScaleBy::create(0.8f, 1.3);
				auto seq = Sequence::create(st, st->reverse(), NULL);
				auto repeat = RepeatForever::create(seq);
				newBestLabel->runAction(repeat);

				
			}
			else
			{
				showInit();
			}

		}
		if (ModeSelectScene::level == 3)
		{
			
			//ȡ������
			//this->unschedule(SEL_SCHEDULE(&HelloWorld::isComboLabelArrived));
			//�������combo
			int histryBestCombo = UserDefault::getInstance()->getIntegerForKey("BestCombo");
			if (bestCombo >= histryBestCombo)
			{
				UserDefault::getInstance()->setIntegerForKey("BestCombo", bestCombo);
				UserDefault::getInstance()->flush();//����©��

				//combo����
				auto st1 = ScaleBy::create(0.6f, 1.3);
				auto seq1 = Sequence::create(st1, st1->reverse(), NULL);
				auto repeat1 = RepeatForever::create(seq1);
				combo->runAction(repeat1);

				auto st2 = ScaleBy::create(0.6f, 1.3);
				auto seq2 = Sequence::create(st2, st2->reverse(), NULL);
				auto repeat2 = RepeatForever::create(seq2);
				multiply->runAction(repeat2);

				auto st3 = ScaleBy::create(0.6f, 1.3);
				auto seq3 = Sequence::create(st3, st3->reverse(), NULL);
				auto repeat3 = RepeatForever::create(seq3);
				comboLabel->runAction(repeat3);

			}
							
			//���¿�ʼ�Ķ���
			auto st = ScaleBy::create(0.6f, 1.3);
			auto seq = Sequence::create(st, st->reverse(), NULL);
			auto repeat = RepeatForever::create(seq);
			rg->runAction(repeat);

			Size visibleSize = Director::getInstance()->getVisibleSize();
			auto tl = Label::createWithTTF("Arcade", "fonts/pirulenrg.ttf", 50);
			tl->setColor(Color3B::WHITE);
			tl->setAnchorPoint(Point(0, 0));//��ֹ���ֶ���
			tl->setPosition(visibleSize.width - 220, visibleSize.height - 110);
			addChild(tl);
			tl->setString(StringUtils::format("%0.1f", ((double)offset) / 1000000)); //��ʼ��ʱ��				  

			WelcomeScene::highestScoreProphet = UserDefault::getInstance()->getDoubleForKey("highestScoreProphet");
			WelcomeScene::SecondhighestScoreProphet = UserDefault::getInstance()->getDoubleForKey("SecondhighestScoreProphet");
			WelcomeScene::ThirdhighestScoreProphet = UserDefault::getInstance()->getDoubleForKey("ThirdhighestScoreProphet");
			prophet[0] = WelcomeScene::highestScoreProphet;
			prophet[1] = WelcomeScene::SecondhighestScoreProphet;
			prophet[2] = WelcomeScene::ThirdhighestScoreProphet;

			char *temp1[3] = { "highestScoreProphet", "SecondhighestScoreProphet", "ThirdhighestScoreProphet" };
			for (int i = 0; i < 3; i++)
			{
				if (((double)offset) / 1000 < prophet[i]) //���¼�¼
				{
					//����i
					int t = i;
					//���º������ݣ����벽��
					for (int j = 2; j > t; j--)
					{
						UserDefault::getInstance()->setDoubleForKey(temp1[j], UserDefault::getInstance()->getDoubleForKey(temp1[j - 1]));
					}

					UserDefault::getInstance()->setDoubleForKey(temp1[i], offset / 1000);
					UserDefault::getInstance()->flush();//����©��

					break;//����ѭ������
				}
			}

			if (((double)offset) / 1000 <= WelcomeScene::highestScoreProphet)
			{
				
				newBestLabel->setString(StringUtils::format("%0.1f", ((double)offset) / 1000000));
				newBestLabel->setVisible(true);
				newBestLabel->setColor(Color3B::YELLOW);

				cong->setVisible(true);
				record->setVisible(true);
				t1->setVisible(true);
				t2->setVisible(true);

				//����
				auto st = ScaleBy::create(0.8f, 1.3);
				auto seq = Sequence::create(st, st->reverse(), NULL);
				auto repeat = RepeatForever::create(seq);
				newBestLabel->runAction(repeat);
			
			}
			else
			{
				showInit();
			}
		}


		//ȡ�����Ⱥ�������ֹһֱ�ж���ȥ
		this->unschedule(SEL_SCHEDULE(&HelloWorld::isGameEnd));
	}
	
}
void
HelloWorld::restartGame(Ref* r)
{
	
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, HelloWorld::createScene()));
}
void HelloWorld::startTimer()
{
	if (!timerRunning)
	{
		scheduleUpdate();
		startTime = clock();
		timerRunning = true;
	}
}
void HelloWorld::endTimer()
{
	if (timerRunning)
	{
		unscheduleUpdate();
		timerRunning = false;
	}
}
void HelloWorld::update(float dt)
{
	offset = clock() - startTime;
	timerLabel->setString(StringUtils::format("%0.1f", ((double)offset) / 1000000));

}
void HelloWorld::backToMainMenu(cocos2d::Ref* r)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, ModeSelectScene::createScene()));
}
void HelloWorld::genAllPoints()
{
	while (pointArr->count())
	{
		pointArr->removeControlPointAtIndex(0);//�Ƴ�Ԫ�أ����
	}
	for (int x = 0; x< H_NUM;x++)
	for (int y = 0; y < V_NUM-1; y++)
	{
		pointArr->addControlPoint(Point(x*cardWidth+60, y*cardHeight+60));
	}
}
void HelloWorld::addBackCard()
{
	for (int x = 0; x< H_NUM; x++)
	  for (int y = 0; y < V_NUM - 1; y++)
	  {  
		Sprite *s;
		s = Sprite::create("unknown.png");
		s->setPosition(Point(x*cardWidth+65, y*cardHeight+65));//add a little offset
		addChild(s);
		
	  }
}
void HelloWorld::addCard()//also add back cards
{
	int randNum;
	srand(time(NULL));
	for (int i = 0; i < 9; i++)
	{
		addCards(i);						
	}
	//rightIndex = rand() % 5;
	//addCards(rightIndex);
	for (int i = 9; i < 18; i++)
	{
		addCards(i);
	}
}
Sprite *HelloWorld::addCards(int index)
{
	Point p;
	int randNum;
	Sprite *s;
	Sprite *sb;
	if (index < 9)
	{
		s = Sprite::create(imageName[index]);
		s->setScale(1.1);
		//all cards are invisible at first
		s->setVisible(false);
		//add back cards
		
		sb = Sprite::create("unknown.png");
		sb->setVisible(true);
		sb->setScale(0.25);

		
	}
	else
	{
		s = Sprite::create(imageName[index - 9]);
		s->setScale(1.1);
		s->setVisible(false);
		//add back cards
		
		sb = Sprite::create("unknown.png");
		sb->setVisible(true);
		sb->setScale(0.25);
	}
	
	randNum = rand() % pointArr->count();//��ȡ0-size(pointArr)�������
	p = pointArr->getControlPointAtIndex(randNum);//���ȡ��pointarr�����һ��Ԫ��
	pointArr->removeControlPointAtIndex(randNum);//�Ƴ�����Ԫ��
	tempArrayX.push_back(p.x);//��������������
	tempArrayY.push_back(p.y);//��������������
	s->setTag(index);
	sb->setTag(index);
	s->setAnchorPoint(Point(0, 0));
	sb->setAnchorPoint(Point(0, 0));
	
	cards->pushBack(s);
	backCards->pushBack(sb);
	
	s->setPosition(p);
	sb->setPosition(p);
	
    addChild(sb);	
	addChild(s);

	return s;
}
void
HelloWorld::showInit()
{
	Sprite *s;
	for (int i = 0; i < 9; i++)
	{
		
			s = Sprite::create(imageName[i]);
			s->setScale(1.1);
			s->setVisible(true);
			s->setPosition(Point(tempArrayX[i], tempArrayY[i]));
			s->setAnchorPoint(Point(0, 0));
			addChild(s);	
	}

	for (int i = 9; i < 18; i++)
	{
		s = Sprite::create(imageName[i-9]);
		s->setScale(1.1);
		s->setVisible(true);
		s->setPosition(Point(tempArrayX[i], tempArrayY[i]));
		s->setAnchorPoint(Point(0, 0));
		addChild(s);

	}
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
