#pragma once

#include "CoreMinimal.h"

class FThreadClass:public FRunnable
{
public:
	virtual uint32 Run() override;

public:
	TSharedPtr<class FMyClass> MyClass;
};
