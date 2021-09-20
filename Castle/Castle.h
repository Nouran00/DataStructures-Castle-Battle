#pragma once
#include "..\Defs.h"
#include "..\Enemies\Enemy.h"
#include "..\fighter.h"
#include "..\freezer.h"
#include "..\PQueue.h"
#include "..\Generic_DS\Queue.h"
#include "..\Stack.h"
class Castle
{
	double Health;
	int totalEnemyno;
	//ADDED
	CASTLE_STATUS status;
	int MaxNumbertoAttack;                    // max number of enemies castle can attack can attack 
	int castlePower;
	PQueue <Enemy*> fighterQueue;
	Queue <Enemy*> freezerQueue;
	Queue <Enemy*> killedQueue;
	Stack <Enemy*> HealersStack;
	PQueue <Enemy*> frostedQueue;
	int fightercount;
	int freezercount;
	int killedcount;
	int healercount;
	int frostedcount;
	int IceAmount;              //to check if castle is frosted 
	int static const threshold =500;


	



	//
	// TODO: Add More Data Members As Needed
	//

public:
	void castle();
	void castle(double H, int Max, float pwr);

	void SetHealth(double h);
	double GetHealth() const;
	void setMaxNumbertoAttack( int n);
	int getMaxNumbertoAttack() const;
	void setcastlepwr(int p);
	float getcastlepwr() const;

	void AddFightertoQueue( Enemy* f,int p);
	void AddfreezertoQueue( Enemy* f);
	void AddtoKilledQueue( Enemy* E);
	void AddHealertoStack(Enemy*h);
	void AddFrostedtoQueue(Enemy* f, int p);

	void removefighterfromQueue(  Enemy* f);
	void removefreezerfromQueue(  Enemy* f);
	void removehealerfromStack(  Enemy* f);
	void removefrostedfromQueue(  Enemy* f);
	void removekilledfromQueue(  Enemy* f);

	void setfightercount(int fi_count);
	int getfightercount() const;

	void setfreezercount(int fr_count);
	int getfreezercount() const;

	void setkilledcount(int k_count);
	int getkilledcount() const;

	void sethealercount(int h_count);
	int gethealercount() const;

	void setfrostedcount(int fr_count);
	int getfrostedcount() const;

	Queue <Enemy*>  getkilledQueue ();
	PQueue <Enemy*>  getfighterQueue ();
	Queue <Enemy*>  getfreezerQueue ();
	Stack <Enemy*> getHealersStack();
	PQueue <Enemy*> getFrostedQueue();

	void setIceAmount(int n);
	int getIceAmount ();
	
	void setStatus( CASTLE_STATUS s);
	CASTLE_STATUS  getStatus () const;

	void BulletAttack(Enemy *Eptr);
	void IceAttack(Enemy *Eptr);
	//void CastleAttack();

	//
	// TODO: Add More Member Functions As Needed
	//

};

