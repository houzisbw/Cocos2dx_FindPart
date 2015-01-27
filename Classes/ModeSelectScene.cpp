#include "ModeSelectScene.h"
#include "WelcomeScene.h"
#include "HelloWorldScene.h"
#include "ArcadeDesciptionScene.h"
#include "HowToPlay.h"
USING_NS_CC;

Scene*
ModeSelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ModeSelectScene::create();
	scene->addChild(layer);
	return scene;

}
bool
ModeSelectScene::init()
{
	Layer::init();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite * bg = Sprite::create("select_bg.jpg");
	bg->setAnchorPoint(Point(0, 0));
	bg->setPosition(Point(0, 0));
	this->addChild(bg);

	//回到主菜单
	auto backToMenu = MenuItemImage::create("forward_arrow.png", "forward_arrow.png", CC_CALLBACK_1(ModeSelectScene::backToMainMenu, this));
	backToMenu->setScale(1.8);
	auto btm = Menu::create(backToMenu, NULL);
	btm->setPosition(80, visibleSize.height - 80);
	addChild(btm, 2);
		
	//右下角装饰物
	auto list = Sprite::create("list.png");
	list->setScale(1.5);
	list->setPosition(visibleSize.width-100,100);
	addChild(list);

	///////////////模式1
	//特别说明，必须用下面这个函数来使用自定义字体，而且fonts里的字体还要安装才行,不能用label：：create来创建
	auto title = Label::createWithTTF("GAME  MODE","fonts/Alien_Resurrection.ttf",50);
	title->setPosition(visibleSize.width/2, visibleSize.height-150);
	addChild(title);

	auto icon1 = Sprite::create("right_t.png");
	icon1->setScale(1.3);
	icon1->setPosition(visibleSize.width / 2 -160, visibleSize.height - 300);
	addChild(icon1);

	auto icon2 = Sprite::create("left_t.png");
	icon2->setScale(1.3);
	icon2->setPosition(visibleSize.width / 2 +170, visibleSize.height - 300);
	addChild(icon2);

	auto level1 = Label::createWithTTF("ARCADE", "fonts/Alien_Resurrection.ttf", 30);
	level1->setPosition(visibleSize.width / 2+10 , visibleSize.height - 300);
	addChild(level1);

	//利用label来作为事件侦听器的触发，不用menu
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = [=](Touch*t ,Event*e){
	
		if (level1->getBoundingBox().containsPoint(t->getLocation()))
		{
			level = 1;//第一种模式 : 休闲模式
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, ArcadeDesciptionScene::createScene()));
		}
	
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);
	
	// 模式2
	auto icon3 = Sprite::create("right_t.png");
	icon3->setScale(1.3);
	icon3->setPosition(visibleSize.width / 2 - 160, visibleSize.height - 390);
	addChild(icon3);

	auto icon4 = Sprite::create("left_t.png");
	icon4->setScale(1.3);
	icon4->setPosition(visibleSize.width / 2 + 170, visibleSize.height - 390);
	addChild(icon4);

	auto level2 = Label::createWithTTF("TiMiNG", "fonts/Alien_Resurrection.ttf", 30);
	level2->setPosition(visibleSize.width / 2 + 10, visibleSize.height - 390);
	addChild(level2);

	//利用label来作为事件侦听器的触发，不用menu
	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = [=](Touch*t, Event*e){

		if (level2->getBoundingBox().containsPoint(t->getLocation()))
		{
			level = 2;//第一种模式 : 休闲模式
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, ArcadeDesciptionScene::createScene()));
		}

		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, this);

	//模式3
	auto icon5 = Sprite::create("right_t.png");
	icon5->setScale(1.3);
	icon5->setPosition(visibleSize.width / 2 - 160, visibleSize.height - 480);
	addChild(icon5);

	auto icon6 = Sprite::create("left_t.png");
	icon6->setScale(1.3);
	icon6->setPosition(visibleSize.width / 2 + 170, visibleSize.height - 480);
	addChild(icon6);

	auto level3 = Label::createWithTTF("PROPHET", "fonts/Alien_Resurrection.ttf", 30);
	level3->setPosition(visibleSize.width / 2 + 10, visibleSize.height - 480);
	addChild(level3);

	//利用label来作为事件侦听器的触发，不用menu
	auto listener3 = EventListenerTouchOneByOne::create();
	listener3->onTouchBegan = [=](Touch*t, Event*e){

		if (level3->getBoundingBox().containsPoint(t->getLocation()))
		{
			level = 3;//第一种模式 : 休闲模式
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, ArcadeDesciptionScene::createScene()));
		}

		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener3, this);

	return true;
}
void 
ModeSelectScene::backToMainMenu(Ref* r)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, HowToPlay::createScene()));
}
ModeSelectScene::ModeSelectScene()
{
}

int ModeSelectScene::level = 1;//必须初始化，否则出现无法解析的外部命令的错误
ModeSelectScene::~ModeSelectScene()
{
}
