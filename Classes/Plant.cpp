/**
    SDEV435-81 Capstone Project
    Plant.cpp
    Purpose: Code file for the Plant class.  This class creates objects
      for plants in the plants table of the MySQL garden_space_planner
      database.

    @author Jeremiah Kellogg
    @version 1.0.1 12/08/19
*/

#include "Plant.h"

//Default Constructor.
Plant::Plant() { }

//Default Destructor.
Plant::~Plant() { }

//Set the name of the plant object.
void Plant::SetName(std::string name)
{
  m_name = name;
}

//Returns the m_name value of the plant.
std::string Plant::GetName()
{
  return m_name;
}

//Set the variety of the plant object.
void Plant::SetVariety(std::string variety)
{
  m_variety = variety;
}

//Returns the m_variety value of the plant.
std::string Plant::GetVariety()
{
  return m_variety;
}

//Set the value for spacing between each plant in the m_spacing variable.
void Plant::SetSpacing(int spacing)
{
  m_spacing = spacing;
}

//Returns the space between plants stored in the m_spacing value of the plant.
int Plant::GetSpacing()
{
  return m_spacing;
}

//Set the value for spacing between each row in the m_rowSpacing variable.
void Plant::SetRowSpacing(int rowSpacing)
{
  m_rowSpacing = rowSpacing;
}

//Returns the row space between plants stored in the m_rowSpacing value of the plant.
int Plant::GetRowSpacing()
{
  return m_rowSpacing;
}

//Set the value for the m_plantID member variable.
void Plant::SetID(int id)
{
  m_plantID = id;
}

//Returns the plant's ID stored in the m_plantID member variable.
int Plant::GetID()
{
  return m_plantID;
}

//Assign the RGB color value to the plant that will be used to set the fill color of the plant's tile.
void Plant::SetRGBColors(int red, int green, int blue)
{
  m_red = red;
  m_green = green;
  m_blue = blue;
}

//Returns the plant's red color value stored in m_red member variable.
int Plant::GetRed()
{
  return m_red;
}

//Returns the plant's green color value stored in m_green member variable.
int Plant::GetGreen()
{
  return m_green;
}

//Returns the plant's blue color value stored in m_blue member variable.
int Plant::GetBlue()
{
  return m_blue;
}

//Updates whether or not the plant is currently selected by the user and stores that value in the database.
void Plant::SetSelectedDatabase(bool selected, int plantID)
{
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  prep_stmt = con->prepareStatement("UPDATE plants SET is_selected=? WHERE plant_id=?");
  prep_stmt->setBoolean(1, selected);
  prep_stmt->setInt(2, plantID);
  prep_stmt->execute();
  delete con;
  delete prep_stmt;
  m_isSelected = selected;
}

//Returns the m_isSelected variable to indicate whether or not the plant is currently selected by the user.
bool Plant::IsSelected()
{
  return m_isSelected;
}

void Plant::SetSelected(bool selected)
{
  m_isSelected = selected;
}

//Sets all user inputed data to required member variables and then pushes them to the proper database table columns.
void Plant::AddToDatabase()
{
  std::srand(time(NULL));
  m_red = rand() % 255;
  m_green = rand() % 255;
  m_blue = rand() % 255;

  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  prep_stmt = con->prepareStatement("INSERT INTO plants(plant_name, plant_variety, plant_spacing_width, plant_spacing_length, red_color_value, green_color_value, blue_color_value) VALUES (?, ?, ?, ?, ?, ?, ?)");
  prep_stmt->setString(1, m_name);
  prep_stmt->setString(2, m_variety);
  prep_stmt->setInt(3, m_spacing);
  prep_stmt->setInt(4, m_rowSpacing);
  prep_stmt->setInt(5, m_red);
  prep_stmt->setInt(6, m_green);
  prep_stmt->setInt(7, m_blue);
  prep_stmt->execute();
  delete con;
  delete prep_stmt;
}

//Updates a plant's info in the plants table of the MySQL garden_space_planner database.
void Plant::UpdateDatabase()
{
  try
  {
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
    con->setSchema("garden_space_planner");
    prep_stmt = con->prepareStatement("UPDATE plants SET plant_name=?, plant_variety=?, plant_spacing_width=?, plant_spacing_length=? WHERE is_selected=true");
    prep_stmt->setString(1, m_name);
    prep_stmt->setString(2, m_variety);
    prep_stmt->setInt(3, m_spacing);
    prep_stmt->setInt(4, m_rowSpacing);
    prep_stmt->execute();
    delete con;
    delete prep_stmt;
  }
  catch (sql::SQLException &e)
  {
    std::cout << "# ERR: SQLException in " << __FILE__;
    std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
    std::cout << "# ERR: " << e.what();
    std::cout << " (MySQL error code: " << e.getErrorCode();
    std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
  }
}
