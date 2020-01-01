#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ContentContainer.h"

class ScrollBar
{
public:
  //Default Constructor
  ScrollBar();

  /**
    Constructor

    @param &view Reference to the view object the scrollbar belongs to.
  */
  ScrollBar(sf::View &view);

  //Default Destructor.
  ~ScrollBar();

  /**
    Sets the m_firstClick member variable to true or false.

    @param click A true or false value.
  */
  void SetFirstClick(bool click);

  /**
    Returns the value of the m_firstClick member variable.
  */
  bool GetFirstClick();

  /**
    Implements the logic behind scroll functionality

    @param &window The sf::RenderWindow object the scrollbar should be drawn to.
    @param &viewborder References the sf::RectangleShape object set as a border for the left column.
  */
  void Scroll(sf::RenderWindow &window, sf::RectangleShape &viewborder);

  /**
    Returns true or false depending on whether the mouse is positioned over the scrollbar or not.

    @param &window The sf::RenderWindow object the scrollbar is drawn to.
  */
  bool MouseOverScroll(sf::RenderWindow &window);

  /**
    Returns an sf::Vector2f object containing x and y axis position coordinates of the scrollbar.

    @param &container References a ContentContainer object to get scrollbar position relative to the content container position.
  */
  sf::Vector2f GetScrollPosition(ContentContainer &container);

  /**
    Sets whether or not the user is utilizing scroll functionality by passing the right value to the m_isScrolling member variable.

    @param toScroll The boolean value to be assigned to m_isScrolling member variable.
  */
  void SetScrolling(bool toScroll);

  /**
    Returns the value of the m_isScrolling member variable to determine if user is scrolling or not.
  */
  bool GetScrolling();

  /**
    Sets the color of the scrollbar (used for changing scrollbar color when user clicks on it).

    @param color The sf::Color object passed to m_scrollElement (scrollbar) to set the fill color.
  */
  void SetElementColor(sf::Color color);


  void SetContainerColor(sf::Color color);

  void SetContainerSize(sf::Vector2f size);

  sf::Vector2f GetContainerSize();

  void SetContainerPos(sf::Vector2f position);

  sf::Vector2f GetContainerPos();

  void SetScrollMin();

  sf::Vector2f GetScrollMin();

  void SetScrollMax();

  void SetElementSize(sf::Vector2f size);

  void SetElementPos(sf::Vector2f position);

  void SetCenterScreen(float x, float y);

  void Draw(sf::RenderWindow &window);

  void SetView(sf::View &view);

private:
  bool m_isScrolling;  //Member variable identifying if the user is scrolling or not.
  bool m_firstClick;  //Member variable identifying if a user is clicking on the scrollbar from a non scrolling state.
  sf::View m_scrollBarView; //Object identifyinng the view the left column should be associated with.
  float m_mouseYNew; //Most current postion of the mouse's y coordinate position.
  float m_offset; //Offset between where the user clicked the scrollbar and the position of the scrollbar.
  sf::RectangleShape m_scrollElement; //Object for the scrollbar slider.
  sf::RectangleShape m_scrollContainer;  //Container holding the scrollbar slider.
  sf::RectangleShape m_centerScreen;//Object that determines where the view camera is positioned over the content display.
  sf::Vector2f m_scrollMaximum; //Object with x & y coordinates for maximum scrollbar position.
  sf::Vector2f m_scrollMinimum; //Object with x & coordinates for minimum scollbar position.

};
