/**
    SDEV435-81 Capstone Project
    ContentContainer.h
    Purpose: Header file for the ContentContainer class.  This class
      is used to create content areas within the program.  Content
      can then be added to these areas.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#pragma once
#include <SFML/Graphics.hpp>


class ContentContainer
{
public:

  /**
    Constructor

  	@param &mainWindow References an sf::RenderWindow object that is used to size the container.
    @param sizeXRatio The x axis size of the container in relation to the &mainWindow.
    @param sizeYRatio The y axis size of the container in relation to the &mainWindow.
    @param posXRatio The x axis position of the container in relation to the &mainWindow.
    @param posYRatio The y axis position of the container in relation to the &mainWindow.
  */
  ContentContainer(sf::RenderWindow& mainWindow, float sizeXRatio, float sizeYRatio, float posXRatio, float posYRatio, sf::Color color);

  //Default Destructor
  ~ContentContainer();

  /**
    Draws the ContentContainer object to the window.

  	@param &window The sf::RenderWindow object the ContentContainer object is to be drawn to.
  */
  void Draw(sf::RenderWindow& window);

  /**
    Returns the sf::Vector2f object with the x and y sizes of the container.
  */
  sf::Vector2f GetSize();

  /**
    Returns the sf::Vector2f object with the x and y position of the container.
  */
  sf::Vector2f GetPosition();

private:
  sf::RectangleShape m_container; //Object holding data for the ContentContainer.
};
