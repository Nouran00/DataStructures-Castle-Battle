#pragma once

#include "Defs.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include "Enemies\Enemy.h"
#include "freezer.h"
#include "Battle.h"

class GUI;
 freezer:: freezer(int id, int arrTime, int initial ,int speed, int d  )
	:Enemy(id, arrTime, initial ,1,speed ,d)
{
	
}
 void freezer:: Move()
	{
		if (status == FRST)
			return;
		if (status == INAC  || status ==KILD)
			return;
		if (Health> 0.5* initial_health)
		{
		if (Distance - speed < MinDistance )
			Distance= MinDistance;
			Distance-=speed;
		}
		else 
		{
			if (Distance - (0.5*speed) < MinDistance )
				Distance= MinDistance;
				Distance-=int((0.5)*speed);
		}
		if (Distance<=0)
		{
			Distance=2;
		}

	}
void freezer::Act(Battle* battlePtr)

{ 
	
	int iceadded=( power/ ((Distance/2)+1) ) *10;
	if (reloading==0 && status==ACTV)  
	{
		if (Health> 0.5* initial_health)
			battlePtr->GetCastle()->setIceAmount(battlePtr->GetCastle()->getIceAmount() + iceadded);
		else
			battlePtr->GetCastle()->setIceAmount( battlePtr->GetCastle()->getIceAmount() + iceadded/2);
		 reloading= reload_period+1;
		 

	}
	reloading --;
}

 freezer:: ~freezer(void)
 {
 }