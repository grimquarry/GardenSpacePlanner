/**
    Garden Space Planner
    LeftColumnContent.h
    Purpose: Header file for the LeftColumnContent class.  This class
      creates a space for displaying content in the left column of the
      Garden Space Planner program's GUI.  This area holds a list of
      plants user can select to edit or drop into a garden map.

    @author Jeremiah Kellogg
    @version 2.0.0 01/02/20
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "ContentContainer.h"
#include "Plant.h"
#include "ScrollBar.h"

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
    Returns true or false dependig on whether the mouse is positioned over a container listing plant info.

    @param &window References the sf::RenderWindow object the plant container is drawn to.
  */
  bool MouseOverPlantContainer(sf::RenderWindow &window);

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
    Draws the m_displayArea, m_scrollBar pointer, m_plantContainer, m_plantTxtName, m_plantTxtVariety, and m_plantTxtSpacing object to the window.

    @param &window The sf::RenderWindow object the left column objects should be drawn to.
    @param event The event polled in main.cpp, used to determin mouse hovering to change colors of elements being hovered over.
  */
  void Draw(sf::RenderWindow &window, sf::Event event);

  /**
    Returns a pointer to a ScrollBar object that's used for calling ScrollBar class functions.
  */
  ScrollBar* GetScrollBar();

private:
  sf::RectangleShape m_displayArea;  //Stores x and y size of the content being displayed.
  sf::RectangleShape m_plantContainer;  //Object for a container storing plant data.
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
  ScrollBar *m_scrollBar; //Object for scrollbar functionality.
  ScrollBar ptrAddress; //Object used for giving an address to the m_scrollBar pointer.

  //Pointers to MySQL Connector/C++ objects needed for communicating with the MySQL database.
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;

  /**
    Finds the currently selected Plant in the garden_space_planner.plants MySQL table;
  */
  void GetSelectedPlant();
};
