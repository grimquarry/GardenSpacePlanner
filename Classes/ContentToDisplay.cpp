/**
  Garden Space Planner
  ContentToDisplay.cpp
  Purpose: Source code file for the ContentToDisplay class.  This class
    manages and handles what content should actually be drawn to
    the window.  Version 2.0.0 removes Content object parameters and
    replaces them with SelectMap, CreateMap, AddPlant, and EditPlant
    object parameters.

  @author Jeremiah Kellogg
  @version 2.0.0 12/26/19
*/

#include "ContentToDisplay.h"

//Default Constructor.
ContentToDisplay::ContentToDisplay() { }

//Default Destructor.
ContentToDisplay::~ContentToDisplay() { }

//Displays the most current Content object the user has selected.
void ContentToDisplay::DisplayContent(sf::RenderWindow &window, Content &welcome,
  SelectMap &selectmap,
  CreateMap &createmap,
  AddPlant &addplant,
  EditPlant &editplant,
  sf::Event &event,
  MapDisplay &mapDisplay,
  sf::View &view)
{
  if(welcome.GetActiveStatus())
  {
    welcome.DrawText(window);
  }
  else if(selectmap.GetActiveStatus())
  {
    if(selectmap.GetScrollBar()->GetScrolling())
		{
			selectmap.GetScrollBar()->Scroll(window);
		}

    selectmap.DrawMapMenu(window, event, mapDisplay, view);
  }
  else if(createmap.GetActiveStatus())
  {
    createmap.DrawText(window);
    createmap.DrawInputField(window);
  }
  else if(addplant.GetActiveStatus())
  {
    addplant.DrawText(window);
    addplant.DrawInputField(window);
  }
  else if (editplant.GetActiveStatus())
  {
    editplant.GetSelectedPlant();
    editplant.DrawText(window);
    editplant.DrawInputField(window);
  }
}
