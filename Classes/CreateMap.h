/**
  Garden Space Planner
  CreateMap.h
  Purpose: Header file for the CreateMap class.  This class inherits from the
  ContentInput class, which in turn inherits from the Content Class.  The
  CreateMap Class is specific to the module where users can add new maps to
  the database.  It was re-factored from the Content class because it allows
  for more unique functionality than the more general Content class was capable of.

  @author Jeremiah Kellogg
  @version 1.0.0 12/26/19
*/
#pragma once
#include "ContentInput.h"

class CreateMap : public ContentInput
{
public:
  //Default Constructor
  CreateMap();

  //Default Destructor
  ~CreateMap();

  /**
    Submit user inputed data to the maps table in the garden_space_planner MySQL database.

    @param &window The RenderWindow object needed to pass to a button object to determine
      when a user has clicked the submit button.
  */
  virtual void SubmitData(sf::RenderWindow &window) override;

  /**
    Sets the map display to the map that was most recently created.  Used for immediatly displaying
      a newly created map.

    @param &mapDisplay Reference to a map display object so newly created map data can be stored in it.
    @param &view Reference to the view the newly created map should be displayed in.
  */
  void DisplayNewestMap(MapDisplay &mapDisplay, sf::View &view);

  /**
    Sets whether or not the user has clicked the submit data button.

    @param submitted Sets the boolean value used for determining if data has be submitted or not.
  */
  /***********SHOULD THIS BE REFACTORED AS A setButtonClicked FUNCTION IN THE BUTTON CLASS?**************/
  void SetDataSubmitted(bool submitted);

  /**
    Gets whether or not the user has clicked the submit data button.
  */
  /***********SHOULD THIS BE REFACTORED AS A GetbuttonClicked FUNCTION IN THE BUTTON CLASS?**************/
  bool GetDataSubmitted();

private:
  Map m_newMap; //Object for holding newly created map data
  bool m_dataSubmitted;  //Determines if the user has clicked the submit data button.  Maybe move to Button class?
};
