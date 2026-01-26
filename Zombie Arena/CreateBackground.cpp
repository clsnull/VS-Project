#include "Zombie Arena.h"

int createBackground(sf::VertexArray &rVA, sf::IntRect arena)
{
    const int TILE_SIZE = 50;
    const int TILE_TYPES = 3;
    const int VERTS_IN_QUAD = 3 * 2; // 使用两个三角形构成一个四边形

    int worldWidth = arena.size.x / TILE_SIZE;
    int worldHeight = arena.size.y / TILE_SIZE;

    // 使用那种基本图形
    rVA.setPrimitiveType(sf::PrimitiveType::Triangles);

    // 设置顶点数组的大小
    rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

    // 从顶点数据的开关开始
    int currentVertex = 0;

    for (int w = 0; w < worldWidth; w++)
    {
        for (int h = 0; h < worldHeight; h++)
        {
            // 第一个三角形
            rVA[currentVertex + 0].position = sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE);
            rVA[currentVertex + 1].position = sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
            rVA[currentVertex + 2].position = sf::Vector2f(w * TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

            // 第二个三角形
            rVA[currentVertex + 3].position = sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
            rVA[currentVertex + 4].position = sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
            rVA[currentVertex + 5].position = sf::Vector2f(w * TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

            if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1)
            {
                rVA[currentVertex + 0].texCoords = sf::Vector2f(0, 0 + TILE_TYPES * TILE_SIZE);
                rVA[currentVertex + 1].texCoords = sf::Vector2f(TILE_SIZE, 0 + TILE_TYPES * TILE_SIZE);
                rVA[currentVertex + 2].texCoords = sf::Vector2f(0, TILE_SIZE + TILE_TYPES * TILE_SIZE);

                rVA[currentVertex + 3].texCoords = sf::Vector2f(TILE_SIZE, 0 + TILE_TYPES * TILE_SIZE);
                rVA[currentVertex + 4].texCoords = sf::Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE);
                rVA[currentVertex + 5].texCoords = sf::Vector2f(0, TILE_SIZE + TILE_TYPES * TILE_SIZE);
            }
            else
            {
                //随机种子
                srand((int)time(0) + h * w - h);
                // 随机数，0 - TILE_TYPES
                int mOrG = (rand() % TILE_TYPES);
                int verticalOffset = mOrG * TILE_SIZE;

                rVA[currentVertex + 0].texCoords = sf::Vector2f(0, 0 + verticalOffset);
                rVA[currentVertex + 1].texCoords = sf::Vector2f(TILE_SIZE, 0 + verticalOffset);
                rVA[currentVertex + 2].texCoords = sf::Vector2f(0, TILE_SIZE + verticalOffset);

                rVA[currentVertex + 3].texCoords = sf::Vector2f(TILE_SIZE, 0 + verticalOffset);
                rVA[currentVertex + 4].texCoords = sf::Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
                rVA[currentVertex + 5].texCoords = sf::Vector2f(0, TILE_SIZE + verticalOffset);
            }

            // 下六个顶点的位置
            currentVertex = currentVertex + VERTS_IN_QUAD;
        }
    }
    return TILE_SIZE;
}