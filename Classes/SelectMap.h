/**
  Garden Space Planner
  SelectMap.h
  Purpose: Header file for the SelectMap class.  This class inherits from the Content
  Class.  The SelectMap class is used to build an object that displays a screen where
  users can select maps they've already created to edit.

  @author Jeremiah Kellogg
  @version 1.0.0 12/26/19
*/

#pragma once
#include "Content.h"
#include "ContentContainer.h"

class SelectMap : public Content
{
public:
  SelectMap();
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

/*************PUBLIC FUNCTIONS THAT SHOULD BE REFACTORED INTO A NEW SCROLLBAR CLASS****************/
  /**
    Sets the size of m_mapSelectContainer data member and sets the size and position of the m_displayArea data member
	   based on the m_contentView data member sf::View object.
  */
  void AddScrollArea();

  /**
    Adds scrollbar functionality and objects to the screen users can select maps from.
  */
  void AddScrollBar();

  /**
    Returns a boolean value indicating whether or not the user's mouse is hovering over the scrollbar.

  	@param &window References what window the mouse and scrollbar live in.
  */
  bool MouseOverScroll(sf::RenderWindow &window);

  /**
    Sets the color of the scrollbar (used for changing color when the user clicks on the scrollbar).

  	@param color An sf::Color value for changing the color of the sf::RectangleShape m_scrollElement data member.
  */
  void ChangeColor(sf::Color color);

  /**
    Sets whether or not the user is currently using the scroll bar.

  	@param toScroll A boolean that indicates whether the user is using scroll functionality or not.
  */
  void SetScrolling(bool toScroll);

  /**
    Returns the value for the boolean data member m_isScrolling to indicate whether a user is trying to scroll or not.
  */
  bool GetScrolling();

  /**
    Sets whether or not the user is initializing scroll functionality from a state where they were not using the scrollbar.
	   This value is saved to the boolean data member m_firstClick.

  	@param click A boolean that indicates whether the user has clicked on the scrollbar to initializeze scrolling.
  */
  void SetFirstClick(bool click);

  /**
    Returns the value for the boolean data member m_firstClick to indicate whether a user has clicked on the scrollbar or not.
  */
  bool GetFirstClick();

  /**
    Returns sf::Vector2f object containing x and y coordinate for the current scrollbar position.

  	@param &container References the ContentContainer object the scrollbar is located in for setting the scrollbar's location
		in relation to the ContentContainer object it lives in.
  */
  sf::Vector2f GetScrollPosition(ContentContainer &container);

  /**
    Updates size and position of scroll area when a new Map object is added to or removed from the m_mapsList vector.
  */
  void UpdateScrollArea();

  /**
    Updates position of scroll bar and centered position of the view on each loop.

  	@param &window Reference to the sf::RenderWindow object the scroll bar appears in.
  */
  void Scroll(sf::RenderWindow &window);


private:
  std::vector<Map> m_mapList;  //A list of maps available in the MySQL database.
  std::vector<sf::Vector2f> m_mapContainerList;  //A list of container positions for displaying available maps in the MySQL database.
  sf::Vector2f m_mapContainerDisplayPos;  //A Variable for a map container position that's pushed to the m_mapContainerList vector.
  sf::Text m_mapTxtName;  //Object holding the name of an m_map object.
  sf::Text m_mapTxtYear;  //Object holding the year of an m_map object.
  sf::Text m_mapTxtLength;  //Object holding the length of an m_map object.
  sf::Text m_mapTxtWidth;  //Object holding the width of an m_map object.

  sf::RectangleShape m_mapSelectContainer;//Object for area containing a list of maps the user can select.
                                          //This is used by the SelectMap class as well as for scroll functionality.
                                          //I believe it should stay in SelectMap and I should create functions that
                                          //return any data the scrollbar class might need.
  sf::RectangleShape m_displayArea; //This is mostly used for scroll functionality but also appears in
                                    //in the SetMapConainerVector function.  Should probably go in scroll class?
                                    //Putting here for now. It may make sense to create a function in the Scrollbar
                                    //class that the SelectClass might need passed to it.

  //Scrollbar Members that can go to a new scrollbar class at some point
  bool m_isScrolling;  //Variable indicating if the user is scrolling in the Content Object or not.
  bool m_firstClick;  //Variable determining if a user has clicked on the scrollbar to initiate scrolling functionality.
  float mouseYNew;  //Variable holding the most current mouse position.
  float m_offset;  //Variable holding the difference between where the user clicked on the scrollbar and the current position of the scrollbar.
  sf::RectangleShape m_scrollContainer; //Object that holds the scrollbar element the user interacts with.  Used in DrawMapMenu
                                        //function, so will likely need a getter function when moved to Scrollbar class.
  sf::RectangleShape m_scrollElement;  //Object for the scrollbar the user can interact with.
                                       //This is also used for the DrawMapMenu function, so a getter function might be
                                       //appropriate when this is moved to a scrollbar class.
  sf::View m_contentView;  //Object for storing what view the Content object should be contained in, used for scroll functionality.
  float m_screenToViewRatio;  //Variable determining the ratio between the view size and the content size.
  sf::Vector2f m_scrollMinimum;  //Object holding the x and y coordinates the scroll bar element can go below.
  sf::Vector2f m_scrollMaximum;  //Object holding the x and y coordinates the scrollbar can't go above.
  sf::RectangleShape m_centerScreen;  //Object that determines where the camera focuses in the view object.
};
