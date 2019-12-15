/**
    SDEV435-81 Capstone Project
    ContentContainer.cpp
    Purpose: Code file for the ContentContainer class.  This class
      is used to create content areas within the program.  Content
      can then be added to these areas.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#include "ContentContainer.h"

//Constructor
ContentContainer::ContentContainer(sf::RenderWindow& mainWindow, float sizeXRatio, float sizeYRatio, float posXRatio, float posYRatio, sf::Color color)
{
  m_container.setSize(sf::Vector2f((float)(mainWindow.getSize().x * sizeXRatio), (float)(mainWindow.getSize().y * sizeYRatio)));
	m_container.setPosition(sf::Vector2f((float)((mainWindow.getSize().x * posXRatio)/2), (float)(mainWindow.getSize().y * posYRatio)));
	m_container.setFillColor(color);
	m_container.setOutlineColor(sf::Color(42, 85, 34, 255));
	m_container.setOutlineThickness(2.0f);
}

//Default Destructor
ContentContainer::~ContentContainer() { }

//Draws the ContentContainer object to the window.
void ContentContainer::Draw(sf::RenderWindow& window)
{
  window.draw(m_container);
}

//Returns the sf::Vector2f object with the x and y sizes of the container.
sf::Vector2f ContentContainer::GetSize()
{
  return m_container.getSize();
}

//Returns the sf::Vector2f object with the x and y position of the container.
sf::Vector2f ContentContainer::GetPosition()
{
  return m_container.getPosition();
}
