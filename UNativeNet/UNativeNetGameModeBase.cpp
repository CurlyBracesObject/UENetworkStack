// Copyright Epic Games, Inc. All Rights Reserved.


#include "UNativeNetGameModeBase.h"

#include "FThreadClass.h"
#include "XmlFile.h"
#include "MyBox.pb.h"
#include "NativeNetPlayerController.h"

AUNativeNetGameModeBase::AUNativeNetGameModeBase()
{
	MyThread=nullptr;
	PlayerControllerClass=ANativeNetPlayerController::StaticClass();
}

void AUNativeNetGameModeBase::RunThread()
{
	/*//接口实例对象
	MyClass=MakeShareable(new FMyClass);
	//启动线程 返回一个线程对象
	MyThread=FRunnableThread::Create(MyClass.Get(),TEXT("MyThreadTest"));
	
	UE_LOG(LogTemp, Log, TEXT("启动线程"));*/
	char* MyChar="你好，我是测试文本！";
	TCHAR* MyTChar=UTF8_TO_TCHAR(MyChar);
	UE_LOG(LogTemp, Log, TEXT("====%s"),MyTChar);
}

void AUNativeNetGameModeBase::StopMyThread()
{
	//停止线程执行
	if(MyThread)
	{
		UE_LOG(LogTemp, Log, TEXT("***********主动关闭线程"));
		MyThread->Kill(true);
		UE_LOG(LogTemp, Log, TEXT("*************调用主动关闭线程函数结束！"));
		delete MyThread;//删除线程 清理接口对象
		MyThread=nullptr;
		MyClass=nullptr;
	}
}

void AUNativeNetGameModeBase::RunOtherThread()
{
	UE_LOG(LogTemp, Log, TEXT("启动了另外一条线程"));
	
	//启动另外一条线程
	TSharedPtr<FThreadClass> ThreadClass=MakeShareable(new FThreadClass);
	ThreadClass->MyClass=MyClass;
	auto Thread=FRunnableThread::Create(ThreadClass.Get(),TEXT("第二条"));
}

void AUNativeNetGameModeBase::RequestHttpGet(const FString& Url)
{
	if(!HttpHelper)
	{
		HttpHelper=MakeShareable(new FHttpHelper);
	}
	HttpHelper->RequestHttpGet(*Url);
}

void AUNativeNetGameModeBase::RequestHttpPost(const FString& Url, const FString& Msg)
{
	if(!HttpHelper)
	{
		HttpHelper=MakeShareable(new FHttpHelper);
	}
	HttpHelper->RequestHttpPost(*Url,Msg);
}

void AUNativeNetGameModeBase::ConnectSocket()
{
	if(!SocketHepler)
	{
		SocketHepler=MakeShareable(new FSocketHepler);
	}
	if(SocketHepler->Connect(TEXT("127.0.0.1"),8060))
	{
		SocketHepler->Listen();
	}
}

void AUNativeNetGameModeBase::SendSocketMsg(const FString& Msg)
{
	if(SocketHepler)
	{
		SocketHepler->SendMessage(Msg);
	}
}

void AUNativeNetGameModeBase::SendUdpMessage(const FString& Message)
{
	if(!UdpHelper)
	{
		UdpHelper=MakeShareable(new FUdpHelper);
	}
	UdpHelper->SendMessage(Message);
	UdpHelper->StartListen();
}

void AUNativeNetGameModeBase::ParseXML()
{
	/*MyBox box;
	box.set_age(100);
	UE_LOG(LogTemp, Log, TEXT("ok==%05d"),box.age());*/
	//数据结果 转成 数据流
	//创建xml文档读取器
	TSharedPtr<FXmlFile> XmlFile=MakeShareable(new FXmlFile);
	//尝试解析路径资产
	if(XmlFile->LoadFile(TEXT("e:\\a.xml")))
	{
		FXmlNode* RootNode=XmlFile->GetRootNode();
		if(RootNode)
		{
			FString RootTag=RootNode->GetTag();
			UE_LOG(LogTemp, Log, TEXT("== %s"),*RootTag);
			FXmlNode* AxNode = RootNode->GetChildrenNodes()[0];
			FString AxAttributeOne=AxNode->GetAttribute(TEXT("graduate"));
			UE_LOG(LogTemp, Log, TEXT("AxAttributeOne:%s"),*AxAttributeOne);

			FString AddrStr=AxNode->GetChildrenNodes()[0]->GetContent();
			UE_LOG(LogTemp, Log, TEXT("Ax Addr:%s"),*AddrStr);
		}
	}
	UE_LOG(LogTemp, Log, TEXT("a.xml read successfully"));
	FString XmlStr=TEXT("<A></A>");
	TSharedPtr<FXmlFile> XmlFileWrite=MakeShareable(new FXmlFile(XmlStr,EConstructMethod::ConstructFromBuffer));
	XmlFileWrite->GetRootNode()->AppendChildNode(TEXT("From"),TEXT("Jhon"));
	XmlFileWrite->Save(TEXT("e:\\b.xml"));
	UE_LOG(LogTemp, Log, TEXT("b.xml is written successfully"));

	UE_LOG(LogTemp, Log, TEXT("Parsing XML to compare file size with PB: "));
	TSharedPtr<FXmlFile> XmlFileCompare=MakeShareable(new FXmlFile);
	if(XmlFileCompare->LoadFile(TEXT("e:\\mybox.xml")))
	{
		FXmlNode* RootNode=XmlFileCompare->GetRootNode();
		if(RootNode)
		{
			FString Age=RootNode->GetAttribute(TEXT("age"));
			FString Name=RootNode->GetAttribute(TEXT("name"));

			TArray<FXmlNode*> NumsNode=RootNode->GetChildrenNodes();
			UE_LOG(LogTemp, Log, TEXT("XML Data - Age:%s,Name:%s, ArraySize:%d"),*Age,*Name,NumsNode.Num());

			FString XmlContent;
			if(FFileHelper::LoadFileToString(XmlContent,TEXT("e:\\mybox.xml")))
			{
				int32 XmlSize=XmlContent.Len();
				UE_LOG(LogTemp, Log, TEXT("Xml File Size: %d bytes"),XmlSize);
			}
			
		}
	}
	
}

void AUNativeNetGameModeBase::TestProtobuf()
{
	//创建和序列化
	MyBox box;
	box.set_age(100);
	box.set_name("PlayerData");
	box.add_nums(10);
	box.add_nums(20);

	UE_LOG(LogTemp, Log, TEXT("Age:%d,Name: %s,theArraySize: %d"),
		box.age(),UTF8_TO_TCHAR(box.name().c_str()),box.nums_size());

	std::string data;
	box.SerializeToString(&data);
	UE_LOG(LogTemp, Log, TEXT("Serialized size：%d bytes"),data.size());
	
}
