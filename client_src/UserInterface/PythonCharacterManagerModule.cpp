// find
void initchrmgr()

// add BEFORE
#ifdef ENABLE_ENTITY_PRELOADING
PyObject* chrmgrPreloadEntity(PyObject* poSelf, PyObject* poArgs)
{
	int iEntityVnum;//race/mob vnum
	if (!PyTuple_GetInteger(poArgs, 0, &iEntityVnum))
		return Py_BuildException();

	CInstanceBase::SCreateData d{};
	d.m_dwRace = iEntityVnum;
	d.m_dwVID = iEntityVnum;
	if (!CPythonCharacterManager::Instance().CreateInstance(d))
		TraceError("Failed to preload race %d", iEntityVnum);

	return Py_BuildNone();
}
#endif


// Add this
#ifdef ENABLE_ENTITY_PRELOADING
		{ "PreloadEntity",				chrmgrPreloadEntity,					METH_VARARGS },
#endif

// before 
		{ NULL,							NULL,									NULL },
