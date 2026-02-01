#include "CommandParser.h"
#include <cstring>
#include <cstdio>

CCommandParser::CCommandParser(C2812bDevCtrl &ledCtrl, CSerialDevCtrl &seriaCtrl) 
: m_ledCtrl(ledCtrl),m_serialCtrl(seriaCtrl)
{
}

void CCommandParser::ProcessCommand(const char *command)
{ 
    if(strcmp(command,"onled") == 0)
    {
        m_serialCtrl.SendData("开灯");
    }else if (strcmp(command,"offled") == 0)
    {
        m_serialCtrl.SendData("关灯");
        m_ledCtrl.SetColor(CRGB::Black);  // 关闭灯光
    }else if(strcmp(command,"onbreath") == 0)
    {
        m_serialCtrl.SendData("开启呼吸");
        m_ledCtrl.EnableBreath(true);
    }else if(strcmp(command,"offbreath") == 0)
    {
        m_serialCtrl.SendData("关闭呼吸");
        m_ledCtrl.EnableBreath(false);
    }
    else if(strcmp(command,"update") == 0)
    {
        m_serialCtrl.SendData("update");
        CmdUpdate();
    }else if(strncmp(command,"setcolor",7) == 0)
    {
        m_serialCtrl.SendData("设置灯光颜色");
        CmdSetColor(command);
    }else if(strncmp(command,"setlumi",7) == 0)
    {
        m_serialCtrl.SendData("设置亮度");
        CmdSetLumi(command);
    }else
    {
        m_serialCtrl.SendData("无效命令");
    }
}

//执行led更新操作
void CCommandParser::CmdUpdate()
{
    m_serialCtrl.SendData("设置led中。。。");
    m_ledCtrl.UpDate();
}
//解析设置颜色命令并设置颜色
void CCommandParser::CmdSetColor(const char* command)
{
    int r,g,b;
    // 使用sscanf解析命令字符串，获取rgb颜色值
    if(sscanf(command,"setcolor %d %d %d",&r,&g,&b) == 3)
    {
        //输出解析得到的rgb值
        m_serialCtrl.SendData("设置颜色的RGB值为:");
        m_serialCtrl.SendData("R:");
        m_serialCtrl.SendData((String)r);
        m_serialCtrl.SendData("G:");
        m_serialCtrl.SendData((String)g);
        m_serialCtrl.SendData("B:");
        m_serialCtrl.SendData((String)b);
        //设置LED颜色
        m_ledCtrl.SetColor(CRGB(r,g,b));

    }else
    {
        m_serialCtrl.SendData("请输入正确的颜色格式");
    }
}

void CCommandParser::CmdSetLumi(const char* command)
{
    uint8_t lumi;
    if(sscanf(command,"setlumi %d" ,&lumi) == 1)
    {
        if(false == m_ledCtrl.SetLuminance(lumi))
        {
            m_serialCtrl.SendData("要先关闭呼吸功能");
            return;
        }
        m_serialCtrl.SendData("设置亮度为:");
        m_serialCtrl.SendData((String)lumi);
    }

}
