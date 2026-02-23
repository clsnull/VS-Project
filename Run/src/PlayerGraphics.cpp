#include "PlayerGraphics.h"

#include "PlayerUpdate.h"
#include "Animator.h"

void PlayerGraphics::assemble(sf::VertexArray &canvas,
                              std::shared_ptr<Update> genericUpdate,
                              sf::IntRect texCoords)
{
    m_playerUpdate = std::static_pointer_cast<PlayerUpdate>(genericUpdate);
    m_position = m_playerUpdate->getPositionPointer();

    m_animator = new Animator(
        texCoords.position.x,
        texCoords.position.y,
        6, // 6帧
        texCoords.size.x * 6,
        texCoords.size.y,
        12); // 帧率

    m_sectionToDraw = m_animator->getCurrentFrame(false);
    m_standingStillSectionToDraw = m_animator->getCurrentFrame(false);

    m_vertexStartIndex = canvas.getVertexCount();

    canvas.resize(canvas.getVertexCount() + 6);
}

void PlayerGraphics::draw(sf::VertexArray &canvas)
{
    const sf::Vector2f &position = m_position->position;

    const sf::Vector2f &size = m_position->size;

    // 第一个三角形的位置
    canvas[m_vertexStartIndex].position = position;                                          // 左上
    canvas[m_vertexStartIndex + 1].position = sf::Vector2f(position.x + size.x, position.y); // 右上
    canvas[m_vertexStartIndex + 2].position = sf::Vector2f(position.x, position.y + size.y); // 左下

    // 第二个三角形的位置
    canvas[m_vertexStartIndex + 3].position = sf::Vector2f(position.x + size.x, position.y); // 右上
    canvas[m_vertexStartIndex + 4].position = position + size;                               // 右下
    canvas[m_vertexStartIndex + 5].position = sf::Vector2f(position.x, position.y + size.y); // 左

    if (m_playerUpdate->m_rightIsHeldDown && !m_playerUpdate->m_inJump &&
        !m_playerUpdate->m_boostIsHeldDown && m_playerUpdate->m_isGrounded)
    {
        m_sectionToDraw = m_animator->getCurrentFrame(false);
    }
    if (m_playerUpdate->m_leftIsHeldDown && !m_playerUpdate->m_inJump &&
        !m_playerUpdate->m_boostIsHeldDown &&
        m_playerUpdate->m_isGrounded)
    {
        m_sectionToDraw = m_animator->getCurrentFrame(true);
        //  reversed
    }
    else
    {
        //  Test  the players facing position
        //  in  case  it  changed  while jumping  or  boosting
        //  This  value  is  used  in  the final  animation  option
        if (m_playerUpdate->m_leftIsHeldDown)
        {
            m_lastFacingRight = false;
        }
        else
        {
            m_lastFacingRight = true;
        }
    }

    const int uPos = m_sectionToDraw->position.x;
    const int vPos = m_sectionToDraw->position.y;
    const int texWidth = m_sectionToDraw->size.x;
    const int texHeight = m_sectionToDraw->size.y;

    if (m_playerUpdate->m_rightIsHeldDown && !m_playerUpdate->m_inJump &&
        !m_playerUpdate->m_boostIsHeldDown)
    {
        canvas[m_vertexStartIndex].texCoords.x = uPos;
        canvas[m_vertexStartIndex].texCoords.y = vPos;
        canvas[m_vertexStartIndex + 1].texCoords.x = uPos + texWidth;
        canvas[m_vertexStartIndex + 1].texCoords.y = vPos;
        canvas[m_vertexStartIndex + 2].texCoords.x = uPos;
        canvas[m_vertexStartIndex + 2].texCoords.y = vPos + texHeight;

        canvas[m_vertexStartIndex + 3].texCoords.x = uPos + texWidth;
        canvas[m_vertexStartIndex + 3].texCoords.y = vPos;
        canvas[m_vertexStartIndex + 4].texCoords.x = uPos + texWidth;
        canvas[m_vertexStartIndex + 4].texCoords.y = vPos + texHeight;
        canvas[m_vertexStartIndex + 5].texCoords.x = uPos;
        canvas[m_vertexStartIndex + 5].texCoords.y = vPos + texHeight;
    }
    else if (m_playerUpdate->m_leftIsHeldDown && !m_playerUpdate->m_inJump &&
             !m_playerUpdate->m_boostIsHeldDown)
    {
        canvas[m_vertexStartIndex].texCoords.x = uPos;
        canvas[m_vertexStartIndex].texCoords.y = vPos;
        canvas[m_vertexStartIndex + 1].texCoords.x = uPos - texWidth;
        canvas[m_vertexStartIndex + 1].texCoords.y = vPos;
        canvas[m_vertexStartIndex + 2].texCoords.x = uPos;
        canvas[m_vertexStartIndex + 2].texCoords.y = vPos + texHeight;

        canvas[m_vertexStartIndex + 3].texCoords.x = uPos - texWidth;
        canvas[m_vertexStartIndex + 3].texCoords.y = vPos;
        canvas[m_vertexStartIndex + 4].texCoords.x = uPos - texWidth;
        canvas[m_vertexStartIndex + 4].texCoords.y = vPos + texHeight;
        canvas[m_vertexStartIndex + 5].texCoords.x = uPos;
        canvas[m_vertexStartIndex + 5].texCoords.y = vPos + texHeight;
    }
    else if (m_playerUpdate->m_rightIsHeldDown && m_playerUpdate->m_boostIsHeldDown)
    {
        canvas[m_vertexStartIndex].texCoords.x = BOOST_TEX_LEFT;
        canvas[m_vertexStartIndex].texCoords.y = BOOST_TEX_TOP;
        canvas[m_vertexStartIndex + 1].texCoords.x = BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[m_vertexStartIndex + 1].texCoords.y = BOOST_TEX_TOP;
        canvas[m_vertexStartIndex + 2].texCoords.x = BOOST_TEX_LEFT;
        canvas[m_vertexStartIndex + 2].texCoords.y = BOOST_TEX_TOP + BOOST_TEX_HEIGHT;

        canvas[m_vertexStartIndex + 3].texCoords.x = BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[m_vertexStartIndex + 3].texCoords.y = BOOST_TEX_TOP;
        canvas[m_vertexStartIndex + 4].texCoords.x = BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[m_vertexStartIndex + 4].texCoords.y = BOOST_TEX_TOP + BOOST_TEX_HEIGHT;
        canvas[m_vertexStartIndex + 5].texCoords.x = BOOST_TEX_LEFT;
        canvas[m_vertexStartIndex + 5].texCoords.y = BOOST_TEX_TOP + BOOST_TEX_HEIGHT;
    }
    else if (m_playerUpdate->m_leftIsHeldDown && m_playerUpdate->m_boostIsHeldDown)
    {
        canvas[m_vertexStartIndex].texCoords.x = BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[m_vertexStartIndex].texCoords.y = 0;
        canvas[m_vertexStartIndex + 1].texCoords.x = BOOST_TEX_LEFT;
        canvas[m_vertexStartIndex + 1].texCoords.y = 0;
        canvas[m_vertexStartIndex + 2].texCoords.x = BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[m_vertexStartIndex + 2].texCoords.y = 100;

        canvas[m_vertexStartIndex + 3].texCoords.x = BOOST_TEX_LEFT;
        canvas[m_vertexStartIndex + 3].texCoords.y = 0;
        canvas[m_vertexStartIndex + 4].texCoords.x = BOOST_TEX_LEFT;
        canvas[m_vertexStartIndex + 4].texCoords.y = 100;
        canvas[m_vertexStartIndex + 5].texCoords.x = BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[m_vertexStartIndex + 5].texCoords.y = 100;
    }
    else if (m_playerUpdate->m_boostIsHeldDown)
    {
        canvas[m_vertexStartIndex].texCoords.x = BOOST_TEX_LEFT;
        canvas[m_vertexStartIndex].texCoords.y = BOOST_TEX_TOP;
        canvas[m_vertexStartIndex + 1].texCoords.x = BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[m_vertexStartIndex + 1].texCoords.y = BOOST_TEX_TOP;
        canvas[m_vertexStartIndex + 2].texCoords.x = BOOST_TEX_LEFT;
        canvas[m_vertexStartIndex + 2].texCoords.y = BOOST_TEX_TOP + BOOST_TEX_HEIGHT;

        canvas[m_vertexStartIndex + 3].texCoords.x = BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[m_vertexStartIndex + 3].texCoords.y = BOOST_TEX_TOP;
        canvas[m_vertexStartIndex + 4].texCoords.x = BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[m_vertexStartIndex + 4].texCoords.y = BOOST_TEX_TOP + BOOST_TEX_HEIGHT;
        canvas[m_vertexStartIndex + 5].texCoords.x = BOOST_TEX_LEFT;
        canvas[m_vertexStartIndex + 5].texCoords.y = BOOST_TEX_TOP + BOOST_TEX_HEIGHT;
    }
    else
    {
        if (m_lastFacingRight)
        {
            canvas[m_vertexStartIndex].texCoords.x = m_standingStillSectionToDraw->position.x;
            canvas[m_vertexStartIndex].texCoords.y = m_standingStillSectionToDraw->position.y;
            canvas[m_vertexStartIndex + 1].texCoords.x = m_standingStillSectionToDraw->position.x + texWidth;
            canvas[m_vertexStartIndex + 1].texCoords.y = m_standingStillSectionToDraw->position.y;
            canvas[m_vertexStartIndex + 2].texCoords.x = m_standingStillSectionToDraw->position.x;
            canvas[m_vertexStartIndex + 2].texCoords.y = m_standingStillSectionToDraw->position.y + texHeight;

            canvas[m_vertexStartIndex + 3].texCoords.x = m_standingStillSectionToDraw->position.x + texWidth;
            canvas[m_vertexStartIndex + 3].texCoords.y = m_standingStillSectionToDraw->position.y;
            canvas[m_vertexStartIndex + 4].texCoords.x = m_standingStillSectionToDraw->position.x + texWidth;
            canvas[m_vertexStartIndex + 4].texCoords.y = m_standingStillSectionToDraw->position.y + texHeight;
            canvas[m_vertexStartIndex + 5].texCoords.x = m_standingStillSectionToDraw->position.x;
            canvas[m_vertexStartIndex + 5].texCoords.y = m_standingStillSectionToDraw->position.y + texHeight;
        }
        else
        {
            canvas[m_vertexStartIndex].texCoords.x = m_standingStillSectionToDraw->position.x + texWidth;
            canvas[m_vertexStartIndex].texCoords.y = m_standingStillSectionToDraw->position.y;
            canvas[m_vertexStartIndex + 1].texCoords.x = m_standingStillSectionToDraw->position.x;
            canvas[m_vertexStartIndex + 1].texCoords.y = m_standingStillSectionToDraw->position.y;
            canvas[m_vertexStartIndex + 2].texCoords.x = m_standingStillSectionToDraw->position.x + texWidth;
            canvas[m_vertexStartIndex + 2].texCoords.y = m_standingStillSectionToDraw->position.y + texHeight;

            canvas[m_vertexStartIndex + 3].texCoords.x = m_standingStillSectionToDraw->position.x;
            canvas[m_vertexStartIndex + 3].texCoords.y = m_standingStillSectionToDraw->position.y;
            canvas[m_vertexStartIndex + 4].texCoords.x = m_standingStillSectionToDraw->position.x;
            canvas[m_vertexStartIndex + 4].texCoords.y = m_standingStillSectionToDraw->position.y + texHeight;
            canvas[m_vertexStartIndex + 5].texCoords.x = m_standingStillSectionToDraw->position.x + texWidth;
            canvas[m_vertexStartIndex + 5].texCoords.y = m_standingStillSectionToDraw->position.y + texHeight;
        }
    }
}

PlayerGraphics::~PlayerGraphics()
{
    delete m_animator;
}