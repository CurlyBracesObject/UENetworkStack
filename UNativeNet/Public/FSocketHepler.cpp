#include "FSocketHepler.h"

#include "Sockets.h"
#include "SocketSubsystem.h"

FSocketHepler::FSocketHepler()
{
	NativeSocket=nullptr;
	MyThread=nullptr;
	bReceiving=false;
}

FSocketHepler::~FSocketHepler()
{
	Close();
}

bool FSocketHepler::Connect(const FString& IP, const int32 Port)
{
	
	//创建链接地址
	TSharedRef<FInternetAddr> FInternetAddr=ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	//设置地址IP
	bool IsValid=false;
	FInternetAddr->SetIp(*IP,IsValid);//*IP: UE特有的语法糖，不是普通的指针解引用 调用FString的转换函数，*FString 返回的是 const TCHAR*
	if(!IsValid)//说明地址格式解析错误！
	{
		UE_LOG(LogTemp, Log, TEXT("Address format error"));
		return false;
	}

	//设置端口
	FInternetAddr->SetPort(Port);/*IP地址 = 大楼地址（192.168.1.1）
端口 = 房间号（80, 443, 8080等）
Socket = 电话机
SetPort() = 告诉总机"我要找80号房间"*/
	//if(NativeSocket){Close();}
	//创建Socket对象
	NativeSocket=ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream,TEXT("MySocket"));

	//启动链接
	return NativeSocket->Connect(*FInternetAddr);
}

void FSocketHepler::Listen()
{
	//监听 启动线程监听
	bReceiving=true;
	MyThread=FRunnableThread::Create(this,TEXT("MySocketThread"));
}

/*void FSocketHepler::Close()//第一次：关闭程序的一瞬间 析构函数 对象销毁时自动调用 
{
	//设置退出标志
	if(bReceiving)
	{
		bReceiving=false;
		UE_LOG(LogTemp, Log, TEXT("Close()-正在关闭Socket连接..."));
	}

	//最后关闭套接字 关闭Socket
	if(NativeSocket)
	{
		NativeSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(NativeSocket);
		NativeSocket=nullptr;
		UE_LOG(LogTemp, Log, TEXT("Close()-Socket已关闭"));
	}
	//等待线程结束
	if(MyThread)
	{
		//MyThread->WaitForCompletion();
		
		MyThread->Kill();
		delete MyThread;
		MyThread=nullptr;
		UE_LOG(LogTemp, Log, TEXT("Close()-工作线程已关闭"));
	}
}*/
/*void FSocketHepler::Close()
{
	UE_LOG(LogTemp, Log, TEXT("Close() - 开始关闭Socket连接..."));
    
	// 🔑 关键改进1：首先设置退出标志，让线程自然退出
	if (bReceiving)
	{
		bReceiving = false;
		UE_LOG(LogTemp, Log, TEXT("Close() - 设置退出标志"));
	}

	// 🔑 关键改进2：等待线程完成后再清理资源
	if (MyThread)
	{
		UE_LOG(LogTemp, Log, TEXT("Close() - 等待工作线程结束..."));
		MyThread->WaitForCompletion();  // 等待线程自然结束，不用Kill()
		delete MyThread;
		MyThread = nullptr;
		UE_LOG(LogTemp, Log, TEXT("Close() - 工作线程已安全关闭"));
	}

	// 🔑 关键改进3：最后才关闭Socket资源
	if (NativeSocket)
	{
		NativeSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(NativeSocket);
		NativeSocket = nullptr;
		UE_LOG(LogTemp, Log, TEXT("Close() - Socket已关闭"));
	}
}*/
void FSocketHepler::Close()
{
	//UE_LOG(LogTemp, Log, TEXT("Close() - 开始关闭Socket连接..."));
    
	// 关键改进：首先设置退出标志
	if (bReceiving)
	{
		bReceiving = false;
		UE_LOG(LogTemp, Log, TEXT("Close() - Set exit flag:bReceiving = false"));
	}

	//关键改进：先关闭Socket，让Recv()立即失败退出    这里关闭了网络连接！
	if (NativeSocket)
	{
		NativeSocket->Close();
		UE_LOG(LogTemp, Log, TEXT("Close() - Socket connection has been closed"));
	}

	// 现在等待线程结束（Recv失败后会快速退出）
	if (MyThread)
	{
		UE_LOG(LogTemp, Log, TEXT("Close() - Waiting for the work thread to end..."));
		MyThread->WaitForCompletion();  // 现在不会卡住了
		delete MyThread;
		MyThread = nullptr;
		UE_LOG(LogTemp, Log, TEXT("Close() - Work thread has been safely closed"));
	}

	// 最后销毁Socket资源
	if (NativeSocket)
	{
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(NativeSocket);
		NativeSocket = nullptr;
		UE_LOG(LogTemp, Log, TEXT("Close() - Socket has been closed"));
	}
}

