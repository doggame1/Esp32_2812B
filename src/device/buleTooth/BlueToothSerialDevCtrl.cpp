#include "BlueToothSerialDevCtrl.h"
#include "./device/Serial/CommandParser.h"

CBlueToothSerialCtrl::CBlueToothSerialCtrl(CCommandParser &parser)
: m_commandParser(parser)
{
}

void CBlueToothSerialCtrl::Init()
{
    m_needInit = true;
}

void CBlueToothSerialCtrl::Update()
{
    // 第 1 阶段：只负责 begin，一次
    if (m_needInit && !m_started)
    {
        m_bt.begin("Wangzh_Esp32");
        m_started = true;
        m_needInit = false;
        m_bt.println("蓝牙初始化完成");
        return; // 这一帧只干初始化
    }

    // 第 2 阶段：蓝牙未 ready，什么都不干
    if (!m_bt.isReady())
    {
        m_bt.println("蓝牙还未初始化");
        return;
    }

    // 第 3 阶段：接收数据
    while (m_bt.available() > 0)
    {
        char ch = m_bt.read();
        
        // 跳过回车符
        if (ch == '\r')
        {
            continue;
        }
        
        // 检查缓冲区溢出
        if (recvIndex >= sizeof(recvBuffer) - 1)
        {
            // 缓冲区满，但没收到换行符，清空缓冲区
            recvIndex = 0;
        }
        
        // 存储字符
        recvBuffer[recvIndex++] = ch;
        
        // 检查行结束
        if (ch == '\n')
        {
            // 去掉可能的换行符
            if (recvIndex > 0 && recvBuffer[recvIndex-1] == '\n')
            {
                recvIndex--;
            }
            
            // 确保字符串以\0结尾
            recvBuffer[recvIndex] = '\0';
            
            // 输出接收到的完整消息
            if (recvIndex > 0)  // 确保不是空行
            {
                m_bt.print("收到消息: ");
                m_bt.println(recvBuffer);
                
                // 处理命令
                m_commandParser.ProcessCommand(recvBuffer);
            }
            
            // 重置接收索引
            recvIndex = 0;
        }
    }
    //m_bt.println("走到最后了");
}

bool CBlueToothSerialCtrl::IsReady()
{
    return m_started;
}

void CBlueToothSerialCtrl::SendData(const String &data)
{
    m_bt.println(data);
}
