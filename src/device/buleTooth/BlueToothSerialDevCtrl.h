#pragma once
#include <Arduino.h>
#include <BluetoothSerial.h>

class CCommandParser;

class CBlueToothSerialCtrl
{
public:
    CBlueToothSerialCtrl(CCommandParser& parser);

    void Init();  //因为freeRtos还没有初始化 蓝牙初始化需要系统调度 所以初始化再Update里
    void Update();
    bool IsReady();
    void SendData(const String& data);

private:
    BluetoothSerial m_bt;
    CCommandParser&  m_commandParser;

    char recvBuffer[128];
    uint8_t recvIndex = 0;
    bool m_started = false; //是否链接
    bool m_needInit = false; //需要链接

};