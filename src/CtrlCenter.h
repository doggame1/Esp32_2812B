#pragma once
#include "device/2812b/2812bDevCtrl.h"
#include "device/Serial/Serial.h"
#include "device/Serial/CommandParser.h"
#include "device/buleTooth/BlueToothSerialDevCtrl.h"
class CtrlCenter
{
public:
    static CtrlCenter& Instance();
    void Init();
    void Update();

    C2812bDevCtrl& Get2812b();
    CSerialDevCtrl& GetSerial();

private:
    CtrlCenter();
    CtrlCenter(const CtrlCenter&) = delete;

private:
    C2812bDevCtrl m_2812b;
    CCommandParser m_commandParser;
    CSerialDevCtrl m_Serial;
    CBlueToothSerialCtrl m_buleTooth;

};