// find
#include "sectree.h"

// add after

#include <unordered_set>

// find
	size_t		GetMonsterCountInMap(long lMpaIndex, uint32_t dwVnum);

// add after
#ifdef ENABLE_ENTITY_PRELOADING
	void GeneratePreloadedEntitiesMap(int32_t mapIndex, LPSECTREE_MAP lpMapSectree);
	void ExtendPreloadedEntitiesMap(int32_t mapIndex, uint32_t mob_race);
	void SendPreloadEntitiesPacket(LPCHARACTER ch);
#endif

// find
	typedef std::unordered_map<long, int> PrivateIndexMapType;
	PrivateIndexMapType next_private_index_map_;

// add this after
#ifdef ENABLE_ENTITY_PRELOADING
	std::unordered_map<int32_t, std::unordered_set<uint32_t>> m_preloadedEntities;
#endif
