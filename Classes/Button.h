/**
    SDEV435-81 Capstone Project
    Button.h
    Purpose: Header file for the Button class, which allows for
      the creation of objects that act like buttons users can
      click on the screen to navigate from page to page and submit data.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>


class Button
{
public:

  //Default Constructor.
  Button();

  /**
    Constructor.

    @param name The string that displays on the button.
    @param window The window where the button will be drawn.
    @param color The fill color of the button.
    @param textColor the color of the displayed text;
  */
  Button(std::string name, sf::RenderWindow& window, sf::Color color, sf::Color textColor);

  //Default Destructor
  ~Button();


  /**
    Set Button data for Button objects created with Default Constructor.

  	@param name The string to display on the Button object.
    @param &window Reference to Window object to draw to.
  */
  void SetButton(std::string name, sf::RenderWindow& window);

  /**
    Draw Button object to a Window object.

    @param &window Reference to Window object to draw to.
  */
  void Draw(sf::RenderWindow& window);

  /**
    Position a Button object in relation to a ContentContainer object.

  	@param area sf::Vector2f returned by ContentContainer::GetSize object.
  	@param ratioX Determines where the button is positioned on the x axis in relation to the ContentContainer object.
  	@param ratioY Determines where the button is positioned on the y axis in relation to the ContentContainer object.
  */
  void SetPosition(sf::Vector2f area, float ratioX, float ratioY);

  /**
    Set the background color of the button.

	   @param color An sf::Color object that determines background color of button.
  */
  void SetColor(sf::Color color);

  /**
    Return whether mouse is over a button object created in main.cpp.

    @param &window Reference to a RenderWindow object the Button object exists in.
  */
  bool mouseOver(sf::RenderWindow &window);

  /**
    Return whether mouse is over a button object created in a Content object.

    @param &window Reference to a RenderWindow object the Button object exists in.
  */
  bool ContentBtnMouseOver(sf::RenderWindow & window);

private:
  sf::RectangleShape m_button; //Shape of button object.
  sf::Font m_ubuntu; //Font used to display text on button.
  sf::Text m_text; //Object that contains text displayed on button.
};
