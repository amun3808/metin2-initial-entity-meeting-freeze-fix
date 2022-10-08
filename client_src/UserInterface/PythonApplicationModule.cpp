// find
#ifdef ENABLE_DRAGON_SOUL_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_DRAGON_SOUL_SYSTEM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_DRAGON_SOUL_SYSTEM", 0);
#endif


// add this
#ifdef ENABLE_ENTITY_PRELOADING
	PyModule_AddIntConstant(poModule, "ENABLE_ENTITY_PRELOADING", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_ENTITY_PRELOADING", 0);
#endif
