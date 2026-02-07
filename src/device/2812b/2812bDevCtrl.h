#pragma once
#include <FastLED.h>
#include <Preferences.h>


enum LedMode
{
    MODE_STATIC,        //常亮
    MODE_BREATH,        //呼吸
    MODE_RAINBOW_FLOW,  //幻彩流水
    MODE_OFF            //关灯
};


class C2812bDevCtrl
{
public:
    C2812bDevCtrl();

    //设备初始化setup用
    void Init();
    //周期更新loop用
    void UpDate();
    //对外接口
    void SetColor(const CRGB& color); //设置颜色
    bool SetLuminance(u_int8_t lumi); //设置亮度
    void SetLedNum(u_int16_t num); //设置灯珠数量
    void SetMode(LedMode mode);  //设置模式
    void testOne(uint8_t num); //设置亮度

private:
    //========灯效实现=======
    void StaticLight();
    void BreathLight();
    void RainbowLight();
    //=======掉电存储========
    Preferences m_prefs; //掉电不丢失类实例
    void SaveStatus();
    void LoadStatus();
private:
    //硬件参数
    static constexpr uint8_t LED_PIN = 18;  //灯珠引脚
    int32_t LED_NUM = 18;           //灯珠数量
    LedMode m_mode = MODE_STATIC; //灯效状态
    CRGB* c_leds = nullptr;

    //呼吸灯参数
    uint8_t n_brightness = 0;       // 当前亮度
    int8_t n_step = 2;                // 亮度步进
    CRGB c_baseColor;           // 基础颜色

    //流水灯参数
    uint8_t n_rainbowHue;    // 当前幻彩色相
    unsigned long m_rainbowLastTick; // 上次更新时间
    uint16_t m_rainbowInterval;      // 流水速度

    //非阻塞时间
    unsigned long m_lastTick = 0; //上一次更新时间
    const unsigned long m_interval = 30;  //更新时间（ms）

};