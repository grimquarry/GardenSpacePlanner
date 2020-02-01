/**
  Garden Space Planner
  ScrollBar.cpp
  Purpose: Source file for the ScrollBar class.  This class can be used to add
  a scrollbar to content displayed in a sf::View object.

  @author Jeremiah Kellogg
  @version 1.0.2 02/1/2020
*/
#include "ScrollBar.h"

//Default Constructor
ScrollBar::ScrollBar() { }

//Constructor
ScrollBar::ScrollBar(sf::View &view)
{
  m_isScrolling = false;
  m_firstClick = false;
  m_scrollBarView = view;
}

//Destructor
ScrollBar::~ScrollBar() { }

//Sets the m_firstClick member variable to true or false.
void ScrollBar::SetFirstClick(bool click)
{
  m_firstClick = click;
}

//Implements the logic behind scroll functionality
void ScrollBar::Scroll(sf::RenderWindow &window)
{
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
    m_scrollElement.setPosition(m_scrollElement.getPosition().x, m_mouseYNew - m_offset);
    m_centerScreen.setPosition(m_scrollBarView.getSize().x / 2.f, m_scrollBarView.getSize().y / 2 + m_scrollElement.getPosition().y * viewScrollSpeed);
  }
  //What to do if scroll bar slider is outside the max bounds of scrollbar container.
  else if(m_mouseYNew - m_offset > m_scrollContainer.getSize().y)
  {
    m_scrollElement.setPosition(m_scrollMaximum);
    m_centerScreen.setPosition(m_scrollBarView.getSize().x / 2.f, (m_scrollBarView.getSize().y / 2.f) + m_scrollMaximum.y);
  }
  //What to do if scrollbar slider is below the minimum bounds of scrollbar container.
  else if (m_mouseYNew - m_offset < m_scrollContainer.getPosition().y)
  {
    m_scrollElement.setPosition(m_scrollMinimum);
    m_centerScreen.setPosition(m_scrollBarView.getSize().x / 2.f, (m_scrollBarView.getSize().y / 2.f));
  }

  //What to do when user clicks inside scroll container above the scroll slider (m_scrollElement).
  if(m_mouseYNew < m_scrollElement.getPosition().y && m_scrollElement.getPosition().y > m_scrollMinimum.y)
  {
    m_scrollElement.setPosition(m_scrollElement.getPosition().x, m_scrollElement.getPosition().y  + m_offset - 20.f);
    m_centerScreen.setPosition(m_scrollBarView.getSize().x / 2.f, m_scrollBarView.getSize().y / 2 + m_scrollElement.getPosition().y * viewScrollSpeed);
  }
  //What to do when user clicks inside scroll container blow the scroll slider (m_scrollElement).
  else if(m_mouseYNew > m_scrollElement.getPosition().y + m_scrollElement.getSize().y && m_scrollElement.getPosition().y < m_scrollMaximum.y - m_scrollElement.getSize().y)
  {
    m_scrollElement.setPosition(m_scrollElement.getPosition().x, m_scrollElement.getPosition().y  + m_offset - 20.f);
    m_centerScreen.setPosition(m_scrollBarView.getSize().x / 2.f, m_scrollBarView.getSize().y / 2 + m_scrollElement.getPosition().y * viewScrollSpeed);
  }

  m_firstClick = false;//first click is no longer true after the program loop runs once after scrollbar is clicked.
}

