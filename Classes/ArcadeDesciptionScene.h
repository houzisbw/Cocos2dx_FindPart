#ifndef _ARCADEDESCIPTIONSCENE_H_
#define _ARCADEDESCIPTIONSCENE_H_
#include "cocos2d.h"
class ArcadeDesciptionScene:public cocos2d::Layer
{
public:
	ArcadeDesciptionScene();
	~ArcadeDesciptionScene();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ArcadeDesciptionScene);
public:
	void backToMainMenu(Ref* r);
	void startGame(Ref* r);
};
#endif

