/**
    SDEV435-81 Capstone Project
    LeftColumnContent.cpp
    Purpose: Code file for the LeftColumnContent class.  This class
      creates a space for creating and displaying content in the
      left column of the Garden Space Planner program's GUI.  This
      area holds a list of plants user can select to edit or drop
      into a garden map.

    @author Jeremiah Kellogg
    @version 1.0.1 12/08/19
*/

#include "LeftColumnContent.h"

/*************Public Functions************/

//Default Constructor
LeftColumnContent::LeftColumnContent() { }

//Constructor
LeftColumnContent::LeftColumnContent(sf::View &view)
{
  m_leftColumnView = view;

  //Set defaults for sf::Text objects
  if(!m_ubuntu.loadFromFile("Fonts/Ubuntu-M.ttf"))
  {
    std::cout << "Unable to load Ubuntu-M.ttf font file" << std::endl;
  };
  m_plantTxtName.setFont(m_ubuntu);
  m_plantTxtName.setFillColor(sf::Color::Black);
  m_plantTxtVariety.setFont(m_ubuntu);
  m_plantTxtVariety.setFillColor(sf::Color::Black);
  m_plantTxtVariety.setCharacterSize(23);
  m_plantTxtSpacing.setFont(m_ubuntu);
  m_plantTxtSpacing.setFillColor(sf::Color::Black);
  m_plantTxtSpacing.setCharacterSize(15);
  m_plantTxtRow.setFont(m_ubuntu);
  m_plantTxtRow.setFillColor(sf::Color::Black);
  m_plantTxtRow.setCharacterSize(15);

  GetSelectedPlant();
}

//Default Destructor.
LeftColumnContent::~LeftColumnContent() { }

//Add a Scrollbar in the left column.
//Don't move to Scrollbarr class?  This class needs to instantiate a Scrollbar object, and this function is a good candidate for that.
void LeftColumnContent::AddScrollBar()
{
  m_scrollBar = &ptrAddress;
  std::cout << "AddScrollBar was called" << std::endl;
  m_scrollBar->SetView(m_leftColumnView);
  m_scrollBar->SetContainerSize({m_leftColumnView.getSize().x * .07f, m_displayArea.getSize().y});
  m_scrollBar->SetContainerPos({m_displayArea.getPosition().x + (m_displayArea.getSize().x - m_scrollBar->GetContainerSize().x), m_displayArea.getPosition().y});
  m_scrollBar->SetContainerColor(sf::Color(220, 220, 220, 255));

  m_screenToViewRatio = m_displayArea.getSize().y / m_leftColumnView.getSize().y; //Used for properly sizing scrollbar slider.

  m_scrollBar->SetElementSize({m_scrollBar->GetContainerSize().x * .75f, m_leftColumnView.getSize().y / m_screenToViewRatio});
  /*m_scrollMinimum.x = m_scrollContainer.getPosition().x * 1.015f;
  m_scrollMinimum.y =  m_scrollContainer.getPosition().y;*/
  m_scrollBar->SetScrollMin();
  /*m_scrollMaximum.x = m_scrollContainer.getPosition().x * 1.01f;
  m_scrollMaximum.y = m_scrollContainer.getGlobalBounds().height;*/
  m_scrollBar->SetScrollMax();
  m_scrollBar->SetElementPos(m_scrollBar->GetScrollMin());
  m_scrollBar->SetElementColor(sf::Color(175, 175, 175, 255));
  m_scrollBar->SetCenterScreen(m_leftColumnView.getSize().x / 2.f, (m_leftColumnView.getSize().y / 2.f));
}

//Sets the m_firstClick member variable to true or false.
//******Move to Scrollbar class.***********
/*void LeftColumnContent::SetFirstClick(bool click)
{
  m_firstClick = click;
}*/

//Returns the value of the m_firstClick member variable.
//******Move to Scrollbar class.***********
/*bool LeftColumnContent::GetFirstClick()
{
  return m_firstClick;
}*/

