#pragma once
#include "../2812b/2812bDevCtrl.h"
#include "Serial.h"
#include "./device/buleTooth/BlueToothSerialDevCtrl.h"
class CSerialDevCtrl;
class CCommandParser  //解析串口命令执行操作类 
{
public:
    CCommandParser(C2812bDevCtrl& ledCtrl, CSerialDevCtrl& seriaCtrl,CBlueToothSerialCtrl& blueTooth);
    
    //处理接收到的数据
    void ProcessCommand(const char* command);

private:
    C2812bDevCtrl& m_ledCtrl;
    CSerialDevCtrl& m_serialCtrl;
    CBlueToothSerialCtrl& m_blueTooth;

private:
    void CmdUpdate();
    void CmdSetColor(const char* command);
    void CmdSetLumi(const char* command);
};