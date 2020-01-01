#include "ScrollBar.h"

ScrollBar::ScrollBar() { }

ScrollBar::ScrollBar(sf::View &view)
{
  //Scrolling and first click on scrollbar should not be true on instantiation of the object.
  m_isScrolling = false;
  m_firstClick = false;
  m_scrollBarView = view;
}

ScrollBar::~ScrollBar() { }

//Sets the m_firstClick member variable to true or false.
void ScrollBar::SetFirstClick(bool click)
{
  m_firstClick = click;
}

//Returns the value of the m_firstClick member variable.
bool ScrollBar::GetFirstClick()
{
  return m_firstClick;
}

//Implements the logic behind scroll functionality
void ScrollBar::Scroll(sf::RenderWindow &window, sf::RectangleShape &viewborder)
{
  std::cout << "Scroll was called" << std::endl;
  sf::Vector2i mouseWindowPostion = sf::Mouse::getPosition(window); //Grabs position of mouse in the window.  *****Should this be it's own function?  It's used in other spots, too*****
  sf::Vector2f mouseViewPosition = window.mapPixelToCoords(mouseWindowPostion);  //Translates mouse position in window to mouse position in the view. *****Should this be it's own function?  It's used in other spots, too*****

  m_mouseYNew = mouseViewPosition.y;

  //Establish difference between scroll bar slider position and where the user clicked in the scroll bar slider.
  if(m_firstClick)
  {
    m_offset = m_mouseYNew - m_scrollElement.getPosition().y;
  }

  //Algorithm for determining how fast the view should scroll in relation to scroll bar slider movement.
  float viewScrollSpeed = (m_scrollContainer.getSize().y - m_scrollBarView.getSize().y) / (m_scrollContainer.getSize().y - m_scrollElement.getSize().y);

  //What to do if scroll bar slider is within bounds of scroll bar container.
  if(m_mouseYNew - m_offset > m_scrollContainer.getPosition().y && m_mouseYNew - m_offset < m_scrollContainer.getSize().y - m_scrollElement.getSize().y)
  {
    std::cout << "First if statment ran." << std::endl;
    m_scrollElement.setPosition(m_scrollElement.getPosition().x, m_mouseYNew - m_offset);
    m_centerScreen.setPosition(m_scrollBarView.getSize().x / 2.f, m_scrollBarView.getSize().y / 2 + m_scrollElement.getPosition().y * viewScrollSpeed);
  }
  //What to do if scroll bar slider is outside the max bounds of scrollbar container.
  else if(m_mouseYNew - m_offset > m_scrollContainer.getSize().y)
  {
    std::cout << "First else if statement ran." << std::endl;
    m_scrollElement.setPosition(m_scrollMaximum);
    m_centerScreen.setPosition(m_scrollBarView.getSize().x / 2.f, (m_scrollBarView.getSize().y / 2.f) + m_scrollMaximum.y);
  }
  //What to do if scrollbar slider is below the minimum bounds of scrollbar container.
  else if (m_mouseYNew - m_offset < m_scrollContainer.getPosition().y)
  {
    std::cout << "Second else if statment ran" << std::endl;
    m_scrollElement.setPosition(m_scrollMinimum);
    m_centerScreen.setPosition(m_scrollBarView.getSize().x / 2.f, (m_scrollBarView.getSize().y / 2.f));
  }
  m_firstClick = false;//first click is no longer true after the program loop runs once after scrollbar is clicked.
}

