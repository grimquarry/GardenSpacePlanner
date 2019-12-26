/**
    Garden Space Planner
    AddPlant.cpp
    Purpose: Source code for the AddPlant class.  This class inherits from the
    ContentInput class, which in turn inherits from the Content Class.  The
    AddPlant Class is specific to the module where users can add new plants to
    the database.  It was re-factored from the Content class because it allows
    for more unique functionality than the more general Content class was capable of.

    @author Jeremiah Kellogg
    @version 1.0.0 12/26/19
*/

#include "AddPlant.h"

//Default Constructor
AddPlant::AddPlant() { }

//Default Destructor
AddPlant::~AddPlant(){ }

//Submit user inputed data to the plants table in the garden_space_planner MySQL database.
void AddPlant::SubmitData(sf::RenderWindow &window)
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
        m_plant.SetName(box1);
        m_plant.SetVariety(box2);
        m_plant.SetSpacing(std::stoi(box3));
        m_plant.SetRowSpacing(std::stoi(box4));
        m_plant.AddToDatabase();
        m_messageDisplay.SetDisplay(true);
        m_messageDisplay.AddMessage("The Database has been successfully updated\nwith the following info\nPlant Name: " + box1 +"\nPlant Variety: " + box2 + "\nPlant Spacing: " + box3 + "\nRow Spacing: " + box4);
      }
      m_inputBox1.ClearContent();
      m_inputBox2.ClearContent();
      m_inputBox3.ClearContent();
      m_inputBox4.ClearContent();
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
