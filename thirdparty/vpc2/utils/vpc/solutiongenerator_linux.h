/**
 * 
 * Linux-only solution adapter
 * 
 */ 
#pragma once

#include "vpc.h"
#include "dependencies.h"

class CLinuxSolutionGenerator
{
public:
	CLinuxSolutionGenerator(const char* name);

	virtual void WriteSolution(const char *pSolutionFilename, CUtlVector<CDependency_Project*> &projects) = 0;

	static void ExecuteSolutionGenerators(const char* pSlnFile, CUtlVector<CDependency_Project*>& projects);
};