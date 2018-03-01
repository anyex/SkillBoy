#include "ActionTool.h"

Animate* ActionTool::animationWithFrameName(const char *each_name, int iloops, float delay)
{
	SpriteFrame* frame = NULL;
	Animation* animation = Animation::create();
	int index = 1;
	do
	{
		String * name = String::createWithFormat("%s%d", each_name, index++);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name->getCString());
		if (frame == NULL)
		{
			break;
		}
		animation->addSpriteFrame(frame);
	} while (true);
	animation->setDelayPerUnit(delay);
	animation->setRestoreOriginalFrame(true);
	Animate* animate = Animate::create(animation);
	return animate;
}

Animate* ActionTool::animationWithFrameAndNum(const char *frameName, int framecount, float delay)
{
	SpriteFrame* frame = NULL;
	Animation* animation = Animation::create();
	for (int index = 1; index <= framecount; index++)
	{
		String * name = String::createWithFormat("%s%d", frameName, index++);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(delay);
	animation->setRestoreOriginalFrame(true);
	Animate* animate = Animate::create(animation);

	/*
	Vector<SpriteFrame*> animFrames;
	char str[20];
	for (int k = 1; k <= framecount; k++)
	{
	sprintf(str, "%s%d.png", frameName, k);
	SpriteFrame *frame = SpriteFrameCache::getInstance()->spriteFrameByName(str);
	animFrames.pushBack(frame);
	}
	return Animate::create(Animation::createWithSpriteFrames(animFrames, delay));*/

	return animate;
}