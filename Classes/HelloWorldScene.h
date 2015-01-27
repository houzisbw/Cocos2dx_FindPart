#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#define V_NUM 4
#define H_NUM 6
#include "cocos2d.h"
#include <vector>
using namespace std;
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void backToMainMenu(cocos2d::Ref* r);

	virtual void update(float dt);//计时方法
	void startTimer();//开始计时
	void endTimer();//结束计时
	void showInit();//游戏结束时显示游戏之前的状态
	void isGameEnd(float dt);//游戏是否结束
	void restartGame(Ref* r);
	void prophetInit();//先知模式初始化：可以看见所有的卡片
	void isProphetWatchOver(float dt);//检查先知游戏观察是否结束
	void isComboLabelArrived(float dt);//检查combol label是否到达目标，然后消失
	void resumeColor(float dt);//恢复combo颜色：白色

	static int bestCombo;//最佳combo数
   
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	string imageName[9];//存放图片的字符串数组 
	void genAllPoints();//生产坐标点，把窗口网格化，每一个网格子放一张图片,水平6个，垂直4个
	PointArray *pointArr;//存放坐标点的数组
	float cardWidth, cardHeight;//卡片尺寸
	void addCard();//添加 卡片
	void addBackCard();//添加卡片背面
	Vector <Sprite*> *cards;
	Vector <Sprite*> *backCards;
	vector <int> tempArrayX; //保存产生过的random number，最后要显示出游戏开始的卡片状态
	vector <int> tempArrayY; //保存产生过的random number，最后要显示出游戏开始的卡片状态
	Sprite * addCards(int index);
	int rightIndex;
	Sprite *lastCard;//上一次点击的卡片
	Sprite *thisCard;
	Sprite *lastBCard;//上次点击的卡片背面图片
	Sprite *thisBCard;
	bool actionRunning;
	Sprite *bgm;
	static int count;
	LabelTTF *label;
	Label *timerLabel;
	Label *newBestLabel;
	Label *prophetCountDown;
	Label *cong;
	Label *record;
	Sprite* t1;
	Sprite* t2;
	bool timerRunning;//计时器是否运行
	long startTime;//游戏开始的时间
	bool isGameOver;//判断游戏是否结束
	bool prophetStart;//先知模式是否开始游戏
	static int prophetCount;//计时器
	double offset;//游戏时间成绩

	//游戏记录数组
	static double timing[3];
	static double prophet[3];
	//combo图标
	Sprite* combo;
	Sprite* multiply;
	//combo数
	int comboCount;
	Label * comboLabel;
	Vector<Sprite*> vec_combo;
	MenuItemImage* rg;


};

#endif // __HELLOWORLD_SCENE_H__
