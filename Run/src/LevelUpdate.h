#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Update.h"

class LevelUpdate : public Update
{
private:
    // 是否暂停
    bool m_isPaused = true;
    // 所有平台的位置和大小
    std::vector<sf::FloatRect *> m_platformPositions;
    // 当前游戏尝试运行的秒数
    float *m_cameraTime = new float;
    // 玩家的位置
    sf::FloatRect *m_playerPosition;
    // 用于保存创建新平台之间的等待时间
    float m_platformCreationInterval = 0;
    float m_timeSinceLastPlatform = 0;
    // 下一个要重复使用的平台在平台位置向量中的位置
    int m_nextPlatformToMove = 0;
    // 已创建的平台数量
    int m_numberOfPlatforms = 0;
    // 下一个平台相对于前一个平台在平台位置向量中的移动位置
    int m_moveRelativeToPlatform = 0;
    // 游戏是否结束
    bool m_gameOver = true;
    // 设置所有游戏对象的初始位置
    void positionLevelAtStart();

public:
    void addPlatformPosition(sf::FloatRect *newPosition);
    void connectToCameraTime(float *cameraTime);
    bool *getIsPausedPointer();
    int getRandomNumber(int minHeight, int maxHeight);

    void update(float fps) override;
    void assemble(
        std::shared_ptr<LevelUpdate> levelUpdate,
        std::shared_ptr<PlayerUpdate> playerUpdate) override;
};