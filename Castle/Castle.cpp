#include "Castle.h"

void Castle:: castle()
{
	IceAmount=0;
	fightercount=0;
	freezercount=0;
	killedcount=0;
	healercount=0;
	frostedcount=0;
}
void Castle:: castle(double H, int Max, float pwr)
{
	Health=H;
	MaxNumbertoAttack=Max;
	castlePower=pwr;
	IceAmount=0;
	fightercount=0;
	freezercount=0;
	killedcount=0;
	healercount=0;
	frostedcount=0;
}

void Castle::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Castle::GetHealth() const
{
	return Health;
}
void Castle:: setMaxNumbertoAttack( int n)
{
	MaxNumbertoAttack=n;
}
int Castle:: getMaxNumbertoAttack() const
{
	return MaxNumbertoAttack;
}
void Castle:: setcastlepwr(int p)
{
 castlePower=p;
}
float Castle:: getcastlepwr() const
{
	return castlePower;
}
void Castle:: setStatus(CASTLE_STATUS s)
{
 status=s;
}
CASTLE_STATUS Castle:: getStatus() const
{
	return status;
}
void Castle:: AddFightertoQueue( Enemy* f, int p)
{
	fighterQueue.enqueue(f,p);
	fightercount++;
}
void Castle::  AddfreezertoQueue( Enemy* f)
{
	freezerQueue.enqueue(f);
	freezercount++;
}
void Castle:: AddtoKilledQueue( Enemy* E)
{
	killedQueue.enqueue(E);
	killedcount++;
}
void Castle::AddHealertoStack(Enemy*f)
{
	HealersStack.Push(f);
	healercount ++;
}
void Castle::AddFrostedtoQueue(Enemy* f, int p)
{
	frostedQueue.enqueue(f, p);
	frostedcount++;
}
void Castle:: removefighterfromQueue(  Enemy* f)
{
	fighterQueue.dequeue(f);
	fightercount--;
}
void Castle:: removefreezerfromQueue(  Enemy* f)
{
	freezerQueue.dequeue(f);
	freezercount--;
}
void Castle::removehealerfromStack(  Enemy* f)
{
	HealersStack.Pop(f);
	healercount--;
}
void  Castle::removefrostedfromQueue(  Enemy* f)
{
	frostedQueue.dequeue(f);
	frostedcount--;
}
void  Castle:: removekilledfromQueue (  Enemy* f)
{
	killedQueue.dequeue(f);
	killedcount--;
}


void Castle:: setfightercount(int fi_count)
{
	fightercount=fi_count;
}
int Castle:: getfightercount() const
{
	return fightercount;
}
void Castle:: setfreezercount(int fr_count)
{
	freezercount=fr_count;
}
int Castle:: getfreezercount() const
{
	return freezercount;
}
void Castle:: setkilledcount(int fr_count)
{
	killedcount=fr_count;
}
int Castle:: getkilledcount() const
{
	return killedcount;
}

void Castle:: sethealercount(int h_count)
{
	healercount=h_count;
}
int Castle::gethealercount() const
{
	return healercount;
}
void Castle::setfrostedcount(int fr_count)
{
	frostedcount = fr_count;
}
int Castle::getfrostedcount() const
{
	return frostedcount;
}

Queue <Enemy*> Castle:: getkilledQueue ()
{
	return killedQueue;
}
void Castle:: setIceAmount(int n)
{
	IceAmount=n;
}
int Castle::getIceAmount()
{
	return IceAmount ;
}
PQueue <Enemy*> Castle:: getfighterQueue ()
{
	return fighterQueue;
}
Queue <Enemy*> Castle:: getfreezerQueue ()
{
	return freezerQueue;
}
Stack <Enemy*> Castle::getHealersStack()
{
	return HealersStack;
}
PQueue <Enemy*> Castle::getFrostedQueue()
{
	return frostedQueue;
}
void Castle::BulletAttack(Enemy *Eptr)
{
	int k;
	if (Eptr->GetType()==2) //if healers
		k=2;
	else k=1;
	double healthdecrement=  castlePower *  ( 1/(Eptr->GetDistance()))   *   (1/k)+0.05;
	Eptr->SetHealth(Eptr->GetHealth() - healthdecrement);
	if (Eptr->GetHealth()<=0)
	{
		Eptr->SetStatus(KILD);
		
	}
		

}
void Castle::IceAttack(Enemy *Eptr)
{
	Eptr->SetStatus(FRST);
	if (Eptr->GetDistance()<15)
		Eptr->SetFrostedFor(50);

	if (Eptr->GetDistance()<30)
		Eptr->SetFrostedFor(25);

	if (Eptr->GetDistance()<45)
		Eptr->SetFrostedFor(12);

	else Eptr->SetFrostedFor(6);

}
