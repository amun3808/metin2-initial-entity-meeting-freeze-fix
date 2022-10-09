The old version required root changes, the new version is only src. 
It still requires the list of entities in root, of course.


NOTE: The parser for old group structures has been fixed.


Description:
This is a solution for those micro freezes when you meet an entity(mob, npc) for the first time. 
The python script should extract all mobs and NPCs from each map and list them in a file called 'preload.txt'.
When opening the client, that list is going to be loaded as an unordered_map belonging to CPythonCharacterManager.
When the loading phase is finished, right before showing the game 'world', all (unique) mobs in that specific map(the one where the player is going to show up) are going to be loaded ahead of time, so that whenever you're meeting an entity, the client only has to create it with the data coming from the server, instead of loading its files(model, textures, etc) as well.
