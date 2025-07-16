# UE4 网络通信技术栈完整演示项目

**视频演示链接：** https://www.bilibili.com/video/BV1kmutz4Ehm/

**开发工具：** 虚幻引擎4.27 C++ + JetBrains Rider + VSCode + ProtoShell编译器集成

**项目描述：** 基于虚幻引擎4开发的完整网络通信技术栈演示项目，深入探索HTTP协议、Socket编程、数据序列化等核心网络技术。项目从底层Socket API构建网络通信层，实现多种通信协议和数据格式的性能对比测试，为现代游戏网络开发提供完整的技术参考和最佳实践。

## 核心技术实现

### 网络通信基础
深入理解TCP/UDP协议本质差异，实现HTTP GET/POST请求处理、Socket TCP面向连接通信、UDP无连接数据传输机制。通过NetSoldier测试工具验证网络连接稳定性和数据传输可靠性。

### 并发编程技术  
多线程网络监听机制实现、FRunnable接口继承的异步数据接收、线程安全的资源管理和优雅关闭机制。解决多线程环境下的Socket资源竞争和数据同步问题。

### 数据序列化方案
XML传统文本格式解析处理、Google Protobuf高效二进制序列化集成、UTF-8与TCHAR编码转换机制。通过实际数据对比测试，XML格式81字节 vs Protobuf格式18字节，压缩效率提升4.5倍。

### 引擎扩展开发
虚幻引擎第三方库静态链接配置、Protobuf编译工具链集成、跨平台兼容性处理。解决UE4项目中外部依赖库的编译配置和版本兼容问题。

## 技术亮点

* **底层网络编程实践**：从Socket API层面构建通信框架，深入理解网络协议栈原理和数据传输机制

* **性能优化对比验证**：通过XML与Protobuf实际数据测试，量化分析不同序列化方案的传输效率差异

* **企业级代码规范**：完整的错误处理机制、资源管理策略、线程安全实现和优雅关闭流程

* **工具链集成方案**：VSCode Protobuf开发、ProtoShell编译集成、UE4项目配置的完整技术栈

## 主要代码实现

### HTTP通信模块
```cpp
void FHttpHelper::RequestHttpGet(const TCHAR* Url) {
    TSharedPtr<IHttpRequest,ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetURL(Url);
    HttpRequest->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
    HttpRequest->SetVerb(TEXT("Get"));
    HttpRequest->ProcessRequest();
}
```

### Socket TCP连接
```cpp
bool FSocketHepler::Connect(const FString& IP, const int32 Port) {
    TSharedRef<FInternetAddr> FInternetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    FInternetAddr->SetIp(*IP, IsValid);
    FInternetAddr->SetPort(Port);
    NativeSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("MySocket"));
    return NativeSocket->Connect(*FInternetAddr);
}
```

### UDP无连接通信
```cpp
void FUdpHelper::SendMessage(const FString& Msg) {
    UdpSocket = FUdpSocketBuilder(TEXT("MyUdp")).AsReusable().AsBlocking();
    TSharedRef<FInternetAddr> InterAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    InterAddr->SetIp(TEXT("127.0.0.1"), IsValid);
    InterAddr->SetPort(8050);
    UdpSocket->SendTo(Buffer.GetData(), Buffer.Num(), SendSize, *InterAddr);
}
```

### XML数据解析
```cpp
void AUNativeNetGameModeBase::ParseXML() {
    TSharedPtr<FXmlFile> XmlFileCompare = MakeShareable(new FXmlFile);
    if(XmlFileCompare->LoadFile(TEXT("e:\\mybox.xml"))) {
        FXmlNode* RootNode = XmlFileCompare->GetRootNode();
        FString Age = RootNode->GetAttribute(TEXT("age"));
        FString Name = RootNode->GetAttribute(TEXT("name"));
        UE_LOG(LogTemp, Log, TEXT("Xml File Size: %d bytes"), XmlSize);
    }
}
```

### Protobuf序列化
```cpp
void AUNativeNetGameModeBase::TestProtobuf() {
    MyBox box;
    box.set_age(100);
    box.set_name("PlayerData");
    box.add_nums(10);
    box.add_nums(20);
    
    std::string data;
    box.SerializeToString(&data);
    UE_LOG(LogTemp, Log, TEXT("Serialized size：%d bytes"), data.size());
}
```

同样的数据格式对比测试显示，XML文件占用81字节，而Protobuf序列化后仅需18字节，数据传输效率提升4.5倍，充分展现了二进制序列化在游戏网络通信中的显著优势。

---

# UE4 Complete Network Communication Technology Stack Demo Project

**Video Demo Link:** https://www.bilibili.com/video/BV1kmutz4Ehm/

