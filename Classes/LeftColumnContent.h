/**
    SDEV435-81 Capstone Project
    LeftColumnContent.h
    Purpose: Header file for the LeftColumnContent class.  This class
      creates a space for creating and displaying content in the
      left column of the Garden Space Planner program's GUI.  This
      area holds a list of plants user can select to edit or drop
      into a garden map.

    @author Jeremiah Kellogg
    @version 1.0.1 12/08/19
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "ContentContainer.h"
#include "Plant.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

class LeftColumnContent
{
public:

  //Default Constructor
  LeftColumnContent();

  /**
    Constructor

    @param &view Reference to the view object the left column belongs to.
  */
  LeftColumnContent(sf::View &view);

  //Default Destructor.
  ~LeftColumnContent();

  /**
    Add a Scrollbar in the left column.
  */
  void AddScrollBar();

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
    Returns true or false dependig on whether the mouse is positioned over a container listing plant info.

    @param &window References the sf::RenderWindow object the plant container is drawn to.
  */
  bool MouseOverPlantContainer(sf::RenderWindow &window);

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
  void ChangeColor(sf::Color color);

  /**
    Sets the size of the content area that the view can scroll over and sets the size of plant data containers.
  */
  void AddDisplayArea();

  /**
    Grabs all plants from the MySQL garden_space_planner database in the plants table and stores them in the m_plants vector.
  */
  void SetPlantVector();

  /**
    Builds and positions a container for each plant in the m_plants vector and stores position values in the m_plantDisplayPos vector.
  */
  void SetPlantContainerVector();

  /**
    Draws the m_displayArea, m_scrollElement, m_scrollContainer, m_plantContainer, m_plantTxtName, m_plantTxtVariety, and m_plantTxtSpacing object to the window.

    @param &window The sf::RenderWindow object the left column objects should be drawn to.
    @param event The event polled in main.cpp, used to determin mouse hovering to change colors of elements being hovered over.
  */
  void Draw(sf::RenderWindow &window, sf::Event event);

private:
  sf::RectangleShape m_scrollElement; //Object for the scrollbar slider.
  sf::Vector2f m_scrollMinimum; //Object with x & coordinates for minimum scollbar position.
  sf::Vector2f m_scrollMaximum; //Object with x & y coordinates for maximum scrollbar position.
  float mouseYNew; //Most current postion of the mouse's y coordinate position.
  float m_offset; //Offset between where the user clicked the scrollbar and the position of the scrollbar.
  sf::RectangleShape m_centerScreen;//Object that determines where the view camera is positioned over the content display.
  sf::RectangleShape m_scrollContainer;  //Container holding the scrollbar slider.
  sf::RectangleShape m_displayArea;  //X and y size of the content being displayed.
  sf::RectangleShape m_plantContainer;  //Object for a container storing plant data.
  bool m_isScrolling;  //Member variable identifying if the user is scrolling or not.
  bool m_firstClick;  //Member variable identifying if a user is clicking on the scrollbar from a non scrolling state.
  sf::View m_leftColumnView;  //Object identifyinng the view the left column should be associated with.
  float m_screenToViewRatio;  //Ratio between the content displayed (on the screen) to the smaller size of the view.
  Plant m_plant;  //Object storing data on a plant.
  std::vector<Plant> m_plants;  //List of all plants in the MySQL garden_space_planner database in the plants table.
  Plant m_currentPlant;  //Object storing data on the plant that's most recently selected by the user.
  std::vector<sf::Vector2f> m_plantDisplayList;  //The list of plants to be displayed to the window.
  sf::Vector2f m_plantDisplayPos;  //List of container positions for each plant in the m_plants vector.
  sf::Text m_plantTxtName;  //Object storing text and postion of a plant's name.
  sf::Text m_plantTxtVariety;  //Object storing text and position of a plant's variety.
  sf::Text m_plantTxtSpacing;  //Object storing text and postion of a plant's spacing.
  sf::Text m_plantTxtRow;  //Object storing text and position of a plant's row spacing
  sf::Font m_ubuntu;  //Object storing font info for the ubuntu font.

  //Pointers to MySQL Connector/C++ objects needed for communicating with the MySQL database.
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;

  //Finds the currently selected Plant in the garden_space_planner.plants MySQL table;
  void GetSelectedPlant();
};
