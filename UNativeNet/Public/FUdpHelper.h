#pragma once

class FUdpHelper:public FRunnable
{
public:
	FUdpHelper();
	virtual ~FUdpHelper() override;
	
public:
	
	void SendMessage(const FString& Msg);

	void StartListen();

	void Close();
	
protected:
	
	virtual uint32 Run() override;

private:
	FSocket* UdpSocket;
	FRunnableThread* MyThread;
	bool bReceiving;
	
};
