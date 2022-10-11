// find
void CInputLogin::Entergame(LPDESC d, const char* data)
{
	...
}

// add this as the last thing in the method
#ifdef ENABLE_ENTITY_PRELOADING
	SECTREE_MANAGER::Instance().SendPreloadEntitiesPacket(ch);
#endif

// if you don't know where, just look for
	if (g_noticeBattleZone)
	{
		if (FN_is_battle_zone(ch))
		{
			ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("There may be forced battles on this map."));
			ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("If you do not agree to this provision"));
			ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("Please return to your own master and father."));
		}
	}
// and add it after
