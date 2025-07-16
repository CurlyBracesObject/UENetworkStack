#include "FUdpHelper.h"

#include "Common/UdpSocketBuilder.h"

FUdpHelper::FUdpHelper()
{
   UdpSocket=nullptr;
   MyThread=nullptr;
   bReceiving=false;
}

FUdpHelper::~FUdpHelper()
{
   Close();
}

void FUdpHelper::SendMessage(const FString& Msg)
{
   //创建套接字对象
   if(!UdpSocket)
   {
      UdpSocket=FUdpSocketBuilder(TEXT("MyUdp")).AsReusable().AsBlocking();
   }
   //设置消息发送缓冲区
   int32 NewSize=0;
   if(!UdpSocket->SetSendBufferSize(1024,NewSize))
   {
      UE_LOG(LogTemp, Log, TEXT("UDP send buffer setup error!"));
      return;
   }
   //创建地址
   TSharedRef<FInternetAddr> InterAddr=ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
   //设置IP
   bool IsValid=false;
   InterAddr->SetIp(TEXT("127.0.0.1"),IsValid);
   if(!IsValid)
   {
      UE_LOG(LogTemp, Log, TEXT("Send address setup error!"));
      return;
   }
   
   //设置端口号
   InterAddr->SetPort(8050);
   
   FTCHARToUTF8 Data(*Msg,Msg.Len());//UTF-8转换器对象
   //传进来的 Message 转换成 UTF-8字节流的工具对象
   //*Message返回内部的 const TCHAR* 指针
   TArray<uint8> Buffer;
   Buffer.Append(reinterpret_cast<const uint8*>(Data.Get()),Data.Length());
   //Data.Get() 返回的是 const char* （指向转换后的UTF-8字符数据）
   int SendSize=0;
   //NativeSocket->Send(Buffer.GetData(),Buffer.Num(),SendSize);
   UdpSocket->SendTo(Buffer.GetData(),Buffer.Num(),SendSize,*InterAddr);
         //客户端向服务器发消息
}

void FUdpHelper::StartListen()
{
   if(bReceiving)//（已经启动监听）
   {
      return;
   }
   bReceiving=true;
   MyThread=FRunnableThread::Create(this,TEXT("MyUdpThread"));
}

void FUdpHelper::Close()
{
   UE_LOG(LogTemp, Log, TEXT("Close() - Starting to close Socket connection..."));
    
   // 关键改进：首先设置退出标志
   if (bReceiving)
   {
      bReceiving = false;
      UE_LOG(LogTemp, Log, TEXT("Close() - Set exit flag"));
   }

   //关键改进：先关闭Socket，让Recv()立即失败退出    这里关闭了网络连接！
   if (UdpSocket)
   {
      UdpSocket->Close();
      UE_LOG(LogTemp, Log, TEXT("Close() - Socket connection has been closed"));
   }

   // 现在等待线程结束（Recv失败后会快速退出）
   if (MyThread)
   {
      UE_LOG(LogTemp, Log, TEXT("Close() - Waiting for work thread to end..."));
      MyThread->WaitForCompletion();  // 现在不会卡住了
      delete MyThread;
      MyThread = nullptr;
      UE_LOG(LogTemp, Log, TEXT("Close() - Work thread has been safely closed"));
   }

   // 最后销毁Socket资源
   if (UdpSocket)
   {
      ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(UdpSocket);
      UdpSocket = nullptr;
      UE_LOG(LogTemp, Log, TEXT("Close() - Socket has been closed"));
   }
}

uint32 FUdpHelper::Run()
{
   /*while (bReceiving&&UdpSocket)
   {
      //接受消息
      UdpSocket->Recv(,)
   }
   return 0;*/
   UE_LOG(LogTemp, Log, TEXT("Run() - Work thread starts running"));
    
   if (!UdpSocket)
   {
      UE_LOG(LogTemp, Error, TEXT("Run() - UdpSocket is null"));
      return 0;
   }
    
   // 创建接收缓冲区
   uint8* buffer = new uint8[1024];
   int32 RecSize = 0;
    
   // 改进循环逻辑，避免访问已销毁的Socket
   while (bReceiving)
   {
      // 在每次使用前检查Socket是否有效
      if (!UdpSocket || !bReceiving) 
      {
         UE_LOG(LogTemp, Log, TEXT("Check Socket validity before each use, loop check exit: UdpSocket=%p, bReceiving=%s"), 
               UdpSocket, bReceiving ? TEXT("true") : TEXT("false"));
         break;
      }
        
      //记录Recv调用前的状态
      UE_LOG(LogTemp, Log, TEXT("Recv is about to be called, bReceiving=%s"), 
            bReceiving ? TEXT("true") : TEXT("false"));
        
      // 接收数据
      bool bSuccess = UdpSocket->Recv(buffer, 1024, RecSize);
        
      //记录Recv调用后的具体结果
      UE_LOG(LogTemp, Log, TEXT("UdpSocket->Recv() completed, Recv returns: bSuccess=%s, RecSize=%d, bReceiving=%s"), 
            bSuccess ? TEXT("true") : TEXT("false"), RecSize, 
            bReceiving ? TEXT("true") : TEXT("false"));
        
      if (bSuccess && RecSize > 0)
      {
         // 解析接收到的数据 
         FUTF8ToTCHAR UTC(reinterpret_cast<ANSICHAR*>(buffer), RecSize);
         FString Msg(UTC.Length(), UTC.Get());
         UE_LOG(LogTemp, Log, TEXT("UDP socket connection received data: %s"), *Msg);
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
         UE_LOG(LogTemp, Warning, TEXT("Run() - Recv failed or no data"));
         UE_LOG(LogTemp, Warning, TEXT("Run() - Failed to receive data"));
         break;
      }
   }
   // 清理缓冲区
   delete[] buffer;
    
   UE_LOG(LogTemp, Log, TEXT("Run() - Work thread exited safely"));
   return 0;
}