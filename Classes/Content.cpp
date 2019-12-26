/**
    Garden Space Planner
    Content.cpp
    Purpose: Source code file for the Content base class.  This class provides
      basic functionality for creating varioius types of content that can
      be selected and viewed by the user.  It's focus is more on the main content
      display of the Garden Space Planner program.  This code was re-factcored for
      version 2.0.0 to make it a base class, which allowed for more granular
      functionality for the varying types of content and their unique needs.

    @author Jeremiah Kellogg
    @version 2.0.0 12/26/19
*/

#include "Content.h"

//Default Constructor.
Content::Content()
{
  //New objects should not be active, scrolling or clicked until user selects them
  m_isActive = false;

  if(!m_ubuntu.loadFromFile("Fonts/Ubuntu-M.ttf"))
  {
    std::cout << "Unable to load Ubuntu-M.ttf font file" << std::endl;
  };
  //Default settings for sf::Text objects
  m_contentText.setFont(m_ubuntu);
  m_contentText.setPosition(30.f, 10.f);
  m_contentText.setCharacterSize(27);
  m_contentText.setFillColor(sf::Color::Black);
}

//Default Destructor.
Content::~Content() { }

//Add text from a file to display in the Content window.
void Content::AddText(std::string fileName)
{
  m_inputFile.open(fileName);

  //Get text from file line by line and concantenate to m_contentString for full block of text
  while (std::getline(m_inputFile, m_stringSection))
  {
    m_contentString += m_stringSection + "\n";
  }

  m_contentText.setString(m_contentString);
}

//Draw all Content text to the window.
void Content::DrawText(sf::RenderWindow &window)
{
  window.draw(m_contentText);
}

//Dismiss pop-ups called by the Content object to convey important messages to the user.
void Content::MessageDismissed(sf::RenderWindow &window)/******THIS SHOULD BE MOVED TO MessageWindow CLASS********/
{
  m_messageDisplay.clickedOn(window);
}

//Returns whether or not a Content object is the most current content selected to view by the user.
bool Content::GetActiveStatus()
{
  return m_isActive;
}

//Makes a Content object the most current selected by the user to view and display in the main content area.
void Content::MakeActive()
{
  m_isActive = true;
}

//Makes a Content objects not currently selected by the user inactive so they don't display to the main content view.
void Content::MakeInactive()
{
  m_isActive = false;
}
