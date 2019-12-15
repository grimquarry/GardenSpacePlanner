/**
    SDEV435-81 Capstone Project
    MessageWindow.cpp
    Purpose: Code file for the MessageWindow class.  This class
      creates objects for displaying important messages to the
      user, which the user can dismiss after reading.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#include "MessageWindow.h"

//Default Constructor that sets default values for sf::Text objects and sf::RectangleShape objects.
MessageWindow::MessageWindow()
{
  m_isDisplayed = false;
  m_windowHeader.setSize({400, 50});
  m_windowHeader.setFillColor(sf::Color(200, 200, 200, 255));
  m_windowHeader.setOutlineColor(sf::Color::Blue);
  m_windowHeader.setOutlineThickness(1.f);
  m_windowHeader.setPosition(200.f, 100.f);

  m_messageWindow.setSize({400, 200});
  m_messageWindow.setFillColor(sf::Color(220, 220, 220, 255));
  m_messageWindow.setOutlineColor(sf::Color::Blue);
  m_messageWindow.setOutlineThickness(1.f);
  m_messageWindow.setPosition(200.f, 150.f);

  m_messageButton.setSize({100, 30});
  m_messageButton.setFillColor(sf::Color(200, 200, 200, 255));
  m_messageButton.setOutlineColor(sf::Color::Blue);
  m_messageButton.setOutlineThickness(1);
  m_messageButton.setPosition(m_messageWindow.getPosition().x + 150 - (m_messageButtonText.getGlobalBounds().width / 2), 300.f);

  if(!m_ubuntu.loadFromFile("Fonts/Ubuntu-M.ttf"))
  {
    std::cout << "Unable to load Ubuntu-M.ttf font file" << std::endl;
  };
  m_headerText.setFont(m_ubuntu);
  m_headerText.setCharacterSize(20);
  m_headerText.setFillColor(sf::Color::Black);
  m_headerText.setString("Message");
  m_headerText.setPosition(m_windowHeader.getPosition().x + ((m_windowHeader.getSize().x / 2) -30),
    m_windowHeader.getPosition().y + 10);

  m_messageText.setFont(m_ubuntu);
  m_messageText.setCharacterSize(15);
  m_messageText.setFillColor(sf::Color::Black);
  m_messageText.setPosition(m_messageWindow.getPosition().x + 10, m_messageWindow.getPosition().y + 10);

  m_messageButtonText.setFont(m_ubuntu);
  m_messageButtonText.setCharacterSize(15);
  m_messageButtonText.setString("DISMISS");
  m_messageButtonText.setFillColor(sf::Color::Black);
  m_messageButtonText.setPosition({370.f, 305.f});
}

//Default Destructor.
MessageWindow::~MessageWindow() { }

//Assigns string to the sf::Text m_messageText object to display a message to the user.
void MessageWindow::AddMessage(std::string message)
{
  m_messageText.setString(message);
}

//Renders the m_windowHeader, m_headerText, m_messageWindow, m_messageText, m_messageButton, & m_messageButtonText object to the window.
void MessageWindow::Draw(sf::RenderWindow &window)
{
  window.draw(m_windowHeader);
  window.draw(m_headerText);
  window.draw(m_messageWindow);
  window.draw(m_messageText);
  window.draw(m_messageButton);
  window.draw(m_messageButtonText);
}

//Returns the m_isDisplayed member variable to determine if a message window is being displayed.
bool MessageWindow::GetDisplay()
{
  return m_isDisplayed;
}

//Sets true or false to the m_isDisplayed member variable for determining if a message window should be displayed or not.
void MessageWindow::SetDisplay(bool display)
{
  m_isDisplayed = display;
}

//Sets the fill collor for sf::RectangleShape m_messageButton object (used for changing color of button on hover).
void MessageWindow::SetButtonColor(sf::Color color)
{
  m_messageButton.setFillColor(color);
}

//Returns whether or not the mouse is hovering over the Message window dismiss button.
bool MessageWindow::MessageDismissHover(sf::RenderWindow &window)
{
  float mouseX = sf::Mouse::getPosition(window).x;
  float mouseY = sf::Mouse::getPosition(window).y;

  float boxPosX = m_messageButton.getPosition().x + window.getSize().x / 3.7f;
  float boxPosY = m_messageButton.getPosition().y + window.getSize().y / 8.523;

  float boxXPosWidth = boxPosX + m_messageButton.getGlobalBounds().width;
  float boxYPosHeight = boxPosY + m_messageButton.getGlobalBounds().height;

  if(mouseX < boxXPosWidth && mouseX > boxPosX && mouseY < boxYPosHeight && mouseY > boxPosY)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//Used to detect if the mouse is over the dismiss button when left mouse button is clicked.
void MessageWindow::clickedOn(sf::RenderWindow &window)
{
  float mouseX = sf::Mouse::getPosition(window).x;
  float mouseY = sf::Mouse::getPosition(window).y;

  float boxPosX = m_messageButton.getPosition().x + window.getSize().x / 3.7f;
  float boxPosY = m_messageButton.getPosition().y + window.getSize().y / 8.523;

  float boxXPosWidth = boxPosX + m_messageButton.getGlobalBounds().width;
  float boxYPosHeight = boxPosY + m_messageButton.getGlobalBounds().height;

  if(mouseX < boxXPosWidth && mouseX > boxPosX && mouseY < boxYPosHeight && mouseY > boxPosY)
  {
    m_isDisplayed = false;
    m_messageButton.setFillColor(sf::Color::White);
  }
  else
  {
    m_messageButton.setFillColor(sf::Color(200, 200, 200, 255));
  }
}
