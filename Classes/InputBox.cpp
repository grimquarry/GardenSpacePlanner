/**
    SDEV435-81 Capstone Project
    InputBox.cpp
    Purpose: Code file for the InputBox class.  This class creates
      objects used for user input boxes.  Each InputBox object
      has a header that identifies what input should go into the
      box and allows users to type data into that box.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#include "InputBox.h"

//Default Constructor
InputBox::InputBox()
{
  //Default settings
  m_isSelected = false;
  m_hasLimit = true;
  m_limit = 30;
  m_textBox.setFillColor(sf::Color::Black);
  m_container.setSize({450.f, 40.f});
  m_container.setOutlineColor(sf::Color::Black);
  m_container.setOutlineThickness(1);

  //Add cursor to textbox.
  if(m_isSelected == true)
  {
    m_textBox.setString("_");
  }
  else
  {
    m_textBox.setString(" ");
  }

  if(!m_ubuntu.loadFromFile("Fonts/Ubuntu-M.ttf"))
  {
    std::cout << "Unable to load Ubuntu-M.ttf font file" << std::endl;
  }

  m_inputHeader.setFont(m_ubuntu);
  m_inputHeader.setFillColor(sf::Color::Black);

  if(!a_Futurica.loadFromFile("Fonts/a_Futurica.ttf"))
  {
    std::cout << "Unable to load a_Futurica.ttf font file" << std::endl;
  }

  m_textBox.setFont(a_Futurica);
  m_textBox.setCharacterSize(20);
}

//Default Destructor
InputBox::~InputBox() { }

/******Public Functions******/

//Sets postions for m_inputHeader sf::Text object, m_container sf::RectangleShape object, and m_textBox sf::Text object.
void InputBox::SetPosition(sf::Vector2f pos)
{
  m_inputHeader.setPosition(pos);
  m_container.setPosition(pos.x + 270.f, pos.y);
  m_textBox.setPosition(pos.x + 275, pos.y + 10);
}

//Sets whether or not the user has selected the input box to enter data.
void InputBox::setSelected(bool sel)
{
  m_isSelected = sel;

  if(!sel)
  {
    std::string t = m_text.str();
    std::string newT = "";
    for(int i = 0; i < t.length(); i++)
    {
      newT += t[i];
    }
    m_textBox.setString(newT);
  }
}

//Returns text currently held in the m_text sf::Text ostringstream object.
std::string InputBox::GetText()
{
  return m_text.str();
}

//Sets the string for the m_text ostringstream object and the m_textBox sf::Text object.
void InputBox::AddText(std::string s)
{
  m_textBox.setString(s);
  m_text.str(s);
}

//Removes all text from the m_text ostringstream object and the m_textBox sf::Text object.
void InputBox::ClearContent()
{
  m_textBox.setString("");
  m_text.str("");
}

//Sets the string for the m_inputHeader sf::Text object.
void InputBox::SetHeader(std::string header)
{
  m_inputHeader.setString(header);
}

//Displays user input in the InputBox object as the user is typing.
void InputBox::typedOn(sf::Event input)
{
  if(m_isSelected)
  {
    int charTyped = input.text.unicode; //Gets the unicode value for the keyboard char the user typed.
    if(charTyped < 128) //Anything above Unicode 128 is unnecessary
    {
      if(m_hasLimit)//Only accept characters when the text box hasn't exceeded this limit.
      {
        if(m_text.str().length() <= m_limit)
        {
          inputLogic(charTyped);//Private inputLogic function takes the key the user pressed and displays it to the text box.
        }
        else if(m_text.str().length() > m_limit  && charTyped == DELETE_KEY)
        {
          deleteLastChar();
        }
      }
      else
      {
        inputLogic(charTyped);
      }
    }
  }
}

//Checks to see if InputBox object has a mouse positioned over it and if clicked on changes the backgound color of the input box.
void InputBox::clickedOn(sf::RenderWindow &window)
{
  float mouseX = sf::Mouse::getPosition(window).x;
  float mouseY = sf::Mouse::getPosition(window).y;

  float boxPosX = m_container.getPosition().x * 2;
  float boxPosY = m_container.getPosition().y + window.getSize().y / 8.523;

  float boxXPosWidth = boxPosX + m_container.getGlobalBounds().width;
  float boxYPosHeight = boxPosY + m_container.getGlobalBounds().height;

  if(mouseX < boxXPosWidth && mouseX > boxPosX && mouseY < boxYPosHeight && mouseY > boxPosY)
  {
    m_isSelected = true;
    m_container.setFillColor(sf::Color(223, 223, 223));
  }
  else
  {
    m_isSelected = false;
    m_container.setFillColor(sf::Color::White);
  }
}

//Draws the sf::RectangleShape m_container, sf::Text m_textBox, and sf::Text m_inputHeader text objects to the window.
void InputBox::Draw(sf::RenderWindow &window)
{
  window.draw(m_container);
  window.draw(m_textBox);
  window.draw(m_inputHeader);
}

/******Private Functions****/

//Logic that sets the cursor in the input box, deletes characters when user presses backspace, and adds text to the m_texBox object through the stringstream object.
void InputBox::inputLogic(int charTyped)
{
  if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
  {
    m_text << static_cast<char>(charTyped);
  }
  else if (charTyped == DELETE_KEY)
  {
    if(m_text.str().length() > 0)
    {
      deleteLastChar();
    }
  }
  m_textBox.setString(m_text.str() + "_");
}

//Removes the last character in the text box (used with DELETE_KEY).
void InputBox::deleteLastChar()
{
  std::string t = m_text.str();
  std::string newT = "";
  for(int i = 0; i < t.length() - 1; i++)
  {
    newT += t[i];
  }
  m_text.str("");
  m_text << newT;
  m_textBox.setString(m_text.str());
}
