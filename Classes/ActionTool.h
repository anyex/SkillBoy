#pragma once
#ifndef _ActionTool_H_
#define _ActionTool_H_

#include "cocos2d.h"
USING_NS_CC;

class ActionTool
{
public:
	//static 类型的方法可以直接调用，不需要通过实例化对象

	//创建帧动画
	static Animate* animationWithFrameName(const char *each_name, int iloops, float delay);
	static Animate* animationWithFrameAndNum(const char *frameName, int num, float delay);
	

};

#endif