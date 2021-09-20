#pragma once

#include "Enemies\Enemy.h"
#include "Castle\Castle.h"
#include "Generic_DS\Queue.h"
#include "GUI\GUI.h"
#include<fstream>

// it is the controller of the project
class Battle
{
private:
	GUI* pGUI;
	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	int ActiveCount, FrostedCount, KilledCount;	//no. of enemies (Active, Frosted, killed so far)
	int CurrentTimeStep;
	//Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function

	Queue<Enemy*> Q_Inactive;		//Queue of inactive enemies
	Queue<Enemy*> Q_Active;

	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	//Queue for all enemies in the battle
	int DemoListCount;
	Enemy* DemoList[MaxEnemyCount];	//Important: This is just for demo
	/// ==>


	//
	// TODO: Add More Data Members As Needed
	string lfilename;//Load function's members
	ifstream loadfile;

	string sfilename;//Save function's members
	ofstream savefile;
	int TotalNumberOfEnemies;
	bool AttackType; // castle attack : ICE -> 0  , bullet -> 1
	int killedfighterscount;
	int killedfreezerscount;
	int killedhealerscount;
	int frostedfighterscount;
	int frostedfreezerscount;
	int frostedhealerscount;
	Queue <Enemy*> toshoot; // Queue of enemies for castle to shoot
public:
	
	Battle();
	void AddAllListsToDrawingList();		//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
	Castle * GetCastle();
	void RunSimulation();
	void ActivateEnemies();		//check the inactive list and activate all enemies that has arrived


	void AddtoDemoList(Enemy* Ptr);		//Add Enemy to the demo queue of enemies (for demo purposes only)
	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes)

	//
	// TODO: Add More Member Functions As Needed
	//
	int getCurrentTimeStep();
	void Load();
	void Save();

	void ActivateEnemiesFR();
	void AddEnemies();

	void InteractiveMode();
	void stepMode();
	void silentMode();
	void incrementTimeStep();
	void UpdateEnemiesFR();
	void CastleAction();
	//void Add_toshoot();
	void UpdateDS();
	void Enemiesaction();
	void AverageFirstShot(float & Averagekilldelay,float & AverageShotDelay);

};

