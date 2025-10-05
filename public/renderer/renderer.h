#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>

class Renderer {
private:
    SDL_Window* window;       // 窗口指针
    SDL_Renderer* renderer;   // 渲染器指针
    int windowWidth;          // 窗口宽度
    int windowHeight;         // 窗口高度
    bool isInitialized;       // 初始化状态

public:
    // 构造函数：创建指定大小的窗口
    Renderer(int width, int height, const std::string& title = "Renderer Window") 
        : window(nullptr), renderer(nullptr), 
          windowWidth(width), windowHeight(height), isInitialized(false) {
        // 初始化SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error("SDL初始化失败: " + std::string(SDL_GetError()));
        }

        // 初始化图像加载库
        if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
            SDL_Quit();
            throw std::runtime_error("SDL_image初始化失败: " + std::string(IMG_GetError()));
        }

        // 创建窗口
        window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_SHOWN
        );

        if (!window) {
            IMG_Quit();
            SDL_Quit();
            throw std::runtime_error("窗口创建失败: " + std::string(SDL_GetError()));
        }

        // 创建渲染器
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!renderer) {
            SDL_DestroyWindow(window);
            IMG_Quit();
            SDL_Quit();
            throw std::runtime_error("渲染器创建失败: " + std::string(SDL_GetError()));
        }

        isInitialized = true;
    }

    // 析构函数：清理资源
    ~Renderer() {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
        IMG_Quit();
        SDL_Quit();
    }

    // 禁用拷贝构造和赋值操作
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    // 在指定位置绘制图片
    bool image(int x, int y, const std::string& imagePath) {
        if (!isInitialized) {
            return false;
        }

        // 加载图片
        SDL_Surface* surface = IMG_Load(imagePath.c_str());
        if (!surface) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "图片加载失败 %s: %s", 
                       imagePath.c_str(), IMG_GetError());
            return false;
        }

        // 创建纹理
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);  // 释放surface

        if (!texture) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "纹理创建失败: %s", SDL_GetError());
            return false;
        }

        // 获取图片尺寸
        int imgWidth, imgHeight;
        SDL_QueryTexture(texture, nullptr, nullptr, &imgWidth, &imgHeight);

        // 设置绘制位置和尺寸
        SDL_Rect destRect = {x, y, imgWidth, imgHeight};

        // 绘制纹理
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);
        
        // 释放纹理
        SDL_DestroyTexture(texture);
        
        return true;
    }

    // 清空渲染器（准备绘制新帧）
    void clear() {
        if (isInitialized) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // 黑色背景
            SDL_RenderClear(renderer);
        }
    }

    // 更新窗口显示
    void present() {
        if (isInitialized) {
            SDL_RenderPresent(renderer);
        }
    }

    // 获取窗口宽度
    int getWindowWidth() const { return windowWidth; }

    // 获取窗口高度
    int getWindowHeight() const { return windowHeight; }

    // 检查是否初始化成功
    bool isReady() const { return isInitialized; }
};

#endif // RENDERER_H