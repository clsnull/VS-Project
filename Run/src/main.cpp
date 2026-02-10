#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"
#include "Factory.h"
#include "InputDispatcher.h"

int main()
{
	// 创建一个窗口
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Booster");

	// 一个顶点数组，用于保存我们所有的图形
	sf::VertexArray canvas(sf::PrimitiveType::Triangles, 0);

	// 这个可以将事件分发给任何对象
	InputDispatcher inputDispatcher(&window);

	// 所有东西都将是游戏对象，这个向量将保存它们
	std::vector<GameObject> gameObjects;

	// 这个类拥有构建执行各种不同功能的游戏对象所需的所有知识
	Factory factory(&window);

	// 这个调用会将游戏对象向量、用于绘制的画布以及输入分发器发送给工厂，以设置游戏
	factory.loadLevel(gameObjects, canvas, inputDispatcher);

	// 计时的时钟
	sf::Clock clock;
	// 背景颜色
	const sf::Color BACKGROUND_COLOR(100, 100, 100, 255);

	while (window.isOpen())
	{
		float timeTakenInSeconds = 0.00046; //clock.restart().asSeconds();
		// 处理玩家输入
		inputDispatcher.dispatchInputEvents();
		// 清除上一帧
		window.clear(BACKGROUND_COLOR);
		// 更新所有游戏对象
		for (auto &gameObject : gameObjects)
		{
			gameObject.update(timeTakenInSeconds);
		}
		// 绘制所有游戏对象
		for (auto &gameObject : gameObjects)
		{
			gameObject.draw(canvas);
		}

		// 显示新的一帧
		window.display();
	}

	return 0;
}