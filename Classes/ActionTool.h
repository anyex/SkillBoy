#pragma once
#ifndef _ActionTool_H_
#define _ActionTool_H_

#include "cocos2d.h"
USING_NS_CC;

class ActionTool
{

	static Animate* animationWithFrameName(const char *frameName, int iloops, float delay);
	static Animate* animationWithFrameAndNum(const char *frameName, int num, float delay);
	
};

#endif