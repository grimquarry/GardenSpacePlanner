/**
  Garden Space Planner
  SelectMap.cpp
  Purpose: Source code for the SelectMap class.  This class inherits from the Content
  Class.  The SelectMap class is used to build an object that displays a screen where
  users can select maps they've already created to edit.

  @author Jeremiah Kellogg
  @version 2.1.1 01/19/2020
*/

#include "SelectMap.h"

//Default Constructor
SelectMap::SelectMap() { }

//Constructor
SelectMap::SelectMap(sf::View &view)
{
  m_contentView = view;

  m_mapTxtName.setFont(m_ubuntu);
  m_mapTxtName.setFillColor(sf::Color::Black);
  m_mapTxtYear.setFont(m_ubuntu);
  m_mapTxtYear.setFillColor(sf::Color::Black);
  m_mapTxtLength.setFont(m_ubuntu);
  m_mapTxtLength.setFillColor(sf::Color::Black);
  m_mapTxtWidth.setFont(m_ubuntu);
  m_mapTxtWidth.setFillColor(sf::Color::Black);

  SetStopMapView(false);
}

//Destructor
SelectMap::~SelectMap() { }

//Populates the m_mapList vector with a list of maps from the MySQL database.
void SelectMap::SetMapList()
{
  m_mapList.clear();
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT * FROM maps");

  while (res->next())
  {
    m_map.SetMapID(res->getInt("map_id"));
    m_map.SetName(res->getString("map_name"));
    m_map.SetYear(res->getString("map_year"));
    m_map.SetLength(res->getInt("map_length"));
    m_map.SetWidth(res->getInt("map_width"));

    m_mapList.push_back(m_map);
  }

  delete res;
  delete stmt;
  delete con;
}

//Add clickable containers that hold map data to the m_mapContainerList vector.
void SelectMap::SetMapContainerVector()
{
  m_mapContainerList.clear();
  m_mapContainerDisplayPos = (m_displayArea.getPosition());

  for(int i = 0; i < m_mapList.size(); i++)
  {
    m_mapContainerList.push_back(m_mapContainerDisplayPos);
    m_mapContainerDisplayPos.y += m_mapSelectContainer.getSize().y;
  }
}

/*Returns a boolean value indicating whether or not the user's mouse is hovering over an sf::RectangleShape m_mapContainer object
  that's used to contain map data for listing in the select map screen.*/
bool SelectMap::MouseOverMapContainer(sf::RenderWindow &window)
{
  sf::Vector2i mouseWindowPostion = sf::Mouse::getPosition(window);  //Mouse position in relation to the screen, does not account for accurate mouse view positions
  sf::Vector2f mouseViewPosition = window.mapPixelToCoords(mouseWindowPostion); //This is necessary for getting accurate mouse view positions, which have their own coordinates
  mouseViewPosition.y -= m_mapSelectContainer.getSize().y;

  float containerPosX = m_mapSelectContainer.getPosition().x;
  float containerPosY = m_mapSelectContainer.getPosition().y;

  float containerXPosWidth = containerPosX + m_mapSelectContainer.getGlobalBounds().width;
  float containerYPosHeight = containerPosY + m_mapSelectContainer.getGlobalBounds().height;

  if(mouseViewPosition.x < containerXPosWidth && mouseViewPosition.x > containerPosX && mouseViewPosition.y < containerYPosHeight && mouseViewPosition.y > containerPosY)
  {
    return true;
  }
  return false;
}

