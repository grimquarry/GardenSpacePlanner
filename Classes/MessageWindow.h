/**
    SDEV435-81 Capstone Project
    MessageWindow.h
    Purpose: Header file for the MessageWindow class.  This class
      creates objects for displaying important messages to the
      user, which the user can dismiss after reading.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class MessageWindow
{
public:
  //Default Constructor that sets default values for sf::Text objects and sf::RectangleShape objects.
  MessageWindow();

  //Default Destructor.
  ~MessageWindow();

  /**
    Assigns string to the sf::Text m_messageText object to display a message to the user.

    @param message The message to be displayed in the message box.
  */
  void AddMessage(std::string message);

  /**
    Renders the m_windowHeader, m_headerText, m_messageWindow, m_messageText, m_messageButton, & m_messageButtonText object to the window.

    @param &window References the sf::RenderWindow object the message window should be drawn to.
  */
  void Draw(sf::RenderWindow &window);

  /**
    Returns the m_isDisplayed member variable to determine if a message window is being displayed.
  */
  bool GetDisplay();

  /**
    Sets true or false to the m_isDisplayed member variable for determining if a message window should be displayed or not.

    @param display True or false depending on whether a message window should be displayed or not.
  */
  void SetDisplay(bool display);

  /**
    Sets the fill collor for sf::RectangleShape m_messageButton object (used for changing color of button on hover).

    @param color The sf::Color object for setting the desired color of the button.
  */
  void SetButtonColor(sf::Color color);

  /**
    Returns whether or not the mouse is hovering over the Message window dismiss button.

    @param &window References the sf::RenderWindow object the message window dismiss button lives in.
  */
  bool MessageDismissHover(sf::RenderWindow &window);

  /**
    Used to detect if the mouse is over the dismiss button when left mouse button is clicked.

    @param &window References the sf::RenderWindow object the message window button lives in.
  */
  void clickedOn(sf::RenderWindow &window);


private:
  sf::RectangleShape m_messageWindow; //The rectangle shape of the message window.
  sf::RectangleShape m_windowHeader; //The rectangle shape of the header on top of the message window.
  sf::Text m_headerText;  //The text to display in the header.
  sf::Text m_messageText;  //The text to display for the message.
  sf::Font m_ubuntu;  //Fond object holding info for the ubuntu font.
  sf::RectangleShape m_messageButton;  //The rectangle shape of the message dismiss button.
  sf::Text m_messageButtonText;  //The DISMISS text on the dismiss button.
  bool m_isDisplayed;  //Variable for determining if a message is being displayed or not.
};
