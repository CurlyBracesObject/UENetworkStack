#include "FHttpHelper.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

void FHttpHelper::RequestHttpGet(const TCHAR* Url)
{
	//创建请求对象HttpRequest
	TSharedPtr<IHttpRequest,ESPMode::ThreadSafe> HttpRequest=FHttpModule::Get().CreateRequest();
															// 单例 = 全程序只有一个实例 总是返回同一个对象 自动清理完成的请求
																//释放响应数据的内存
	//设置请求地址路径 
	HttpRequest->SetURL(Url);
	//设置请求头
	HttpRequest->SetHeader(TEXT("User-Agent"),TEXT("X-UnrealEngine-Agent"));
	HttpRequest->SetHeader(TEXT("Content-Type"),TEXT("application/json"));
	//设置请求方式
	HttpRequest->SetVerb(TEXT("Get"));
	//绑定请求回调
	//HttpRequest->OnRequestProgress().BindRaw(this,&FHttpHelper::OnResponse);
	HttpRequest->OnProcessRequestComplete().BindRaw(this,&FHttpHelper::OnResponse);
	//发起请求
	HttpRequest->ProcessRequest();
	
}

void FHttpHelper::RequestHttpPost(const TCHAR* Url, const FString& Msg)
{
	//创建请求对象HttpRequest
	TSharedPtr<IHttpRequest,ESPMode::ThreadSafe> HttpRequest=FHttpModule::Get().CreateRequest();
	// 单例 = 全程序只有一个实例 总是返回同一个对象 自动清理完成的请求
	//释放响应数据的内存
	//设置请求地址路径 
	HttpRequest->SetURL(Url);
	//设置请求头
	HttpRequest->SetHeader(TEXT("User-Agent"),TEXT("X-UnrealEngine-Agent"));
	HttpRequest->SetHeader(TEXT("Content-Type"),TEXT("application/json"));
	//设置请求方式
	HttpRequest->SetVerb(TEXT("Post"));
	//添加Post消息信息
	HttpRequest->SetContentAsString(Msg);
	
	//绑定请求回调
	//HttpRequest->OnRequestProgress().BindRaw(this,&FHttpHelper::OnResponse);
	HttpRequest->OnProcessRequestComplete().BindRaw(this,&FHttpHelper::OnResponsePost);
	//发起请求
	HttpRequest->ProcessRequest();
}

void FHttpHelper::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	UE_LOG(LogTemp, Log, TEXT("HTTP response received!"));
	if(Response->GetResponseCode())
	{
		UE_LOG(LogTemp, Log, TEXT("%s"),*Response->GetContentAsString());
	}
}

void FHttpHelper::OnResponsePost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if(Response->GetResponseCode())
	{
		UE_LOG(LogTemp, Log, TEXT("%s"),*Response->GetContentAsString());
	}
}
