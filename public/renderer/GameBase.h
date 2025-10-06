#ifndef GAME_BASE_H
#define GAME_BASE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <stdexcept>

// 游戏基础类，封装窗口和图片处理功能
class GameBase {
private:
    // 窗口对象
    sf::RenderWindow window;
    // 窗口尺寸
    unsigned int windowWidth;
    unsigned int windowHeight;
    // 窗口标题
    std::string windowTitle;

public:
    // 构造函数：初始化窗口参数
    GameBase(unsigned int width = 800, unsigned int height = 600,
             const std::string& title = "SFML Game")
        : windowWidth(width), windowHeight(height), windowTitle(title) {
        // 初始化窗口
        window.create(sf::VideoMode(width, height), title);
        // 设置帧率上限
        window.setFramerateLimit(60);
    }

    // 析构函数
    ~GameBase() {
        if (window.isOpen()) {
            window.close();
        }
    }

    // 检查窗口是否打开
    bool isWindowOpen() const {
        return window.isOpen();
    }

    // 处理窗口事件
    bool processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }
        }
        return true;
    }

    // 清除窗口
    void clearWindow(const sf::Color& color = sf::Color::Black) {
        window.clear(color);
    }

    // 显示窗口内容
    void displayWindow() {
        window.display();
    }

    // 加载并绘制图片
    // 参数：x-左上角x坐标, y-左上角y坐标, imagePath-图片路径
    bool drawImage(float x, float y, const std::string& imagePath) {
        sf::Texture texture;
        // 加载纹理
        if (!texture.loadFromFile(imagePath)) {
            return false; // 加载失败
        }

        sf::Sprite sprite(texture);
        // 设置位置
        sprite.setPosition(x, y);
        // 绘制精灵
        window.draw(sprite);
        return true; // 绘制成功
    }

    // 获取窗口引用
    sf::RenderWindow& getWindow() {
        return window;
    }

    // 获取窗口宽度
    unsigned int getWindowWidth() const {
        return windowWidth;
    }

    // 获取窗口高度
    unsigned int getWindowHeight() const {
        return windowHeight;
    }

    // 改变窗口大小
    void resizeWindow(unsigned int width, unsigned int height) {
        windowWidth = width;
        windowHeight = height;
        window.setSize(sf::Vector2u(width, height));
    }

    // 改变窗口标题
    void setWindowTitle(const std::string& title) {
        windowTitle = title;
        window.setTitle(title);
    }
};

#endif // GAME_BASE_H
