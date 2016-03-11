#pragma once
#include "ITessellation.h"

class TESSELLATION_API FTessellation : public ITessellation
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
