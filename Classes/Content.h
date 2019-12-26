/**
    Garden Space Planner
    Content.h
    Purpose: Header file for the Content base class.  This class provides
      basic functionality for creating varioius types of content that can
      be selected and viewed by the user.  It's focus is more on the main content
      display of the Garden Space Planner program.  This code was re-factcored for
      version 2.0.0 to make it a base class, which allowed for more granular
      functionality for the varying types of content and their unique needs.

    @author Jeremiah Kellogg
    @version 2.0.0 12/26/19
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>

#include "MessageWindow.h"
#include "Plant.h"
#include "Map.h"
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
    Draw all Content text to the window.

    @param &window Reference to the RenderWindow object to draw Content text to.
  */
  void DrawText(sf::RenderWindow &window);

  /**
    Dismiss pop-ups called by the Content object to convey important messages to the user.

    @param &window The RenderWindow object the Content object message is displayed in.
  */
  /******THIS SHOULD BE MOVED TO MessageWindow CLASS********/
  void MessageDismissed(sf::RenderWindow &window);

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

protected:
  sf::Text m_contentText; //Object for storing text relating to content selected.
  std::string m_contentString; //Variable for storing strings in text files to be set in the m_contentText object.
  std::ifstream m_inputFile; //Variable for grabbing contents of a text file for displaying in a Content object.
  std::string m_stringSection; //Variable for storing individual lines in a text file (used for concantnating to m_contentString for full block of text).
  sf::Font m_ubuntu; //Font to be used for text in Content objects.
  bool m_isActive;  //Variable for determining what Content object a user has selected to view.
  MessageWindow m_messageDisplay;  //Object for displaying messages to the user.
  Plant m_plant; //Object for storing plant data.
  int m_currentPlantID; //Variable for storing the currently selected m_plant object MySQL ID.
  int m_previousPlantID; //Variable for storing the m_plant ID selected previous to the current selection.
  Map m_map; //Object for storing Map object data.

  //Pointers to MySQL Connector/C++ objects (needed for communicating with MySQL database)
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;
};
