# Optimizing Battle Simulators (Using AI Crowd Simulation)

This is a small research project on using crowd simulation to optimize a large amount of ai agents in a battle simulator.
Inspired by the millions of agents that some battle simulators can simulate. A good example of this is Ultimate Epic Battle Simulator (https://store.steampowered.com/app/616560/Ultimate_Epic_Battle_Simulator/), and its sequel Ultimate Epic Battle Simulator 2 (https://store.steampowered.com/app/1468720/Ultimate_Epic_Battle_Simulator_2/).


These are three common techniques that are used to optimize battle simulators:
1. Using the GPU instead of CPU, not only for rendering but also for pathfinding and ai behavior.
2. Crowd simulation, simulating a crowd making it look like every individual has its own behavior
3. Using flow fields for pathfinding

For this project, I'll be looking into crowd simulation.


The focus will still be on optimizing a battle simulator.
This means the algorithms we use need to very efficient.
They also need to be used for finding the closest enemy target in a crowd of enemies
They also need to be able to be used


In our case (a battle simulator)
The crowd will need to make its way to the closest enemy crowd
Once the crowd is close enough, all agents need to find their own closest target to attack.
Once that target dies, the agent needs to find the next closest target.


we need to simulate a crowd of soldiers, attacking another crowd of soldiers. This needs to be done in an opimized way, so that there can be as many as possible




















