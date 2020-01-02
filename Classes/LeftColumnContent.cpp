/**
    SDEV435-81 Capstone Project
    LeftColumnContent.cpp
    Purpose: Code file for the LeftColumnContent class.  This class
      creates a space for displaying content in the left column of
      the Garden Space Planner program's GUI.  This area holds a list
      of plants user can select to edit or drop into a garden map.

    @author Jeremiah Kellogg
    @version 2.0.0 01/02/20
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

  GetSelectedPlant(); //Not calling this function in the constructor causes odd behavior that should probably be investigated.
}

//Default Destructor.
LeftColumnContent::~LeftColumnContent() { }

//Add a Scrollbar in the left column.
void LeftColumnContent::AddScrollBar()
{
  m_scrollBar = &ptrAddress;
  m_scrollBar->SetView(m_leftColumnView);
  m_scrollBar->SetContainerSize({m_leftColumnView.getSize().x * .07f, m_displayArea.getSize().y});
  m_scrollBar->SetContainerPos({m_displayArea.getPosition().x + (m_displayArea.getSize().x - m_scrollBar->GetContainerSize().x), m_displayArea.getPosition().y});
  m_scrollBar->SetContainerColor(sf::Color(220, 220, 220, 255));

  m_screenToViewRatio = m_displayArea.getSize().y / m_leftColumnView.getSize().y; //Used for properly sizing scrollbar slider.

  m_scrollBar->SetElementSize({m_scrollBar->GetContainerSize().x * .75f, m_leftColumnView.getSize().y / m_screenToViewRatio});
  m_scrollBar->SetScrollMin();
  m_scrollBar->SetScrollMax();
  m_scrollBar->SetElementPos(m_scrollBar->GetScrollMin());
  m_scrollBar->SetElementColor(sf::Color(175, 175, 175, 255));
  m_scrollBar->SetCenterScreen(m_leftColumnView.getSize().x / 2.f, (m_leftColumnView.getSize().y / 2.f));
}

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

//Draws the m_displayArea, m_scrollBar pointer, m_plantContainer, m_plantTxtName, m_plantTxtVariety, and m_plantTxtSpacing object to the window.
void LeftColumnContent::Draw(sf::RenderWindow &window, sf::Event event)
{
  window.draw(m_displayArea);
  m_scrollBar->Draw(window);
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

//Returns a pointer to a ScrollBar object that's used for calling ScrollBar class functions.
ScrollBar* LeftColumnContent::GetScrollBar()
{
  return m_scrollBar;
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
