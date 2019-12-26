/**
  Garden Space Planner
  EditPlant.h
  Purpose: Header file for the EditPlant class.  This class inherits from the
  ContentInput class, which in turn inherits from the Content Class.  The
  EditPlant Class is specific to the module where users can edit existing plants
  in the database.  It was re-factored from the Content class because it allows
  for more unique functionality than the more general Content class was capable of.

  @author Jeremiah Kellogg
  @version 1.0.0 12/26/19
*/

#pragma once
#include "ContentInput.h"

class EditPlant : public ContentInput
{
public:
  //Default Constructor
  EditPlant();

  //Default Destructor
  ~EditPlant();

/**
  Submit user edited plant data to the plants table in the garden_space_planner MySQL database.

  @param &window The RenderWindow object needed to pass to a button object to determine
    when a user has clicked the submit button.
*/
virtual void SubmitData(sf::RenderWindow &window) override;

/**
  Finds the currently selected Plant in the garden_space_planner.plants MySQL table;
*/
void GetSelectedPlant();

private:

};
