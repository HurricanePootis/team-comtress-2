/**
 * 
 * projectgenerator_linux.h
 * 
 * Project generator for Linux systems.
 * This is an adapter around the Makefile generator
 * 
 * 
 */ 
#pragma once

#include "vpc.h"
#include "tier1/utlstack.h"
#include "projectgenerator_codelite.h"
#include "tier1/utlvector.h"
#include "tier1/utlstring.h"
#include "baseprojectdatacollector.h"



class CLinuxProjectGenerator
{
public:
	explicit CLinuxProjectGenerator(const char* name);

	virtual void Write(CSpecificConfig* pRelease, CSpecificConfig* pDebug, const char* folder, CBaseProjectDataCollector* generator) = 0;

	static CLinuxProjectGenerator* GetGenerator(const char* name);

	static void ExecuteGenerators(CSpecificConfig* pRelease, CSpecificConfig* pDebug, const char* filder, CBaseProjectDataCollector* generator);
};