#include "Serial.h"


CSerialDevCtrl::CSerialDevCtrl(CCommandParser& parser) : recvIndex(0),m_commandParser(parser)
{
}

CSerialDevCtrl::~CSerialDevCtrl()
{
}

void CSerialDevCtrl::Init()
{
    delay(300);
    Serial.begin(BAUD_RATE);
    Serial.println("串口已初始化");
}

void CSerialDevCtrl::UpDate()
{
    //没数据直接返回
    if(Serial.available() <= 0)
    {
        return;
    }
    //读取一个字节
    char incomingByte = Serial.read();
    if(recvIndex < BUFFER_SIZE - 1)
    {
        recvBuffer[recvIndex ++] = incomingByte;
    }
    if(incomingByte == '\n')
    {
        recvBuffer[recvIndex -1] = '\0'; //添加字符串结束符
        Serial.println("接收到数据");
        Serial.println(recvBuffer);
        recvIndex = 0;   //清空接收区缓存
        m_commandParser.ProcessCommand(recvBuffer); //传递的信息做处理
    }
}

void CSerialDevCtrl::SendData(const String &data)
{
    Serial.println(data);
}

bool CSerialDevCtrl::OnProcData(char *outBuf, size_t bufSize)
{
    if(Serial.available() <= 0)
    {
        return  false;
    }

    //读取一个字节
    char ch = Serial.read();
    //丢掉回车
    if(ch == '\r')
    {
        return false;
    }

    //如果还没满缓冲区，就存进去
    if(recvIndex < BUFFER_SIZE -1)
    {
        recvBuffer[recvIndex ++] = ch;
    }

    //如果遇到换行符 说明结束
    if(ch == '\n')
    {
        //字符串结尾
        recvBuffer[recvIndex-1] = '\0';
        //把接收到的内容拷贝给调用者
        strncpy(outBuf,recvBuffer,bufSize -1);
        outBuf[bufSize -1] = '\0';
        //重置内部状态
        recvIndex = 0;

        return true;
    }

    //还没读完一行
    return false;
}
