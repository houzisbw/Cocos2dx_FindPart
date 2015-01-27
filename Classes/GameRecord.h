#ifndef _GAMERECORD_H_
#define _GAMERECORD_H_
#include "cocos2d.h"
class GameRecord:public cocos2d::Layer
{
public:
	GameRecord();
	~GameRecord();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameRecord);
public:
	void backToMainMenu(Ref *r);
	
	cocos2d::Label *tm1;
	cocos2d::Label *tm2;
	cocos2d::Label *tm3;

	cocos2d::Label *ph1;
	cocos2d::Label *ph2;
	cocos2d::Label *ph3;
};
#endif

