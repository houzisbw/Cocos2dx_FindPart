#ifndef _WELCOMESCENE_H_
#define _WELCOMESCENE_H_
#include "cocos2d.h"
class WelcomeScene:public cocos2d::Layer
{
public:
	WelcomeScene();
	~WelcomeScene();
	static cocos2d::Scene* createScene();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	//callback function
	void gameStart(Ref* r);
	void gameOption(Ref* r);
	void gameHelp(Ref* r);
	void gameOver(Ref* r);
	bool isSaveFile();
	//·ÖÊý¼ÇÂ¼
	static double highestScoreTiming;
	static double highestScoreProphet;
	static double SecondhighestScoreTiming;
	static double SecondhighestScoreProphet;
	static double ThirdhighestScoreTiming;
	static double ThirdhighestScoreProphet;

	CREATE_FUNC(WelcomeScene);
};
#endif

