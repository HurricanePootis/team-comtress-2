#include "solutiongenerator_linux.h"
#include "utlvector.h"

struct linux_sln_generator_t
{
	const char* name;
	CLinuxSolutionGenerator* generator;
};

CUtlVector<linux_sln_generator_t>* g_SlnGenerators;

CLinuxSolutionGenerator::CLinuxSolutionGenerator(const char* name)
{
	if(!g_SlnGenerators) g_SlnGenerators = new CUtlVector<linux_sln_generator_t>();
	g_SlnGenerators->AddToTail(linux_sln_generator_t{name, this});
}

void CLinuxSolutionGenerator::ExecuteSolutionGenerators(const char* pFile, CUtlVector<CDependency_Project*>& projects)
{
	for(int i = 0; i < g_SlnGenerators->Count(); i++)
	{
		((*g_SlnGenerators)[i]).generator->WriteSolution(pFile, projects);
	}
}