**Development Tools:** Unreal Engine 4.27 C++ + JetBrains Rider + VSCode + ProtoShell Compiler Integration

**Project Description:** A comprehensive network communication technology stack demonstration project based on Unreal Engine 4, deeply exploring core networking technologies including HTTP protocols, Socket programming, and data serialization. The project builds network communication layers from underlying Socket APIs, implements performance comparison tests for multiple communication protocols and data formats, providing complete technical reference and best practices for modern game network development.

## Core Technical Implementation

### Network Communication Foundation
Deep understanding of essential differences between TCP/UDP protocols, implementing HTTP GET/POST request handling, Socket TCP connection-oriented communication, and UDP connectionless data transmission mechanisms. Network connection stability and data transmission reliability verified through NetSoldier testing tools.

### Concurrent Programming Technology
Multi-threaded network listening mechanism implementation, asynchronous data reception through FRunnable interface inheritance, thread-safe resource management and graceful shutdown mechanisms. Solving Socket resource competition and data synchronization issues in multi-threaded environments.

### Data Serialization Solutions
Traditional XML text format parsing and processing, Google Protobuf efficient binary serialization integration, UTF-8 and TCHAR encoding conversion mechanisms. Through actual data comparison testing, XML format 81 bytes vs Protobuf format 18 bytes, compression efficiency improved by 4.5 times.

### Engine Extension Development
Unreal Engine third-party library static linking configuration, Protobuf compilation toolchain integration, cross-platform compatibility handling. Solving compilation configuration and version compatibility issues for external dependency libraries in UE4 projects.

## Technical Highlights

* **Low-level Network Programming Practice**: Building communication frameworks from Socket API level, deeply understanding network protocol stack principles and data transmission mechanisms

* **Performance Optimization Comparison Verification**: Quantitative analysis of transmission efficiency differences between different serialization solutions through actual XML and Protobuf data testing

* **Enterprise-level Code Standards**: Complete error handling mechanisms, resource management strategies, thread-safe implementation and graceful shutdown processes

* **Toolchain Integration Solutions**: VSCode Protobuf development, ProtoShell compilation integration, complete technology stack of UE4 project configuration

## Main Code Implementation

### HTTP Communication Module
```cpp
void FHttpHelper::RequestHttpGet(const TCHAR* Url) {
    TSharedPtr<IHttpRequest,ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetURL(Url);
    HttpRequest->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
    HttpRequest->SetVerb(TEXT("Get"));
    HttpRequest->ProcessRequest();
}
```

### Socket TCP Connection
```cpp
bool FSocketHepler::Connect(const FString& IP, const int32 Port) {
    TSharedRef<FInternetAddr> FInternetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    FInternetAddr->SetIp(*IP, IsValid);
    FInternetAddr->SetPort(Port);
    NativeSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("MySocket"));
    return NativeSocket->Connect(*FInternetAddr);
}
```

### UDP Connectionless Communication
```cpp
void FUdpHelper::SendMessage(const FString& Msg) {
    UdpSocket = FUdpSocketBuilder(TEXT("MyUdp")).AsReusable().AsBlocking();
    TSharedRef<FInternetAddr> InterAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    InterAddr->SetIp(TEXT("127.0.0.1"), IsValid);
    InterAddr->SetPort(8050);
    UdpSocket->SendTo(Buffer.GetData(), Buffer.Num(), SendSize, *InterAddr);
}
```

### XML Data Parsing
```cpp
void AUNativeNetGameModeBase::ParseXML() {
    TSharedPtr<FXmlFile> XmlFileCompare = MakeShareable(new FXmlFile);
    if(XmlFileCompare->LoadFile(TEXT("e:\\mybox.xml"))) {
        FXmlNode* RootNode = XmlFileCompare->GetRootNode();
        FString Age = RootNode->GetAttribute(TEXT("age"));
        FString Name = RootNode->GetAttribute(TEXT("name"));
        UE_LOG(LogTemp, Log, TEXT("Xml File Size: %d bytes"), XmlSize);
    }
}
```

### Protobuf Serialization
```cpp
void AUNativeNetGameModeBase::TestProtobuf() {
    MyBox box;
    box.set_age(100);
    box.set_name("PlayerData");
    box.add_nums(10);
    box.add_nums(20);
    
    std::string data;
    box.SerializeToString(&data);
    UE_LOG(LogTemp, Log, TEXT("Serialized size：%d bytes"), data.size());
}
```

Performance comparison testing shows that XML files occupy 81 bytes while Protobuf serialization requires only 18 bytes, improving data transmission efficiency by 4.5 times, fully demonstrating the significant advantages of binary serialization in game network communication.
