#ifndef _INFOSCENE_H_
#define _INFOSCENE_H_
#include "cocos2d.h"
class infoScene:public cocos2d::Layer
{
public:
	infoScene();
	~infoScene();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(infoScene);
public:
	void backToMainMenu(Ref * r);
};
#endif

