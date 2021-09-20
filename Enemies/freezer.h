#pragma once

#include "Defs.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include "Enemies\Enemy.h"

class GUI;

class freezer : public Enemy

{
private : 
	//int static const type =1;

	public:
	freezer(int id, int arrTime, int initial ,int speed, int d = MaxDistance );
	void Move() ;
	virtual void Act(Battle* battlePtr);
	
	~freezer(void);
};
