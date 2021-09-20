#pragma once

#include "Defs.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include "Enemies\Enemy.h"
#include "fighter.h"
#include "Battle.h"
class GUI;
fighter:: fighter(int id, int arrTime, int initial ,int speed, int d  )
	:Enemy(id, arrTime, initial ,0,speed ,d)
{
	
}
 void fighter:: Move()
	{
		if (status == FRST)
			return;
		if (status == INAC ||  status ==KILD)
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
				Distance-=(0.5)*speed;
		}
		if (Distance<=0)
		{
			Distance=2;
		}

	}
void fighter::  Act(Battle * battlePtr)
 {
	 int castle_health=battlePtr->GetCastle()->GetHealth();

	if (reloading==0 && status ==ACTV)
	{
		 if (Health >0.5* initial_health)
		  battlePtr->GetCastle()->SetHealth( castle_health - ((1.0 / Distance)* power));
	    else 
		  battlePtr->GetCastle()->SetHealth( castle_health - ((0.5 / Distance)* power));
		 reloading= reload_period+1;

	}
	reloading --;
	 
 }
void fighter::CalculatePriority( int power, int health)
 {
	 int s;
	 if (status==FRST)
		  s=1;
	 else s=2;
	 Priority = (power) /(health+1) +s;
	 
 }
int fighter::getpriority()
 {
	 return Priority;
 }

 
 fighter:: ~fighter(void)
 {
 }
