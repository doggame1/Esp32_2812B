#include "CtrlCenter.h"

CtrlCenter &CtrlCenter::Instance()
{
    static CtrlCenter m_instance;
    return m_instance;
}

void CtrlCenter::Init()
{
    m_2812b.Init();
    m_Serial.SendData("2812初始化完毕");
    //m_Serial.Init();
    m_Serial.SendData("开始初始化蓝牙...");
    m_buleTooth.Init();
    
}

void CtrlCenter::Update()
{
    static bool btNotified = false;

    m_2812b.UpDate();
    //m_Serial.UpDate();
    m_buleTooth.Update();
    //判断蓝牙是否链接了
    if (!btNotified && m_buleTooth.IsReady())
    {
        m_Serial.SendData("蓝牙已连接");
        btNotified = true;
    }
    // char serialData[128];
    // if(m_Serial.OnProcData(serialData,sizeof(serialData)))
    // {
    //     m_Serial.SendData(serialData);
    //     m_commandParser.ProcessCommand(serialData); //处理消息
    // }
}
C2812bDevCtrl &CtrlCenter::Get2812b()
{
    return m_2812b;
}

CSerialDevCtrl &CtrlCenter::GetSerial()
{
    return m_Serial;
}

CtrlCenter::CtrlCenter() : 
    m_buleTooth(m_commandParser),
    m_commandParser(m_2812b, m_Serial,m_buleTooth),
    m_Serial(m_commandParser)
    
    
    
{
}
