#include "WelcomeScene.h"
#include "HelloWorldScene.h"
#include "ModeSelectScene.h"
#include "HowToPlay.h"
#include "GameRecord.h"
#include "SimpleAudioEngine.h"
#include "OptionScene.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* WelcomeScene::createScene()
{
	auto scene = Scene::create();
	auto layer = WelcomeScene::create();
	scene->addChild(layer);
	return scene;
}

double WelcomeScene::highestScoreTiming = 10000.0;//时间记录
double WelcomeScene::highestScoreProphet = 10000.0; 
double WelcomeScene::SecondhighestScoreTiming = 10000.0;
double WelcomeScene::SecondhighestScoreProphet = 10000.0;
double WelcomeScene::ThirdhighestScoreTiming = 10000.0;
double WelcomeScene::ThirdhighestScoreProphet = 10000.0;

bool WelcomeScene::init()
{
	Layer::init();
	
	//添加音乐 预加载
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgm.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("scoring.ogg");
	//判断是否有数据记录
	isSaveFile();
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* bg = Sprite::create("select1_bg.jpg");
	bg->setAnchorPoint(Point(0, 0));
	bg->setPosition(Point(0, 0));
	this->addChild(bg);
	
	//title
	auto title = Sprite::create("g.png");
	Size titleSize = title->getContentSize();
	//title->setAnchorPoint(Point(0,0));
	title->setScale(1.1);
	title->setPosition(Point(visibleSize.width / 2 - titleSize.width / 2-280, visibleSize.height - 100));
	title->setOpacity(0);//注意不是setvisible，否则图片永远不会显示
	addChild(title);
	auto action1 = FadeIn::create(2);
	auto mt1 = MoveTo::create(2, Point(visibleSize.width / 2 - titleSize.width / 2 - 280, visibleSize.height - 150));
	auto sp1 = Spawn::create(action1, mt1, NULL);
	title->runAction(sp1);

	auto title_st = ScaleBy::create(1.3f, 1.2);
	auto title_seq = Sequence::create(title_st, title_st->reverse(), NULL);
	auto title_repeat = RepeatForever::create(title_seq);
	title->runAction(title_repeat);
				
	auto title1 = Sprite::create("j.png");	
	//title1->setAnchorPoint(Point(0, 0));
	title1->setScale(1);
	title1->setRotation(20);
	title1->setPosition(Point(visibleSize.width / 2 - titleSize.width / 2 - 170, visibleSize.height - 240));
	title1->setOpacity(0);
	auto action2 = FadeIn::create(2);
	auto mt2 = MoveTo::create(2, Point(visibleSize.width / 2 - titleSize.width / 2 - 170, visibleSize.height - 170));
	auto sp2 = Spawn::create(action2, mt2, NULL);
	title1->runAction(sp2);
	addChild(title1);
	auto title1_st = ScaleBy::create(1.1f, 1.2);
	auto title1_seq = Sequence::create(title1_st, title1_st->reverse(), NULL);
	auto title1_repeat = RepeatForever::create(title1_seq);
	title1->runAction(title1_repeat);

	auto title2 = Sprite::create("title_1.png");
	//title2->setAnchorPoint(Point(0, 0));
	title2->setScale(1);
	title2->setRotation(-20);
	title2->setPosition(Point(visibleSize.width / 2 - titleSize.width / 2-50, visibleSize.height - 160));
	title2->setOpacity(0);
	auto action3 = FadeIn::create(2);
	auto mt3 = MoveTo::create(2, Point(visibleSize.width / 2 - titleSize.width / 2 - 50, visibleSize.height - 160));
	auto sp3 = Spawn::create(action3, mt3, NULL);
	title2->runAction(sp3);
	addChild(title2);
	auto title2_st = ScaleBy::create(1.1f, 1.2);
	auto title2_seq = Sequence::create(title2_st, title2_st->reverse(), NULL);
	auto title2_repeat = RepeatForever::create(title2_seq);
	title2->runAction(title2_repeat);

	auto title3 = Sprite::create("p.png");
	//title3->setAnchorPoint(Point(0, 0));
	title3->setScale(1.1);
	title3->setRotation(10);
	title3->setPosition(Point(visibleSize.width / 2 - titleSize.width / 2 +100, visibleSize.height - 220));
	title3->setOpacity(0);
	auto action4 = FadeIn::create(2);
	auto mt4 = MoveTo::create(2, Point(visibleSize.width / 2 - titleSize.width / 2 + 100, visibleSize.height - 160));
	auto sp4 = Spawn::create(action4, mt4, NULL);
	title3->runAction(sp4);
	addChild(title3);
	auto title3_st = ScaleBy::create(1.1f, 1.2);
	auto title3_seq = Sequence::create(title3_st, title3_st->reverse(), NULL);
	auto title3_repeat = RepeatForever::create(title3_seq);
	title3->runAction(title3_repeat);

	auto title4 = Sprite::create("a.jpg");
	//title4->setAnchorPoint(Point(0, 0));
	title4->setScale(1.5);
	title4->setRotation(-10);
	title4->setPosition(Point(visibleSize.width / 2 - titleSize.width / 2 + 190, visibleSize.height - 150));
	title4->setOpacity(0);
	auto action5 = FadeIn::create(2);
	auto mt5 = MoveTo::create(2, Point(visibleSize.width / 2 - titleSize.width / 2 + 190, visibleSize.height - 150));
	auto sp5 = Spawn::create(action5, mt5, NULL);
	title4->runAction(sp5);
	addChild(title4);
	auto title4_st = ScaleBy::create(1.5f, 1.2);
	auto title4_seq = Sequence::create(title4_st, title4_st->reverse(), NULL);
	auto title4_repeat = RepeatForever::create(title4_seq);
	title4->runAction(title4_repeat);

	auto title5 = Sprite::create("r.jpg");	
	//title5->setAnchorPoint(Point(0, 0));
	title5->setScale(0.4);
	title5->setRotation(0);
	title5->setPosition(Point(visibleSize.width / 2 - titleSize.width / 2 + 280, visibleSize.height - 210));
	title5->setOpacity(0);
	auto action6 = FadeIn::create(2);
	auto mt6 = MoveTo::create(2, Point(visibleSize.width / 2 - titleSize.width / 2 + 280, visibleSize.height - 170));
	auto sp6 = Spawn::create(action6, mt6, NULL);
	title5->runAction(sp6);
	addChild(title5);
	auto title5_st = ScaleBy::create(1.3f, 1.1);
	auto title5_seq = Sequence::create(title5_st, title5_st->reverse(), NULL);
	auto title5_repeat = RepeatForever::create(title5_seq);
	title5->runAction(title5_repeat);

	auto title6 = Sprite::create("t.png");
	//title6->setAnchorPoint(Point(0, 0));
	title6->setScale(1);
	title6->setRotation(-15);
	title6->setPosition(Point(visibleSize.width / 2 - titleSize.width / 2 + 380, visibleSize.height - 120));
	title6->setOpacity(0);
	auto action7 = FadeIn::create(2);
	auto mt7 = MoveTo::create(2, Point(visibleSize.width / 2 - titleSize.width / 2 + 380, visibleSize.height - 150));
	auto sp7 = Spawn::create(action7, mt7, NULL);
	title6->runAction(sp7);
	addChild(title6);
	auto title6_st = ScaleBy::create(1.5f, 1.2);
	auto title6_seq = Sequence::create(title6_st, title6_st->reverse(), NULL);
	auto title6_repeat = RepeatForever::create(title6_seq);
	title6->runAction(title6_repeat);

	//menu
	auto start = MenuItemImage::create("start_game.png", "start_game.png", CC_CALLBACK_1(WelcomeScene::gameStart, this));
	start->setScale(2.5);
	auto menu_start = Menu::create(start, NULL);
	menu_start->setOpacity(0);
	Size start_size = start->getContentSize();
	menu_start->setAnchorPoint(Point(0, 0));
	menu_start->setPosition(visibleSize.width / 2 , visibleSize.height - 460);
	addChild(menu_start);

	auto option = MenuItemImage::create("option.png", "option.png", CC_CALLBACK_1(WelcomeScene::gameOption, this));
	option->setScale(1.7);
	auto option_start = Menu::create(option, NULL);
	option_start->setOpacity(0);
	Size option_size = option->getContentSize();
	option_start->setAnchorPoint(Point(0, 0));
	option_start->setPosition(visibleSize.width / 2-190, visibleSize.height - 460);
	addChild(option_start);

	auto help = MenuItemImage::create("help.png", "help.png", CC_CALLBACK_1(WelcomeScene::gameHelp, this));
	help->setScale(1.7);
	auto help_start = Menu::create(help, NULL);
	help_start->setOpacity(0);
	Size help_size = help->getContentSize();
	help_start->setAnchorPoint(Point(0, 0));
	help_start->setPosition(visibleSize.width / 2+190, visibleSize.height - 460);
	addChild(help_start);

	//menu 动画
	ActionInterval * delaytime = CCDelayTime::create(1);
	auto fi = FadeIn::create(2);
	auto st = ScaleBy::create(2.0f, 1.2);
	auto seq = Sequence::create(st, st->reverse(), NULL);
	auto repeat1 = RepeatForever::create(seq);
	//repeat动作不能用在sequence中
	auto seq1 = Sequence::create(delaytime, fi, NULL);
	menu_start->runAction(seq1);
	menu_start->runAction(repeat1);

	ActionInterval * delaytime1 = CCDelayTime::create(2);
	auto fi1 = FadeIn::create(2);
	auto seq2 = Sequence::create(delaytime1, fi1, NULL);
	option_start->runAction(seq2);
	auto rotate1 = RotateBy::create(0.5, 45);
	auto rotate_repeat1 = RepeatForever::create(rotate1);
	option_start->runAction(rotate_repeat1);

	ActionInterval * delaytime2 = CCDelayTime::create(2);
	auto fi2 = FadeIn::create(2);
	auto seq3 = Sequence::create(delaytime2, fi2, NULL);
	help_start->runAction(seq3);
	auto rotate2 = RotateBy::create(0.5, 45);
	auto rotate_repeat2 = RepeatForever::create(rotate2);
	help_start->runAction(rotate_repeat2);

    
	//播放音乐:背景音乐
	if (OptionScene::isBgmOn == true) 
	{
		//让音乐连续播放检测是否正在播放音乐
		if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.OGG", true);
		}
	}
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0);

	//游戏音效：消去方块时的音效
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.4f);
		
	
	
	return true;
}
bool
WelcomeScene::isSaveFile()
{
	//只有dubug模式下才看得见xml文档
    if (!UserDefault::getInstance()->getBoolForKey("score"))
	{
		UserDefault::getInstance()->setBoolForKey("score", true);
		//设置3个不同难度的分数
		UserDefault::getInstance()->setDoubleForKey("highestScoreTiming", 100000.0);
		UserDefault::getInstance()->setDoubleForKey("highestScoreProphet", 100000.0);

		UserDefault::getInstance()->setDoubleForKey("SecondhighestScoreTiming", 100000.0);
		UserDefault::getInstance()->setDoubleForKey("SecondhighestScoreProphet", 100000.0);

		UserDefault::getInstance()->setDoubleForKey("ThirdhighestScoreTiming", 100000.0);
		UserDefault::getInstance()->setDoubleForKey("ThirdhighestScoreProphet", 100000.0);

		//设置最佳combo
		UserDefault::getInstance()->setIntegerForKey("BestCombo", 0);

		//写入
		UserDefault::getInstance()->flush();
		return false;
	}
	else
		return true;
}
void
WelcomeScene::gameOver(Ref* r)
{
	Director::getInstance()->end();
}
void
WelcomeScene::gameStart(Ref* r)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, HowToPlay::createScene()));
}
void
WelcomeScene::gameOption(Ref* r)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, OptionScene::createScene()));
}
void
WelcomeScene::gameHelp(Ref* r)//游戏记录
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameRecord::createScene()));
}

WelcomeScene::WelcomeScene()
{
}


WelcomeScene::~WelcomeScene()
{
}
