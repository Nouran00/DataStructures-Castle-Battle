#include "Battle.h"
#include <time.h>
#include "Enemies\Enemy.h"
#include "fighter.h"
#include "Healer.h"
#include "freezer.h"
#include "Castle\Castle.h"
Battle::Battle()
{	
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	DemoListCount = 0;
	CurrentTimeStep = 0;
	pGUI = NULL;
	BCastle.setfightercount(0);
	BCastle.setfreezercount(0);
	BCastle.sethealercount(0);
	BCastle.setfrostedcount(0);
	BCastle.setkilledcount(0);
	BCastle.setStatus(ACTIV);
	BCastle.setIceAmount(0);
}

void Battle::AddtoDemoList(Enemy* Ptr)
{
	DemoList[DemoListCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It just enqueue a pointer that is already allocated into the queue
}


Castle * Battle::GetCastle()
{
	return &BCastle;
}
int Battle:: getCurrentTimeStep()
{
	return CurrentTimeStep;
}


void Battle::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
	Load();	
	
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		InteractiveMode();
		break;
	case MODE_STEP:
		stepMode();
		break;
	case MODE_SLNT:
		silentMode();
		break;
	case MODE_DEMO:
		Just_A_Demo();

	}

	delete pGUI;
	
}


//This is just a demo function for project introductory phase
//It should be removed in phases 1&2
void Battle::Just_A_Demo()
{	
	
	pGUI->PrintMessage("Just a Demo. Enter Enemies Count(next phases should read I/P filename):");
	EnemyCount = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->PrintMessage("Generating Enemies randomly... In next phases, Enemies should be loaded from a file...CLICK to continue");
	pGUI->waitForClick();

	CurrentTimeStep = 0;
	//
	// THIS IS JUST A DEMO Function
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	//
	 
	srand(time(NULL));
	int Enemy_id = 0;
	int ArrivalTime=1;
	fighter* pE= NULL;
	//Create Random enemies and add them all to inactive queue
	for(int i=0; i<EnemyCount; i++)
	{			
		ArrivalTime += (rand()%3);	//Randomize arrival time
		//pE = new fighter(++Enemy_id,ArrivalTime);
		pE->SetStatus( INAC); //initiall all enemies are inactive
		Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
	}	

	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();
	
	while( KilledCount < EnemyCount )	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();

		Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes only)

		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep);
		Sleep(250);
	}		
}

//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{	
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy* const * EnemyList = Q_Inactive.toArray(InactiveCount);
	for(int i=0; i<InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyList[i]);

	//Add other lists to drawing list
	//TO DO
	//In next phases, you should add enemies from different lists to the drawing list
	//For the sake of demo, we will use DemoList
	//for(int i=0; i<DemoListCount; i++)
		//pGUI->AddToDrawingList(DemoList[i]);

	int FrostedCount;
	Enemy* const * EnemyList2 = BCastle.getFrostedQueue().toArray(FrostedCount);
	for(int i=0; i<FrostedCount; i++)
		pGUI->AddToDrawingList(EnemyList2[i]);

	int KilledCount;
	Enemy* const * EnemyList3 = BCastle.getkilledQueue().toArray(KilledCount);
	for(int i=0; i<KilledCount; i++)
		pGUI->AddToDrawingList(EnemyList3[i]);

	int fightersCount;
	Enemy* const * EnemyList4 = BCastle.getfighterQueue().toArray(fightersCount);
	for(int i=0; i<fightersCount; i++)
		pGUI->AddToDrawingList(EnemyList4[i]);

	int freezersCount;
	Enemy* const * EnemyList5 = BCastle.getfreezerQueue().toArray(freezersCount);
	for(int i=0; i<freezersCount; i++)
		pGUI->AddToDrawingList(EnemyList5[i]);

	int healerscount;
	Enemy* const * EnemyList6 = BCastle.getHealersStack().toArray(healerscount);
	for(int i=0; i<healerscount; i++)
		pGUI->AddToDrawingList(EnemyList6[i]);

	
}

