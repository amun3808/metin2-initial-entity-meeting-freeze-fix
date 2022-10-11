// find
HEADER_GC_RESPOND_CHANNELSTATUS = 210,

// add
#ifdef ENABLE_ENTITY_PRELOADING
	HEADER_GC_PRELOAD_ENTITIES = 211,
#endif
// of just add it wherever the fuck you want.. Feel free to change the index as well, just don't forget about client src packet.h


// add this at the end (BEFORE #pragma pack())
#ifdef ENABLE_ENTITY_PRELOADING
/*** HEADER_GC_PRELOAD_ENTITIES ***/
typedef struct packet_preload_entities
{
	uint8_t header;
	uint16_t size;
	uint16_t count;
} TPacketGCPreloadEntities;
#endif
