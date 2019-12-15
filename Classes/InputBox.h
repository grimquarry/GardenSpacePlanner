/**
    SDEV435-81 Capstone Project
    InputBox.h
    Purpose: Header file for the InputBox class.  This class creates
      objects used for user input boxes.  Each InputBox object 
      has a header that identifies what input should go into the
      box and allows users to type data into that box.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

//Directives for assigning Unicode codes to backspace, enter, and esape keys
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class InputBox
{
public:

  //Default Constructor
  InputBox();

  //Default Destructor
  ~InputBox();

  /**
    Sets postions for m_inputHeader sf::Text object, m_container sf::RectangleShape object, and m_textBox sf::Text object.

  	@param pos An sf::Vector2f object holding x and y coordinates to place the InputBox object.
  */
  void SetPosition(sf::Vector2f pos);

  /**
    Sets whether or not the user has selected the input box to enter data.

  	@param sel A Boolean value indicating whether the user has selected the InputBox object or not.
  */
  void setSelected(bool sel);

  /**
    Returns text currently held in the m_text sf::Text ostringstream object.
  */
  std::string GetText();

  /**
    Sets the string for the m_text ostringstream object and the m_textBox sf::Text object.

  	@param s A string to be passed to the m_text and m_textBox objects.
  */
  void AddText(std::string s);

  /**
    Removes all text from the m_text ostringstream object and the m_textBox sf::Text object.
  */
  void ClearContent();

  /**
    Sets the string for the m_inputHeader sf::Text object.

  	@param header A string to be passed to the m_inputHeader object to display the InputBox's purpose.
  */
  void SetHeader(std::string header);

  /**
    Displays user input in the InputBox object as the user is typing.

  	@param input An sf::Event object that checks for user input and if found displays the characters as the user types them.
  */
  void typedOn(sf::Event input);

  /**
    Checks to see if InputBox object has a mouse positioned over it and if clicked on changes the backgound color of the input box.

  	@param &window References an sf::RenderWindow object to check for mouse position.
  */
  void clickedOn(sf::RenderWindow &window);

  /**
    Draws the sf::RectangleShape m_container, sf::Text m_textBox, and sf::Text m_inputHeader text objects to the window.

  	@param &window References an sf::RenderWindow object to draw to.
  */
  void Draw(sf::RenderWindow &window);

  bool m_isSelected;//Public variable to check if InputBox object has been selected by the user.

private:
  sf::RectangleShape m_container; //An object that contains all input box components.
  sf::Text m_textBox; //Object holding text to display in the input box.
  sf::Text m_inputHeader;  //Variable for storing the label for the input box.
  std::ostringstream m_text;  //Variable that holds what text the user is inputing or deleting.
  bool m_hasLimit;  //Variable holding whether or not there's a character limit for input boxes.
  int m_limit;  //Variable storing how many characters an input box will accept.
  sf::Font a_Futurica;  //Object for holding a Futurica font info.
  sf::Font m_ubuntu; //Object for holding Ubuntu font info.

  //Private Functions

  /**
    Logic that sets the cursor in the input box, deletes characters when user presses backspace, and adds text to the m_texBox object through the stringstream object.

  	@param int The Unicode code for the key the user pressed to enter text into the text box.
  */
  void inputLogic(int charTyped);

  /**
    Removes the last character in the text box (used with DELETE_KEY).
  */
  void deleteLastChar();
};
