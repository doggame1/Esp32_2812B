#include "2812bDevCtrl.h"

C2812bDevCtrl::C2812bDevCtrl()
{
    LoadStatus();
    c_leds = new CRGB[LED_NUM];
}

void C2812bDevCtrl::Init()
{
    LoadStatus();
    b_breathEnable = false;
    FastLED.addLeds<WS2812B,LED_PIN,GRB>(c_leds,LED_NUM);
    
    //从flash加载掉电后的数据
    //LoadStatus();
    FastLED.setBrightness(n_brightness);
    fill_solid(c_leds,LED_NUM,c_baseColor);
    FastLED.show();

}

void C2812bDevCtrl::UpDate()
{
    if(!b_breathEnable)
    {
        FastLED.setBrightness(n_brightness);
        fill_solid(c_leds,LED_NUM,c_baseColor);
        FastLED.show();
        return;
    }
    Breath();

}

void C2812bDevCtrl::Breath()
{
    // 读取系统从启动到现在经过的毫秒数
    // millis() 是 Arduino 提供的“系统时间”
    unsigned long now = millis();

    // 判断：距离上一次真正更新，是否还没到设定的间隔时间
    // 如果还没到，就直接 return，避免更新太快
    if (now - m_lastTick < m_interval)
    {
        return;
    }
    // 能走到这里，说明时间已经到了
    // 记录这一次更新发生的时间
    m_lastTick = now;

    // 当前亮度加上变化步进（正数变亮，负数变暗）
    n_brightness += n_step;

    if(n_brightness >= 120 || n_brightness <= 0)
    {
        n_step = -n_step;
    }
    FastLED.setBrightness(n_brightness);
    fill_solid(c_leds,LED_NUM,c_baseColor);
    FastLED.show();
}

void C2812bDevCtrl::SetColor(const CRGB &color)
{
    c_baseColor = color;
    fill_solid(c_leds,LED_NUM,c_baseColor);
    FastLED.show();
    SaveStatus();
}

void C2812bDevCtrl::EnableBreath(bool enable)
{
    b_breathEnable = enable;
    SaveStatus();
}

bool C2812bDevCtrl::SetLuminance(u_int8_t lumi)
{
    if(b_breathEnable)
    {
        return false;
    }
    n_brightness = lumi;
    SaveStatus();
    return true;

    
}

void C2812bDevCtrl::SetLedNum(u_int16_t num)
{
    
    FastLED.setBrightness(0);
    fill_solid(c_leds,LED_NUM,c_baseColor);
    FastLED.show();

    
    LED_NUM = num;  //设置led数量
    if(c_leds)
    {
        delete[] c_leds; //释放之前的内存
    }

    c_leds = new CRGB[LED_NUM];
    FastLED.addLeds<WS2812B,LED_PIN,GRB>(c_leds,LED_NUM);
    fill_solid(c_leds, LED_NUM, c_baseColor);
    FastLED.setBrightness(n_brightness);
    FastLED.show();
    SaveStatus();
}

void C2812bDevCtrl::testOne(uint8_t num)
{
    FastLED.setBrightness(num);
}

void C2812bDevCtrl::SaveStatus()
{
    m_prefs.begin("led_status",false); //打开命名空间 led_status

    //保存颜色值
    m_prefs.putUChar("red",c_baseColor.r);
    m_prefs.putUChar("green",c_baseColor.g);
    m_prefs.putUChar("bule",c_baseColor.b);
    //保存亮度
    m_prefs.putUChar("brightness",n_brightness);
    //保存呼吸模式
    m_prefs.putBool("breathEnable",b_breathEnable);
    //保存灯珠数量
    m_prefs.putUInt("ledNum",LED_NUM);
    m_prefs.end();//关闭命名空间
}

void C2812bDevCtrl::LoadStatus()
{
    m_prefs.begin("led_status",true); //打开命名空间led_status 只读模式
    //获取rgb值 默认白色
    uint8_t r = m_prefs.getUChar("red",255);   
    uint8_t g = m_prefs.getUChar("green",255);
    uint8_t b = m_prefs.getUChar("bule",255);
    c_baseColor = CRGB(r,g,b);
    //获取亮度
    n_brightness = m_prefs.getUChar("brightness",100);
    //获取是否为呼吸模式
    b_breathEnable = m_prefs.getBool("breathEnable",false);
    //获取灯珠数量
    LED_NUM = m_prefs.getUInt("ledNum",18);
    m_prefs.end(); //关闭命名空间
}
