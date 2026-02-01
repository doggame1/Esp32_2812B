#include "CtrlCenter.h"

CtrlCenter &CtrlCenter::Instance()
{
    static CtrlCenter m_instance;
    return m_instance;
}

void CtrlCenter::Init()
{
    m_2812b.Init();
    m_Serial.Init();
}

void CtrlCenter::Update()
{
    m_2812b.UpDate();

    char serialData[128];
    if(m_Serial.OnProcData(serialData,sizeof(serialData)))
    {
        m_Serial.SendData(serialData);
        m_commandParser.ProcessCommand(serialData); //处理消息
    }
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
    m_commandParser(m_2812b, m_Serial),
    m_Serial(m_commandParser)
{
}
