/**
  Garden Space Planner
  SelectMap.cpp
  Purpose: Source code for the SelectMap class.  This class inherits from the Content
  Class.  The SelectMap class is used to build an object that displays a screen where
  users can select maps they've already created to edit.

  @author Jeremiah Kellogg
  @version 1.0.0 12/26/19
*/

#include "SelectMap.h"

SelectMap::SelectMap()
{
  m_isScrolling = false;
  m_firstClick = false;

  m_mapTxtName.setFont(m_ubuntu);
  m_mapTxtName.setFillColor(sf::Color::Black);
  m_mapTxtYear.setFont(m_ubuntu);
  m_mapTxtYear.setFillColor(sf::Color::Black);
  m_mapTxtLength.setFont(m_ubuntu);
  m_mapTxtLength.setFillColor(sf::Color::Black);
  m_mapTxtWidth.setFont(m_ubuntu);
  m_mapTxtWidth.setFillColor(sf::Color::Black);
}

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
  UpdateScrollArea();
  SetMapContainerVector();

  window.draw(m_displayArea);
  window.draw(m_scrollContainer);
  window.draw(m_scrollElement);

  //Loop through map list and draw available maps to the window
  for(int i = 0; i < m_mapContainerList.size(); i++)
  {
    if(MouseOverMapContainer(window))
    {
      m_mapSelectContainer.setFillColor(sf::Color(238, 244, 177, 255));
      if(event.mouseButton.button == sf::Mouse::Left)
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


/*************************Function specific to Scrollbar******************************/

//Set the view the Content object is associated with.
void SelectMap::SetView(sf::View &view)
{
  m_contentView = view;
}

/*Sets the size of m_mapSelectContainer data member and sets the size and position of the m_displayArea data member
  based on the m_contentView data member sf::View object.*/
void SelectMap::AddScrollArea()
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
  m_scrollContainer.setSize({m_contentView.getSize().x * .02f, m_displayArea.getSize().y});
  m_scrollContainer.setPosition({m_displayArea.getPosition().x + (m_displayArea.getSize().x - m_scrollContainer.getSize().x), m_displayArea.getPosition().y});
  m_scrollContainer.setFillColor(sf::Color(220, 220, 220, 255));

  m_screenToViewRatio = m_displayArea.getSize().y / m_contentView.getSize().y;

  m_scrollElement.setSize({m_scrollContainer.getSize().x * .75f, m_contentView.getSize().y / m_screenToViewRatio});
  m_scrollMinimum.x = m_scrollContainer.getPosition().x * 1.0032f;
  m_scrollMinimum.y =  m_scrollContainer.getPosition().y;
  m_scrollMaximum.x = m_scrollContainer.getPosition().x * 1.01f;
  m_scrollMaximum.y = m_scrollContainer.getGlobalBounds().height;
  m_scrollElement.setPosition(m_scrollMinimum);
  m_scrollElement.setFillColor(sf::Color(175, 175, 175, 255));
  m_centerScreen.setPosition(m_contentView.getSize().x / 2.f, (m_contentView.getSize().y / 2.f));
}

//Returns a boolean value indicating whether or not the user's mouse is hovering over the scrollbar.
bool SelectMap::MouseOverScroll(sf::RenderWindow &window)
{
  sf::Vector2i mouseWindowPosition = sf::Mouse::getPosition(window);  //Mouse position in relation to the screen, does not account for accurate mouse view positions
  sf::Vector2f mouseViewPosition = window.mapPixelToCoords(mouseWindowPosition); //This is necessary for getting accurate mouse view positions, which have their own coordinates
  //Accounts for weird offset that was happening for currently undetermined reasons
  float offset = window.getSize().x * .304;
  mouseViewPosition.x -= offset;

  float scrollPosX = m_scrollElement.getPosition().x;
  float scrollXPosWidth = scrollPosX + m_scrollElement.getGlobalBounds().width;

  if(mouseViewPosition.x < scrollXPosWidth && mouseViewPosition.x > scrollPosX && mouseViewPosition.y < m_scrollElement.getPosition().y + m_scrollElement.getSize().y && mouseViewPosition.y > m_scrollContainer.getPosition().y)
  {
    return true;
  }
  return false;
}

//Sets the color of the scrollbar (used for changing color when the user clicks on the scrollbar).
void SelectMap::ChangeColor(sf::Color color)
{
  m_scrollElement.setFillColor(color);
}

//Sets whether or not the user is currently using the scroll bar.
void SelectMap::SetScrolling(bool toScroll)  //*******MOVE TO SelectMap CLASS**********/
{
  m_isScrolling = toScroll;
}

//Returns the value for the boolean data member m_isScrolling to indicate whether a user is trying to scroll or not.
bool SelectMap::GetScrolling()  //*******MOVE TO SelectMap CLASS**********/
{
  return m_isScrolling;
}

/*Sets whether or not the user is initializing scroll functionality from a state where they were not using the scrollbar.
  This value is saved to the boolean data member m_firstClick.*/
void SelectMap::SetFirstClick(bool click)
{
  m_firstClick = click;
}

//Returns the value for the boolean data member m_firstClick to indicate whether a user has clicked on the scrollbar or not.
bool SelectMap::GetFirstClick()
{
  return m_firstClick;
}

//Returns sf::Vector2f object containing x and y coordinate for the current scrollbar position.
sf::Vector2f SelectMap::GetScrollPosition(ContentContainer &container)
{
  return {m_centerScreen.getPosition().x, m_centerScreen.getPosition().y};
}

//Updates size and position of scroll area when a new Map object is added to or removed from the m_mapsList vector.
void SelectMap::UpdateScrollArea()
{
  m_mapSelectContainer.setSize({m_contentView.getSize().x - (m_contentView.getSize().x * .02f), m_contentView.getSize().y / 4});
  m_displayArea.setSize({m_contentView.getSize().x, m_mapSelectContainer.getSize().y * m_mapList.size()});
  m_scrollContainer.setSize({m_contentView.getSize().x * .02f, m_displayArea.getSize().y});
  m_scrollElement.setSize({m_scrollContainer.getSize().x * .75f, m_contentView.getSize().y / m_screenToViewRatio});
  m_scrollMinimum.x = m_scrollContainer.getPosition().x * 1.0032f;
  m_scrollMinimum.y =  m_scrollContainer.getPosition().y;
  m_scrollMaximum.x = m_scrollContainer.getPosition().x * 1.01f;
  m_scrollMaximum.y = m_scrollContainer.getGlobalBounds().height;
}

//Updates position of scroll bar and centered position of the view on each loop.
void SelectMap::Scroll(sf::RenderWindow &window) //*******MOVE TO SelectMap CLASS**********/
{
  sf::Vector2i mouseWindowPostion = sf::Mouse::getPosition(window);
  sf::Vector2f mouseViewPosition = window.mapPixelToCoords(mouseWindowPostion);

  mouseYNew = mouseViewPosition.y;

  if(m_firstClick)
  {
    m_offset = mouseYNew - m_scrollElement.getPosition().y;
  }

  //Algorithm for determining how fast the view should scroll in relation to scrollbar movement
  float viewScrollSpeed = (m_scrollContainer.getSize().y - m_contentView.getSize().y) / (m_scrollContainer.getSize().y - m_scrollElement.getSize().y);

  //Instructions for when mouse and scrollbar are in bounds of the scrollbar container
  if(mouseYNew - m_offset > m_scrollContainer.getPosition().y && mouseYNew - m_offset < m_scrollContainer.getSize().y - m_scrollElement.getSize().y)
  {
    m_scrollElement.setPosition(m_scrollElement.getPosition().x, mouseYNew - m_offset);
    m_centerScreen.setPosition(m_contentView.getSize().x / 2.f, m_contentView.getSize().y / 2 + m_scrollElement.getPosition().y * viewScrollSpeed);
  }
  //Instructions for stopping scrollbar from going past the max position of the scrollbar container
  else if(mouseYNew - m_offset > m_scrollContainer.getSize().y)
  {
    m_scrollElement.setPosition(m_scrollMaximum);
    m_centerScreen.setPosition(m_contentView.getSize().x / 2.f, (m_contentView.getSize().y / 2.f) + m_scrollMaximum.y);
  }
  //Instructions for stopping scrollbar from going past the min position of the scrollbar container
  else if (mouseYNew - m_offset < m_scrollContainer.getPosition().y)
  {
    m_scrollElement.setPosition(m_scrollMinimum);
    m_centerScreen.setPosition(m_contentView.getSize().x / 2.f, (m_contentView.getSize().y / 2.f));
  }

  m_firstClick = false; //First click has done it's job after first loop so it's set to false
}
