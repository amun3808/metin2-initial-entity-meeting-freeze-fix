// find
virtual void AdjustCollisionWithOtherObjects(CActorInstance* pInst);

// add
#ifdef ENABLE_ENTITY_PRELOADING
	void PreloadEntities();
	void ConstructPreloadedEntitiesMap();
#endif


// find
public:
	class CharacterIterator


// add BEFORE
#ifdef ENABLE_ENTITY_PRELOADING
	std::unordered_map < std::string, std::vector<uint32_t> > m_mapPreloadedEntities;
#endif
