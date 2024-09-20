#include <TFT_eSPI.h>   // 引入TFT_eSPI库

TFT_eSPI tft = TFT_eSPI();  // 创建TFT_eSPI对象

int screenWidth = 240;  // 屏幕宽度
int screenHeight = 240; // 屏幕高度

unsigned long startTime;
float totalTime = 0;
float averageFPS;
float fillFPS;
int colorCount = 6;  // 总共要填充6种颜色

void setup() {
  Serial.begin(115200);  // 初始化串口，用于输出结果
  tft.init();            // 初始化TFT屏幕
  tft.fillScreen(TFT_BLACK);  // 将屏幕初始为黑色
}

void fillScreenAndMeasure(uint16_t color) {
  startTime = millis();  // 记录开始时间
  for (int y = 0; y < screenHeight; y++) {
    for (int x = 0; x < screenWidth; x++) {
      tft.drawPixel(x, y, color);  // 填充每个像素为指定颜色
    }
  }
  unsigned long fillTime = millis() - startTime;  // 计算填充所用时间
  fillFPS = 1000.0 / fillTime;  // 计算FPS
  totalTime += fillTime;  // 累加到总时间

  // 输出填充时间和FPS
  Serial.print("Fill time (ms): ");
  Serial.println(fillTime);
  Serial.print("Fill FPS: ");
  Serial.println(fillFPS);
}

void loop() {
  // 填充6种颜色
  fillScreenAndMeasure(TFT_RED);
  fillScreenAndMeasure(TFT_BLUE);
  fillScreenAndMeasure(TFT_GREEN);
  fillScreenAndMeasure(TFT_YELLOW);
  fillScreenAndMeasure(TFT_BLACK);
  fillScreenAndMeasure(TFT_WHITE);

  // 计算平均FPS
  averageFPS = (1000.0 * colorCount) / totalTime;

  // 输出总时间和平均FPS
  Serial.print("Total fill time (ms): ");
  Serial.println(totalTime);
  Serial.print("Average FPS: ");
  Serial.println(averageFPS);

  // 在白色背景上显示总时间和平均FPS
  tft.setTextColor(TFT_BLACK);  // 文字颜色设置为黑色
  tft.setTextSize(2);  // 设置文字大小

  tft.setCursor(10, 90);  // 设置文字位置

  tft.print("XIAO RP2350"); //使用xiao_rp2350
  // tft.print("XIAO RP2040"); //使用xiao_rp2040


  tft.setCursor(10, 115);  // 设置文字位置
  tft.print("Total time: ");
  tft.print(totalTime);
  tft.println(" ms");

  tft.setCursor(10, 150);  // 位置稍微调整
  tft.print("Avg FPS: ");
  tft.print(averageFPS);

  delay(5000);  // 等待一段时间再重复测量

  totalTime = 0;  // 重置总时间
}
