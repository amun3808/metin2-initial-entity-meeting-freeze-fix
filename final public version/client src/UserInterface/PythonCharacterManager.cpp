// find
void CPythonCharacterManager::DeleteAllInstances()

// add before
#ifdef ENABLE_ENTITY_PRELOADING
void CPythonCharacterManager::PreloadEntities()
{
	CInstanceBase::SCreateData d{};
	for (const auto& vnum : m_vecPreloadedEntities)
	{
		d.m_dwRace = vnum;
		d.m_dwVID = vnum;
		TraceError("Preloading %d", vnum);
		if (!CPythonCharacterManager::Instance().CreateInstance(d))
			TraceError("Failed to preload race %d", vnum);
	}
}
#endif


// find
void CPythonCharacterManager::Destroy()
{
	DeleteAllInstances();

	CInstanceBase::DestroySystem();

	__Initialize();
}

// add this inside
#ifdef ENABLE_ENTITY_PRELOADING
	m_vecPreloadedEntities.clear();
#endif

// like this
void CPythonCharacterManager::Destroy()
{
#ifdef ENABLE_ENTITY_PRELOADING
	m_vecPreloadedEntities.clear();
#endif
	DeleteAllInstances();

	CInstanceBase::DestroySystem();

	__Initialize();
}