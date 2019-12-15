/**
    SDEV435-81 Capstone Project
    Content.cpp
    Purpose: Header file for the Content class.  This class provides
      functionality for creating varioius types of content that can
      be selected and viewed by the user.  It's focus is more on the
      main content display of the Garden Space Planner program.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <exception>
#include "InputBox.h"
#include "Button.h"
#include "MessageWindow.h"
#include "Plant.h"
#include "Map.h"
#include "LeftColumnContent.h"
#include "ContentContainer.h"
#include "MapDisplay.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>


class Content
{
public:
  //Default Constructor.
  Content();

  //Default Destructor.
  ~Content();

  /**
    Add text from a file to display in the Content window.

    @param fileName A path to the file with the text for the selected content to display.
  */
  void AddText(std::string fileName);

  /**
    Add a section of the Content display for user input boxes.

    @param width The size of the input area on the x axis.
    @param height The size of the input area on the y axis.
	  @param posX The x axis position of the user input area.
	  @param posY The y axis position of the user input area.
  */
  void AddInputArea(float width, float height, float posX, float posY);

  /**
    Draw all Content text to the window.

    @param &window Reference to the RenderWindow object to draw Content text to.
  */
  void DrawText(sf::RenderWindow &window);

  /**
    Add InputBox objects to the Content object for user input.

    @param header1 The label/header for the 1st InputBox object.
  	@param pos1 sf::Vector2f object holding the x & y coordinates for 1st InputBox object.
  	@param header2 The label/header for the 2nd InputBox object.
  	@param pos2 sf::Vector2f object holding the x & y coordinates for 2nd InputBox object.
  	@param header3 The label/header for the 3rd InputBox object.
  	@param pos3 sf::Vector2f object holding the x & y coordinates for 3rd InputBox object.
  	@param header4 The label/header for the 4th InputBox object.
  	@param pos4 sf::Vector2f object holding the x & y coordinates for 4th InputBox object.
  */
  void AddInputBoxes(std::string header1, sf::Vector2f pos1,
    std::string header2, sf::Vector2f pos2,
    std::string header3, sf::Vector2f pos3,
    std::string header4, sf::Vector2f pos4);

  /**
    Focus on InputBox object the user has selected for inputing data.

    @param &window The RenderWindow object the InputBox object is displayed in.
  */
  void FocusOnBox(sf::RenderWindow &window);

  /**
    Dismiss pop-ups called by the Content object to convey important messages to the user.

    @param &window The RenderWindow object the Content object message is displayed in.
  */
  void MessageDismissed(sf::RenderWindow &window);

  /**
    Checks to see if user is typing, and if so displays text the user is typing into the InputBox object.

    @param input The sf::Event object that grabs what keyboard key is pressed.
  */
  void EnterText(sf::Event input);

  /**
    Returns whether or not a Content object is the most current content selected to view by the user.
  */
  bool GetActiveStatus();

  /**
    Makes a Content object the most current selected by the user to view and display in the main content area.
  */
  void MakeActive();

  /**
    Makes a Content objects not currently selected by the user inactive so they don't display to the main content view.
  */
  void MakeInactive();

  /**
    Adds a Button object to the Content display so users can submit data they've entered into InputBox objects.

  	@param name The string to display on the input button.
  	@param &window References the RenderWindow object the button is displayed on.
  	@param area The sf::Vector2f object holding the size of the ContentContainer object the Button object belongs to.
  	@param ratioX The ratio that sets the x axis position of the Button object in relation to the Content ContentContainer object.
  	@param ratioY The ratio that sets the y axis position of the Button object in relation to the Content ContentContainer object.
  */
  void AddInputButton(std::string name, sf::RenderWindow& window,
    sf::Vector2f area, float ratioX, float ratioY);

  /**
    Submits user input to the specified MySQL database.

  	@param &window References the RenderWindow user inputed data is being displayed.
  	@param databaseName The name of the database to submit data to.
  	@param &mapDisplay Reference to a MapDisplay object for submitting data to maps database (not used by Content objects).
  	@param &view Reference to an sf::View object to ensure mouse movement is picked up by a specific view and not just the main window.
  */
  void SubmitData(sf::RenderWindow &window, std::string databaseName, MapDisplay &mapDisplay, sf::View &view);

  /**
    Finds the currently selected Plant in the garden_space_planner.plants MySQL table;
  */
  void GetSelectedPlant();

  /**
    Populates the m_mapList vector with a list of maps from the MySQL database.
  */
  void SetMapList();

  /**
    Sets the size of m_mapSelectContainer data member and sets the size and position of the m_displayArea data member
	   based on the m_contentView data member sf::View object.
  */
  void AddScrollArea();

  /**
    Updates size and position of scroll area when a new Map object is added to or removed from the m_mapsList vector.
  */
  void UpdateScrollArea();

  /**
    Adds scrollbar functionality and objects to the screen users can select maps from.
  */
  void AddScrollBar();

  /**
    Add clickable containers that hold map data to the m_mapContainerList vector.
  */
  void SetMapContainerVector();

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
    Updates position of scroll bar and centered position of the view on each loop.

  	@param &window Reference to the sf::RenderWindow object the scroll bar appears in.
  */
  void Scroll(sf::RenderWindow &window);

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
    Returns a boolean value indicating whether or not the user's mouse is hovering over the scrollbar.

  	@param &window References what window the mouse and scrollbar live in.
  */
  bool MouseOverScroll(sf::RenderWindow &window);

  /**
    Returns a boolean value indicating whether or not the user's mouse is hovering over an sf::RectangleShape m_mapContainer object
	   that's used to contain map data for listing in the select map screen.

  	@param &window References what window the mouse and m_mapContainer object live in.
  */
  bool MouseOverMapContainer(sf::RenderWindow &window);

  /**
    Returns sf::Vector2f object containing x and y coordinate for the current scrollbar position.

  	@param &container References the ContentContainer object the scrollbar is located in for setting the scrollbar's location
		in relation to the ContentContainer object it lives in.
  */
  sf::Vector2f GetScrollPosition(ContentContainer &container);

  /**
    Sets the color of the scrollbar (used for changing color when the user clicks on the scrollbar).

  	@param color An sf::Color value for changing the color of the sf::RectangleShape m_scrollElement data member.
  */
  void ChangeColor(sf::Color color);

  /**
    Draws InputBox objects to the sf::Renderwindow object.

  	@param &window References an sf::RenderWindow object to draw to.
  */
  void DrawInputField(sf::RenderWindow &window);

