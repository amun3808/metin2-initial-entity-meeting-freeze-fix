// find
void CPythonNetworkStream::StartGame()
{
	m_isStartGame=TRUE;
}

// Add/Change like this
void CPythonNetworkStream::StartGame()
{
#ifdef ENABLE_ENTITY_PRELOADING
	TraceError("CURRENT WARP MAP NAME %s", CPythonBackground::Instance().GetWarpMapName());
	CPythonCharacterManager::Instance().PreloadEntities();
#endif
	m_isStartGame=TRUE;
}

// Why are we doing this here?
// Because we need the name of the map and all the npcs/mobs need to be initialized
// Which happen when calling __LoadMap and __LoadNPC in root
// If you don't want to do this here, you can swap those 2 (root)function calls and add 'PreloadEntities' at the end of ::Warp, in 