//Implements the logic behind scroll functionality
//******Move to Scrollbar class.***********
/*void LeftColumnContent::Scroll(sf::RenderWindow &window, sf::RectangleShape &viewborder)
{
  sf::Vector2i mouseWindowPostion = sf::Mouse::getPosition(window); //Grabs position of mouse in the window.
  sf::Vector2f mouseViewPosition = window.mapPixelToCoords(mouseWindowPostion);  //Translates mouse position in window to mouse position in the view.

  mouseYNew = mouseViewPosition.y;

  //Establish difference between scroll bar slider position and where the user clicked in the scroll bar slider.
  if(m_firstClick)
  {
    m_offset = mouseYNew - m_scrollElement.getPosition().y;
  }

  //Algorithm for determining how fast the view should scroll in relation to scroll bar slider movement.
  float viewScrollSpeed = (m_scrollContainer.getSize().y - m_leftColumnView.getSize().y) / (m_scrollContainer.getSize().y - m_scrollElement.getSize().y);

  //What to do if scroll bar slider is within bounds of scroll bar container.
  if(mouseYNew - m_offset > m_scrollContainer.getPosition().y && mouseYNew - m_offset < m_scrollContainer.getSize().y - m_scrollElement.getSize().y)
  {
    m_scrollElement.setPosition(m_scrollElement.getPosition().x, mouseYNew - m_offset);
    m_centerScreen.setPosition(m_leftColumnView.getSize().x / 2.f, m_leftColumnView.getSize().y / 2 + m_scrollElement.getPosition().y * viewScrollSpeed);
  }
  //What to do if scroll bar slider is outside the max bounds of scrollbar container.
  else if(mouseYNew - m_offset > m_scrollContainer.getSize().y)
  {
    m_scrollElement.setPosition(m_scrollMaximum);
    m_centerScreen.setPosition(m_leftColumnView.getSize().x / 2.f, (m_leftColumnView.getSize().y / 2.f) + m_scrollMaximum.y);
  }
  //What to do if scrollbar slider is below the minimum bounds of scrollbar container.
  else if (mouseYNew - m_offset < m_scrollContainer.getPosition().y)
  {
    m_scrollElement.setPosition(m_scrollMinimum);
    m_centerScreen.setPosition(m_leftColumnView.getSize().x / 2.f, (m_leftColumnView.getSize().y / 2.f));
  }
  m_firstClick = false;//first click is no longer true after the program loop runs once after scrollbar is clicked.
}*/

//Returns true or false depending on whether the mouse is positioned over the scrollbar or not.
/*//******Move to Scrollbar class.***********
bool LeftColumnContent::MouseOverScroll(sf::RenderWindow &window)
{
  sf::Vector2i mouseWindowPostion = sf::Mouse::getPosition(window); //Grabs position of mouse in the window.
  sf::Vector2f mouseViewPosition = window.mapPixelToCoords(mouseWindowPostion); //Translates mouse position in window to mouse position in the view.

  float scrollPosX = m_scrollElement.getPosition().x;
  float scrollXPosWidth = scrollPosX + m_scrollElement.getGlobalBounds().width;

  if(mouseViewPosition.x < scrollXPosWidth && mouseViewPosition.x > scrollPosX && mouseViewPosition.y < m_scrollElement.getPosition().y + m_scrollElement.getSize().y && mouseViewPosition.y > m_scrollContainer.getPosition().y)
  {
    return true;
  }
  return false;
}*/

//Returns true or false dependig on whether the mouse is positioned over a container listing plant info.
bool LeftColumnContent::MouseOverPlantContainer(sf::RenderWindow &window)
{
  sf::Vector2i mouseWindowPostion = sf::Mouse::getPosition(window); //Grabs position of mouse in the window.
  sf::Vector2f mouseViewPosition = window.mapPixelToCoords(mouseWindowPostion);  //Translates mouse position in window to mouse position in the view.

  float containerPosX = m_plantContainer.getPosition().x;
  float containerPosY = m_plantContainer.getPosition().y;

  float containerXPosWidth = containerPosX + m_plantContainer.getGlobalBounds().width;
  float containerYPosHeight = containerPosY + m_plantContainer.getGlobalBounds().height;

  if(mouseViewPosition.x < containerXPosWidth && mouseViewPosition.x > containerPosX && mouseViewPosition.y < containerYPosHeight && mouseViewPosition.y > containerPosY)
  {
    return true;
  }
  return false;
}

