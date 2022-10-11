#ifdef ENABLE_ENTITY_PRELOADING
	PyModule_AddIntConstant(poModule, "ENABLE_ENTITY_PRELOADING", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_ENTITY_PRELOADING", 0);
#endif