// Fill out your copyright notice in the Description page of Project Settings.


#include "FMyClass.h"

FMyClass::FMyClass()
{
	Num=0;
}

FMyClass::~FMyClass()
{
}

bool FMyClass::Init()
{
	UE_LOG(LogTemp, Log, TEXT("Init"));
	return true;
}

uint32 FMyClass::Run()
{
	UE_LOG(LogTemp, Log, TEXT("Run运行！"));
	
	bRunning=true;
	
	while(Num<7 && bRunning)
	{
		{
			FScopeLock Lock(&NumMutex);//FScopeLock 的构造函数签名 有指针，需要指针参数
			Num++;
		}
		//Num++;
		UE_LOG(LogTemp, Log, TEXT("Num:%d"),Num);
		FPlatformProcess::Sleep(1);
	}
	UE_LOG(LogTemp, Log, TEXT("结束循环"));

	//FPlatformProcess::Sleep(5);
	/*// 加这行验证Num是否被修改
	UE_LOG(LogTemp, Log, TEXT("Sleep后的Num: %d"), Num);*/
	// 持续监控Num的变化
	for(int i = 0; i < 10; i++)
	{
		UE_LOG(LogTemp, Log, TEXT("监控第%d秒，Num: %d"), i, Num);
		FPlatformProcess::Sleep(1);
	}
	
	if(Num>5)
	{
		UE_LOG(LogTemp, Log, TEXT("Num成功超过5了，Num: %05d"),Num);
	}else
	{
		UE_LOG(LogTemp, Log, TEXT("Num没有超过5，Num: %05d"),Num);
	}

	

	return 0;
}

void FMyClass::Stop()
{
	UE_LOG(LogTemp, Log, TEXT("Stop"));
	bRunning=false;
}

void FMyClass::Exit()
{
	UE_LOG(LogTemp, Log, TEXT("Exit"));
}
