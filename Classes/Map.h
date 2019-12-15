/**
    SDEV435-81 Capstone Project
    Map.cpp
    Purpose: Header file for the Map class.  This class
      creates objects for user defined maps.  The data
      held by these map objects is stored in the maps
      table of the MySQL garden_space_planner database.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#pragma once
#include <SFML/Graphics.hpp>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

class Map
{
public:

  //Default Constructor.
  Map();

  //Default Destructor.
  ~Map();

  /**
    Assigns a value to the m_mapID member variable.

    @param id Sets the map ID for the Map object.
  */
  void SetMapID(int id);

  /**
    Returns the value assigned to the m_mapID member variable.
  */
  int GetMapID();

  /**
    Assigns a value to the m_name member variable.

    @param name Sets the map Name for the Map object.
  */
  void SetName(std::string name);

  /**
    Returns the value assigned to the m_name member variable.
  */
  std::string GetName();

  /**
    Assigns a value to the m_year member variable.

    @param year Sets the map year for the Map object.
  */
  void SetYear(std::string year);

  /**
    Returns the value assigned to the m_year member variable.
  */
  std::string GetYear();

  /**
    Assigns a value to the m_length member variable (for x axis).

    @param length Sets the map length (x axis) for the Map object.
  */
  void SetLength(int length);

  /**
    Returns the value assigned to the m_length (x axis) member variable.
  */
  int GetLength();

  /**
    Assigns a value to the m_width (y axis) member variable.

    @param width Sets the map width (y axis) for the Map object.
  */
  void SetWidth(int width);

  /**
    Returns the value assigned to the m_width (y axis) member variable.
  */
  int GetWidth();

  /**
    Assigns a value to the m_isSelected variable for determining if the map is most currently selected by user.

    @param selected The true or false value determining if the map is most currently selected by the user.
  */
  void SetIsSelected(bool selected);

  /**
    Returns the value assigned to the m_isSelected variable for determining if the most currently selected map should be displayed.
  */
  bool GetIsSelected();

  /**
    Adds all relevant member variable data to MySQL garden_space_planner database in the maps table.
  */
  void AddToDatabase();

private:
  int m_mapID;  //Variable for holding the map's database ID.
  std::string m_name;  //Variable for holding the map's user given name.
  std::string m_year;  //Variable for holding the map's user given year.
  int m_length;  //Variable for holding the map's user given length (on x axis).
  int m_width;  //Variable for holding the map's user given width (on y axis).
  bool m_isSelected;  //Variable holding true or false value for determining if a map has been selected by the user.

  //Pointers to MySQL Connector/C++ objects needed for adding map data to the MySQL garden_space_planner database in the maps table.
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;
};