//Returns an sf::Vector2f object containing x and y axis position coordinates of the scrollbar.
//******Move to Scrollbar class.***********
/*sf::Vector2f LeftColumnContent::GetScrollPosition(ContentContainer &container)
{
  return {m_centerScreen.getPosition().x, m_centerScreen.getPosition().y};
}*/

//Sets whether or not the user is utilizing scroll functionality by passing the right value to the m_isScrolling member variable.
//******Move to Scrollbar class.***********
/*void LeftColumnContent::SetScrolling(bool toScroll)
{
  m_isScrolling = toScroll;
}*/

//Returns the value of the m_isScrolling member variable to determine if user is scrolling or not.
/*//******Move to Scrollbar class.***********
bool LeftColumnContent::GetScrolling()
{
  return m_isScrolling;
}*/

//Sets the color of the scrollbar (used for changing scrollbar color when user clicks on it).
//******Move to Scrollbar class.***********
/*void LeftColumnContent::ChangeColor(sf::Color color)
{
  m_scrollElement.setFillColor(color);
}*/

//Sets the size of the content area that the view can scroll over and sets the size of plant data containers.
void LeftColumnContent::AddDisplayArea()
{
  m_plantContainer.setSize({m_leftColumnView.getSize().x - (m_leftColumnView.getSize().x * .07f), m_leftColumnView.getSize().y / 4});
  m_plantContainer.setOutlineColor(sf::Color(42, 85, 34, 255));
  m_plantContainer.setOutlineThickness(1.f);

  m_displayArea.setFillColor(sf::Color(228, 243, 127, 255));
  m_displayArea.setSize({m_leftColumnView.getSize().x * .995f, m_plantContainer.getSize().y * m_plants.size()});
  m_displayArea.setPosition({1, 3});
  m_displayArea.setOutlineThickness(1.f);
}

//Grabs all plants from the MySQL garden_space_planner database in the plants table and stores them in the m_plants vector.
void LeftColumnContent::SetPlantVector()
{
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT * FROM plants");

  while (res->next()) {
    m_plant.SetID(res->getInt("plant_id"));
    m_plant.SetName(res->getString("plant_name"));
    m_plant.SetVariety(res->getString("plant_variety"));
    m_plant.SetSpacing(res->getInt("plant_spacing_width"));
    m_plant.SetRowSpacing(res->getInt("plant_spacing_length"));
    m_plant.SetSelected(res->getBoolean("is_selected"));

    m_plants.push_back(m_plant);
  }

  delete res;
  delete stmt;
  delete con;
}

//Builds and positions a container for each plant in the m_plants vector and stores position values in the m_plantDisplayPos vector.
void LeftColumnContent::SetPlantContainerVector()
{
  m_plantDisplayPos = (m_displayArea.getPosition());
  for(int i = 0; i < m_plants.size(); i++)
  {
    m_plantDisplayList.push_back(m_plantDisplayPos);
    m_plantDisplayPos.y += m_plantContainer.getSize().y;
  }
}

