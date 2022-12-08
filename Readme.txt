UPDATE 17/10/2022:
If we send the packet from input_login it is guaranteed to have the NPCs loaded,
since we're sending it in the game phase, so we don't need to store the entities
in a vector to make sure we're loading them after the NPC paths have been set.

Since the entities are sent asynchronously, one by one, they will load while showing(rendering?) the game world, in the beginning of game phase.

Files removed: PythonCharacterManager.cpp, PythonCharacterManager.h, PythonNetworkStreamPhaseLoading.cpp
Updated Methods in PythonNetworkStreamPhaseGame.cpp


UPDATE 08/12/2022:
Refactored to use unordered_set from the beginning instead of creating a vector, 
then filtering unique entities by creating a set, and then moving them back to a vector.

Extended to load the full spectrum of entities(both static and dynamic),
	except for PC(which are loaded in loading phase), WARP, GOTO, and DOOR.
