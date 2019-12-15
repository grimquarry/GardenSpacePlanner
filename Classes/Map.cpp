/**
    SDEV435-81 Capstone Project
    Map.cpp
    Purpose: Code file for the Map class.  This class
      creates objects for user defined maps.  The data
      held by these map objects is stored in the maps
      table of the MySQL garden_space_planner database.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#include "Map.h"

//Default Constructor.
Map::Map() { }

//Default Destructor.
Map::~Map() { }

//Assigns a value to the m_mapID member variable.
void Map::SetMapID(int id)
{
  m_mapID = id;
}

//Returns the value assigned to the m_mapID member variable.
int Map::GetMapID()
{
  return m_mapID;
}

//Assigns a value to the m_name member variable.
void Map::SetName(std::string name)
{
  m_name = name;
}

//Returns the value assigned to the m_name member variable.
std::string Map::GetName()
{
  return m_name;
}

//Assigns a value to the m_year member variable.
void Map::SetYear(std::string year)
{
  m_year = year;
}

//Returns the value assigned to the m_year member variable.
std::string Map::GetYear()
{
  return m_year;
}

//Assigns a value to the m_length member variable (for x axis).
void Map::SetLength(int length)
{
  m_length = length;
}

//Returns the value assigned to the m_length (x axis) member variable.
int Map::GetLength()
{
  return m_length;
}

//Assigns a value to the m_width (y axis) member variable.
void Map::SetWidth(int width)
{
  m_width = width;
}

//Returns the value assigned to the m_width (y axis) member variable.
int Map::GetWidth()
{
  return m_width;
}

//Assigns a value to the m_isSelected variable for determining if the map is most currently selected by user.
void Map::SetIsSelected(bool selected)
{
  m_isSelected = selected;
}

//Returns the value assigned to the m_isSelected variable for determining if the most currently selected map should be displayed.
bool Map::GetIsSelected()
{
  return m_isSelected;
}

//Adds all relevant member variable data to MySQL garden_space_planner database in the maps table.
void Map::AddToDatabase()
{
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  prep_stmt = con->prepareStatement("INSERT INTO maps (map_name, map_year, map_length, map_width) VALUES (?, ?, ?, ?)");
  prep_stmt->setString(1, m_name);
  prep_stmt->setString(2, m_year);
  prep_stmt->setInt(3, m_length);
  prep_stmt->setInt(4, m_width);
  prep_stmt->execute();
  delete con;
  delete prep_stmt;
}
