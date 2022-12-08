UPDATE 17/10/2022:
If we send the packet from input_login it is guaranteed to have the NPCs loaded,
since we're sending it in the game phase, so we don't need to store the entities
in a vector to make sure we're loading them after the NPC paths have been set.

Since the entities are sent asynchronously, one by one, they will load while showing(rendering?) the game world, in the beginning of game phase.

Files removed: PythonCharacterManager.cpp, PythonCharacterManager.h, PythonNetworkStreamPhaseLoading.cpp
Updated Methods in PythonNetworkStreamPhaseGame.cpp


08/12/2022 UPDATE_1:
Refactored to use unordered_set from the beginning instead of creating a vector, 
then filtering unique entities by creating a set, and then moving them back to a vector.

Extended to load the full spectrum of entities(both static and dynamic),
	except for PC(which are loaded in loading phase), WARP, GOTO, and DOOR.

08/12/2022 UPDATE_2:
Looks like the biggest factor slowing us down(and creating the freeze) are the motion thing registrations,
	which I'm too lazy of coming up with some other way of loading them.
	To see what I'm talking about, go to GameLib/ActorInstanceData.cpp
	and find bool CActorInstance::SetRace(uint32_t eRace)

I'm too sick of it to look into alternative ways of fixing this,
so we'll just create a dummy entity to force them to load, and then get rid of it. EZ

With these changes, we should see around 97 - 99% reduction in processing time(from up to 200ms down to about 0 - 5ms),
however, loading will slow down with about 1-3 seconds, but that's insignificant compared to the benefits.