//check the inactive list and activate all enemies that has arrived
void Battle::ActivateEnemies()
{
	Enemy *pE;
	while( Q_Inactive.peekFront(pE) )	//as long as there are more inactive enemies
	{
		if(pE->GetArrvTime() > CurrentTimeStep )	//no more arrivals at current time
			return;
				
		Q_Inactive.dequeue(pE);	//remove enemy from the queue
		pE->SetStatus(ACTV);	//make status active
		AddtoDemoList(pE);		//move it to demo list (for demo purposes)
	}
}


//Randomly update enemies distance/status (for demo purposes)
void Battle::Demo_UpdateEnemies()	
{
	Enemy* pE;
	int Prop;
	//Freeze, activate, and kill propablities (for sake of demo)
	int FreezProp = 5, ActvProp = 10, KillProp = 1;	
	srand(time(0));
	for(int i=0; i<DemoListCount; i++)
	{
		pE = DemoList[i];
		switch(pE->GetStatus())
		{
		case ACTV:
			pE->DecrementDist();	//move the enemy towards the castle
			Prop = rand()%100;
			if(Prop < FreezProp)		//with Freeze propablity, change some active enemies to be frosted
			{
				pE->SetStatus(FRST); 
				ActiveCount--;
				FrostedCount++;
			}
			else	if (Prop < (FreezProp+KillProp) )	//with kill propablity, kill some active enemies
					{
						pE->SetStatus(KILD);	
						ActiveCount--;
						KilledCount++;
					}
			
			break;
		case FRST:
			Prop = rand()%100;
			if(Prop < ActvProp)			//with activation propablity, change restore some frosted enemies to be active again
			{
				pE->SetStatus(ACTV);
				ActiveCount++;
				FrostedCount--;
			}

			else	if (Prop < (ActvProp+KillProp) )			//with kill propablity, kill some frosted enemies
					{
						pE->SetStatus(KILD);	
						FrostedCount--;
						KilledCount++;
					}

			break;
		}
	}
}
void Battle::Load()
{
	pGUI->PrintMessage("Enter the file name to get the data from.");
	lfilename = pGUI->GetString();
	loadfile.open(lfilename + ".txt");
	if (loadfile.fail())
	{
		pGUI->PrintMessage("Can't open the text file, Click to continue");
	}
	else
	{
		double health;
		loadfile >> health;
		BCastle.SetHealth(health);
		int maxtoattack;
		loadfile >> maxtoattack;
		BCastle.setMaxNumbertoAttack(maxtoattack);
		float CPower;
		loadfile >> CPower;
		BCastle.setcastlepwr(CPower);
		int totalnumberofeenemies;//total number of enemies in the input file
		loadfile >> totalnumberofeenemies;
		TotalNumberOfEnemies = totalnumberofeenemies;
		for (int i = 0;i < totalnumberofeenemies;i++)
		{
			int id;
			int type;
			int ArrivalTime;
			int Health;
			int Power;
			int Reload;
			int Speed;
			loadfile >> id;
			loadfile >> type;
			loadfile >> ArrivalTime;
			loadfile >> Health;
			loadfile >> Power;
			loadfile >> Reload;//
			loadfile >> Speed;//
			Enemy* NewEnemy;
			// 0-fighter , 1-healer, 2-freezer
			if (type == 0)
			{
				NewEnemy = new fighter(id,ArrivalTime,Health,Speed,MaxDistance);
				NewEnemy->SetHealth(Health);
				NewEnemy->SetReload(Reload);
				NewEnemy->SetStatus(INAC);
				NewEnemy->setType(0);
				NewEnemy->setpower(Power);
				Q_Inactive.enqueue(NewEnemy);
			}
			else if (type == 2)
			{
				NewEnemy = new Healer(id, ArrivalTime, Health, Speed, MaxDistance);
				NewEnemy->SetHealth(Health);
				NewEnemy->SetReload(Reload);
				NewEnemy->SetStatus(INAC);
				NewEnemy->setType(2);
				NewEnemy->setpower(Power);
				Q_Inactive.enqueue(NewEnemy);
			}
			else if (type == 1)
			{
				NewEnemy = new freezer(id, ArrivalTime, Health, Speed, MaxDistance);
				NewEnemy->SetHealth(Health);
				NewEnemy->SetReload(Reload);
				NewEnemy->SetStatus(INAC);
				NewEnemy->setType(1);
				NewEnemy->setpower(Power);
				Q_Inactive.enqueue(NewEnemy);
			}
		}
	}
}
void Battle::Save()
{
	pGUI->PrintMessage("Enter the name of the file to be saved to.");
	sfilename = pGUI->GetString();
	savefile.open(sfilename + ".txt", ios::out);
	/*The game is win if all enemies are killed. The game is loss if the castle is destroyed.
	Otherwise, the game is "drawn".*/
	float avg_KD;
	float avg_FD;
	if (BCastle.getkilledcount() == TotalNumberOfEnemies)//win
	{
		AverageFirstShot( avg_KD ,avg_FD);
		savefile << "Game is WIN" << endl;
	}
	else if(BCastle.GetHealth()==0)//loss
	{
		savefile << "Game is LOSS" << endl;
	}
	else//draw
	{
		savefile << "Game is DRAW" << endl;
	}
	savefile << "KTS   ID   FD   KD   LT" << endl;
	
	int totalkilled=BCastle.getkilledcount();
	Enemy* SEnemy;
	while (BCastle.getkilledQueue().peekFront(SEnemy))
	{
		BCastle.removekilledfromQueue(SEnemy);
		int KTS = SEnemy->GetT_killed();
		int ID = SEnemy->GetID();
		int FD = SEnemy->GetFirstShotDelay();
		int KD = SEnemy->GetKillDelay();
		int LT = SEnemy->GetLifeTime();
		//savefile << "KTS ID FD KD LT" << endl;
		savefile << KTS << "   " << ID << "   " << FD << "   " << KD << "   " << LT << "   " << endl;
	}
	if (totalkilled == TotalNumberOfEnemies)
	{
		
		savefile << "Castle Total Damage = " << BCastle.GetHealth() << endl;
		savefile << "Total Enemies = " << TotalNumberOfEnemies << endl;
		savefile << "Average first shot delay "<<avg_FD  <<endl;
		savefile << "Average kill delay "<<avg_KD  <<endl;
	}
	else
	{
		savefile << "Number of killed enemies = " << totalkilled << endl;
		savefile << "Number of alive enemies = " << TotalNumberOfEnemies-totalkilled << endl;

	}
}
void Battle::ActivateEnemiesFR()
{
	Enemy* pE;
	while (Q_Inactive.peekFront(pE))	//as long as there are more inactive enemies
	{
		if (pE->GetArrvTime() > CurrentTimeStep)	//no more arrivals at current time
			return;

		Q_Inactive.dequeue(pE);	//remove enemy from the queue
		pE->SetStatus(ACTV);	//make status active
		Q_Active.enqueue(pE);	//add enemies to the active queue
		
	}
}
void Battle::AddEnemies()
{
	Enemy* X;
	//int c = 60;
	// 0-fighter , 1-healer, 2-freezer
	while (Q_Active.peekFront(X))
	{
		Q_Active.dequeue(X);
		if (X->GetType() == 0)
		{
			fighter* f= dynamic_cast <fighter*>(X);
			//f->SetDistance(c);
			int health = f->GetHealth();
			int power = f->GetPower();
			f->CalculatePriority(power,health);
			BCastle.AddFightertoQueue(f,f->getpriority());
		}
		else if (X->GetType() == 2)
		{
			//X->SetDistance(c);
			BCastle.AddHealertoStack(X);
		}
		else if (X->GetType() == 1)
		{
			//X->SetDistance(c);
			BCastle.AddfreezertoQueue(X);
		}
	}
}
void Battle::InteractiveMode()
{
	srand(time(NULL));
	Enemy* pE;

	while (Q_Inactive.peekFront(pE) || !BCastle.getfreezerQueue().isEmpty() 
		|| !BCastle.getfighterQueue().isEmpty() || !BCastle.getHealersStack().isEmpty()
		||  !BCastle.getFrostedQueue().isEmpty() )
	{ 
		pGUI->waitForClick();
		ActivateEnemiesFR(); 
		AddEnemies();                    //ADD enemies to the 3 lists  (fighter ,freezer and healer)
		CastleAction();
		Enemiesaction();
		UpdateDS();
		incrementTimeStep();
		if (BCastle.getStatus()==KILLED)
			break;
	}
	Save();
	pGUI->waitForClick();
}
void Battle::stepMode()
{
srand(time(NULL));
Enemy* pE;

while (Q_Inactive.peekFront(pE) || !BCastle.getfreezerQueue().isEmpty() 
		|| !BCastle.getfighterQueue().isEmpty() || !BCastle.getHealersStack().isEmpty()
		||  !BCastle.getFrostedQueue().isEmpty() )
	{ 
		Sleep(1000);
	
		ActivateEnemiesFR(); 
		AddEnemies();              //ADD enemies to the 3 lists  (fighter ,freezer and healer)
		CastleAction();
		Enemiesaction();
		UpdateDS();
		incrementTimeStep();
		if (BCastle.getStatus()==KILLED)
			break;
	}
	Save();
}
void Battle:: silentMode()
{
	srand(time(NULL));
	Enemy* pE;

while (Q_Inactive.peekFront(pE) || !BCastle.getfreezerQueue().isEmpty() 
		|| !BCastle.getfighterQueue().isEmpty() || !BCastle.getHealersStack().isEmpty()
		||  !BCastle.getFrostedQueue().isEmpty() )
	{ 
		ActivateEnemiesFR(); 
		AddEnemies();                   //ADD enemies to the 3 lists  (fighter ,freezer and healer)
		CastleAction();
		Enemiesaction();
		UpdateDS();
		CurrentTimeStep++;
		if (BCastle.getStatus()==KILLED)
			break;
	}
	Save();

}
void Battle::incrementTimeStep()
{
	CASTLE_STATUS status= BCastle.getStatus();
	string s;
	if (status== ACTIV)
	    s= "Active";
	else if( status== FROSTED)
		s= "frosted";
	else if (status==KILLED)
		s="Killed";
	CurrentTimeStep++;
	string msg = "CurrentTimeStep: " + to_string(CurrentTimeStep - 1);
	string msg2= "  Caslte's health= " + to_string(BCastle.GetHealth()) + "    Castle's status: " + s ;
	string msg3= "  \nActive fighters= " + to_string(BCastle.getfightercount()) + "    Active freezers= " + to_string(BCastle.getfreezercount()) + "     Active healers= " + to_string(BCastle.gethealercount()) + "    Total active= " +to_string(BCastle.gethealercount()+BCastle.getfreezercount()+BCastle.getfightercount()) ;
	string msg4= "  \nTotalkilled= "+ to_string(BCastle.getkilledcount()) +  "    Total frosted= " + to_string(BCastle.getfrostedcount());
	pGUI->PrintMessage(msg +msg2 + msg3+msg4);
	pGUI->ResetDrawingList();
	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep);
	
}