void FSocketHepler::SendMessage(const FString& Message)//FString内部可能存储为 TCHAR*
{
	if(NativeSocket)
	{
		FTCHARToUTF8 Data(*Message,Message.Len());//UTF-8转换器对象
		//传进来的 Message 转换成 UTF-8字节流的工具对象
						//*Message返回内部的 const TCHAR* 指针

		TArray<uint8> Buffer;
		Buffer.Append(reinterpret_cast<const uint8*>(Data.Get()),Data.Length());
					      //Data.Get() 返回的是 const char* （指向转换后的UTF-8字符数据）
		int SendSize=0;
		NativeSocket->Send(Buffer.GetData(),Buffer.Num(),SendSize);
		//客户端向服务器发消息
		
	}
}


/*
uint32 FSocketHepler::Run()
{
	if(NativeSocket)
	{
		//创建一个接受数据的buffer
		uint8* buffer=new uint8[1024];//创建一个1024大小的buffer缓冲器用来接收数据
		int32 RecSize=0;
		//启动轮询接受消息
		while (bReceiving)
		{
			NativeSocket->Recv(buffer,1024,RecSize);//这个函数这样就算直接进行了吗 也不用啥返回值？
			if(RecSize>0)//说明收到服务器消息 
				{  // 处理数据
				//解析数据
				FUTF8ToTCHAR UTC(reinterpret_cast<ANSICHAR*>(buffer),RecSize);
				//ANSICHAR* = char*
				//	FString M1(UTC.Get(),UTC.Length());//Create a copy of the Other string with extra space for characters at the end of the string
				FString Msg(UTC.Length(),UTC.Get());//最终存储在 FString 中的确实是 TCHAR 类型的字符数据
			
				UE_LOG(LogTemp, Log, TEXT("socket接收数据：%s"),*Msg);
				}
			/*else if(RecSize==0)
			{
				UE_LOG(LogTemp, Log, TEXT("服务器断开连接"));
				break;
			}#1#
			else//本地断开链接，网络出现异常
				{
				//关闭整个链接器
				//Close();
			
				//bReceiving=false;
				//break;

				UE_LOG(LogTemp, Log, TEXT("接收数据错误"));
				Abort();
				}
		}
	}
	return 0;
}*/
/*uint32 FSocketHepler::Run()
{
	UE_LOG(LogTemp, Log, TEXT("Run() - 工作线程开始运行"));
    
	if (!NativeSocket)
	{
		UE_LOG(LogTemp, Error, TEXT("Run() - NativeSocket为空"));
		return 0;
	}

	// 创建接收缓冲区
	uint8* buffer = new uint8[1024];
	int32 RecSize = 0;

	// 🔑 关键改进4：改进循环逻辑，避免访问已销毁的Socket
	while (bReceiving)
	{
		// 在每次使用前检查Socket是否有效
		if (!NativeSocket || !bReceiving)
		{
			UE_LOG(LogTemp, Log, TEXT("Run() - Socket无效或收到退出信号"));
			break;
		}

		// 接收数据
		bool bSuccess = NativeSocket->Recv(buffer, 1024, RecSize);
        
		if (bSuccess && RecSize > 0)
		{
			// 处理接收到的数据
			FUTF8ToTCHAR UTC(reinterpret_cast<ANSICHAR*>(buffer), RecSize);
			FString Msg(UTC.Length(), UTC.Get());
			UE_LOG(LogTemp, Log, TEXT("socket接收数据：%s"), *Msg);
		}
		else if (bSuccess && RecSize == 0)
		{
			// 服务器主动断开连接
			UE_LOG(LogTemp, Log, TEXT("Run() - 服务器断开连接"));
			break;
		}
		else
		{
			// 接收失败或网络错误
			UE_LOG(LogTemp, Warning, TEXT("Run() - 接收数据失败"));
			break;
		}
	}

	// 清理缓冲区
	delete[] buffer;
    
	UE_LOG(LogTemp, Log, TEXT("Run() - 工作线程安全退出"));
	return 0;
}*/

uint32 FSocketHepler::Run() 
{    
	UE_LOG(LogTemp, Log, TEXT("Run() - Work thread starts running"));
    
	if (!NativeSocket)
	{
		UE_LOG(LogTemp, Error, TEXT("Run() - NativeSocket is null"));
		return 0;
	}
    
	// 创建接收缓冲区
	uint8* buffer = new uint8[1024];
	int32 RecSize = 0;
    
	// 改进循环逻辑，避免访问已销毁的Socket
	while (bReceiving)
	{
		// 在每次使用前检查Socket是否有效
		if (!NativeSocket || !bReceiving) 
		{
			UE_LOG(LogTemp, Log, TEXT("Check Socket validity before each use, loop check exit: NativeSocket=%p, bReceiving=%s"), 
				   NativeSocket, bReceiving ? TEXT("true") : TEXT("false"));
			break;
		}
        
		//记录Recv调用前的状态
		UE_LOG(LogTemp, Log, TEXT("Recv is about to be called, bReceiving=%s"), 
			   bReceiving ? TEXT("true") : TEXT("false"));
        
		// 接收数据
		bool bSuccess = NativeSocket->Recv(buffer, 1024, RecSize);
        
		//记录Recv调用后的具体结果
		//UE_LOG(LogTemp, Log, TEXT("NativeSocket->Recv()进行完，Recv返回：bSuccess=%s, RecSize=%d, bReceiving=%s"), 
			   //bSuccess ? TEXT("true") : TEXT("false"), RecSize, 
			   //bReceiving ? TEXT("true") : TEXT("false"));
        
		if (bSuccess && RecSize > 0)
		{
			// 解析接收到的数据 
			FUTF8ToTCHAR UTC(reinterpret_cast<ANSICHAR*>(buffer), RecSize);
			FString Msg(UTC.Length(), UTC.Get());
			          UE_LOG(LogTemp, Log, TEXT("socket received data：%s"), *Msg);
		}
		else if (bSuccess && RecSize == 0)
		{
			// 服务器主动断开连接
			UE_LOG(LogTemp, Log, TEXT("Run() - Server disconnected"));
			break;
		}
		else
		{
			// 接收失败或网络错误
			UE_LOG(LogTemp, Warning, TEXT("Recv failed or no data"));
			UE_LOG(LogTemp, Warning, TEXT("Run() - Failed to receive data"));
			break;
		}
	}
    
	// 清理缓冲区
	delete[] buffer;
    
	UE_LOG(LogTemp, Log, TEXT("Run() - Work thread exited safely"));
	return 0;
}





