/**
    SDEV435-81 Capstone Project
    Button.cpp
    Purpose: Code file for the Button class, which allows for
      the creation of objects that act like buttons users can
      click on the screen to navigate from page to page and submit data.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#include "Button.h"

//Default Constructor.
Button::Button() { }

//Constructor.
Button::Button(std::string name, sf::RenderWindow& window, sf::Color color, sf::Color textColor)
{
  m_text.setString(name);
  m_button.setSize(sf::Vector2f((float)(window.getSize().x * .16f), (float)(window.getSize().y * .06f)));
  m_button.setFillColor(color);
  m_text.setFillColor(textColor);
  m_button.setOutlineColor(sf::Color(42, 85, 34, 255));
	m_button.setOutlineThickness(3.0f);
  if(!m_ubuntu.loadFromFile("Fonts/Ubuntu-M.ttf"))
  {
    std::cout << "Unable to load Ubuntu-M.ttf font file" << std::endl;
  };
  m_text.setFont(m_ubuntu);
}

//Default Destructor
Button::~Button() { }

//Set Button data for Button objects created with Default Constructor.
void Button::SetButton(std::string name, sf::RenderWindow& window)
{
  m_text.setString(name);
  m_button.setSize(sf::Vector2f((float)(window.getSize().x * .16f), (float)(window.getSize().y * .06f)));
  m_button.setFillColor(sf::Color(228, 243, 127, 255));
  m_text.setFillColor(sf::Color::Black);
  m_button.setOutlineColor(sf::Color(42, 85, 34, 255));
	m_button.setOutlineThickness(3.0f);

  if(!m_ubuntu.loadFromFile("Fonts/Ubuntu-M.ttf"))
  {
    std::cout << "Unable to load Ubuntu-M.ttf font file" << std::endl;
  };
  m_text.setFont(m_ubuntu);
}

//Draw Button object to a Window object.
void Button::Draw(sf::RenderWindow& window)
{
  window.draw(m_button);
  window.draw(m_text);
}

//Position a Button object in relation to a ContentContainer object.
void Button::SetPosition(sf::Vector2f area, float ratioX, float ratioY)
{
  sf::Vector2f position = {area.x * ratioX, (area.y * ratioY) / 2.5f};
  m_button.setPosition(position);

  float xPos = position.x + ((m_button.getGlobalBounds().width - m_text.getGlobalBounds().width) / 2);
  float yPos = position.y + ((m_button.getGlobalBounds().height - m_text.getGlobalBounds().height)) * .25;
  m_text.setPosition(xPos, yPos);
}

//Set the background color of the button.
void Button::SetColor(sf::Color color)
{
  m_button.setFillColor(color);
}

//Return whether mouse is over a button object created in main.cpp.
bool Button::mouseOver(sf::RenderWindow &window)
{
  float mouseX = sf::Mouse::getPosition(window).x;
  float mouseY = sf::Mouse::getPosition(window).y;

  float btnPosX = m_button.getPosition().x;
  float btnPosY = m_button.getPosition().y;

  float btnXPosWidth = btnPosX + m_button.getGlobalBounds().width;
  float btnYPosHeight = btnPosY + m_button.getGlobalBounds().height;

  if(mouseX < btnXPosWidth && mouseX > btnPosX && mouseY < btnYPosHeight && mouseY > btnPosY)
  {
    return true;
  }
  return false;
}

//Return whether mouse is over a button object created in a Content object.
bool Button::ContentBtnMouseOver(sf::RenderWindow &window)
{
  float mouseX = sf::Mouse::getPosition(window).x;
  float mouseY = sf::Mouse::getPosition(window).y;

  float btnPosX = m_button.getPosition().x * 1.935f;
  float btnPosY = m_button.getPosition().y * 1.15f;

  float btnXPosWidth = btnPosX + m_button.getGlobalBounds().width;
  float btnYPosHeight = btnPosY + m_button.getGlobalBounds().height;

  if(mouseX < btnXPosWidth && mouseX > btnPosX && mouseY < btnYPosHeight && mouseY > btnPosY)
  {
    return true;
  }
  return false;
}
