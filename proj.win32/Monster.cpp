#include "Monster.h"
#include "ActionTool.h"
#include "Hero.h"
#include "GameMap.h"

USING_NS_CC;

Monster::Monster()
{
	IsRunning = false;//�����ܶ�
	MonsterDirection = true;//�����˶�
	Monster_name = NULL;
	IsAttack = false;
	my_hero = NULL;//��ǰӢ��
	my_map = NULL;//��ǰ��ͼ

	dis = 10000;
	IsHurt = false;
	Isdead = false;

}

Monster::~Monster()
{

}

Sprite* Monster::GetSprite()
{
	return m_MonsterSprite;
}

void Monster::InitMonsterSprite(char* name, char* a,char*die, char* walk, char* dieLast, int m_iLevel) {
	Monster_name = name;
	Monster_a = a;
	Monster_walk = walk;
	Monster_die = die;
	Die_name = dieLast;

	m_iHP = 100 * (1 + 0.3*m_iLevel);
	this->m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	this->addChild(m_MonsterSprite);

}

void Monster::SetAnimation(const char* name_each, bool run_direction, float delay, int iLoops) {
	//���ù��﷽��
	if (MonsterDirection	!=	run_direction)
	{
		MonsterDirection = run_direction;
		m_MonsterSprite->setFlippedX(run_direction);
	}

	if (IsRunning||IsAttack||IsHurt||Isdead)
	{
		return;
	}

	Animate* action = ActionTool::animationWithFrameName(name_each, iLoops, delay);
	m_MonsterSprite->runAction(RepeatForever::create(action));
	CCLog("Walk����");
	IsRunning = true;



};

void Monster::StopAnimation() {
	if (!IsRunning)
	{
		return;
	}

	m_MonsterSprite->stopAllActions();//ֹͣ��ǰ��������ж���

	//�ָ�����ԭ���ĳ�ʼ����ͼ
	this->removeChild(m_MonsterSprite, true);
	m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Monster_name));//�ָ�����ԭ������ͼ
	m_MonsterSprite->setFlippedX(MonsterDirection);
	this->addChild(m_MonsterSprite);
	IsRunning = false;


}

//����
void Monster::AttackAnimation(const char* name_each, bool run_direction, float delay, int iLoops) {
	//�����߶������������˻��Ѿ��������ͷ���
	if (IsRunning||IsAttack||IsHurt||Isdead)
	{
		return;
	}
	//��������֡����
	Animate* action = ActionTool::animationWithFrameName(name_each, 1, delay);
	//�����ص��������������������AttackEnd()
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::AttackEnd));

	//������������
	m_MonsterSprite->runAction(Sequence::create(action,callFunc,NULL));

	IsAttack = true;
}

void Monster::AttackEnd() {
	//�ָ�����Ϊԭ���ĳ�ʼ����ͼ
	this->removeChild(m_MonsterSprite, true);//��ԭ���ľ���ɾ����
	m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Monster_name));
	m_MonsterSprite->setFlippedX(MonsterDirection);
	addChild(m_MonsterSprite);
	IsAttack = false;
}
// ����
void Monster::HurtAnimation(const char *name_each, bool run_directon, float delay, int iLoops)
{
	if (IsHurt || Isdead)
		return;
	//��������
	if (IsRunning || IsAttack)
	{
		m_MonsterSprite->stopAllActions();// ��ǰ����ֹͣ���ж���
										  // �ָ�����ԭ���ĳ�ʼ����ͼ 
		this->removeChild(m_MonsterSprite, true);// ��ԭ���ľ���ɾ����
		m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Monster_name));//�ָ�����ԭ������ͼ����
		m_MonsterSprite->setFlipX(MonsterDirecton);
		this->addChild(m_MonsterSprite);
		IsRunning = false;
		IsAttack = false;
	}

	Animate* action = ActionTool::animationWithFrameName(name_each, 1, delay);
	// �����ص����������˶�����������HurtEnd()
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::HurtEnd));
	// ������������
	ActionInterval* hurtackact = Sequence::create(action, callFunc, NULL);

	m_MonsterSprite->runAction(hurtackact);
	IsHurt = true;
}
// ���˽���
void Monster::HurtEnd()
{
	IsHurt = false;


	if (my_hero->m_bCanCrazy)
	{
		m_iHP -= 100;
	}
	else
		m_iHP -= 30;

	if (m_iHP <= 0)
	{
		//���Ź�������
		DeadAnimation(Monster_die, MonsterDirection, 0.1f, 1.0f);
	}
	log("Monster Hurt");
}
// ����
void Monster::DeadAnimation(const char *name_each, bool run_directon, float delay, int iLoops)
{
	Isdead = true;
	// ��������
	Animate* action = ActionTool::animationWithFrameName(name_each, 1, delay);
	// �����ص��������������������deadact()
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::DeadEnd));
	// ������������
	CCActionInterval* deadact = Sequence::create(action, callFunc, NULL);
	m_MonsterSprite->runAction(deadact);
	if (my_hero->m_iCurrentMp < 100)
	{
		my_hero->m_iCurrentMp = (my_hero->m_iCurrentMp + 50);
		if (my_hero->m_iCurrentMp > 100)
		{
			my_hero->m_iCurrentMp = 100;
		}
	}
}
// ��������
void Monster::DeadEnd()
{
	// �ָ�����������
	this->removeChild(m_MonsterSprite, true);  // ��ԭ���ľ���ɾ����
	m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Die_name)); // �ָ�����������
	m_MonsterSprite->setFlipX(MonsterDirection);
	this->addChild(m_MonsterSprite);

	// ��������������
	Blink* blinkact = Blink::create(3, 3);//3�ǳ���ʱ�䣬6�����Ĵ���

										  // �����ص���������˸���������BlinkEnd()
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::BlinkEnd));
	// ������������
	CCActionInterval* deadact = Sequence::create(blinkact, callFunc, NULL);
	m_MonsterSprite->runAction(deadact);

}
// ��˸����
void Monster::BlinkEnd()
{
	this->removeAllChildren();//�ѹ����Ѫ����ɾ����;
}

