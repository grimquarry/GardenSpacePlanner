/**
    Garden Space Planner
    AddPlant.h
    Purpose: Header file for the AddPlant Class.  This class inherits from the
    ContentInput class, which in turn inherits from the Content Class.  The
    AddPlant Class is specific to the module where users can add new plants to
    the database.  It was re-factored from the Content class because it allows
    for more unique functionality than the more general Content class was capable
    of.

    @author Jeremiah Kellogg
    @version 1.0.0 12/26/19
*/

#pragma once
#include "ContentInput.h"

class AddPlant : public ContentInput
{
public:
  //Default Constructor
  AddPlant();

  //Default Destructor
  ~AddPlant();

  /**
    Submit user inputed data to the plants table in the garden_space_planner MySQL database.

    @param &window The RenderWindow object needed to pass to a button object to determine
      when a user has clicked the submit button.
  */
  virtual void SubmitData(sf::RenderWindow &window) override;

};
