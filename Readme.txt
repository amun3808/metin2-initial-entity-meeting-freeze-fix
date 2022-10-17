UPDATE 17/10/2022:
If we send the packet from input_login it is guaranteed to have the NPCs loaded,
since we're sending it in the game phase, so we don't need to store the entities
in a vector to make sure we're loading them after the NPC paths have been set.

Since the entities are sent asynchronously, one by one, they will load while showing(rendering?) the game world, in the beginning of game phase.

Files removed: PythonCharacterManager.cpp, PythonCharacterManager.h, PythonNetworkStreamPhaseLoading.cpp
Updated Methods in PythonNetworkStreamPhaseGame.cpp
