#ifndef _HOWTOPLAY_H_
#define _HOWTOPLAY_H_
#include "cocos2d.h"
class HowToPlay:public cocos2d::Layer
{
public:
	HowToPlay();
	~HowToPlay();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HowToPlay);
public:
	void backToMainMenu(Ref* r);
	void next(Ref *r);
};
#endif

