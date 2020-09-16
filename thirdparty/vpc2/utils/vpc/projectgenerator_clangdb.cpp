/**
 * 
 * Project and solution generator for clangdb compile_commands.json 
 * 
 */ 
#include "projectgenerator_linux.h"
#include "solutiongenerator_linux.h"

static const char *g_pOption_BufferSecurityCheck = "$BufferSecurityCheck";
static const char *g_pOption_CustomBuildStepCommandLine = "$CustomBuildStep/$CommandLine";
static const char *g_pOption_PostBuildEventCommandLine = "$PostBuildEvent/$CommandLine";
static const char *g_pOption_CompileAs = "$CompileAs";
static const char *g_pOption_ConfigurationType = "$ConfigurationType";
static const char *g_pOption_Description = "$Description";
static const char *g_pOption_EntryPoint = "$EntryPoint";
static const char *g_pOption_ExtraCompilerFlags = "$GCC_ExtraCompilerFlags";
static const char *g_pOption_ExtraLinkerFlags = "$GCC_ExtraLinkerFlags";
static const char *g_pOption_CustomVersionScript = "$GCC_CustomVersionScript";
static const char *g_pOption_ForceInclude = "$ForceIncludes";
static const char *g_pOption_IgnoreAllDefaultLibraries = "$IgnoreAllDefaultLibraries";
static const char *g_pOption_LocalFrameworks = "$LocalFrameworks";
static const char *g_pOption_LowerCaseFileNames = "$LowerCaseFileNames";
static const char *g_pOption_OptimizerLevel = "$OptimizerLevel";
static const char *g_pOption_AdditionalDependencies = "$AdditionalDependencies";
static const char *g_pOption_Outputs = "$Outputs";
static const char *g_pOption_PrecompiledHeader = "$Create/UsePrecompiledHeader";
static const char *g_pOption_PrecompiledHeaderFile = "$PrecompiledHeaderFile";
static const char *g_pOption_SymbolVisibility = "$SymbolVisibility";
static const char *g_pOption_SystemFrameworks = "$SystemFrameworks";
static const char *g_pOption_SystemLibraries = "$SystemLibraries";
static const char *g_pOption_UsePCHThroughFile = "$Create/UsePCHThroughFile";
static const char *g_pOption_TargetCopies = "$TargetCopies";
static const char *g_pOption_TreatWarningsAsErrors = "$TreatWarningsAsErrors";

struct clangdb_file_t
{
	CUtlStringList includes;
	CUtlStringList defines;
};

struct clangdb_project_t
{
	CUtlVector<clangdb_file_t> files;
	CUtlStringList includes;
	CUtlStringList defines;
	CUtlStringList flags;
};

class CClangDbProjectGenerator : public CLinuxProjectGenerator
{
public:
	CClangDbProjectGenerator();

	virtual void Write(CSpecificConfig* pRelease, CSpecificConfig* pDebug, const char* folder, CBaseProjectDataCollector* generator);
};

class CClangDbSlnGenerator : public CLinuxSolutionGenerator
{
public:
	CClangDbSlnGenerator();

	virtual void WriteSolution(const char *pSolutionFilename, CUtlVector<CDependency_Project*> &projects);
};
 
/*

PROJECT GENERATOR COMPONENT

*/

CClangDbProjectGenerator::CClangDbProjectGenerator() :
	CLinuxProjectGenerator("clangdb")
{

}

void CClangDbProjectGenerator::Write(CSpecificConfig* pRelease, CSpecificConfig* pDebug, const char* folder, CBaseProjectDataCollector* generator)
{
	/* Only generate for debug for now */

}

/*

SOLUTION GENERATOR COMPONENT

*/


CClangDbSlnGenerator::CClangDbSlnGenerator() :
	CLinuxSolutionGenerator("clangdb")
{

}

void CClangDbSlnGenerator::WriteSolution(const char* pSolutionFilename, CUtlVector<CDependency_Project*>& projects)
{

}