/*uint32 FSocketHepler::Run()
{
	if(NativeSocket)
	{
		//创建一个接受数据的buffer
		uint8* buffer=new uint8[1024];
		int32 RecSize=0;
		//启动轮询接受消息
		while (bReceiving)
		{
			if(!NativeSocket)
			{
				break;
			}
         
			// 关键修改：检查Recv的返回值
			bool bSuccess = NativeSocket->Recv(buffer,1024,RecSize);
         
			if(bSuccess && RecSize>0)//说明收到服务器消息 
				{  
				//解析数据
				FUTF8ToTCHAR UTC(reinterpret_cast<ANSICHAR*>(buffer),RecSize);
				FString Msg(UTC.Length(),UTC.Get());
         
				UE_LOG(LogTemp, Log, TEXT("socket接收数据：%s"),*Msg);
				}
			else if(bSuccess && RecSize==0)
			{
				UE_LOG(LogTemp, Log, TEXT("Run()-服务器断开连接"));
				break;
			}
			else//Recv失败或网络异常
				{
				UE_LOG(LogTemp, Log, TEXT("Run()-接收数据错误"));
				Abort();
				break;  // 添加break，避免继续循环
				}
		}
		delete[] buffer;
	}
	return 0;
}*/

/*uint32 FSocketHepler::Run()
{
	if(NativeSocket)
	{
		//创建一个接受数据的buffer
		uint8* buffer=new uint8[1024];
		int32 RecSize=0;
		//启动轮询接受消息
		while (bReceiving)
		{
			// 关键修改：在使用时再次检查，避免线程竞争
			FSocket* LocalSocket = NativeSocket;  // 先保存到局部变量
			if(!LocalSocket)
			{
				break;
			}
         
			// 使用局部变量调用，避免在调用过程中被其他线程修改
			bool bSuccess = LocalSocket->Recv(buffer,1024,RecSize);
         
			if(bSuccess && RecSize>0)//说明收到服务器消息 
				{  
				//解析数据
				FUTF8ToTCHAR UTC(reinterpret_cast<ANSICHAR*>(buffer),RecSize);
				FString Msg(UTC.Length(),UTC.Get());
         
				UE_LOG(LogTemp, Log, TEXT("socket接收数据：%s"),*Msg);
				}
			else if(bSuccess && RecSize==0)
			{
				UE_LOG(LogTemp, Log, TEXT("Run()-服务器断开连接"));
				break;
			}
			else//Recv失败或网络异常
				{
				UE_LOG(LogTemp, Log, TEXT("Run()-接收数据错误"));
				Abort();
				break;  // 添加break，避免继续循环
				}
		}
		delete[] buffer;
	}
	return 0;
}*/




/*
void FSocketHepler::Abort()
{
	if(!bReceiving)//已经有人在关
	{
		return;
	}
	//设置退出标志
	if(bReceiving)
	{
		bReceiving=false;
		UE_LOG(LogTemp, Log, TEXT("Abort()—正在关闭Socket连接..."));
	}

	//最后关闭套接字 关闭Socket
	if(NativeSocket)
	{
		
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(NativeSocket);
		NativeSocket=nullptr;
		UE_LOG(LogTemp, Log, TEXT("Abort()-Socket已关闭"));
	}
	//等待线程结束
	if(MyThread)
	{
		//MyThread->WaitForCompletion();
		
		MyThread->Kill();
		delete MyThread;
		MyThread=nullptr;
		UE_LOG(LogTemp, Log, TEXT("Abort()-工作线程已关闭"));
	}
}*/
/*// 如果需要在网络异常时清理，使用这个方法
void FSocketHepler::Abort()
{
	UE_LOG(LogTemp, Warning, TEXT("Abort() - 异常中止连接"));
    
	// 设置退出标志
	bReceiving = false;
    
	// 注意：不要在工作线程中调用这个方法！
	// 应该让工作线程自然退出，由主线程调用Close()
}*/