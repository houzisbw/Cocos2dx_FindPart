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
	//�ص����˵�
	auto backToMenu = MenuItemImage::create("forward_arrow.png", "forward_arrow.png", CC_CALLBACK_1(OptionScene::backToMainMenu, this));
	backToMenu->setScale(1.5);
	auto btm = Menu::create(backToMenu, NULL);
	btm->setPosition(80, visibleSize.height - 80);
	addChild(btm, 2);

	//���½�װ����
	auto cong = Sprite::create("cogs.png");
	cong->setScale(1.5);
	cong->setPosition(visibleSize.width-80,80);
	addChild(cong);

	//��Ϸoption����
	auto title = Label::createWithTTF("Game    OPTion", "fonts/Alien_Resurrection.ttf", 45);
	title->setPosition(visibleSize.width / 2, visibleSize.height - 230);
	addChild(title);

	//��Ϸ��Ϣ
	auto info = Sprite::create("info.png");
	info->setScale(1.5);
	info->setPosition(visibleSize.width / 2+250, visibleSize.height - 360);
	auto st = ScaleBy::create(1.0f, 1.3);
	auto seq = Sequence::create(st, st->reverse(), NULL);
	auto repeat = RepeatForever::create(seq);
	info->runAction(repeat);
	addChild(info);

	//��Ϸ��Ч
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

	//��Ϸ�������ֿ�
	auto bgm_on = Sprite::create("bgm_on.png");
	bgm_on->setScale(1.8);
	bgm_on->setPosition(visibleSize.width / 2 , visibleSize.height - 360);
	addChild(bgm_on);
	//��Ϸ�������ֹ�
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

	//����رջ����Ϸ��Ч
	auto listener_sound = EventListenerTouchOneByOne::create();
	listener_sound->onTouchBegan = [=](Touch*t,Event*e){
	
		//�����Ϸ��Ч
		if (effect_on->getBoundingBox().containsPoint(t->getLocation()))
		{
			//�����Ч�򿪣���ر�֮
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
		//�����Ϸ��������
		if (bgm_on->getBoundingBox().containsPoint(t->getLocation()))
		{
			//�����Ч�򿪣���ر�֮
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
		//�����Ϸ��Ϣҳ��
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
