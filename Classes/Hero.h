#pragma once
#ifndef _Hero_H_
#define _Hero_H_
#include "cocos2d.h"
USING_NS_CC;

class Hero :public Node{
public:
	
	// ����ͼƬ������Ӣ��
	void InitHeroSprite(char *hero_name, int iLevel);
	// ���ص�ǰӢ��
	Sprite* GetSprite();

	// ���ö�����run_directonΪ����������false����,frameNameΪͼƬ֡����
	void SetAnimation(const char *frameName, float delay, bool run_directon);
	// ֹͣ����
	void StopAnimation();
	// ���𶯻�
	void JumpUpAnimation(const char *name_each, float delay, bool run_directon);
	// ���䶯��
	void JumpDownAnimation(const char *name_each, float delay, bool run_directon);
	// ���䶯������
	void JumpEnd();
	// ��������
	void AttackAnimation(const char *name_each, float delay, bool run_directon);
	// ������������
	void AttackEnd();
	// ��������
	void DeadAnimation(const char *name_each, float delay, bool run_directon);
	// ������������
	void DeadEnd();
	// ���˶���
	void HurtByMonsterAnimation(const char *name_each, float delay, bool run_directon);
	// ���˶�������
	void HurtByMonsterEnd();
	// �ж�Ӣ���Ƿ��˶����˴��ڵ��м�λ��,visibleSizeΪ��ǰ���ڵĴ�С  
	bool JudgePositosn(Size visibleSize);

	bool IsDead;

	// HP & MP ֵ
	float m_iCurrentHp;     //��ǰѪ��
	float m_iTotleHp;		//��Ѫ��
	float m_iCurrentMp;		//��ǰ����
	float m_iTotleMp;		//������

	float percentage;		//�ٷֱ�
	float m_iSpeed;			//�ƶ��ٶ�

	bool m_bIsAction;          // �鿴��ǰ�Ƿ��Ѿ��ڴ����
	bool m_bIsJumping;         // �鿴�Ƿ�����
	bool IsRunning;  // �ж��Ƿ����ܶ���
	bool IsAttack;  // �ж��Ƿ��ڹ�������

	bool IsHurt; // �ж��Ƿ�����

	bool HeroDirecton; // Ӣ���˶��ķ���
	bool m_bCanCrazy; // �ж��Ƿ��ڿ�״̬

	CREATE_FUNC(Hero);
private:
	Sprite* m_HeroSprite; // ����
	char *Hero_name; // ���������ʼ״̬�ľ���ͼƬ����


};


#endif