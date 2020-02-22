/**
  Garden Space Planner
  ScrollBar.h
  Purpose: Header file for the ScrollBar class.  This class can be used to add
  a scrollbar to content displayed in a sf::View object.

  @author Jeremiah Kellogg
  @version 1.0.1 01/11/20
*/
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ContentContainer.h"
#include "Map.h"

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
    Implements the logic behind scroll functionality

    @param &window The sf::RenderWindow object the scrollbar should be drawn to.
  */
  void Scroll(sf::RenderWindow &window, sf::Event &event);

  /**
    Returns true or false depending on whether the mouse is positioned over the scrollbar or not.

    @param &window The sf::RenderWindow object the scrollbar is drawn to.
    @param offset Optional parameter to fix weird offset between mouse position and scroll slider (scroll element) position
      happening in the SelectMap instatiation of a scrollbar.  This should be investigated further.
    @param y_offset Optional parameter to fix wierd y axis offset that's likely tied to poor implementation of a view
      (it works the way it should without offsets in the main content view displaying maps, but not in leftcolumn view).
  */
  bool MouseOverScroll(sf::RenderWindow &window, float x_offset = 0, float y_offset = 0);

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
    Sets the color of the scrollbar slider (used for changing scrollbar color when user clicks on it).

    @param color The sf::Color object passed to m_scrollElement (scrollbar) to set the fill color.
  */
  void SetElementColor(sf::Color color);

  /**
    Function template that updates size and position of scroll area when a new sf::RectangleShape object is added to
      or removed from the scrollable area.  It resizes things when new maps or plants are added.

    @param &newItem References a clickable container used to display the new map or plant.
    @param &displayArea References an object storing the size and location of scrollable content in a view.
    @param &vector References a vector that can be used to update and calculate the new size of a displayArea.
    @param &viewScreenRatio References a screen to view ratio used to calculate and update scroll info.
  */
  template<typename itemVector>
  void UpdateScrollArea(sf::RectangleShape &newItem, sf::RectangleShape &displayArea, std::vector<itemVector> &vector, float &screenViewRatio)
  {
    newItem.setSize({m_scrollBarView.getSize().x - (m_scrollBarView.getSize().x * .02f), m_scrollBarView.getSize().y / 4});
    displayArea.setSize({m_scrollBarView.getSize().x, newItem.getSize().y * vector.size()});
    m_scrollContainer.setSize({m_scrollBarView.getSize().x * .02f, displayArea.getSize().y});
    m_scrollElement.setSize({m_scrollContainer.getSize().x * .75f, m_scrollBarView.getSize().y / screenViewRatio});
    m_scrollMinimum.x = m_scrollContainer.getPosition().x * 1.0032f;
    m_scrollMinimum.y =  m_scrollContainer.getPosition().y;
    m_scrollMaximum.x = m_scrollContainer.getPosition().x * 1.01f;
    m_scrollMaximum.y = m_scrollContainer.getGlobalBounds().height;
  };

  /**
    Sets the color of the scrollbar Container).

    @param color The sf::Color object passed to m_scrollContainer (scrollbar) to set the fill color.
  */
  void SetContainerColor(sf::Color color);

  /**
    Sets the size of a scrollbar container.

    @param size The sf::Vector2f object passed to m_scrollContainer to set the size.
  */
  void SetContainerSize(sf::Vector2f size);

  /**
    Returns the size of the m_scrollContainer member (scroll bar container size).
  */
  sf::Vector2f GetContainerSize();

  /**
    Sets the position of the Scrollbar container.

    @param position The sf::Vector2f value passed to m_scrollContainer to position it.
  */
  void SetContainerPos(sf::Vector2f position);

  /**
    Returns the position of the scrollbar container (m_scrollContainer).
  */
  sf::Vector2f GetContainerPos();

  /**
    Sets the minimum position the scrollbar slider can move to.
  */
  void SetScrollMin();

  /**
    Returns the minimum position the scrollbar slider can move to.
  */
  sf::Vector2f GetScrollMin();

  /**
    Sets the maximum position the scrollbar slider can move to.
  */
  void SetScrollMax();

  /************WHY IS THERE NO SCROLLMAX??? Might be part of the program's bugginess?**********/

  /**
    Sets the size of the scrollbar slider (m_scrollElement).

    @param size The sf::Vector2f value that sets the size of the slider (m_scrollElement).
  */
  void SetElementSize(sf::Vector2f size);

  /**
    Sets the position of the scrollbar slider (m_scrollElement).

    @param position The sf::Vector2f value that sets the position of the slider (m_scrollElement).
  */
  void SetElementPos(sf::Vector2f position);

  /**
    Sets the position of where the view should be in relation to the scrollbar.

    @param x The horizontal center position where the view should focusing.
    @param y The verticle center position where the view should focusing.
  */
  void SetCenterScreen(float x, float y);

  /**
    Draws the scrollbar to the appropriate view.

    @param &window References the window the scrollbar will be drawn.
  */
  void Draw(sf::RenderWindow &window);

  /**
    Sets the view where the scrollbar will be used.

    @param &view References the proper view.
  */
  void SetView(sf::View &view);

  bool MouseOverSlider(sf::Vector2f mousePos);


private:
  bool m_isScrolling;  //Member variable identifying if the user is scrolling or not.
  bool m_firstClick;  //Member variable identifying if a user is clicking on the scrollbar from a non scrolling state.
  sf::View m_scrollBarView; //Object identifyinng the view the scrollbar should be associated with.
  float m_mouseYNew; //Most current postion of the mouse's y coordinate position.
  float m_offset; //Offset between where the user clicked the scrollbar and the position of the scrollbar.
  sf::RectangleShape m_scrollElement; //Object for the scrollbar slider.
  sf::RectangleShape m_scrollContainer;  //Container holding the scrollbar slider.
  sf::RectangleShape m_centerScreen;//Object that determines where the view camera is positioned over the content display.
  sf::Vector2f m_scrollMaximum; //Object with x & y coordinates for maximum scrollbar position.
  sf::Vector2f m_scrollMinimum; //Object with x & coordinates for minimum scollbar position.
  int m_scrollIndex;
};
