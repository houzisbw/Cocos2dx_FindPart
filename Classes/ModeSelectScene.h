#ifndef _MODESELECTSCENE_H_
#define _MODESELECTSCENE_H_
#include "cocos2d.h"
class ModeSelectScene:public cocos2d::Layer
{
public:
	ModeSelectScene();
	~ModeSelectScene();
	static cocos2d::Scene* createScene();
	virtual bool init();
	static int level;//��ʾ�ڼ���ģʽ�ı���
	CREATE_FUNC(ModeSelectScene);
	
public:
	void backToMainMenu(Ref* r);

};
#endif
