/**
  Garden Space Planner
  SelectMap.h
  Purpose: Header file for the SelectMap class.  This class inherits from the Content
  Class.  The SelectMap class is used to build an object that displays a screen where
  users can select maps they've already created to edit.

  @author Jeremiah Kellogg
  @version 2.1.0 01/19/2020
*/

#pragma once
#include "Content.h"
#include "ContentContainer.h"
#include "ScrollBar.h"

class SelectMap : public Content
{
public:
  //Default Contstructor
  SelectMap();

  //Constructor
  SelectMap(sf::View &view);

  //Destructor
  ~SelectMap();

  /**
    Populates the m_mapList vector with a list of maps from the MySQL database.
  */
  void SetMapList();

  /**
    Add clickable containers that hold map data to the m_mapContainerList vector.
  */
  void SetMapContainerVector();

  /**
    Returns a boolean value indicating whether or not the user's mouse is hovering over an sf::RectangleShape m_mapContainer object
	   that's used to contain map data for listing in the select map screen.

  	@param &window References what window the mouse and m_mapContainer object live in.
  */
  bool MouseOverMapContainer(sf::RenderWindow &window);

  /**
    Draws the list of user created maps the user can choose from to the sf::View contentView object in the sf::RenderWindow mainWindow object.

  	@param &window References the RenderWindow mainWindow object.
  	@param &event References user input events to track mouse movement and clicks.
  	@param &display Reference to a MapDisplay object for importing map data based on user selection.
  	@param &view Reference to an sf::View object to ensure mouse movement is picked up by a specific view and not just the main window.
  */
  void DrawMapMenu(sf::RenderWindow &window, sf::Event &event, MapDisplay &display, sf::View &view);

  /**
    Set the view the Content object is associated with.

  	@param &view Reference to an sf::View object the Content object should be drawn to in the mainWindow object.
  */
  void SetView(sf::View &view);

  /**
    Sets the size of m_mapSelectContainer data member and sets the size and position of the m_displayArea data member
	   based on the m_contentView data member sf::View object.
  */
  void AddDisplayArea();

  /**
    Adds scrollbar functionality and objects to the screen users can select maps from.
  */
  void AddScrollBar();

  /**
    Returns a pointer to a ScrollBar object used for calling ScrollBar class functions.
  */
  ScrollBar* GetScrollBar();

  /**
    Set the value for stopping a map view from displaying.  Used to keep a map view from accidentally
      opened when the cursor is over a m_mapSelectContainer and the user stops scrolling.

  	@param stop Boolean value to stop a map view from accidentally being displayed.
  */
  void SetStopMapView(bool stop);

  /**
    Returns true or false to determine if a MapView should be stopped from opening.
      Used to stop a mapview from displaying when a user is hovering over a m_mapSelectContainer
      while scrolling and released the mouse button.
  */
  bool StopMapView();

private:
  std::vector<Map> m_mapList;  //A list of maps available in the MySQL database.
  std::vector<sf::Vector2f> m_mapContainerList;  //A list of container positions for displaying available maps in the MySQL database.
  sf::Vector2f m_mapContainerDisplayPos;  //A Variable for a map container position that's pushed to the m_mapContainerList vector.
  sf::Text m_mapTxtName;  //Object holding the name of an m_map object.
  sf::Text m_mapTxtYear;  //Object holding the year of an m_map object.
  sf::Text m_mapTxtLength;  //Object holding the length of an m_map object.
  sf::Text m_mapTxtWidth;  //Object holding the width of an m_map object.
  ScrollBar *m_scrollBar; //Object for scrollbar functionality.
  ScrollBar ptrAddress; //Object used for giving an address to the m_scrollBar pointer.
  sf::RectangleShape m_displayArea; //X and y size of the content being displayed.
  sf::View m_contentView; //Object for storing what view SelectMap objects should appear in.  Used for scrolling functionality.
  sf::RectangleShape m_mapSelectContainer;//Object for map list display container.
  bool m_stopMapView;
/**********Should the Screen to view ratio go into ScrollBar class?????**************/
  float m_screenToViewRatio;  //Variable determining the ratio between the view size and the content size.
};
