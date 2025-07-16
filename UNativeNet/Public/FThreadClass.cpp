#include "FThreadClass.h"

#include "FMyClass.h"

uint32 FThreadClass::Run()
{
	if(MyClass)
	{
		//修改Num时必须获得锁
		FScopeLock Lock(&MyClass->NumMutex);
		MyClass->Num=0;
		UE_LOG(LogTemp, Log, TEXT("第二个线程set num为0"));
	}

	return 0;
}
