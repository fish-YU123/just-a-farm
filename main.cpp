//g++.exe main.cpp -o main.exe -I mingw64\include -L mingw64\lib -lsfml-graphics -lsfml-window -lsfml-system
#include "./public/renderer/GameBase.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
	// 创建游戏窗口，宽度800，高度600，标题为"SFML图片示例"
	GameBase game(800, 600, "SFML图片示例");

	// 图片路径（请替换为你自己的图片路径）
	string imagePath = "./block/grass/paint/Sptite-0001.png";

	// 游戏主循环
	while (game.isWindowOpen()) {
		// 处理事件（如关闭窗口）
		if (!game.processEvents()) {
			break;
		}

		// 清除窗口（黑色背景）
		game.clearWindow();

		// 在坐标(100, 50)处绘制图片
		bool drawSuccess = game.drawImage(100, 50, imagePath);

		// 如果图片加载失败，输出错误信息
		if (!drawSuccess) {
			std::cerr << "警告：无法加载图片 '" << imagePath << "'" << std::endl;
			std::cerr << "请检查图片路径是否正确" << std::endl;
		}

		// 显示绘制的内容
		game.displayWindow();
	}

	return 0;
}