//Draws the list of user created maps the user can choose from to the sf::View contentView object in the sf::RenderWindow mainWindow object.
void SelectMap::DrawMapMenu(sf::RenderWindow &window, sf::Event &event, MapDisplay &display, sf::View &view)
{
  //Update lists and sizes in case a map was added or deleted
  SetMapList();
  m_scrollBar->UpdateScrollArea(m_mapSelectContainer, m_displayArea, m_mapList, m_screenToViewRatio);
  SetMapContainerVector();

  window.draw(m_displayArea);
  m_scrollBar->Draw(window);

  //Loop through map list and draw available maps to the window
  for(int i = 0; i < m_mapContainerList.size(); i++)
  {
    if(MouseOverMapContainer(window) && !m_scrollBar->GetScrolling())
    {
      m_mapSelectContainer.setFillColor(sf::Color(238, 244, 177, 255));
      if(event.mouseButton.button == sf::Mouse::Left && !StopMapView())
      {
        display.SetDisplay(true);
        display.SetMap(m_mapList[i], view);
      }
    }
    else
    {
      m_mapSelectContainer.setFillColor(sf::Color(228, 243, 127, 255));
    }

    m_mapSelectContainer.setPosition(m_mapContainerList[i]);

    m_mapTxtName.setString(m_mapList[i].GetName());
    m_mapTxtName.setPosition((m_mapSelectContainer.getSize().x / 2) - (m_mapTxtName.getGlobalBounds().width / 2), (m_mapContainerList[i].y + ( m_mapSelectContainer.getSize().y / 4)) - (m_mapTxtName.getGlobalBounds().height));

    m_mapTxtYear.setString("(" + m_mapList[i].GetYear() + ")");
    m_mapTxtYear.setPosition((m_mapSelectContainer.getSize().x / 2) - (m_mapTxtYear.getGlobalBounds().width / 2), (m_mapContainerList[i].y + ( m_mapSelectContainer.getSize().y / 3)));

    std::string mapLength = std::to_string(m_mapList[i].GetLength());
    std::string mapWidth = std::to_string(m_mapList[i].GetWidth());
    m_mapTxtLength.setString(mapLength + " x " + mapWidth);
    m_mapTxtLength.setPosition((m_mapSelectContainer.getSize().x / 2) - (m_mapTxtLength.getGlobalBounds().width / 2), (m_mapContainerList[i].y + ( m_mapSelectContainer.getSize().y / 2)) + (m_mapTxtLength.getGlobalBounds().height));

    window.draw(m_mapSelectContainer);
    window.draw(m_mapTxtName);
    window.draw(m_mapTxtYear);
    window.draw(m_mapTxtLength);
  }
}

/*Sets the size of m_mapSelectContainer data member and sets the size and position of the m_displayArea data member
  based on the m_contentView data member sf::View object.*/
void SelectMap::AddDisplayArea()
{
  m_mapSelectContainer.setSize({m_contentView.getSize().x - (m_contentView.getSize().x * .02f), m_contentView.getSize().y / 4});
  m_mapSelectContainer.setOutlineColor(sf::Color(42, 85, 34, 255));
  m_mapSelectContainer.setOutlineThickness(1.f);

  m_displayArea.setFillColor(sf::Color::White);
  m_displayArea.setSize({m_contentView.getSize().x, m_mapSelectContainer.getSize().y * m_mapList.size()});
  m_displayArea.setPosition({0.f, 0.f});
  m_displayArea.setOutlineColor(sf::Color::Red);
  m_displayArea.setOutlineThickness(1.f);
}

//Adds scrollbar functionality and objects to the screen users can select maps from.
void SelectMap::AddScrollBar()
{
  m_scrollBar = &ptrAddress;
  m_scrollBar->SetView(m_contentView);
  m_scrollBar->SetContainerSize({m_contentView.getSize().x * .02f, m_displayArea.getSize().y});
  m_scrollBar->SetContainerPos({m_displayArea.getPosition().x + (m_displayArea.getSize().x - m_scrollBar->GetContainerSize().x), m_displayArea.getPosition().y});
  m_scrollBar->SetContainerColor(sf::Color(220, 220, 220, 255));

  m_screenToViewRatio = m_displayArea.getSize().y / m_contentView.getSize().y; //Used for properly sizing scrollbar slider.

  m_scrollBar->SetElementSize({m_scrollBar->GetContainerSize().x * .75f, m_contentView.getSize().y / m_screenToViewRatio});
  m_scrollBar->SetScrollMin();
  m_scrollBar->SetScrollMax();
  m_scrollBar->SetElementPos(/*m_scrollBar->GetScrollMin()*/{m_scrollBar->GetScrollMin().x -12.f, m_scrollBar->GetScrollMin().y}); //The -12 is an offset that I'm not sure why is needed.
  m_scrollBar->SetElementColor(sf::Color(175, 175, 175, 255));
  m_scrollBar->SetCenterScreen(m_contentView.getSize().x / 2.f, (m_contentView.getSize().y / 2.f));
}

//Returns a pointer to a ScrollBar object used for calling ScrollBar class functions.
ScrollBar* SelectMap::GetScrollBar()
{
  return m_scrollBar;
}

/*Set the value for stopping a map view from displaying.  Used to keep a map view from accidentally
  opened when the cursor is over a m_mapSelectContainer and the user stops scrolling.*/
void SelectMap::SetStopMapView(bool stop)
{
  m_stopMapView = stop;
}

/*Returns true or false to determine if a MapView should be stopped from opening.
  Used to stop a mapview from displaying when a user is hovering over a m_mapSelectContainer
  while scrolling and released the mouse button.*/
bool SelectMap::StopMapView()
{
  return m_stopMapView;
}
