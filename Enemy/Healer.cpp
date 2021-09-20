#pragma once

#include "Defs.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include "Enemies\Enemy.h"
#include "Healer.h"
#include "Generic_DS\Queue.h"
#include "PQueue.h"
#include "fighter.h"
#include "Battle.h"
class GUI;
Healer:: Healer(int id, int arrTime, int initial ,int speed, int d  )
	:Enemy(id, arrTime, initial ,2,speed ,d)
{
	movingBackward=false;
}
 void Healer:: Move()
	{
		if (status == FRST)
			return;
	
		if (status == INAC  || status ==KILD)
			return;
		if (Health> 0.5* initial_health)
		{
			if (movingBackward)
			{
				if (Distance+speed > MaxDistance)
				{
					Distance=MaxDistance;
					movingBackward=false;
				}
				else
					Distance+=speed;
			}
			else
			{
				if (Distance-speed < MinDistance)
				{
					Distance=MinDistance;
					movingBackward=true;
				}
				else
					Distance-=speed;
			}
		}
		else 
		{
			if (movingBackward)
			{
				if (Distance+ (0.5*speed) > MaxDistance)
				{
					Distance=MaxDistance;
					movingBackward=false;
				}
				else
					Distance+=(0.5*speed) ;
			}
			else
			{
				if (Distance-(0.5*speed)  < MinDistance)
				{
					Distance=MinDistance;
					movingBackward=true;
				}
				else
					Distance-=(0.5*speed) ;
			}
		}
		
	if (Distance<=0)
		{
			Distance=2;
		}	

	}
 void Healer::Act(Battle* battlePtr)
 {
	PQueue <Enemy*> fighterQueue = battlePtr->GetCastle()->getfighterQueue();
	PNode <Enemy*>* ptr =fighterQueue.GetFrontptr();
	if (reloading==0 )
	{
			while( ptr)
		{
			if (!movingBackward)
			{
			if ( (Distance - ptr->getItem()->GetDistance()) <=2 &&(Distance - ptr->getItem()->GetDistance())>=-2 && ptr->getItem()->GetStatus()==ACTV)
			{
				ptr->getItem()->SetHealth (     ptr->getItem()->GetHealth()   +   (Health/10)       );
			}
			}
			
				ptr=ptr->getNext();

		}

		Queue <Enemy*> freezerQueue = battlePtr->GetCastle()->getfreezerQueue();
		Node <Enemy*>* ptr1 =freezerQueue.GetFrontptr();
		while( ptr1)
		{
			if ( (Distance - ptr1->getItem()->GetDistance()) <=2  &&(Distance - ptr1->getItem()->GetDistance())>=-2 && ptr1->getItem()->GetStatus()==ACTV )
				ptr1->getItem()->SetHealth (       ptr1->getItem()->GetHealth()   +   (Health/10)       );
				ptr1=ptr1->getNext();

		}
		 reloading= reload_period+1;
	}
	reloading --;

	
 }
 bool Healer:: getmovingBackward()
 {
	 return movingBackward;
 }
 void Healer:: setmovingBackward(bool b)
 {
	 movingBackward= b;
 }
 
 
 Healer:: ~Healer(void)
 {
 }
