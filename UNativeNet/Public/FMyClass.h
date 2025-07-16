// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UNATIVENET_API FMyClass:public FRunnable
{
public:
	FMyClass();
	~FMyClass();
	
	 virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

private:
	bool bRunning;
	

public:
	int32 Num;
	mutable FCriticalSection NumMutex;//添加互斥锁 允许在 const 成员函数中修改这个变量
	// 你需要类成员锁，因为：
	// 1. 多个线程要访问同一个FMyClass对象的Num
	// 2. 不同的方法（Run, Stop等）可能都要访问Num
	// 3. 锁需要在整个对象生命周期内存在
};