void Battle :: CastleAction()
{
	srand(time(NULL));
	PQueue< Enemy*> fighterqueue= BCastle.getfighterQueue();
	Queue <Enemy*> freezersqueue= BCastle.getfreezerQueue();
	Stack <Enemy*> healerstack= BCastle.getHealersStack();
	PQueue <Enemy*> frostedqueue= BCastle.getFrostedQueue();
	int toshootnumber= BCastle.getMaxNumbertoAttack();
	int AttackType;                // to generates 0 (20%) or 1 (80%)
	PNode <Enemy*> * E= fighterqueue.GetFrontptr();
	if (BCastle.getStatus()==FROSTED)
	{
		BCastle.setIceAmount(0);
		BCastle.setStatus(ACTIV);
		return;
	}
	if (BCastle.getStatus()==ACTIV)
	{
		while (E && toshootnumber>0)
		{
			AttackType=rand()%10 >=2;
			if (E->getItem()->GetT_frstShot()==-1)
			    E->getItem()->SetT_frstShot(CurrentTimeStep);
			

			if (AttackType==1 ) //BulletAttack
			{
				BCastle.BulletAttack(E->getItem());
				if (E->getItem()->GetStatus()==KILD)
					E->getItem()->SetT_killed(CurrentTimeStep);

			}

			else if (AttackType==0) ////Ice Attack
				BCastle.IceAttack(E->getItem());

				E=E->getNext();
				toshootnumber--;
		}
		///////////////////////////////////////////////////////////////////////////
		Node <Enemy*> * E2= freezersqueue.GetFrontptr();
		while (E2 && toshootnumber>0)
		{
			AttackType=rand()%10 >=2;
			if (E2->getItem()->GetT_frstShot()==-1)
			    E2->getItem()->SetT_frstShot(CurrentTimeStep);

			if (AttackType==1 ) //BulletAttack
			{
				BCastle.BulletAttack(E2->getItem());
				if (E2->getItem()->GetStatus()==KILD)
					E2->getItem()->SetT_killed(CurrentTimeStep);
				
			}

			else if (AttackType==0) ////Ice Attack
				BCastle.IceAttack(E2->getItem());

			
				E2=E2->getNext();
				toshootnumber--;
		}
		///////////////////////////////////////////////////////////////
		Node <Enemy*> * E3= healerstack.getheadptr();
		while(E3 && toshootnumber>0)
		{
			AttackType=rand()%10 >=2;
			if (E3->getItem()->GetT_frstShot()==-1)
			    E3->getItem()->SetT_frstShot(CurrentTimeStep);
			
			if (AttackType==1  ) //BulletAttack
			{
				BCastle.BulletAttack(E3->getItem());
				if (E3->getItem()->GetStatus()==KILD)
				{
					E3->getItem()->SetT_killed(CurrentTimeStep);
				}
					
			}

			else if (AttackType==0) ////Ice Attack
				BCastle.IceAttack(E3->getItem());

			
		
			E3=E3->getNext();
			toshootnumber--;
		}
		//////////////////////////////////////////////////////////
		PNode <Enemy*> * E4= frostedqueue.GetFrontptr();
		while(E4 && toshootnumber>0)
		{
			AttackType=rand()%10 >=2;
				if (E4->getItem()->GetT_frstShot()==-1)
			    E4->getItem()->SetT_frstShot(CurrentTimeStep);

			if (AttackType==1) ////bullet Attack
			{
				BCastle.BulletAttack(E4->getItem());
				if (E4->getItem()->GetStatus()==KILD)
					E4->getItem()->SetT_killed(CurrentTimeStep);

			}
				
		

			E4=E4->getNext();
		}
	}
	
}