void Monster::FollowRun(Hero* m_hero, GameMap* m_map)
{

	// �õ�����x�ľ���,�ǵù��������Ҫ���ϵ�ͼ��
	float x = m_hero->getPositionX() - (this->getPositionX() + my_map->getPositionX());

	// �ȼ�������Ӣ�۵ľ���
	dis = fabs(x);

	if (x >= 1280)// ��������Ӣ�۾��볬��1280
		return;
	if (dis <= 120)// �ڹ��﹥����Χ�ڣ�����ֹͣ�ƶ�
	{
		this->StopAnimation();// ֹͣ�ܶ�
		scheduleOnce(schedule_selector(Monster::JudegeAttack), 2.5f); //��һ���ĸ����ж����Ƿ��������
		//scheduleOnce�����һ��ֻ����һ�ε�ѡ������2.5��ִ��һ��
		return;
	}

	if (x < -100)// �жϹ���������Ӣ�۵ľ���
	{
		MonsterDirection = false;
		m_MonsterSprite->setFlippedX(MonsterDirection);// ���÷���setFlippedX��ת���飬������X����Գ�
		if (IsAttack)
			return;
		this->SetAnimation(Monster_walk, MonsterDirection, 0.1f, -1);// ���Ŷ���
		this->setPosition(this->getPositionX() - 1.5, this->getPositionY());// ������Ӣ���ƶ�
	}
	else if (x > 100)
	{

		MonsterDirection = true;
		m_MonsterSprite->setFlippedX(MonsterDirection);// ���÷���
		if (IsAttack)
			return;
		this->SetAnimation(Monster_walk, MonsterDirection, 0.1f, -1);// ���Ŷ���
		this->setPosition(this->getPositionX() + 1.5, this->getPositionY());
	}

}
void Monster::JudegeAttack(float dt)
{

	this->AttackAnimation(Monster_a, MonsterDirection, 0.08f, 0);
}

// ��������
void Monster::StartListen(Hero* m_hero, GameMap* m_map)
{
	my_hero = m_hero;
	my_map = m_map;
	this->schedule(schedule_selector(Monster::updateMonster), 1.0f);// ÿ��1��������
	this->scheduleUpdate();// Ӣ��һ��������ӷ�Χ������׷��Ӣ�۴�
}

// ��������,ÿ��1������
void Monster::updateMonster(float delta)
{
	// ���������ͷ���
	if (Isdead || my_hero->IsDead)
		return;
	// �õ�����x�ľ���,�ǵù��������Ҫ���ϵ�ͼ��
	float x = my_hero->getPositionX() - (this->getPositionX() + my_map->getPositionX());

	// �ȼ�������Ӣ�۵ľ���
	dis = fabs(x);

}
void Monster::update(float delta)
{
	// ���������ͷ���
	if (Isdead || my_hero->IsDead)
		return;
	if (dis < 1280 && my_hero->IsDead == false)// ��Ӣ�������Ŀ��ӷ�Χ�ڣ�����׷��Ӣ��
		FollowRun(my_hero, my_map);
}
