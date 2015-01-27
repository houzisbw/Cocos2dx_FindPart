#include "ArcadeDesciptionScene.h"
#include "ModeSelectScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene*
ArcadeDesciptionScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ArcadeDesciptionScene::create();
	scene->addChild(layer);
	return scene;

}
bool
ArcadeDesciptionScene::init()
{
	Layer::init();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* bg = Sprite::create("select_bg.jpg");
	bg->setAnchorPoint(Point(0, 0));
	bg->setPosition(Point(0, 0));
	addChild(bg);

	//回到主菜单
	auto backToMenu = MenuItemImage::create("forward_arrow.png", "forward_arrow.png", CC_CALLBACK_1(ArcadeDesciptionScene::backToMainMenu, this));
	backToMenu->setScale(1.8);
	auto btm = Menu::create(backToMenu, NULL);
	btm->setPosition(80, visibleSize.height - 80);
	addChild(btm, 2);


	
	//休闲模式
	if (ModeSelectScene::level == 1)
	{
		//游戏说明
		auto folder = Sprite::create("folder.png");
		folder->setPosition(visibleSize.width / 2 - 170, visibleSize.height - 200);
		folder->setScale(2.0);
		addChild(folder);
		
		auto title = Label::createWithTTF("Arcade", "fonts/Alien_Resurrection.ttf", 40);
		title->setColor(Color3B(255, 255, 0));
		title->setPosition(visibleSize.width / 2 + 50, visibleSize.height - 200);
		addChild(title);

		auto title1 = Label::createWithTTF("Play   at   will", "fonts/Alien_Resurrection.ttf", 30);
		title1->setPosition(visibleSize.width / 2 + 10, visibleSize.height - 350);
		addChild(title1);

		auto title2 = Label::createWithTTF("No    pressure", "fonts/Alien_Resurrection.ttf", 30);
		title2->setPosition(visibleSize.width / 2, visibleSize.height - 400);
		addChild(title2);

		auto pen = Sprite::create("edit.png");
		pen->setPosition(visibleSize.width / 2 + 190, visibleSize.height - 440);
		addChild(pen);
	}
	else if (ModeSelectScene::level == 2)
	{
		//游戏说明
		auto folder = Sprite::create("folder.png");
		folder->setPosition(visibleSize.width / 2 - 170, visibleSize.height - 200);
		folder->setScale(2.0);
		addChild(folder);

		auto title = Label::createWithTTF("Timing", "fonts/Alien_Resurrection.ttf", 40);
		title->setColor(Color3B(255, 255, 0));
		title->setPosition(visibleSize.width / 2 + 50, visibleSize.height - 200);
		addChild(title);

		auto title1 = Label::createWithTTF("Play with timer", "fonts/Alien_Resurrection.ttf", 30);
		title1->setPosition(visibleSize.width / 2 + 10, visibleSize.height - 350);
		addChild(title1);

		auto title2 = Label::createWithTTF("try your best", "fonts/Alien_Resurrection.ttf", 30);
		title2->setPosition(visibleSize.width / 2, visibleSize.height - 400);
		addChild(title2);

		auto pen = Sprite::create("edit.png");
		pen->setPosition(visibleSize.width / 2 + 220, visibleSize.height - 450);
		addChild(pen);
	}
	else if (ModeSelectScene::level == 3)
	{
		
		//游戏说明
		auto folder = Sprite::create("folder.png");
		folder->setPosition(visibleSize.width / 2 - 190, visibleSize.height - 150);
		folder->setScale(2.0);
		addChild(folder);
		
		auto title = Label::createWithTTF("PROPHET", "fonts/Alien_Resurrection.ttf", 40);
		title->setColor(Color3B(255, 255, 0));
		title->setPosition(visibleSize.width / 2 + 50, visibleSize.height - 150);
		addChild(title);

		auto title1 = Label::createWithTTF("watch   before ", "fonts/Alien_Resurrection.ttf", 30);
		title1->setPosition(visibleSize.width / 2 + 10, visibleSize.height - 230);
		addChild(title1);

		auto title2 = Label::createWithTTF("you  play      rem", "fonts/Alien_Resurrection.ttf", 30);
		title2->setPosition(visibleSize.width / 2, visibleSize.height - 280);
		addChild(title2);

		auto title3 = Label::createWithTTF("ember  as  much  ", "fonts/Alien_Resurrection.ttf", 30);
		title3->setPosition(visibleSize.width / 2+10, visibleSize.height - 330);
		addChild(title3);
		
		auto title4 = Label::createWithTTF("as  you  can  ", "fonts/Alien_Resurrection.ttf", 30);
		title4->setPosition(visibleSize.width / 2 + 10, visibleSize.height - 380);
		addChild(title4);

		auto icon = Sprite::create("layer.png");
		icon->setScale(1.3);
		icon->setPosition(visibleSize.width / 2 -180, visibleSize.height - 490);
		addChild(icon);

		auto combo = Label::createWithTTF("     :  COMBO", "fonts/pirulenrg.ttf", 50);
		combo->setPosition(visibleSize.width / 2, visibleSize.height - 490);
		addChild(combo);


	}

	//开始游戏按钮
	auto start = MenuItemImage::create("left_t.png", "left_t.png", CC_CALLBACK_1(ArcadeDesciptionScene::startGame, this));
	start->setScale(2);
	auto menu_start = Menu::create(start, NULL);
	menu_start->setAnchorPoint(Point(0, 0));
	menu_start->setPosition(visibleSize.width -80, 80);
	addChild(menu_start);

	auto st = ScaleBy::create(1.0f, 1.5);
	auto seq = Sequence::create(st, st->reverse(), NULL);
	auto repeat = RepeatForever::create(seq);
	menu_start->runAction(repeat);


	return true;
}
void 
ArcadeDesciptionScene::backToMainMenu(Ref* r)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, ModeSelectScene::createScene()));
}
void
ArcadeDesciptionScene::startGame(Ref* r)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, HelloWorld::createScene()));
}

ArcadeDesciptionScene::ArcadeDesciptionScene()
{
}


ArcadeDesciptionScene::~ArcadeDesciptionScene()
{
}