void Battle:: Enemiesaction()
{
	Enemy *Eptr;
	PQueue< Enemy*> fighterqueue= BCastle.getfighterQueue();
	Queue <Enemy*> freezersqueue= BCastle.getfreezerQueue();
	Stack <Enemy*> healerstack= BCastle.getHealersStack();
	PNode <Enemy*> * EFi= fighterqueue.GetFrontptr();
	while (EFi &&  EFi->getItem()->GetStatus()==ACTV)
	{
		if ( EFi->getItem()->GetStatus()==ACTV)
		{
			EFi->getItem()->Move();
			EFi->getItem()->Act(this);
			if (BCastle.GetHealth() ==0)
				BCastle.setStatus(KILLED);
		}
	
			EFi=EFi->getNext();
		
	}
	///////////////////////////////////////////////////////////
	Node <Enemy*> * EFr= freezersqueue.GetFrontptr();
	while(EFr )
	{
		if (BCastle.getStatus()==FROSTED)
			break;
		if (EFr->getItem()->GetStatus()==ACTV)
		{
		EFr->getItem()->Move();
		EFr->getItem()->Act(this);
		if (BCastle.getIceAmount() >=30)
			BCastle.setStatus(FROSTED);
		}
		

		EFr=EFr->getNext();
	}
	//////////////////////////////////////////////////////////
	Node <Enemy*> * Ehe= healerstack.getheadptr();
	while(Ehe && Ehe->getItem()->GetStatus()==ACTV )
	{
		if (Ehe->getItem()->GetStatus()==ACTV)
		{
		Ehe->getItem()->Move();
		Ehe->getItem()->Act(this);
		}
		
		Ehe=Ehe->getNext();
	}
	
}
void Battle:: UpdateDS()
{
	Enemy* Eptr;
	Queue <Enemy*> updatedfighters;
	Queue <Enemy*> updatedfreezers;
	Queue <Enemy*> updatedfrosted;
	Stack <Enemy*> updatedhealers;
	////////////////////////////updatingfihters queue//////////////////////////
	while (BCastle.getfighterQueue().peekFront(Eptr))
	{
		BCastle.removefighterfromQueue(Eptr);
		if (Eptr->GetStatus()==ACTV)
		{
			fighter* f= dynamic_cast <fighter*>(Eptr);
			int health = f->GetHealth();
			int power = f->GetPower();
			f->CalculatePriority(power,health);
			updatedfighters.enqueue(f);
		}
		if (Eptr->GetStatus()==KILD)
		{
			BCastle.AddtoKilledQueue(Eptr);
		}
		if (Eptr->GetStatus()==FRST)
		{
			BCastle.AddFrostedtoQueue(Eptr,-1*Eptr->GetFrostedFor());
		}
	}
	Enemy *E2;
	while (updatedfighters.peekFront(E2) )
	{
		updatedfighters.dequeue(E2);
		fighter* f= dynamic_cast <fighter*>(E2);
		BCastle.AddFightertoQueue(f,f->getpriority());
	}
	/////////////////////////updatingfreezers queue/////////////////////////////
	Enemy *frE;
	while (BCastle.getfreezerQueue().peekFront(frE))
	{
		BCastle.removefreezerfromQueue(frE);
		if (frE->GetStatus()==ACTV)
		{
			updatedfreezers.enqueue(frE);
		}
		if (frE->GetStatus()==KILD)
		{
			BCastle.AddtoKilledQueue(frE);
		}
		if (frE->GetStatus()==FRST)
		{
			BCastle.AddFrostedtoQueue(frE,-1*frE->GetFrostedFor());
		}
	}
	Enemy *E3;
	while (updatedfreezers.peekFront(E3) )
	{
		updatedfreezers.dequeue(E3);
		BCastle.AddfreezertoQueue(E3);
	}
	////////////////////////////updating healersstack////////////////////////
	Enemy *hE;
	while (BCastle.getHealersStack().peek(hE))
	{
		BCastle.removehealerfromStack(hE);
		if (hE->GetStatus()==ACTV)
		{
			updatedhealers.Push(hE);
		}
		if (hE->GetStatus()==KILD)
		{
			BCastle.AddtoKilledQueue(hE);
		}
		if (hE->GetStatus()==FRST)
		{
			BCastle.AddFrostedtoQueue(hE,-1*hE->GetFrostedFor());
		}
	}
	Enemy *E5;
	while (updatedhealers.peek(E5) )
	{
		updatedhealers.Pop(E5);
		BCastle.AddHealertoStack(E5);
	}
	
	///////////////////////updating frosted queue/////////////////////
	Enemy *froE;
	while (BCastle.getFrostedQueue().peekFront(froE))
	{
		BCastle.removefrostedfromQueue(froE);
		if (froE->GetStatus()==ACTV)
		{
			if (froE->GetType()==0)//fighter
			{
				fighter* f= dynamic_cast <fighter*>(froE);
				BCastle.AddFightertoQueue(f,f->getpriority());
			}
				
			if (froE->GetType()==1)//freezer
			{
				BCastle.AddfreezertoQueue(froE);
			}
			
			if (froE->GetType()==2)//healer
			{
				BCastle.AddHealertoStack(froE);
			}
		}
		if (froE->GetStatus()==KILD)
		{
			BCastle.AddtoKilledQueue(froE);
		}
		if (froE->GetStatus()==FRST)
		{
			froE->SetFrostedFor(froE->GetFrostedFor()-1);
			updatedfrosted.enqueue(froE);
		}
	}
	Enemy *E4;
	while (updatedfrosted.peekFront(E4) )
	{
		updatedfrosted.dequeue(E4);
		BCastle.AddFrostedtoQueue(E4, -1*E4->GetFrostedFor());
	}
	
}
void   Battle::AverageFirstShot(float & Averagekilldelay,float & AverageShotDelay)
{
	Enemy *Eptr;
	PQueue< Enemy*> fighterqueue= BCastle.getfighterQueue();
	Queue <Enemy*> freezersqueue= BCastle.getfreezerQueue();
	Stack <Enemy*> healerstack= BCastle.getHealersStack();
	Queue <Enemy*> killedQueue=BCastle.getkilledQueue();
	PNode <Enemy*> * EFi= fighterqueue.GetFrontptr();
	int sumKD=0;
	int sumFD=0;
	while (EFi)
	{
			int FD=EFi->getItem()->GetFirstShotDelay();
				sumFD+=FD;
	
			EFi=EFi->getNext();
	}
	///////////////////////////////////////////////////////////
	Node <Enemy*> * EFr= freezersqueue.GetFrontptr();
	while(EFr )
	{
		int FD2=EFr->getItem()->GetFirstShotDelay();
			sumFD+=FD2;

		EFr=EFr->getNext();
	}
	//////////////////////////////////////////////////////////
	Node <Enemy*> * Ehe= healerstack.getheadptr();
	while(Ehe)
	{
		int FD3=Ehe->getItem()->GetFirstShotDelay();
			sumFD+=FD3;
		
		Ehe=Ehe->getNext();
	}
	////////////////////////////////////////////////////////////
	Node <Enemy*> * kE= killedQueue.GetFrontptr();
	while(kE)
	{
		int KD=kE->getItem()->GetKillDelay();
			sumKD+=KD;
		
		kE=kE->getNext();
	}
	Averagekilldelay=sumKD/BCastle.getkilledcount();
	 AverageShotDelay= sumFD/TotalNumberOfEnemies;
}
////////////////////////////////////////////////////////////
void Battle::UpdateEnemiesFR()
{
	Enemy* fiE;
	Enemy* frE;
	Enemy* free;
	Enemy* hea;
	PQueue<Enemy*>fighters=BCastle.getfighterQueue();
	Queue<Enemy*> updatedfighters;
	Queue<Enemy*> updatedfrosted;
	PQueue<Enemy*>frosted=BCastle.getFrostedQueue();
	Queue <Enemy*> freezers = BCastle.getfreezerQueue();
	Stack <Enemy*> Healers = BCastle.getHealersStack();
	Queue <Enemy*> updatedfreezers;
	Stack <Enemy*> updatedhealers;
	int updatedhealerscount = 0;
	while(fighters.peekFront(fiE))
	//for (int i = 0; i < BCastle.getfightercount(); i++)
	{
		BCastle.removefighterfromQueue(fiE);
		fighter* f= dynamic_cast <fighter*>(fiE);
		int health = f->GetHealth();
		int power = f->GetPower();
		int distance = f->GetDistance();
		int status = f->GetStatus();
		f->CalculatePriority(power,health);
		updatedfighters.enqueue(f);
	}
	//for (int i = 0; i < BCastle.getfightercount(); i++)
	BCastle.setfightercount(0);
	while (updatedfighters.peekFront(fiE))
	{
		updatedfighters.dequeue(fiE);
		if (fiE->GetHealth() <= 0)
		{
			fiE->SetStatus(KILD);
			BCastle.AddtoKilledQueue(fiE);
		
		}
		else if (fiE->GetStatus() == FRST)
		{
			fighter* f= dynamic_cast <fighter*>(fiE);
			BCastle.AddFrostedtoQueue(f, -1*f->GetFrostedFor());
			
		}
		else
		{
			fighter* f= dynamic_cast <fighter*>(fiE);
			
			BCastle.AddFightertoQueue(f, f->getpriority());
		}
	}
	//////////////////////////////////////////////////////////////////////
	while( frosted.peekFront(frE))
	//for (int i = 0;i < BCastle.getfrostedcount();i++)
	{
		BCastle.removefrostedfromQueue(frE);
		updatedfrosted.enqueue(frE);
	}
	BCastle.setfrostedcount(0);
	while (updatedfrosted.peekFront(frE))
	//for (int i = 0; i < BCastle.getfrostedcount(); i++)
	{
		updatedfrosted.dequeue(frE);
		if (frE->GetHealth() <= 0)
		{
			frE->SetStatus(KILD);
			BCastle.AddtoKilledQueue(frE);
		}
		else if (frE->GetStatus() == ACTV)
		{
			// 0-fighter , 1-healer, 2-freezer
			if (frE->GetType() == 0)
			{
				int health = frE->GetHealth();
		        int power = frE->GetPower();
				fighter* f= dynamic_cast <fighter*>(fiE);
				f->CalculatePriority(power,health);
				BCastle.AddFightertoQueue(f, f->getpriority());
			}
			else if(frE->GetType() == 1)
			{
				BCastle.AddHealertoStack(frE);
			}
			else if(frE->GetType() == 2)
			{
				BCastle.AddfreezertoQueue(frE);
			}
		}
		else
		{
			BCastle.AddFrostedtoQueue(frE,-1* frE->GetFrostedFor());
		}
	}
	/////////////////////////////////////////////
	while (freezers.peekFront(free))
	{
		BCastle.removefreezerfromQueue(free);
		if (free->GetHealth() <= 0)
		{
			BCastle.AddtoKilledQueue(free);
			BCastle.setfreezercount(BCastle.getfreezercount() - 1);
		}
		else if (free->GetStatus()==FRST)
		{
			BCastle.AddFrostedtoQueue(free, -1 * frE->GetFrostedFor());
			BCastle.setfreezercount(BCastle.getfreezercount() - 1);
		}
		else 
		{
			BCastle.AddfreezertoQueue(free);

		}
	}
	//////////////////////////////////////////////////
	while (Healers.peek(free))
	{
		BCastle.removehealerfromStack(free);
		if (free->GetStatus() == FRST)
		{
			BCastle.AddFrostedtoQueue(free, -1 * frE->GetFrostedFor());
	
		}
		else if (free->GetHealth() <= 0)
		{
			BCastle.AddtoKilledQueue(free);
		
		}
		else
		{
			updatedhealers.Push(free);
			updatedhealerscount++;
		}
	}
	BCastle.sethealercount(0);
		for (int i = 0;i < updatedhealerscount;i++)
		{
			updatedhealers.Pop(free);
			BCastle.AddHealertoStack(free);
		}

}
