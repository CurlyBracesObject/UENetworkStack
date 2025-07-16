#pragma once

#include "CoreMinimal.h"

class FSocketHepler:public FRunnable
{
public:
	//外部需要创建、销毁对象
	FSocketHepler();

	virtual ~FSocketHepler();

	//外部接口 - 给用户使用的功能
	bool Connect(const FString& IP,const int32 Port);

	void Listen();
	
	void Close();

	//void Abort();

	void SendMessage(const FString& Message);

	
	
protected://内部接口 - 给子类重写的功能  
	virtual uint32 Run() override;

protected://内部实现 - 只有本类使用的数据

	FSocket* NativeSocket;

	FRunnableThread* MyThread;

	bool bReceiving;
};
