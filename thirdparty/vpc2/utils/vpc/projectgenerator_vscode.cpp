/**
 * 
 * Project generator for VS Code
 * 
 * This isn't much of a project generator actually! Things are generated alongside the Makefile generator on Linux
 * 
 */ 
#include "projectgenerator_linux.h"

/* This generator is Linux-only! */
#ifndef _WIN32

#include <sys/stat.h>
#include "tier1/utlvector.h"
#include "tier0/platform.h"
#include "vpc.h"
#include <sys/unistd.h>

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


class CVSCodeGenerator : public CLinuxProjectGenerator
{
public:
	CVSCodeGenerator() :
		CLinuxProjectGenerator("vscode")
	{

	}


	virtual void Write(CSpecificConfig* pRelease, CSpecificConfig* pDebug, const char* folder, CBaseProjectDataCollector* generator);

	void WritePropertiesForConfig(CSpecificConfig* config, FILE* fs);
};


static CVSCodeGenerator g_VSCodeGenerator;

void CVSCodeGenerator::Write(CSpecificConfig* pRelease, CSpecificConfig* pDebug, const char* folder, CBaseProjectDataCollector* generator)
{
	if(!g_pVPC->m_bVSCode) return;
	
	Assert(pRelease);
	Assert(pDebug);

	char vscode_folder[512];
	snprintf(vscode_folder, sizeof(vscode_folder), "%s/.vscode", folder);

	/* Remove old vscode folder */
	rmdir(vscode_folder);

	/* Create new vscode folder */
	_mkdir(vscode_folder);

	char vscode_properties[512];
	snprintf(vscode_properties, sizeof(vscode_properties), "%s/c_cpp_properties.json", vscode_folder);

	printf("Writing %s\n", vscode_properties);

	/* Open the properties */
	FILE* fprops = fopen(vscode_properties, "w");

	if(!fprops)
	{
		printf("ERROR OPENING %s\n", vscode_properties);
		abort();
	}

	fputs("{\n\t\"configurations\": [\n\t\t", fprops);

	this->WritePropertiesForConfig(pRelease, fprops);
	fputs(",\n", fprops);
	this->WritePropertiesForConfig(pDebug, fprops);
	fputs("\n],\n", fprops);
	fputs("\"version\": 4\n}\n", fprops);

	fflush(fprops);
	fclose(fprops);
}

void CVSCodeGenerator::WritePropertiesForConfig(CSpecificConfig* config, FILE* fs)
{
	fprintf(fs, "{\n\"name\": \"%s\",\n", config->GetConfigName());

	/* Includes and defines */
	{
		fprintf(fs, "\"includePath\": [\n");
		CSplitString includes(config->m_pKV->GetString(g_pOption_AdditionalIncludeDirectories), (const char**)g_IncludeSeparators, V_ARRAYSIZE(g_IncludeSeparators));
		
		for(int i = 0; i < includes.Count(); i++)
		{
			char* tmp = strdup(includes[i]);
			V_FixSlashes(tmp);
			if(i < includes.Count() - 1)
				fprintf(fs, "\"%s\",\n", tmp);
			else
				fprintf(fs, "\"%s\"\n", tmp);
			free(tmp);
		}
		fprintf(fs, "],\n\"defines\":[\n");

		CSplitString defines(config->m_pKV->GetString(g_pOption_PreprocessorDefinitions), (const char**)g_IncludeSeparators, V_ARRAYSIZE(g_IncludeSeparators));

		for(int i = 0; i < defines.Count(); i++)
		{
			if(i < defines.Count() - 1)
				fprintf(fs, "\"%s\",\n", defines[i]);
			else
				fprintf(fs, "\"%s\"\n", defines[i]);
		}
		fprintf(fs, "],\n");
	}

	/* We just use some defaults here */
	fprintf(fs, "\"compilerPath\": \"/usr/bin/gcc\",\n");
	fprintf(fs, "\"intelliSenseMode\": \"gcc-x86\",\n");
	fprintf(fs, "\"cStandard\": \"c99\",\n");
	fprintf(fs, "\"cppStandard\": \"c++11\"\n}");
}

#endif //_WIN32