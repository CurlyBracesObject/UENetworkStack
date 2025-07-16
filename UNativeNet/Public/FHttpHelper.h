#pragma once
#include "Interfaces/IHttpRequest.h"

class FHttpHelper
{
public:
	void RequestHttpGet(const TCHAR* Url);
	void RequestHttpPost(const TCHAR* Url,const FString& Msg);

protected:
	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void OnResponsePost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	
};
