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

	virtual void update(float dt);//��ʱ����
	void startTimer();//��ʼ��ʱ
	void endTimer();//������ʱ
	void showInit();//��Ϸ����ʱ��ʾ��Ϸ֮ǰ��״̬
	void isGameEnd(float dt);//��Ϸ�Ƿ����
	void restartGame(Ref* r);
	void prophetInit();//��֪ģʽ��ʼ�������Կ������еĿ�Ƭ
	void isProphetWatchOver(float dt);//�����֪��Ϸ�۲��Ƿ����
	void isComboLabelArrived(float dt);//���combol label�Ƿ񵽴�Ŀ�꣬Ȼ����ʧ
	void resumeColor(float dt);//�ָ�combo��ɫ����ɫ

	static int bestCombo;//���combo��
   
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	string imageName[9];//���ͼƬ���ַ������� 
	void genAllPoints();//��������㣬�Ѵ������񻯣�ÿһ�������ӷ�һ��ͼƬ,ˮƽ6������ֱ4��
	PointArray *pointArr;//�������������
	float cardWidth, cardHeight;//��Ƭ�ߴ�
	void addCard();//��� ��Ƭ
	void addBackCard();//��ӿ�Ƭ����
	Vector <Sprite*> *cards;
	Vector <Sprite*> *backCards;
	vector <int> tempArrayX; //�����������random number�����Ҫ��ʾ����Ϸ��ʼ�Ŀ�Ƭ״̬
	vector <int> tempArrayY; //�����������random number�����Ҫ��ʾ����Ϸ��ʼ�Ŀ�Ƭ״̬
	Sprite * addCards(int index);
	int rightIndex;
	Sprite *lastCard;//��һ�ε���Ŀ�Ƭ
	Sprite *thisCard;
	Sprite *lastBCard;//�ϴε���Ŀ�Ƭ����ͼƬ
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
	bool timerRunning;//��ʱ���Ƿ�����
	long startTime;//��Ϸ��ʼ��ʱ��
	bool isGameOver;//�ж���Ϸ�Ƿ����
	bool prophetStart;//��֪ģʽ�Ƿ�ʼ��Ϸ
	static int prophetCount;//��ʱ��
	double offset;//��Ϸʱ��ɼ�

	//��Ϸ��¼����
	static double timing[3];
	static double prophet[3];
	//comboͼ��
	Sprite* combo;
	Sprite* multiply;
	//combo��
	int comboCount;
	Label * comboLabel;
	Vector<Sprite*> vec_combo;
	MenuItemImage* rg;


};

#endif // __HELLOWORLD_SCENE_H__
