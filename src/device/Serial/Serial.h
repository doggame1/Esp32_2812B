#pragma once
#include <Arduino.h>
#include "CommandParser.h"

class CCommandParser;
class CSerialDevCtrl
{
public:
    CSerialDevCtrl(CCommandParser& parser);
    ~CSerialDevCtrl();

    void Init();
    void UpDate();
    void SendData(const String &data);
    bool OnProcData(char* outBuf , size_t bufSize);
private:
    static const uint32_t BAUD_RATE = 115200; //串口波特率
    static const uint8_t  BUFFER_SIZE = 128; //缓存区大小

    char recvBuffer[BUFFER_SIZE];   //串口接收缓存
    uint8_t recvIndex;  //当前接收的字节索引

    CCommandParser& m_commandParser;

};