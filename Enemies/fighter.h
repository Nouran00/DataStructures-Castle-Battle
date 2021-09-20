#pragma once

#include "Defs.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include "Enemies\Enemy.h"

class GUI;

class fighter : public Enemy

{
private : 
	//int static const type =0;
	int Priority;

	public:
	void CalculatePriority(int power,int health);
    int getpriority();
	fighter(int id, int arrTime, int initial ,int speed, int d = MaxDistance );
	void Move() ;
	virtual void Act(Battle * battlePtr);
	
	~fighter(void);
};
