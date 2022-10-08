// add wherever you want
#ifdef ENABLE_ENTITY_PRELOADING
#include "../eterPack/EterPackManager.h"
void CPythonCharacterManager::ConstructPreloadedEntitiesMap()
{
	if (!CEterPackManager::Instance().isExist("preload.txt"))
	{
		TraceError("Couldn't find preload.txt");
		return;
	}

	CMappedFile file;
	const void* pData = nullptr;
	CEterPackManager::Instance().Get(file, "preload.txt", &pData);

	CMemoryTextFileLoader tfl;
	tfl.Bind(file.Size(), pData);
	uint32_t linesNum = tfl.GetLineCount();

	char* context = nullptr;
	std::string curMap;

	for (uint32_t i = 0; i < linesNum; i++)
	{
		char* c_rstLine = const_cast<char*>(tfl.GetLineString(i).c_str());
		if (!c_rstLine || c_rstLine[0] == '\0')
			continue;

		char* currentKey = strtok_s(c_rstLine, " :\t\r\n", &context);
		if (!currentKey || currentKey[0] == '\0')
			continue;

		if (stricmp(currentKey, "Map") == 0)
		{
			const char* value = strtok_s(NULL, " :\t\r\n", &context);
			if (!value)
				break;// just break.. map name is absolutely required

			curMap.assign(value);
			if (m_mapPreloadedEntities.find(curMap) == m_mapPreloadedEntities.end())
				m_mapPreloadedEntities.insert({ curMap, {}});
		}
		else
		{
			if (m_mapPreloadedEntities.find(curMap) != m_mapPreloadedEntities.end())
				m_mapPreloadedEntities.at(curMap).push_back(atoi(currentKey));
		}
	}
}

void CPythonCharacterManager::PreloadEntities()
{
	std::string mapName = CPythonBackground::Instance().GetWarpMapName();
#ifdef _DEBUG
	Timer t("Preloading Entities for map %s", mapName.c_str());
#endif
	CInstanceBase::SCreateData d{};

	if (m_mapPreloadedEntities.find(mapName) == m_mapPreloadedEntities.end())
	{
		TraceError("No entities to preload for %s", mapName.c_str());
		return;
	}

	for (const auto& vnum : m_mapPreloadedEntities.at(mapName))
	{
		d.m_dwRace = vnum;
		d.m_dwVID = vnum;
		TraceError("Preloading %d", vnum);
		if (!CPythonCharacterManager::Instance().CreateInstance(d))
			TraceError("Failed to preload race %d", vnum);
	}
}
#endif


// FIND
void CPythonCharacterManager::__Initialize()
{
	...somestuff
}
// add this inside
void CPythonCharacterManager::__Initialize()
{
	// this
#ifdef ENABLE_ENTITY_PRELOADING
	ConstructPreloadedEntitiesMap();
#endif
	...somestuff
}

// FIND(should be right before the other one)
void CPythonCharacterManager::Destroy()
{
	..someotherstuff
}

// add/modify like this
void CPythonCharacterManager::Destroy()
{
	// this
#ifdef ENABLE_ENTITY_PRELOADING
	m_mapPreloadedEntities.clear();
#endif
	...someotherstuff
}





