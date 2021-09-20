#include "Enemy.h"


Enemy::Enemy(int id, int arrTime, int initial, int typ,int speed,int d)
	:ID(id),ArrvTime(arrTime),initial_health(initial),type(typ),speed(speed)
{
	SetDistance(d);
	reloading=0;
	T_frstShot=-1;
	T_killed=0;

}

Enemy::~Enemy()
{
}

int Enemy::GetID() const
{
	return ID;
}

void Enemy::SetReload(int R)
 {
	 reload_period = R;
 }
void Enemy::SetStatus(ENMY_STATUS s)
{
	status = s;
}


ENMY_STATUS Enemy::GetStatus() const
{
	return status;
}


void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}

int Enemy::GetArrvTime() const
{
	return ArrvTime;
}
 double Enemy:: GetHealth() const
 {
	 return Health;
 }
 void Enemy:: SetHealth(double H)
 {
	 if (H<0)
		 Health=0;
	 else
	 Health=H;
 }
 int Enemy:: GetFrostedFor() const
 {
	 return FrostedFor;
 }
 void Enemy:: SetFrostedFor(int n)
 {
	 if (n<0)
	{
		FrostedFor=0;
	 SetStatus(ACTV);
	 }
	else 
	 FrostedFor=n;
 }
 int Enemy::GetType()const
{
	return type;
}
void Enemy::setType(int n)
{
	type=n;
}

int Enemy::GetPower()
{
	return power;
}
void Enemy::setpower(int p)
{
	power=p;
}
void Enemy::SetT_frstShot(int F)
{
	T_frstShot = F;
}
void Enemy::SetT_killed(int T)
{
	T_killed = T;
}

int Enemy::GetT_frstShot()
{
	return T_frstShot;
}
int Enemy::GetT_killed()
{
	return T_killed;
}
int Enemy:: GetFirstShotDelay()
{
	return T_frstShot-ArrvTime;
}
int Enemy:: GetKillDelay()
{
	return T_killed-T_frstShot;
}
int Enemy:: GetLifeTime()
{
	return T_killed - ArrvTime;
}
