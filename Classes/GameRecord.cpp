#include "GameRecord.h"
#include "WelcomeScene.h"
USING_NS_CC;
using namespace std;



Scene*
GameRecord::createScene()
{
	auto scene = Scene::create();
	auto layer = GameRecord::create();
	scene->addChild(layer);
	return scene;
}
bool
GameRecord::init()
{
	Layer::init();
	auto bg = Sprite::create("select_bg.jpg");
	bg->setAnchorPoint(Point(0, 0));
	bg->setPosition(Point(0, 0));
	addChild(bg);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//回到主菜单
	auto backToMenu = MenuItemImage::create("forward_arrow.png", "forward_arrow.png", CC_CALLBACK_1(GameRecord::backToMainMenu, this));
	backToMenu->setScale(1.5);
	auto btm = Menu::create(backToMenu, NULL);
	btm->setPosition(80, visibleSize.height - 60);
	addChild(btm, 2);

	//游戏记录标题
	auto title = Label::createWithTTF("Game    record", "fonts/Alien_Resurrection.ttf", 45);
	title->setPosition(visibleSize.width / 2 , visibleSize.height - 150);
	addChild(title);

	//奖杯
	auto t1 = Sprite::create("trophy.png");
	t1->setPosition(visibleSize.width - 170, 80);
	t1->setScale(1.3);
	addChild(t1, 3);

	auto t2 = Sprite::create("trophy.png");
	t2->setPosition(visibleSize.width - 60, 80);
	t2->setScale(1.3);
	addChild(t2, 3);
	//最佳combo记录展示
	auto combo = Label::createWithTTF("2", "fonts/pirulenrg.ttf", 60);
	combo->setPosition(visibleSize.width - 110, 80);
	combo->setColor(Color3B(255, 255, 0));
	addChild(combo);
	auto st = ScaleBy::create(1.0f, 1.5);
	auto seq = Sequence::create(st, st->reverse(), NULL);
	auto repeat = RepeatForever::create(seq);
	combo->runAction(repeat);
	
	//best combo 说明
	auto combo_des = Label::createWithTTF("Best  cOMBO", "fonts/pirulenrg.ttf", 40);
	combo_des->setPosition(visibleSize.width - 480, 80);
	combo_des->setOpacity(0);
	addChild(combo_des);
	ActionInterval* dt1 = DelayTime::create(1.0f);
	auto fi1 = FadeIn::create(1.0f);
	auto seq1 = Sequence::create(dt1,fi1, fi1->reverse(), fi1, fi1->reverse(), NULL);
	combo_des->runAction(seq1);

	auto arrow = Sprite::create("left_t.png");
	arrow->setScale(1.4);
	arrow->setOpacity(0);
	arrow->setPosition(visibleSize.width - 240, 80);
	addChild(arrow);
	ActionInterval* dt2 = DelayTime::create(1.0f);
	auto fi2 = FadeIn::create(1.0f);
	auto seq2 = Sequence::create(dt2,fi2, fi2->reverse(), fi2, fi2->reverse(), NULL);
	arrow->runAction(seq2);
	
	//领导榜
	auto lb1 = Sprite::create("lb.png");
	lb1->setPosition(visibleSize.width / 2 - 290, visibleSize.height - 240);
	addChild(lb1);
	
	auto lb2 = Sprite::create("lb.png");
	lb2->setPosition(visibleSize.width / 2 +10, visibleSize.height - 240);
	addChild(lb2);

	auto title1 = Label::createWithTTF("Timing", "fonts/Alien_Resurrection.ttf", 32);
	title1->setColor(Color3B(255,255,0));
	title1->setPosition(visibleSize.width / 2 - 160, visibleSize.height - 240);
	addChild(title1);

	auto title2 = Label::createWithTTF("prophet", "fonts/Alien_Resurrection.ttf", 32);
	title2->setColor(Color3B(255, 255, 0));
	title2->setPosition(visibleSize.width / 2 +175, visibleSize.height - 240);
	addChild(title2);

	//1,2,3名
	auto p1 = Sprite::create("page1.png");
	p1->setPosition(visibleSize.width / 2 - 290, visibleSize.height - 315);
	addChild(p1);
	
	auto p2 = Sprite::create("page2.png");
	p2->setPosition(visibleSize.width / 2 - 290, visibleSize.height - 380);
	addChild(p2);

	auto p3 = Sprite::create("page3.png");
	p3->setPosition(visibleSize.width / 2 - 290, visibleSize.height - 445);
	addChild(p3);

	//1,2,3名
	auto p4 = Sprite::create("page1.png");
	p4->setPosition(visibleSize.width / 2 +10, visibleSize.height - 315);
	addChild(p4);

	auto p5 = Sprite::create("page2.png");
	p5->setPosition(visibleSize.width / 2 +10, visibleSize.height - 380);
	addChild(p5);

	auto p6 = Sprite::create("page3.png");
	p6->setPosition(visibleSize.width / 2 +10, visibleSize.height - 445);
	addChild(p6);

	
	///////////////////////////////////////////显示数据记录
	//timing模式下
	double timing_1 = UserDefault::getInstance()->getDoubleForKey("highestScoreTiming");
	if (timing_1 >= 99999)
	{
		tm1 = Label::createWithTTF("??", "fonts/pirulenrg.ttf", 30);
		tm1->setPosition(visibleSize.width / 2 - 160, visibleSize.height - 320);
		addChild(tm1);
	}
	else //如果数据存在
	{
		char time[10];
		sprintf(time, "%0.1f", timing_1/1000);
		tm1 = Label::createWithTTF(time, "fonts/pirulenrg.ttf", 40);
		tm1->setPosition(visibleSize.width / 2 - 160, visibleSize.height - 320);
		addChild(tm1);
	}
	
	double timing_2 = UserDefault::getInstance()->getDoubleForKey("SecondhighestScoreTiming");
	if (timing_2 >= 99999)
	{
		tm2 = Label::createWithTTF("??", "fonts/pirulenrg.ttf", 30);
		tm2->setPosition(visibleSize.width / 2 - 160, visibleSize.height - 385);
		addChild(tm2);
	}
	else //如果数据存在
	{
		char time[10];
		sprintf(time, "%0.1f", timing_2/1000);
		tm2 = Label::createWithTTF(time, "fonts/pirulenrg.ttf", 35);
		tm2->setPosition(visibleSize.width / 2 - 160, visibleSize.height - 385);
		addChild(tm2);
	}

	double timing_3 = UserDefault::getInstance()->getDoubleForKey("ThirdhighestScoreTiming");
	if (timing_3 >= 99999)
	{
		tm3 = Label::createWithTTF("??", "fonts/pirulenrg.ttf", 30);
		tm3->setPosition(visibleSize.width / 2 - 160, visibleSize.height - 445);
		addChild(tm3);
	}
	else //如果数据存在
	{
		char time[10];
		sprintf(time, "%0.1f", timing_3/1000);
		tm3 = Label::createWithTTF(time, "fonts/pirulenrg.ttf", 30);
		tm3->setPosition(visibleSize.width / 2 - 160, visibleSize.height - 445);
		addChild(tm3);
	}

	///////////////////////////////////////////显示数据记录
	//prophet模式下
	double ph_1 = UserDefault::getInstance()->getDoubleForKey("highestScoreProphet");
	if (ph_1 >= 99999)
	{
		ph1 = Label::createWithTTF("??", "fonts/pirulenrg.ttf", 30);
		ph1->setPosition(visibleSize.width / 2 + 160, visibleSize.height - 320);
		addChild(ph1);
	}
	else //如果数据存在
	{
		char time[10];
		sprintf(time, "%0.1f", ph_1/1000);
		ph1 = Label::createWithTTF(time, "fonts/pirulenrg.ttf", 40);
		ph1->setPosition(visibleSize.width / 2 + 150, visibleSize.height - 320);
		addChild(ph1);
	}

	double ph_2 = UserDefault::getInstance()->getDoubleForKey("SecondhighestScoreProphet");
	if (ph_2 >= 99999)
	{
		ph2 = Label::createWithTTF("??", "fonts/pirulenrg.ttf", 30);
		ph2->setPosition(visibleSize.width / 2 + 160, visibleSize.height - 385);
		addChild(ph2);
	}
	else //如果数据存在
	{
		char time[10];
		sprintf(time, "%0.1f", ph_2/1000);
		ph2 = Label::createWithTTF(time, "fonts/pirulenrg.ttf", 35);
		ph2->setPosition(visibleSize.width / 2 + 150, visibleSize.height - 385);
		addChild(ph2);
	}

	double ph_3 = UserDefault::getInstance()->getDoubleForKey("ThirdhighestScoreProphet");
	if (ph_3 >= 99999)
	{
		ph3 = Label::createWithTTF("??", "fonts/pirulenrg.ttf", 30);
		ph3->setPosition(visibleSize.width / 2 + 160, visibleSize.height - 445);
		addChild(ph3);
	}
	else //如果数据存在
	{
		char time[10];
		sprintf(time, "%0.1f", ph_3/1000);
		ph3 = Label::createWithTTF(time, "fonts/pirulenrg.ttf", 30);
		ph3->setPosition(visibleSize.width / 2 + 150, visibleSize.height - 445);
		addChild(ph3);
	}

	//显示最佳combo
	int tempBestCombo = UserDefault::getInstance()->getIntegerForKey("BestCombo");
	combo->setString(StringUtils::format("%d", tempBestCombo));
	

	return true;
}
void 
GameRecord::backToMainMenu(Ref *r)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, WelcomeScene::createScene()));
}
GameRecord::GameRecord()
{
}


GameRecord::~GameRecord()
{
}
