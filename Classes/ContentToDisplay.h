/**
    Garden Space Planner
    ContentToDisplay.h
    Purpose: Header file for the ContentToDisplay class.  This class
      manages and handles what content should actually be drawn to
      the window.  Version 2.0.0 removes Content object parameters and
      replaces them with SelectMap, CreateMap, AddPlant, and EditPlant
      object parameters.

    @author Jeremiah Kellogg
    @version 2.0.0 12/26/19
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Content.h"
#include "SelectMap.h"
#include "ContentInput.h"
#include "EditPlant.h"
#include "CreateMap.h"
#include "AddPlant.h"
#include "MapDisplay.h"

class ContentToDisplay
{
public:

  //Default Constructor.
  ContentToDisplay();

  //Default Destructor.
  ~ContentToDisplay();


  /**
    Displays the most current Content object the user has selected.

  	@param &window References an sf::RenderWindow object to draw the Content object to.
    @param &welcome References the Content object for the Welcome Screen.
    @param &selectmap References the SelectMap object for the Select Map Screen.
    @param &createmap References the CreateMap object for the Create Map Screen.
    @param &addplant References the AddPlant object for the Add Plant Screen.
    @param &editplant References the EditPlant object for the Edit Plant Screen.
    @param &event References an sf::Event object for grabbing user mouse movement and input.
    @param &mapDisplay References a MapDisplay object for viewing the map the user has selected.
    @param &view References an sf::View object for the view content should be displayed in.
  */
  void DisplayContent(sf::RenderWindow &window, Content &welcome,
    SelectMap &selectmap,
    CreateMap &createmap,
    AddPlant &addplant,
    EditPlant &editplant,
    sf::Event &event,
    MapDisplay &mapDisplay,
    sf::View &view);

private:

};
