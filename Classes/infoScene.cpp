#include "infoScene.h"
#include "OptionScene.h"
USING_NS_CC;

Scene*
infoScene::createScene()
{
	auto scene = Scene::create();
	auto layer = infoScene::create();
	scene->addChild(layer);
	return scene;
}
bool
infoScene::init()
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
	auto backToMenu = MenuItemImage::create("forward_arrow.png", "forward_arrow.png", CC_CALLBACK_1(infoScene::backToMainMenu, this));
	backToMenu->setScale(1.5);
	auto btm = Menu::create(backToMenu, NULL);
	btm->setPosition(80, visibleSize.height - 80);
	addChild(btm, 2);

	//右下角装饰物
	auto board = Sprite::create("board.png");
	board->setScale(1.5);
	board->setPosition(visibleSize.width - 80, 80);
	addChild(board);

	//游戏信息i图标
	auto info = Sprite::create("info_circle.png");
	info->setScale(2);
	info->setPosition(visibleSize.width/2-195, visibleSize.height/2);
	info->setOpacity(0);
	addChild(info);

	auto fi1 = FadeIn::create(3);
	auto mt1 = MoveTo::create(0.5, Vec2(visibleSize.width / 2 - 195, visibleSize.height / 2 +160));
	auto seq1 = Sequence::create(fi1, mt1, NULL);
	info->runAction(seq1);

	//about
	auto about = Label::createWithTTF("about", "fonts/Alien_Resurrection.ttf", 60);
	about->setPosition(visibleSize.width / 2 + 60, visibleSize.height / 2);
	about->setOpacity(0);
	addChild(about);

	auto fi2 = FadeIn::create(3);
	auto mt2 = MoveTo::create(0.5, Vec2(visibleSize.width / 2 +60, visibleSize.height / 2 + 160));
	auto seq2 = Sequence::create(fi2, mt2, NULL);
	about->runAction(seq2);

	/////////////////////3.5秒延时了/////////////////

	//4条about
	auto b1 = Label::createWithTTF("Engine  :   cocos2d-x", "fonts/ethnocentricrg.ttf", 30);
	b1->setAnchorPoint(Point(0,0));
	b1->setOpacity(0);
	b1->setPosition(visibleSize.width / 2 - 220, visibleSize.height / 2);
	ActionInterval * delaytime1 = CCDelayTime::create(3.5);
	auto fb1 = FadeIn::create(0.5);
	auto seq_b1 = Sequence::create(delaytime1, fb1, NULL);
	b1->runAction(seq_b1);
	addChild(b1);

	auto b2 = Label::createWithTTF("IDE         :   VS        2013", "fonts/ethnocentricrg.ttf", 30);
	b2->setAnchorPoint(Point(0, 0));
	b2->setOpacity(0);
	b2->setPosition(visibleSize.width / 2 - 220, visibleSize.height / 2-60);
	ActionInterval * delaytime2 = CCDelayTime::create(4.0);
	auto fb2 = FadeIn::create(0.5);
	auto seq_b2 = Sequence::create(delaytime2, fb2, NULL);
	b2->runAction(seq_b2);
	addChild(b2);

	auto b3 = Label::createWithTTF("code    :    2500 lines", "fonts/ethnocentricrg.ttf", 30);
	b3->setAnchorPoint(Point(0, 0));
	b3->setOpacity(0);
	b3->setPosition(visibleSize.width / 2 - 220, visibleSize.height / 2 - 120);
	ActionInterval * delaytime3 = CCDelayTime::create(4.5);
	auto fb3 = FadeIn::create(0.5);
	auto seq_b3 = Sequence::create(delaytime3, fb3, NULL);
	b3->runAction(seq_b3);
	addChild(b3);

	auto b4 = Label::createWithTTF("time     :    1          week", "fonts/ethnocentricrg.ttf", 30);
	b4->setAnchorPoint(Point(0, 0));
	b4->setOpacity(0);
	b4->setPosition(visibleSize.width / 2 - 220, visibleSize.height / 2 - 180);
	ActionInterval * delaytime4 = CCDelayTime::create(5.0);
	auto fb4 = FadeIn::create(0.5);
	auto seq_b4 = Sequence::create(delaytime4, fb4, NULL);
	b4->runAction(seq_b4);
	addChild(b4);








	return true;
}
void 
infoScene::backToMainMenu(Ref * r)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, OptionScene::createScene()));
}

infoScene::infoScene()
{
}


infoScene::~infoScene()
{
}
