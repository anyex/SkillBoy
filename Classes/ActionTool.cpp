#include "ActionTool.h"

//参数 each_name :帧图片的名字
//     iloops:循环次数
//     delay:帧间隔时间
Animate* ActionTool::animationWithFrameName(const char *each_name, int iloops, float delay)
{
	SpriteFrame* frame = NULL;
	Animation* animation = Animation::create();//创建动画
	int index = 1;
	do
	{
		String * name = String::createWithFormat("%s%d", each_name, index++);//生成图片帧的名字
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name->getCString());//创建帧缓存
		if (frame == NULL)//当读取完毕，结束循环
		{
			break;
		}
		animation->addSpriteFrame(frame);//将帧缓存添加到动画
	} while (true);
	animation->setDelayPerUnit(delay);//设置帧时间间隔
	animation->setRestoreOriginalFrame(true);//当动画结束后返回到原始帧
	Animate* animate = Animate::create(animation);//创建动作
	return animate;//将动作返回
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