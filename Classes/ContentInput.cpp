/**
    Garden Space Planner
    ContentInput.cpp
    Purpose: Source code for the ContentInput class.  This class inherits from the
    ContentInput class, which in turn inherits from the Content Class.  The
    ContentInput class builds on Content class functionality specifically for content
    that allows for user input.  If focuses on basic user input functions that not
    all kinds of Content objects need.

    @author Jeremiah Kellogg
    @version 1.0.0 12/26/19
*/

#include "ContentInput.h"

//Default Constructor.
ContentInput::ContentInput() { }

//Default Destructor.
ContentInput::~ContentInput() { }

//Add a section of the Content display for user input boxes.
void ContentInput::AddInputArea(float width, float height, float posX, float posY)
{
  m_input_container.setSize(sf::Vector2f(width, height));
  m_input_container.setPosition(sf::Vector2f(posX, posY));
  m_input_container.setFillColor(sf::Color::White);
  m_input_container.setOutlineColor(sf::Color(42, 85, 34, 255));
	m_input_container.setOutlineThickness(1.0f);
}

//Add InputBox objects to the Content object for user input.
void ContentInput::AddInputBoxes(std::string header1, sf::Vector2f pos1,
  std::string header2, sf::Vector2f pos2,
  std::string header3, sf::Vector2f pos3,
  std::string header4, sf::Vector2f pos4)
{
  m_inputBox1.SetPosition(pos1);
  m_inputBox1.SetHeader(header1 + ":");
  m_inputBox2.SetPosition(pos2);
  m_inputBox2.SetHeader(header2 + ":");
  m_inputBox3.SetPosition(pos3);
  m_inputBox3.SetHeader(header3 + ":");
  m_inputBox4.SetPosition(pos4);
  m_inputBox4.SetHeader(header4 + ":");
}

//Focus on InputBox object the user has selected for inputing data.
/********SHOULD THIS BE MOVED TO THE InputBox CLASS?*****************/
void ContentInput::FocusOnBox(sf::RenderWindow &window)
{
  m_inputBox1.clickedOn(window);
  m_inputBox2.clickedOn(window);
  m_inputBox3.clickedOn(window);
  m_inputBox4.clickedOn(window);
}

//Checks to see if user is typing, and if so displays text the user is typing into the InputBox object.
/********SHOULD THIS BE MOVED TO THE InputBox CLASS?*****************/
void ContentInput::EnterText(sf::Event input)
{
  if(m_inputBox1.m_isSelected)
  {
    m_inputBox1.typedOn(input);
  }
  else if(m_inputBox2.m_isSelected)
  {
    m_inputBox2.typedOn(input);
  }
  else if(m_inputBox3.m_isSelected)
  {
    m_inputBox3.typedOn(input);
  }
  else if(m_inputBox4.m_isSelected)
  {
    m_inputBox4.typedOn(input);
  }
}

//Adds a Button object to the Content display so users can submit data they've entered into InputBox objects.
void ContentInput::AddInputButton(std::string name, sf::RenderWindow& window,
  sf::Vector2f area, float ratioX, float ratioY)
{
  m_inputButton.SetButton(name, window);
  m_inputButton.SetPosition(area, ratioX, ratioY);
}

//A virtual function that sub-classes can inherit from to submit user input data to the proper table in the
  //garden_space_planner MySQL database.  It's up to the inheriting class to override and define functionaility.
void ContentInput::SubmitData(sf::RenderWindow &window) { }

//Draws InputBox objects to the sf::Renderwindow object.
/********SHOULD THIS BE MOVED TO THE InputBox CLASS?*****************/
void ContentInput::DrawInputField(sf::RenderWindow &window)
{
  window.draw(m_input_container);
  m_inputBox1.Draw(window);
  m_inputBox2.Draw(window);
  m_inputBox3.Draw(window);
  m_inputBox4.Draw(window);
  if(m_inputButton.ContentBtnMouseOver(window))
  {
    m_inputButton.SetColor(sf::Color(238, 244, 177, 255));
  }
  else
  {
    m_inputButton.SetColor(sf::Color(228, 243, 127, 255));
  }
  m_inputButton.Draw(window);
  if(m_messageDisplay.GetDisplay())
  {
    if(m_messageDisplay.MessageDismissHover(window))
    {
      m_messageDisplay.SetButtonColor(sf::Color::White);
    }
    else
    {
      m_messageDisplay.SetButtonColor(sf::Color(200, 200, 200, 255));
    }
    m_messageDisplay.Draw(window);
  }
}
