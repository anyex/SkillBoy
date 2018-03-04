#pragma once
#ifndef _Monster_H_
#define _Monster_H_

#include "cocos2d.h"
//ͷ�ļ����ֻ����������������ͷ�ļ�
class Hero;
class GameMap;
USING_NS_CC;

class Monster :public cocos2d::Node {
public:
	Monster(void);
	~Monster();
	//��������
	int m_iType;//��������
	bool IsRunning;//�ж��Ƿ����ܵĶ���
	bool IsAttack;//�ж��Ƿ��ڹ�������
	bool IsHurt;//�ж��Ƿ������˶���
	bool Isdead;//�ж��Ƿ�����
	bool MonsterDirection;//�����˶�����

	//����
	//����ͼƬ���ƴ�������
	void InitMonsterSprite(char* name, char* a,char* die,char* walk,char* dieLast,int m_iLevel);
	//����Ӣ��
	Sprite* GetSprite();

	//�����߶�������numΪͼƬ��Ŀ��run_dirrectionΪ���鳯��false���ң�name_eachΪname_png��ÿһ��СͼƬ�Ĺ������Ʋ���
	void SetAnimation(CONST char* name_each,bool run_direction,float delay,int iLoops);

	//ֹͣ�߶�����
	void StopAnimation();

	//��������
	void AttackAnimation(const char* name_each, bool run_direction, float delay, int iLoops);
	void AttackEnd();

	//���˶���
	void HurtAnimation(const char* name_each, bool run_direction, float delay, int iLoops);
	//���˶�������
	void HurtEnd();

	//��������
	void DeadAnimation(const char* name_each, bool run_direction, float delay,int iLoops);
	void DeadEnd();

	//����������˸����
	void BlinkEnd();

	//�ڿ��ӷ�Χ�ڣ��������Ӣ���˶�
	void FollowRun(Hero* m_hero, GameMap* m_map);
	//�ж��Ƿ񹥻�
	void JudegeAttack(float dt);

	//������������Ӣ��
	void StartListen(Hero* m_hero, GameMap* m_map);
	//����������ÿ�������⣬���������ľ���
	void updateMonster(float delta);

	//���º��������Ӣ���ڿ��ӷ�Χ�ڣ����ϴ���
	void update(float delta);

	CREATE_FUNC(Monster);

private:
	Sprite* m_MonsterSprite;//���ﾫ��
	char* Monster_name;//�����ʼ״̬�ľ���ͼƬ����
	char* Monster_a;//���﹥��֡
	char* Monster_die;//����֡
	char* Monster_walk;//����֡
	char* Die_name;

	Hero* my_hero;//��ǰӢ��
	GameMap* my_map;//��ǰ��ͼ
	float dis;//��ǰ�����Ӣ�۵ľ���
	int m_iHP;



};

#endif