//Returns true or false depending on whether the mouse is positioned over the scrollbar or not.
bool ScrollBar::MouseOverScroll(sf::RenderWindow &window, float x_offset, float y_offset)
{
  sf::Vector2i mouseWindowPostion = sf::Mouse::getPosition(window); //Grabs position of mouse in the window.  *****Should this be it's own function?  It's used in other spots, too*****
  window.setView(m_scrollBarView);
  sf::Vector2f mouseViewPosition = window.mapPixelToCoords(mouseWindowPostion); //Translates mouse position in window to mouse position in the view.  *****Should this be it's own function?  It's used in other spots, too*****

  //Use offset paramters to adjust mouse to view coordinates for Views that may not have been implemented properly.
  //This was done to account for the weird offset in the leftColumnView sf::View object that I may have implemented in a bad way (likely trying to account for window to view offsets).
  float adjustXPosition = m_scrollBarView.getSize().x * x_offset;
  mouseViewPosition.x -= adjustXPosition;
  float adjustYPosition = m_scrollBarView.getSize().y * y_offset;
  mouseViewPosition.y -=adjustYPosition;

  float scrollPosX = m_scrollElement.getPosition().x;
  float scrollXPosWidth = scrollPosX + m_scrollElement.getGlobalBounds().width;
  float scrollPosY = m_scrollContainer.getPosition().y;
  float scrollYPosHeight = scrollPosY + m_scrollBarView.getSize().y;

  if(mouseViewPosition.x < scrollXPosWidth && mouseViewPosition.x > scrollPosX && mouseViewPosition.y < scrollYPosHeight && mouseViewPosition.y > scrollPosY)
  {
    return true;
  }

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
  m_isScrolling = toScroll;
}

//Returns the value of the m_isScrolling member variable to determine if user is scrolling or not.
bool ScrollBar::GetScrolling()
{
  return m_isScrolling;
}

//Sets the color of the scrollbar (used for changing scrollbar color when user clicks on it).
void ScrollBar::SetElementColor(sf::Color color)
{
  m_scrollElement.setFillColor(color);
}

//Sets the color of the scrollbar Container).
void ScrollBar::SetContainerColor(sf::Color color)
{
  m_scrollContainer.setFillColor(color);
}

//Sets the size of a scrollbar container.
void ScrollBar::SetContainerSize (sf::Vector2f size)
{
  m_scrollContainer.setSize(size);
}

//Returns the size of the m_scrollContainer member (scroll bar container size).
sf::Vector2f ScrollBar::GetContainerSize()
{
  return m_scrollContainer.getSize();
}

//Sets the position of the Scrollbar container.
void ScrollBar::SetContainerPos(sf::Vector2f position)
{
  m_scrollContainer.setPosition(position);
}

//Returns the position of the scrollbar container (m_scrollContainer).
sf::Vector2f ScrollBar::GetContainerPos()
{
  m_scrollContainer.getPosition();
}

//Sets the minimum position the scrollbar slider can move to.
void ScrollBar::SetScrollMin()
{
  m_scrollMinimum.x = m_scrollContainer.getPosition().x * 1.015f;
  m_scrollMinimum.y =  m_scrollContainer.getPosition().y;
}

//Returns the minimum position the scrollbar slider can move to.
sf::Vector2f ScrollBar::GetScrollMin()
{
  return m_scrollMinimum;
}

//Sets the maximum position the scrollbar slider can move to.
void ScrollBar::SetScrollMax()
{
  m_scrollMaximum.x = m_scrollContainer.getPosition().x * 1.01f;
  m_scrollMaximum.y = m_scrollContainer.getGlobalBounds().height;
}

//Sets the size of the scrollbar slider (m_scrollElement).
void ScrollBar::SetElementSize(sf::Vector2f size)
{
  m_scrollElement.setSize(size);
}

//Sets the position of the scrollbar slider (m_scrollElement).
void ScrollBar::SetElementPos(sf::Vector2f position)
{
  m_scrollElement.setPosition(position);
}

//Sets the position of where the view should be in relation to the scrollbar.
void ScrollBar::SetCenterScreen(float x, float y)
{
  m_centerScreen.setPosition(x, y);
}

//Draws the scrollbar to the appropriate view.
void ScrollBar::Draw(sf::RenderWindow &window)
{
  window.draw(m_scrollContainer);
  window.draw(m_scrollElement);
}

//Sets the view where the scrollbar will be used.
void ScrollBar::SetView(sf::View &view)
{
  m_scrollBarView = view;
}
