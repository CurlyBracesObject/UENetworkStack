// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FHttpHelper.h"
#include "FMyClass.h"
#include "FSocketHepler.h"
#include "FUdpHelper.h"
#include "GameFramework/GameModeBase.h"
#include "UNativeNetGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UNATIVENET_API AUNativeNetGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AUNativeNetGameModeBase();

protected:
	UFUNCTION(Exec)
	void RunThread();
	UFUNCTION(Exec)
	void StopMyThread();
	UFUNCTION(Exec)
	void RunOtherThread();
	UFUNCTION(Exec)
	void RequestHttpGet(const FString& Url);
	//加调用
	UFUNCTION(Exec)
	void RequestHttpPost(const FString& Url,const FString& Msg);
	UFUNCTION(Exec)
	void ConnectSocket();
	UFUNCTION(Exec)
	void SendSocketMsg(const FString& Msg);
	UFUNCTION(Exec)
	void SendUdpMessage(const FString& Message);
	UFUNCTION(Exec)
	void ParseXML();
	UFUNCTION(Exec)
	void TestProtobuf();

protected:
	TSharedPtr<FMyClass> MyClass;
	
	FRunnableThread* MyThread;
	
	TSharedPtr<FHttpHelper> HttpHelper;
	
	TSharedPtr<FSocketHepler> SocketHepler;

	TSharedPtr<FUdpHelper> UdpHelper;
};
