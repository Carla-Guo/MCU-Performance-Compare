#include "rp_test.c"
#include <TFT_eSPI.h>   // 引入TFT_eSPI库

#define WIDTH 240
#define HEIGHT 180
int screenWidth = 240;  // 屏幕宽度
int screenHeight = 240; // 屏幕高度
uint8_t grayImage[WIDTH * HEIGHT];  // Grayscale image array
uint16_t rgb565Image[WIDTH * HEIGHT]; 


uint16_t rgb565;
// Extract RGB components from RGB565
uint8_t r;    // 5 bits for Red
uint8_t g;    // 6 bits for Green
uint8_t b;    // 5 bits for Blue
uint8_t gray;

TFT_eSPI tft = TFT_eSPI();  // 创建TFT_eSPI对象


void RGB565ToGray(){
   for (int i = 0; i < WIDTH * HEIGHT; i++) {
    rgb565 = (gImage_rp_test[i*2] << 8) | gImage_rp_test[i*2 + 1];
    r = (rgb565 >> 11) & 0x1F;   // 5 bits for Red
    g = (rgb565 >> 5) & 0x1F;    // 6 bits for Green
    b = rgb565 & 0x1F;

    r = (r * 255) / 31;
    g = (g * 255) / 63;
    b = (b * 255) / 31;

    // Calculate grayscale value
    uint8_t gray = (r * 77 + g * 150 + b * 29) >> 8;
    grayImage[i] = gray;        
  }
}

void GrayToRGB565() {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        gray = grayImage[i];  // Grayscale value (0-255)
        // Convert grayscale to RGB565
        uint16_t r = (gray >> 3) & 0x1F;  // 5 bits for red
        uint16_t g = (gray >> 2) & 0x3F;  // 6 bits for green
        uint16_t b = (gray >> 3) & 0x1F;  // 5 bits for blue

        // Combine into 16-bit RGB565 format
        rgb565Image[i] = (r << 11) | (g << 5) | b;
    }
}

void displayImage() {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      // Each pixel is 2 bytes (16-bit RGB565)
      int index = (y * WIDTH + x) * 2;
      rgb565 = (gImage_rp_test[index] << 8) | gImage_rp_test[index + 1];
      tft.drawPixel(x, y+30, rgb565);

    }
  }
}

void  displayGrayImage(){
    for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      // Each pixel is 2 bytes (16-bit RGB565)
      int index = (y * WIDTH + x);
      tft.drawPixel(x, y+30, rgb565Image[index]);
}}}
void setup() {
    // Serial.begin(115200);
    // while(!Serial);
    tft.init();            // 初始化TFT屏幕
}

void loop() {
    // Nothing in the loop
    displayImage();
    delay(500);
    tft.fillScreen(TFT_WHITE);
    delay(500);
    unsigned long start = micros();
    RGB565ToGray();
    unsigned long duration = micros() - start;
    GrayToRGB565();
    displayGrayImage();
    
    delay(500);

    tft.fillScreen(TFT_WHITE);  // 将屏幕初始为黑色
    tft.setTextColor(TFT_BLACK);  // 文字颜色设置为黑色
    tft.setTextSize(2);  // 设置文字大小
    tft.setCursor(30, 50);  // 设置文字位置
    // tft.print("XIAO RP2350"); //使用xiao_rp2350
    tft.print("XIAO RP2040"); //使用xiao_rp2040
    tft.setCursor(30, 80);  // 设置文字位置
    tft.print("Image size:");
    tft.setCursor(30, 100);  // 设置文字位置
    tft.print("240*180");
    tft.setCursor(30, 130);  // 位置稍微调整
    tft.print("Gray conversion");
    tft.setCursor(30, 150);  // 位置稍微调整
    tft.print("time (us): ");
    tft.print(duration);
    delay(5000);
}
