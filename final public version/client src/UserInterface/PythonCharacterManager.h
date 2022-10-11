// find
	void								RefreshAllGuildMark();

// add these after
#ifdef ENABLE_ENTITY_PRELOADING
	void PreloadEntities();

	std::vector<uint32_t>* GetPreloadedEntitiesVectorPtr()
	{
		return &m_vecPreloadedEntities;
	};
#endif

// find
public:
	class CharacterIterator

// add BEFORE
#ifdef ENABLE_ENTITY_PRELOADING
private:
	std::vector<uint32_t> m_vecPreloadedEntities;
#endif
