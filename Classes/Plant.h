/**
    SDEV435-81 Capstone Project
    Plant.h
    Purpose: Header file for the Plant class.  This class creates objects
      for plants in the plants table of the MySQL garden_space_planner
      database.

    @author Jeremiah Kellogg
    @version 1.0.1 12/08/19
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

class Plant
{
public:
  //Default Constructor.
  Plant();

  //Default Destructor.
  ~Plant();

  /**
    Set the name of the plant object.

    @param name The name of the plant, assigned to m_name member variable.
  */
  void SetName(std::string name);

  /**
    Returns the m_name value of the plant.
  */
  std::string GetName();

  /**
    Set the variety of the plant object.

    @param variety The plant variety, assigned to the m_variety member variable.
  */
  void SetVariety(std::string variety);

  /**
    Returns the m_variety value of the plant.
  */
  std::string GetVariety();

  /**
    Set the value for spacing between each plant in the m_spacing variable.

    @param spacing The spaced between plants, assigned to the m_space member variable.
  */
  void SetSpacing(int spacing);

  /**
    Returns the space between plants stored in the m_spacing value of the plant.
  */
  int GetSpacing();

  /**
    Set the value for spacing between each row in the m_rowSpacing variable.

    @param rowSpacing The required row space between plants, assigned to the m_rowSpacing member variable.
  */
  void SetRowSpacing(int rowSpacing);

  /**
    Returns the row space between plants stored in the m_rowSpacing value of the plant.
  */
  int GetRowSpacing();

  /**
    Set the value for the m_plantID member variable.

    @param id The plant's MySQL garden_space_planner database ID in the plants table.
  */
  void SetID(int id);

  /**
    Returns the plant's ID stored in the m_plantID member variable.
  */
  int GetID();

  /**
    Assign the RGB color value to the plant that will be used to set the fill color of the plant's tile.

    @param red The 0 - 255 value for the red color that will be assigned to the m_red member variable.
    @param green The 0 - 255 value for the green color that will be assigned to the m_green member variable.
    @param blue The 0 - 255 value for the blue color that will be assigned to the m_blue member variable.
  */
  void SetRGBColors(int red, int green, int blue);

  /**
    Returns the plant's red color value stored in m_red member variable.
  */
  int GetRed();

  /**
    Returns the plant's green color value stored in m_green member variable.
  */
  int GetGreen();

  /**
    Returns the plant's blue color value stored in m_blue member variable.
  */
  int GetBlue();

  /**
    Updates whether or not the plant is currently selected by the user and stores that value in the database.

    @param selected The value for indicating whether or not the plant is currently selected in the database.
    @param plantID The plant's database ID used for selecting the right plant to update in the database.
  */
  void SetSelectedDatabase(bool selected, int plantID);

  /**
    Returns the m_isSelected variable to indicate whether or not the plant is currently selected by the user.
  */
  bool IsSelected();

  void SetSelected(bool selected);

  /**
    Sets all user inputed data to required member variables and then pushes them to the proper database table columns.
  */
  void AddToDatabase();

  /**
    Updates a plant's info in the plants table of the MySQL garden_space_planner database.
  */
  void UpdateDatabase();

private:
  std::string m_name;  //Plant's name.
  std::string m_variety;  //Plant's variety.
  int m_spacing;  //Required space between plants.
  int m_rowSpacing;  //Required space between rows.
  int m_plantID;  //The plant's database ID.
  int m_red;  //A red RGB color value to be used for filling the plant's tile with color.
  int m_green;  //A green RGB color value to be used for filling the plant's tile with color.
  int m_blue;  //A blue RGB color value to be used for filling the plant's tile with color.
  bool m_isSelected;  //Indicates whether the plant has been selected by the user or not.

  //Pointers to MySQL Connector/C++ objects, necessary for communicating with the database.
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::Statement *stmt;
  sql::ResultSet *res;
};
