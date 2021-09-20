 #pragma once

#include "Defs.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include "Enemies\Enemy.h"
#include "PQueue.h"
//class PQueue;

class GUI;

class Healer : public Enemy

{
private : 
	//int static const type =2;
	bool movingBackward; // to check if healer is moving towareds the castle or backward

	public:
	Healer(int id, int arrTime, int initial ,int speed, int d = MaxDistance );
	void Move();
	virtual void Act(Battle* battlePtr);
	bool getmovingBackward();
	void setmovingBackward(bool b);
	~Healer(void);
};
