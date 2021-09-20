#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
class Battle;

class GUI;
// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:
	const int ID;         //Each enemy has a unique ID (sequence number)
	const int ArrvTime;	//arrival time (time it starts to join battle)

	ENMY_STATUS status;	    //status of the enemy (inactive, inactive, frosted, killed)
	int Distance;	//Horizontal distance between enemy & the tower of its region
	                //Always positive (ranges from 2 to 60)
	double Health;	//Enemy health
	///////////////////// added/////////////////////////
	const double initial_health;
	int  power;                 //Enemy power
	int reload_period;          //time for an enemy to reload his weapon
	int speed;                  //no. of meters an enemy can move in a single time step
	int type;                   // 0-fighter , 1-healer, 2-freezer
	int T_frstShot;             //time enemy is first shot 
	int T_killed;               // time enemy got killed 
	int reloading;      // to check if enemy is in relading period or not( if able to attack)
	
	int FrostedFor;   //timesteps to be frosted for
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Enemy(int id, int arrTime, int initial ,int typ, int speed,int d = MaxDistance);
	virtual ~Enemy();

	int Enemy::GetID() const;
	ENMY_STATUS GetStatus() const;
	void SetStatus(ENMY_STATUS);
	
	void DecrementDist();

	void SetDistance(int );
	int GetDistance() const;

	int GetArrvTime() const;
	 double GetHealth() const;
	 void SetHealth(double H);

	 void SetFrostedFor(int);
	 int GetFrostedFor() const;

	 int GetPower();
	 void setpower(int p);
	 int GetType() const;
	 void setType(int n);
	 void SetReload(int R);//z
	 //void setArrvtime(int n);

	// Virtual Functions: ----------------

	virtual void Move() = 0;	//All enemies can move
	virtual void Act(Battle* battlePtr) = 0;	//Acting means fighting or healing

	
	// TODO: Add More Member Functions As Needed
	void SetT_frstShot(int F);
	void SetT_killed(int T);

	int GetT_frstShot();
	int GetT_killed();

	int GetFirstShotDelay();
	int GetKillDelay();
	int GetLifeTime();
	//

};

