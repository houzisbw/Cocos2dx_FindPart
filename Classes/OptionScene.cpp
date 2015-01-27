#include "OptionScene.h"
#include "WelcomeScene.h"
#include "infoScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

bool OptionScene::isSoundOn = true;
bool OptionScene::isBgmOn = true;

Scene*
OptionScene::createScene()
{
	auto scene = Scene::create();
	auto layer = OptionScene::create();
	scene->addChild(layer);
	return scene;
}
bool
OptionScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto bg = Sprite::create("select_bg.jpg");
	bg->setAnchorPoint(Point(0, 0));
	bg->setPosition(Point(0, 0));
	addChild(bg);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//回到主菜单
	auto backToMenu = MenuItemImage::create("forward_arrow.png", "forward_arrow.png", CC_CALLBACK_1(OptionScene::backToMainMenu, this));
	backToMenu->setScale(1.5);
	auto btm = Menu::create(backToMenu, NULL);
	btm->setPosition(80, visibleSize.height - 80);
	addChild(btm, 2);

	//右下角装饰物
	auto cong = Sprite::create("cogs.png");
	cong->setScale(1.5);
	cong->setPosition(visibleSize.width-80,80);
	addChild(cong);

	//游戏option标题
	auto title = Label::createWithTTF("Game    OPTion", "fonts/Alien_Resurrection.ttf", 45);
	title->setPosition(visibleSize.width / 2, visibleSize.height - 230);
	addChild(title);

	//游戏信息
	auto info = Sprite::create("info.png");
	info->setScale(1.5);
	info->setPosition(visibleSize.width / 2+250, visibleSize.height - 360);
	auto st = ScaleBy::create(1.0f, 1.3);
	auto seq = Sequence::create(st, st->reverse(), NULL);
	auto repeat = RepeatForever::create(seq);
	info->runAction(repeat);
	addChild(info);

	//游戏音效
	auto effect_on = Sprite::create("sound_on.png");
	effect_on->setScale(2);
	effect_on->setPosition(visibleSize.width / 2-250, visibleSize.height - 360);
	if (isSoundOn)
	{
		effect_on->setVisible(true);
	}
	else
	{
		effect_on->setVisible(false);

	}
	addChild(effect_on);
	
	auto effect_off = Sprite::create("sound_off.png");
	effect_off->setScale(2);
	effect_off->setVisible(false);
	effect_off->setPosition(visibleSize.width / 2 - 250, visibleSize.height - 360);
	if (isSoundOn)
	{
		effect_off->setVisible(false);
	}
	else
	{
		effect_off->setVisible(true);

	}
	addChild(effect_off);

	//游戏背景音乐开
	auto bgm_on = Sprite::create("bgm_on.png");
	bgm_on->setScale(1.8);
	bgm_on->setPosition(visibleSize.width / 2 , visibleSize.height - 360);
	addChild(bgm_on);
	//游戏背景音乐关
	auto bgm_off = Sprite::create("shutdown.png");
	bgm_off->setScale(0.6);
	bgm_off->setPosition(visibleSize.width / 2+5, visibleSize.height - 360);
	if (isBgmOn)
	{
		bgm_off->setVisible(false);
	}
	else
	{
		bgm_off->setVisible(true);

	}
	addChild(bgm_off);

	//点击关闭或打开游戏音效
	auto listener_sound = EventListenerTouchOneByOne::create();
	listener_sound->onTouchBegan = [=](Touch*t,Event*e){
	
		//检测游戏音效
		if (effect_on->getBoundingBox().containsPoint(t->getLocation()))
		{
			//如果音效打开，则关闭之
			if (isSoundOn == true)
			{
				isSoundOn = false;
				effect_on->setVisible(false);
				effect_off->setVisible(true);

			}
			else
			{
				isSoundOn = true;
				effect_on->setVisible(true);
				effect_off->setVisible(false);
				
			}
		}
		//检测游戏背景音乐
		if (bgm_on->getBoundingBox().containsPoint(t->getLocation()))
		{
			//如果音效打开，则关闭之
			if (isBgmOn == true)
			{
				isBgmOn = false;
				bgm_off->setVisible(true);
				SimpleAudioEngine::getInstance()->stopBackgroundMusic();

			}
			else
			{
				isBgmOn = true;
				bgm_off->setVisible(false);
				SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.OGG");

			}
		}
		//检测游戏信息页面
		if (info->getBoundingBox().containsPoint(t->getLocation()))
		{
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, infoScene::createScene()));
		}
		return false;
	
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener_sound, this);

	return true;
}
void 
OptionScene::backToMainMenu(Ref * r)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, WelcomeScene::createScene()));
}

OptionScene::OptionScene()
{
}


OptionScene::~OptionScene()
{
}