private:
  sf::Text m_contentText; //Object for storing text relating to content selected.
  std::string m_contentString; //Variable for storing strings in text files to be set in the m_contentText object.
  std::ifstream m_inputFile; //Variable for grabbing contents of a text file for displaying in a Content object.
  std::string m_stringSection; //Variable for storing individual lines in a text file (used for concantnating to m_contentString for full block of text).
  sf::Font m_ubuntu; //Font to be used for text in Content objects.
  sf::RectangleShape m_input_container; //Object for containing InputBox objects for the Content object.
  InputBox m_inputBox1;  //Object for input box users can enter data in.
  InputBox m_inputBox2;  //Object for input box users can enter data in.
  InputBox m_inputBox3;  //Object for input box users can enter data in.
  InputBox m_inputBox4;  //Object for input box users can enter data in.
  bool m_isActive;  //Variable for determining what Content object a user has selected to view.
  Button m_inputButton; //Object for configuring buttons for submitting user input to MySQL database.
  MessageWindow m_messageDisplay;  //Object for displaying messages to the user.
  Plant m_plant; //Object for storing plant data.
  int m_currentPlantID; //Variable for storing the currently selected m_plant object MySQL ID.
  int m_previousPlantID; //Variable for storing the m_plant ID selected previous to the current selection.
  Map m_map; //Object for storing Map object data.
  sf::RectangleShape m_mapSelectContainer; //Object for area containing a list of maps the user can select.
  sf::View m_contentView;  //Object for storing what view the Content object should be contained in.
  sf::RectangleShape m_displayArea; //Object for storing the size of the area the content needs to be displayed in.
  std::vector<Map> m_mapList;  //A list of maps available in the MySQL database.
  std::vector<sf::Vector2f> m_mapContainerList;  //A list of container positions for displaying available maps in the MySQL database.
  sf::Vector2f m_mapContainerDisplayPos;  //A Variable for a map container position that's pushed to the m_mapContainerList vector.
  sf::RectangleShape m_scrollContainer;  //Object that holds the scrollbar element the user interacts with.
  sf::RectangleShape m_scrollElement;  //Object for the scrollbar the user can interact with.
  sf::Vector2f m_scrollMinimum;  //Object holding the x and y coordinates the scroll bar element can go below.
  sf::Vector2f m_scrollMaximum;  //Object holding the x and y coordinates the scrollbar can't go above.
  sf::RectangleShape m_centerScreen;  //Object that determines where the camera focuses in the view object.
  float m_screenToViewRatio;  //Variable determining the ratio between the view size and the content size.
  bool m_isScrolling;  //Variable indicating if the user is scrolling in the Content Object or not.
  bool m_firstClick;  //Variable determining if a user has clicked on the scrollbar to initiate scrolling functionality.
  float mouseYNew;  //Variable holding the most current mouse position.
  float m_offset;  //Variable holding the difference between where the user clicked on the scrollbar and the current position of the scrollbar.
  sf::Text m_mapTxtName;  //Object holding the name of an m_map object.
  sf::Text m_mapTxtYear;  //Object holding the year of an m_map object.
  sf::Text m_mapTxtLength;  //Object holding the length of an m_map object.
  sf::Text m_mapTxtWidth;  //Object holding the width of an m_map object.

  //Pointers to MySQL Connector/C++ objects (needed for communicating with MySQL database)
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;
};
