/**
    Garden Space Planner
    ContentInput.h
    Purpose: Header file for the ContentInput class.  This class inherits from the
    ContentInput class, which in turn inherits from the Content Class.  The
    ContentInput class builds on Content class functionality specifically for content
    that allows for user input.  If focuses on basic user input functions that not
    all kinds of Content objects need.

    @author Jeremiah Kellogg
    @version 1.0.0 12/26/19
*/

#pragma once
#include "Content.h"
#include "InputBox.h"
#include "Button.h"

class ContentInput : public Content
{
public:

  //Default Constructor
  ContentInput();

  //Default Destructor
  ~ContentInput();

  /**
    Add a section of the Content display for user input boxes.

    @param width The size of the input area on the x axis.
    @param height The size of the input area on the y axis.
	  @param posX The x axis position of the user input area.
	  @param posY The y axis position of the user input area.
  */
  void AddInputArea(float width, float height, float posX, float posY);

  /**
    Add InputBox objects to the Content object for user input.

    @param header1 The label/header for the 1st InputBox object.
  	@param pos1 sf::Vector2f object holding the x & y coordinates for 1st InputBox object.
  	@param header2 The label/header for the 2nd InputBox object.
  	@param pos2 sf::Vector2f object holding the x & y coordinates for 2nd InputBox object.
  	@param header3 The label/header for the 3rd InputBox object.
  	@param pos3 sf::Vector2f object holding the x & y coordinates for 3rd InputBox object.
  	@param header4 The label/header for the 4th InputBox object.
  	@param pos4 sf::Vector2f object holding the x & y coordinates for 4th InputBox object.
  */
  void AddInputBoxes(std::string header1, sf::Vector2f pos1,
    std::string header2, sf::Vector2f pos2,
    std::string header3, sf::Vector2f pos3,
    std::string header4, sf::Vector2f pos4);

  /**
    Focus on InputBox object the user has selected for inputing data.

    @param &window The RenderWindow object the InputBox object is displayed in.
  */
  /********SHOULD THIS BE MOVED TO THE InputBox CLASS?*****************/
  void FocusOnBox(sf::RenderWindow &window);

  /**
    Checks to see if user is typing, and if so displays text the user is typing into the InputBox object.

    @param input The sf::Event object that grabs what keyboard key is pressed.
  */
  /********SHOULD THIS BE MOVED TO THE InputBox CLASS?*****************/
  void EnterText(sf::Event input);

  /**
    Adds a Button object to the Content display so users can submit data they've entered into InputBox objects.

    @param name The string to display on the input button.
    @param &window References the RenderWindow object the button is displayed on.
    @param area The sf::Vector2f object holding the size of the ContentContainer object the Button object belongs to.
    @param ratioX The ratio that sets the x axis position of the Button object in relation to the Content ContentContainer object.
    @param ratioY The ratio that sets the y axis position of the Button object in relation to the Content ContentContainer object.
  */
  void AddInputButton(std::string name, sf::RenderWindow& window,
    sf::Vector2f area, float ratioX, float ratioY);

  /**
    A virtual function that sub-classes can inherit from to submit user input data to the proper table in the
      garden_space_planner MySQL database.  It's up to the inheriting class to override and define functionaility.

    @param &window The RenderWindow object needed to pass to a button object to determine
      when a user has clicked the submit button.
  */
  virtual void SubmitData(sf::RenderWindow &window);

  /**
    Draws InputBox objects to the sf::Renderwindow object.

  	@param &window References an sf::RenderWindow object to draw to.
  */
  /********SHOULD THIS BE MOVED TO THE InputBox CLASS?*****************/
  void DrawInputField(sf::RenderWindow &window);


protected:
  sf::RectangleShape m_input_container; //Object for containing InputBox objects for the Content object.
  InputBox m_inputBox1;  //Object for input box users can enter data in.
  InputBox m_inputBox2;  //Object for input box users can enter data in.
  InputBox m_inputBox3;  //Object for input box users can enter data in.
  InputBox m_inputBox4;  //Object for input box users can enter data in.
  Button m_inputButton;  //Object for configuring buttons for submitting user input to MySQL database.
};