//Draws the m_displayArea, m_scrollElement, m_scrollContainer, m_plantContainer, m_plantTxtName, m_plantTxtVariety, and m_plantTxtSpacing object to the window.
void LeftColumnContent::Draw(sf::RenderWindow &window, sf::Event event)
{
  window.draw(m_displayArea);
  m_scrollBar->Draw(window);
  //window.draw(m_scrollContainer); //Move to ScrollBar class, and use that class's draw function here.
  //window.draw(m_scrollElement);  //Move to ScrollBar class, and use that class's draw function here.
  for(int i = 0; i < m_plantDisplayList.size(); i++)
  {
    m_plantContainer.setPosition(m_plantDisplayList[i]);
    if(MouseOverPlantContainer(window))
    {
      if(m_plants[i].GetID() != m_currentPlant.GetID())
      {
        m_plantContainer.setFillColor(sf::Color(238, 244, 177, 255));
      }
      else if(m_plants[i].GetID() == m_currentPlant.GetID())
      {
        m_plantContainer.setFillColor(sf::Color(86, 225, 58, 255));
      }

      if(event.mouseButton.button == sf::Mouse::Left)
      {
        m_currentPlant.SetSelectedDatabase(false, m_currentPlant.GetID());
        m_plants[i].SetSelectedDatabase(true, m_plants[i].GetID());
        m_currentPlant.SetID(m_plants[i].GetID());
        m_currentPlant.SetName(m_plants[i].GetName());
        m_currentPlant.SetVariety(m_plants[i].GetVariety());
        m_currentPlant.SetSpacing(m_plants[i].GetSpacing());
        m_currentPlant.SetRowSpacing(m_plants[i].GetRowSpacing());
      }
    }
    else
    {
      if(m_plants[i].GetID() == m_currentPlant.GetID())
      {
        m_plantContainer.setFillColor(sf::Color(86, 225, 58, 255));
      }
      else
      {
        m_plantContainer.setFillColor(sf::Color(228, 243, 127, 255));
      }
    }

    m_plantTxtName.setString(m_plants[i].GetName());
    m_plantTxtName.setPosition((m_plantContainer.getSize().x / 2) - (m_plantTxtName.getGlobalBounds().width / 2), (m_plantDisplayList[i].y + ( m_plantContainer.getSize().y / 4)) - (m_plantTxtName.getGlobalBounds().height));

    m_plantTxtVariety.setString("(" + m_plants[i].GetVariety() + ")");
    m_plantTxtVariety.setPosition((m_plantContainer.getSize().x / 2) - (m_plantTxtVariety.getGlobalBounds().width / 2), (m_plantDisplayList[i].y + ( m_plantContainer.getSize().y / 3))/* + (m_plantTxtVariety.getGlobalBounds().height)*/);

    std::string numberOfPlants = std::to_string((m_plants[i].GetRowSpacing() * 12) / m_plants[i].GetSpacing());
    std::string blockSize = std::to_string(m_plants[i].GetRowSpacing());
    m_plantTxtSpacing.setString(numberOfPlants + " plants per " + blockSize + "x" + blockSize + " foot space");
    m_plantTxtSpacing.setPosition((m_plantContainer.getSize().x / 2) - (m_plantTxtSpacing.getGlobalBounds().width / 2), (m_plantDisplayList[i].y + ( m_plantContainer.getSize().y / 2)) + (m_plantTxtSpacing.getGlobalBounds().height));

    window.draw(m_plantContainer);
    window.draw(m_plantTxtName);
    window.draw(m_plantTxtVariety);
    window.draw(m_plantTxtSpacing);
  }
}

ScrollBar* LeftColumnContent::GetScrollBar()
{
  //std::cout << "GetScrollBar was called" << std::endl;
  return m_scrollBar;
}

void LeftColumnContent::ChangeColor(sf::Color color)
{
  m_scrollBar->SetElementColor(color);
}

/**********Private Functions**********/

//Finds the currently selected Plant in the garden_space_planner.plants MySQL table;
void LeftColumnContent::GetSelectedPlant()
{
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT * FROM plants WHERE is_selected=true");
  while(res->next())
  {
      m_currentPlant.SetName(res->getString("plant_name"));
      m_currentPlant.SetVariety(res->getString("plant_variety"));
      m_currentPlant.SetSpacing(res->getInt("plant_spacing_width"));
      m_currentPlant.SetRowSpacing(res->getInt("plant_spacing_length"));
      m_currentPlant.SetID(res->getInt("plant_id"));
  }
}
