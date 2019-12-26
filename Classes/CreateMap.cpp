/**
    Garden Space Planner
    CreateMap.cpp
    Purpose: Source code for the CreateMap class.  This class inherits from the
    ContentInput class, which in turn inherits from the Content Class.  The
    CreateMap Class is specific to the module where users can add new maps to
    the database.  It was re-factored from the Content class because it allows
    for more unique functionality than the more general Content class was capable of.

    @author Jeremiah Kellogg
    @version 1.0.0 12/26/19
*/

#include "CreateMap.h"

//Default Constructor
CreateMap::CreateMap()
{
  m_dataSubmitted = false;
}

//Default Destructor
CreateMap::~CreateMap() { }

//Submit user inputed data to the maps table in the garden_space_planner MySQL database.
void CreateMap::SubmitData(sf::RenderWindow &window)
{
  try
  {
    if(m_inputButton.ContentBtnMouseOver(window))
    {
      std::string box1 = m_inputBox1.GetText();
      std::string box2 = m_inputBox2.GetText();
      std::string box3 = m_inputBox3.GetText();
      std::string box4 = m_inputBox4.GetText();

      if(box1.length() < 1 || box2.length() < 1 || box3.length() < 1 || box4.length() < 1)
      {
        m_messageDisplay.SetDisplay(true);
        m_messageDisplay.AddMessage("One or more fields haven't been filled in. \n All fields are required.");
      }
      else if (std::stoi(box3) < 1 || std::stoi(box4) < 1)
      {
        m_messageDisplay.SetDisplay(true);
        m_messageDisplay.AddMessage("Number fields can't be less than 1.  Check to make \n sure no fields are less than 1.");
      }
      else if (std::stoi(box3) > 120 || std::stoi(box4) > 120)
      {
        m_messageDisplay.SetDisplay(true);
        m_messageDisplay.AddMessage("This program can't process gardens larger\nthan 120 square feet.  Therefore all numerical\nvalues must be less than 120");
      }
      else
      {
        m_map.SetName(box1);
        m_map.SetYear(box2);
        m_map.SetLength(std::stoi(box3));
        m_map.SetWidth(std::stoi(box4));
        m_map.AddToDatabase();
      }
      m_inputBox1.ClearContent();
      m_inputBox2.ClearContent();
      m_inputBox3.ClearContent();
      m_inputBox4.ClearContent();
      SetDataSubmitted(true);
    }
  }
  catch(std::invalid_argument)
  {
    m_messageDisplay.SetDisplay(true);
    m_messageDisplay.AddMessage("You entered text into a field that requires a number!");
  }
  catch(...)
  {
    m_messageDisplay.SetDisplay(true);
    m_messageDisplay.AddMessage("An Unexpected Error Occured!");
  }
}

//Sets the map display to the map that was most recently created.  Used for immediatly displaying
  //a newly created map.
void CreateMap::DisplayNewestMap(MapDisplay &mapDisplay, sf::View &view)
{
  m_newMap = mapDisplay.GetNewMap();
  mapDisplay.SetMap(m_newMap, view);
  mapDisplay.SetDisplay(true);
}

//Sets whether or not the user has clicked the submit data button.
/***********SHOULD THIS BE REFACTORED AS A setButtonClicked FUNCTION IN THE BUTTON CLASS?**************/
void CreateMap::SetDataSubmitted(bool submitted)
{
  m_dataSubmitted = submitted;
}

//Gets whether or not the user has clicked the submit data button.
/***********SHOULD THIS BE REFACTORED AS A setButtonClicked FUNCTION IN THE BUTTON CLASS?**************/
bool CreateMap::GetDataSubmitted()
{
  return m_dataSubmitted;
}
