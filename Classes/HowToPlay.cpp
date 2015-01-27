#include "HowToPlay.h"
#include "WelcomeScene.h"
#include "ModeSelectScene.h"
USING_NS_CC;

Scene*
HowToPlay::createScene()
{
	auto scene = Scene::create();
	auto layer = HowToPlay::create();
	scene->addChild(layer);
	return scene;
}
bool
HowToPlay::init()
{
	Layer::init();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* bg = Sprite::create("select_bg.jpg");
	bg->setAnchorPoint(Point(0, 0));
	bg->setPosition(Point(0, 0));
	addChild(bg);

	//回到主菜单
	auto backToMenu = MenuItemImage::create("forward_arrow.png", "forward_arrow.png", CC_CALLBACK_1(HowToPlay::backToMainMenu, this));
	backToMenu->setScale(1.8);
	auto btm = Menu::create(backToMenu, NULL);
	btm->setPosition(80, visibleSize.height - 60);
	addChild(btm, 2);
	//下一步
	auto next = MenuItemImage::create("next.png", "next.png", CC_CALLBACK_1(HowToPlay::next, this));
	next->setScale(1.8);
	auto next1 = Menu::create(next, NULL);
	next1->setPosition(visibleSize.width-100, 100);
	auto st = ScaleBy::create(1.0f, 1.5);
	auto seq = Sequence::create(st, st->reverse(), NULL);
	auto repeat = RepeatForever::create(seq);
	next->runAction(repeat);
	addChild(next1, 2);

	//问号
	auto qm = Sprite::create("qm.png");
	qm->setPosition(visibleSize.width / 2 - 260, visibleSize.height - 150);
	qm->setScale(1.2);
	addChild(qm);
	//玩法
	auto title = Label::createWithTTF("How  to  play", "fonts/Alien_Resurrection.ttf", 40);
	title->setPosition(visibleSize.width / 2 + 50, visibleSize.height - 150);
	addChild(title);

	//添加卡片说明	
	for (int i = 1; i <= 2;i++)
	for (int j = 1; j <= 3; j++)
	{
		auto card = Sprite::create("unknown.png");
		card->setPosition(130 + j*120, 80+i*120);
		card->setScale(0.2);
		addChild(card);
	}
	auto same1 = Sprite::create("h.png");
	same1->setScale(1);
	same1->setPosition(130 + 1* 120, 80 + 1* 120);
	addChild(same1);

	auto same2 = Sprite::create("h.png");
	same2->setScale(1);
	same2->setPosition(130 + 3 * 120, 80 + 1 * 120);
	addChild(same2);

	//箭头说明
	auto up_arrow = Sprite::create("upload.png");
	up_arrow->setScale(1.5);
	up_arrow->setPosition(130 + 1 * 120, 110);
	addChild(up_arrow);

	auto up_arrow1 = Sprite::create("upload.png");
	up_arrow1->setScale(1.5);
	up_arrow1->setPosition(130 + 3 * 120, 110);
	addChild(up_arrow1);

	auto minus = Sprite::create("minus.png");
	minus->setScale(1.2);
	minus->setPosition(130 + 1 * 120 + 12, 90);
	addChild(minus);

	auto minus1 = Sprite::create("minus.png");
	minus1->setScale(1.2);
	minus1->setPosition(130 + 3 * 120 - 12, 90);
	addChild(minus1);
	
	auto title2 = Label::createWithTTF("same", "fonts/Alien_Resurrection.ttf", 30);
	title2->setPosition(130 + 1 * 120 + 120, 90);
	addChild(title2);

	auto title3 = Label::createWithTTF("clean the", "fonts/Alien_Resurrection.ttf", 22);
	title3->setPosition(130 + 3 * 120+190, 360);
	addChild(title3);

	auto title4 = Label::createWithTTF("matrix by", "fonts/Alien_Resurrection.ttf", 22);
	title4->setPosition(130 + 3 * 120 + 190, 320);
	addChild(title4);
	
	auto title5 = Label::createWithTTF("removing", "fonts/Alien_Resurrection.ttf", 22);
	title5->setPosition(130 + 3 * 120 + 190, 280);
	addChild(title5);
	
	auto title6 = Label::createWithTTF("the same", "fonts/Alien_Resurrection.ttf", 28);
	title6->setPosition(130 + 3 * 120 + 190, 220);
	title6->setColor(Color3B::YELLOW);
	addChild(title6);

	auto title7 = Label::createWithTTF("square", "fonts/Alien_Resurrection.ttf", 22);
	title7->setPosition(130 + 3 * 120 + 190, 160);
	addChild(title7);

	return true;
}
void 
HowToPlay::backToMainMenu(Ref* r)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, WelcomeScene::createScene()));
}
void 
HowToPlay::next(Ref *r)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, ModeSelectScene::createScene()));
}
HowToPlay::HowToPlay()
{
}


HowToPlay::~HowToPlay()
{
}
