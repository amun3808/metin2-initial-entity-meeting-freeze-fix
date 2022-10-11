void CPythonNetworkStream::StartGame()
{
#ifdef ENABLE_ENTITY_PRELOADING
	CPythonCharacterManager::Instance().PreloadEntities();
#endif
	m_isStartGame = TRUE;
}