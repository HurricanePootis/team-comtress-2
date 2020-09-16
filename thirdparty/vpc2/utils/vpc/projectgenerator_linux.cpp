/**
 * 
 * Adapter for "project" generators on Linux
 * 
 */ 
#include "projectgenerator_linux.h"

struct linux_project_generator_t
{
	const char* name;
	CLinuxProjectGenerator* generator;
};

CUtlVector<linux_project_generator_t>* g_pGenerators;

CLinuxProjectGenerator::CLinuxProjectGenerator(const char* name)
{
	if(!g_pGenerators) g_pGenerators = new CUtlVector<linux_project_generator_t>();
	g_pGenerators->AddToTail(linux_project_generator_t {name, this});
}

CLinuxProjectGenerator* CLinuxProjectGenerator::GetGenerator(const char* name)
{
	for(int i = 0; i < g_pGenerators->Count(); i++)
	{
		auto gen = (*g_pGenerators)[i];
		if(strcmp(gen.name, name) == 0) return gen.generator;
	}
	return nullptr;
}

void CLinuxProjectGenerator::ExecuteGenerators(CSpecificConfig* pRelease, CSpecificConfig* pDebug, const char* folder, CBaseProjectDataCollector* generator)
{
	for(int i = 0; i < g_pGenerators->Count(); i++)
	{
		(*g_pGenerators)[i].generator->Write(pRelease, pDebug, folder, generator);
	}
}