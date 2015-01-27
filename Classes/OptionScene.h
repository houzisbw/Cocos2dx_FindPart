#ifndef _OPTIONSCENE_H_
#define _OPTIONSCENE_H_
#include "cocos2d.h"
class OptionScene:public cocos2d::Layer
{
public:
	OptionScene();
	~OptionScene();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(OptionScene);
	static bool isSoundOn;
	static bool isBgmOn;
public:
	void backToMainMenu(Ref * r);
};
#endif

