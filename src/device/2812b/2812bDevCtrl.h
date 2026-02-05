#pragma once
#include <FastLED.h>
#include <Preferences.h>

class C2812bDevCtrl
{
public:
    C2812bDevCtrl();

    //设备初始化setup用
    void Init();
    //周期更新loop用
    void UpDate();
    //呼吸
    void Breath();
    //对外接口
    void SetColor(const CRGB& color); //设置颜色
    void EnableBreath(bool enable); //启动或停止呼吸
    bool SetLuminance(u_int8_t lumi); //设置亮度
    void SetLedNum(u_int16_t num); //设置灯珠数量
    void testOne(uint8_t num); //设置亮度
private:
    //硬件参数
    static constexpr uint8_t LED_PIN = 18;
    int32_t LED_NUM = 18;

    CRGB* c_leds;
    //状态数据
    bool b_breathEnable = false;
    uint8_t n_brightness = 0;
    int8_t n_step = 2;
    CRGB c_baseColor;

    //非阻塞时间
    unsigned long m_lastTick = 0; //上一次更新时间
    const unsigned long m_interval = 30;  //更新时间（ms）

private:
    //掉电不丢失preferences实例
    Preferences m_prefs;
    void SaveStatus();
    void LoadStatus();
};