//Returns true or false depending on whether the mouse is positioned over the scrollbar or not.
bool ScrollBar::MouseOverScroll(sf::RenderWindow &window)
{
  std::cout << "MouseOverScroll was called" << std::endl;
  sf::Vector2i mouseWindowPostion = sf::Mouse::getPosition(window); //Grabs position of mouse in the window.  *****Should this be it's own function?  It's used in other spots, too*****
  sf::Vector2f mouseViewPosition = window.mapPixelToCoords(mouseWindowPostion); //Translates mouse position in window to mouse position in the view.  *****Should this be it's own function?  It's used in other spots, too*****

  std::cout << "mouseViewPostion X is: " << mouseViewPosition.x << std::endl;
  std::cout << "mouseViewPostion Y is: " << mouseViewPosition.y << std::endl;
  float scrollPosX = m_scrollElement.getPosition().x;
  float scrollXPosWidth = scrollPosX + m_scrollElement.getGlobalBounds().width;
  std::cout << "Scroll element X is: " << scrollPosX << std::endl;
  std::cout << "Scroll element Y is: " << m_scrollElement.getPosition().y << std::endl;

  if(mouseViewPosition.x < scrollXPosWidth && mouseViewPosition.x > scrollPosX && mouseViewPosition.y < m_scrollElement.getPosition().y + m_scrollElement.getSize().y && mouseViewPosition.y > m_scrollContainer.getPosition().y)
  {
    std::cout << "returned true" << std::endl;
    return true;
  }
  std::cout << "returned false" << std::endl;
  return false;
}

//Returns an sf::Vector2f object containing x and y axis position coordinates of the scrollbar.
sf::Vector2f ScrollBar::GetScrollPosition(ContentContainer &container)
{
  return {m_centerScreen.getPosition().x, m_centerScreen.getPosition().y};
}

//Sets whether or not the user is utilizing scroll functionality by passing the right value to the m_isScrolling member variable.
void ScrollBar::SetScrolling(bool toScroll)
{
  std::cout << "SetScrolling was called and assigned: " << toScroll << std::endl;
  m_isScrolling = toScroll;
}

//Returns the value of the m_isScrolling member variable to determine if user is scrolling or not.
bool ScrollBar::GetScrolling()
{
  //std::cout << "GetScrolling was called and returned value of: " << m_isScrolling << std::endl;
  return m_isScrolling;
}

//Sets the color of the scrollbar (used for changing scrollbar color when user clicks on it).
void ScrollBar::SetElementColor(sf::Color color)
{
  std::cout << "SetElementColor was called" << std::endl;
  m_scrollElement.setFillColor(color);
}

void ScrollBar::SetContainerColor(sf::Color color)
{
  m_scrollContainer.setFillColor(color);
}

void ScrollBar::SetContainerSize (sf::Vector2f size)
{
  m_scrollContainer.setSize(size);
}

sf::Vector2f ScrollBar::GetContainerSize()
{
  return m_scrollContainer.getSize();
}

void ScrollBar::SetContainerPos(sf::Vector2f position)
{
  m_scrollContainer.setPosition(position);
}

sf::Vector2f ScrollBar::GetContainerPos()
{
  m_scrollContainer.getPosition();
}

void ScrollBar::SetScrollMin()
{
  m_scrollMinimum.x = m_scrollContainer.getPosition().x * 1.015f;
  m_scrollMinimum.y =  m_scrollContainer.getPosition().y;
}

sf::Vector2f ScrollBar::GetScrollMin()
{
  return m_scrollMinimum;
}

void ScrollBar::SetScrollMax()
{
  m_scrollMaximum.x = m_scrollContainer.getPosition().x * 1.01f;
  m_scrollMaximum.y = m_scrollContainer.getGlobalBounds().height;
}

void ScrollBar::SetElementSize(sf::Vector2f size)
{
  m_scrollElement.setSize(size);
}

void ScrollBar::SetElementPos(sf::Vector2f position)
{
  m_scrollElement.setPosition(position);
}

void ScrollBar::SetCenterScreen(float x, float y)
{
  m_centerScreen.setPosition(x, y);
}

void ScrollBar::SetView(sf::View &view)
{
  m_scrollBarView = view;
}

void ScrollBar::Draw(sf::RenderWindow &window)
{
  window.draw(m_scrollContainer);
  window.draw(m_scrollElement);
}
