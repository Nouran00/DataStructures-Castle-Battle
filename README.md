# Castle battle simulation with different types of enemies criteria
the simulation receives information about a list of enemies as input from an input file. 
This list represents the scenario to be simulated. For each enemy the system will receive the following information:
- Arrival Time stamp (Enemy Arrival Time): When the enemy arrives.
- Health: The starting health of the enemy.
- Power: The power of the enemy.
- Reload Period: Time for an enemy to reload its weapon.
- Speed: number of meters an enemy can move in a single time step.
- Type: fighter, freezer or healer

# Game Rules
- Each enemy has its own speed and its own fire power.
- All enemies start at 60 meters distance from the castle.
- In general, an enemy moves at its original speed each time step.But an enemy with (health < 1/2 its original health) moves at its half original speed.
- The minimum possible distance for any enemy to approach to the castle is 2 meters.
- Enemies can move at their reload period but cannot act. (cannot fire nor heal)
- By default all enemies move in the forward direction (approaching castle) but only healers can move backward. When a healer reaches end of forward direction, it starts moving backward until it reaches end of backward direction where it turns back and moves forward again and so on.
- Healer can heal only enemies that are at most 2 meters ahead in his moving direction.
- Healer cannot heal killed enemies. Healer cannot heal frosted enemies.
- A castle can attack any enemy type.
- Both castle and enemies can attack each other at the same time step.
- A castle can attack at most N enemies at each time step. (N is loaded from input file).
- A castle can either fire bullets or throw ice to freeze an active enemy.
- At random time steps the castle throws ice instead of bullets. The percentage of ice fire should be around 20% of all castle fires.
-  If Castle kills a healer within a distance of 5 meters from the castle, it uses healer's tools to recover its health by a percentage of 3%.
- If an active enemy is hit by castle ice, it gets frosted for some time steps until ice melts
- A frosted enemy is affected by castle fire but is not affected by castle ice.
- A frosted castle cannot attack enemies.
- A frosted castle is affected by fighter attacks only. Freezer enemy has no effect on it.
- The game is “win” if all enemies are killed. The game is “loss” if the castle is destroyed. Otherwise, the game is "drawn".

# Enemies picking criteria:
As mentioned in the game rules, a castle picks at most N enemies (in total) to attack at each time step. Attack means to fire bullets or to throw ice with certain probability. The criteria to pick an enemy to attack are as follows:
1. First attack fighters. The castle should pick fighters depending on their distance, power, and health, status (active or frosted), remaining time steps for an enemy to end reload period. Think about a suitable formula to give a priority for each fighter according to at least four of the above factors. Then pick higher priority fighters first.
2. Then (if N is not exhausted yet), pick healers to attack. A fresh healer who has just joined the forces is picked first. This means that healers are picked in the reverse order of their arrival (Last-Come-First-Serve)
3. Finally (if N is not exhausted yet) pick freezers to attack. A freezer that arrived first should be attacked first (First-Come-First-Serve).
