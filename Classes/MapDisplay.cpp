/**
    SDEV435-81 Capstone Project
    MapDisplay.cpp
    Purpose: Code file for the MapDisplay class.  This class
      creates an object that can be used to handle what user
      selected map should be displayed and what tiles should
      be displayed on that map.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#include "MapDisplay.h"

/***********Public Functions************/

//Default Constructor: sets defaults for m_display, m_gridUnitSize, m_gridUnit, m_viewSpeed, and m_tileSelector objects.
MapDisplay::MapDisplay()
{
  m_display = false;
  m_gridUnitSize = 100.f;
  m_gridUnit.setSize({m_gridUnitSize, m_gridUnitSize});
  m_gridUnit.setOutlineColor(sf::Color(86, 225, 58, 255));
  m_gridUnit.setOutlineThickness(1.f);
  m_viewSpeed = 450.f;
  m_tileSelector.setSize({m_gridUnitSize, m_gridUnitSize});
  m_tileSelector.setFillColor(sf::Color::Transparent);
  m_tileSelector.setOutlineColor(sf::Color::Black);
  m_tileSelector.setOutlineThickness(1.f);
}

//Default Destructor.
MapDisplay::~MapDisplay() { }

//Sets value for m_display variable to determine if the MapDisplay object should be displayed or not.
void MapDisplay::SetDisplay(bool display)
{
  m_display = display;
}

//Returns the value for m_display variable that determines if the MapDisplay object should be displayed or not.
bool MapDisplay::GetDisplay()
{
  return m_display;
}

//Sets the user created map to be displayed, and what view to display it in.
void MapDisplay::SetMap(Map &map, sf::View &view)
{
  m_map = map;
  SetTiles(m_map.GetMapID());
  view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
}

//Returns the Map object data from MySQL garden_space_planner database in the maps table that was most recently instantiated.
Map MapDisplay::GetNewMap()
{
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT * FROM maps ORDER BY map_id DESC LIMIT 1;"); //SQL Query to get most recently created map by listing maps table in descending order.

  while (res->next()) {
    m_map.SetMapID(res->getInt("map_id"));
    m_map.SetName(res->getString("map_name"));
    m_map.SetYear(res->getString("map_year"));
    m_map.SetLength(res->getInt("map_length"));
    m_map.SetWidth(res->getInt("map_width"));
  }
  delete con;
  delete stmt;
  delete res;

  return m_map;
}

//Returns the Map object most currently assigned to m_map.
Map MapDisplay::GetMap()
{
  return m_map;
}

//Draws grid to the window and sets the m_tileSelector object size.
void MapDisplay::DrawMap(sf::RenderWindow &window)
{
  SetPlant();
  m_tileSelector.setSize({static_cast<float>(m_plant.GetRowSpacing()) * m_gridUnitSize, static_cast<float>(m_plant.GetRowSpacing()) * m_gridUnitSize});
  for(int i = 0; i < m_map.GetLength(); i++)
  {
    for(int j = 0; j < m_map.GetWidth(); j++)
    {
      m_gridUnit.setPosition(i * m_gridUnitSize, j * m_gridUnitSize);
      window.draw(m_gridUnit);
    }
  }
  window.draw(m_tileSelector);
}

//Draws all tiles associated with the map to the window.
void MapDisplay::DrawTiles(sf::RenderWindow &window)
{
  if(m_tileList.size() > 0)
  {
    for(int i = 0; i < m_tileList.size(); i++)
    {
      m_tileList[i].Draw(window);
    }
  }
}

//Updates what keys were pressed by user for moving the view over the map/content.
void MapDisplay::UpdateKeys(sf::View &view, float dt)
{
  float gridLength = m_gridUnitSize * m_map.GetLength();
  float minGridPosX = view.getSize().x / 2;
  float maxGridPosX = (view.getCenter().x * (gridLength/view.getCenter().x)) - minGridPosX;

  float gridWidth = m_gridUnitSize * m_map.GetWidth();
  float minGridPosY = view.getSize().y / 2;
  float maxGridPosY = (view.getCenter().y * (gridWidth/view.getCenter().y)) - minGridPosY;

  if(view.getCenter().x >= minGridPosX && view.getCenter().x <= maxGridPosX + 30)
  {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      view.move(-m_viewSpeed * dt, 0.f);
      if(view.getCenter().x <= minGridPosX)
      {
        view.setCenter(minGridPosX, view.getCenter().y);
      }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      view.move(m_viewSpeed * dt, 0.f);
      if(view.getCenter().x >= maxGridPosX)
      {
        view.setCenter(maxGridPosX, view.getCenter().y);
      }
    }
  }
  if(view.getCenter().y >= minGridPosY && view.getCenter().y <= maxGridPosY + 30)
  {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      view.move(0.f, -m_viewSpeed * dt);
      if(view.getCenter().y <= minGridPosY)
      {
        view.setCenter(view.getCenter().x, minGridPosY);
      }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      view.move(0.f, m_viewSpeed * dt);
      if(view.getCenter().y >= maxGridPosY)
      {
        view.setCenter(view.getCenter().x, maxGridPosY);
      }
    }
  }
}

//Updates mouse position in the view and assigns the m_tileSelector object to be drawn to that location.
void MapDisplay::UpdateMouse(sf::RenderWindow &window, sf::View &view)
{
  m_mousePosWindow = sf::Mouse::getPosition(window);//Grab mouse position in the Window.
  window.setView(view);
  m_mousePosView = window.mapPixelToCoords(m_mousePosWindow);//Map the window mouse position to the view.
  if(m_mousePosView.x >= 0.f)
  {
    m_mousePosGrid.x = m_mousePosView.x / m_gridUnitSize;
  }
  if(m_mousePosView.y >= 0.f)
  {
    m_mousePosGrid.y = m_mousePosView.y / m_gridUnitSize;
  }

  m_tileSelector.setPosition(m_mousePosGrid.x * m_gridUnitSize, m_mousePosGrid.y * m_gridUnitSize);
}

//Returns true or false depending on whether the mouse is in bounds of the view (recreated position using a ContentContainer object).
bool MapDisplay::MouseInBounds(sf::RenderWindow &window, ContentContainer &container, ContentContainer &navbar)
{
  m_mousePosWindow = sf::Mouse::getPosition(window);
  if(m_mousePosWindow.x >= container.GetPosition().x  && m_mousePosWindow.x <= container.GetPosition().x + container.GetSize().x && m_mousePosWindow.y >= container.GetPosition().y + navbar.GetSize().y && m_mousePosWindow.y <= container.GetPosition().y + container.GetSize().y)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//Instantiates a tile using m_plant object data and submits it to the MySQL garden_space_planner database tiles table.
void MapDisplay::BuildTile()
{
  SetPlant();
  int plantNumber = (m_plant.GetRowSpacing() * 12) / m_plant.GetSpacing();
  m_tile.SetTileSize(m_tileSelector.getSize());
  m_tile.SetTilePosition(m_tileSelector.getPosition());
  m_tile.SetTileColor(sf::Color(m_plant.GetRed(), m_plant.GetGreen(), m_plant.GetBlue()));
  m_tile.SetText(m_plant.GetVariety(), m_plant.GetName(), plantNumber);

  m_tile.SubmitToDb(m_map.GetMapID(), m_plant.GetID(), m_tileSelector.getPosition().x, m_tileSelector.getPosition().y);

  m_tileList.push_back(m_tile);
}

//Removes tile from the map and the database.
void MapDisplay::RemoveTile(sf::RenderWindow &window, sf::View &view)
{
  for(int i = 0; i < m_tileList.size(); i++)
  {
    if (m_tileList[i].MouseOverTile(window, view))
    {
      RemoveFromDb(m_tileList[i].GetTileID());
      m_tileList.erase(m_tileList.begin()+i);
    }
  }
}

//Removes currently displaying map from the MySQL garden_space_planner database in the maps table.
void MapDisplay::DeleteMap()
{
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  prep_stmt = con->prepareStatement("DELETE FROM tiles WHERE map_id=?");
  prep_stmt->setInt(1, m_map.GetMapID());
  prep_stmt->executeUpdate();
  delete con;
  delete prep_stmt;
  m_tileList.clear();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  prep_stmt = con->prepareStatement("DELETE FROM maps WHERE map_id=? LIMIT 1");
  prep_stmt->setInt(1, m_map.GetMapID());
  prep_stmt->execute();
  delete con;
  delete prep_stmt;
}

/***********Private Functions************/

//Instantiates an m_plant object for the most currently selected plant.
void MapDisplay::SetPlant()
{
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT * FROM plants WHERE is_selected=true");
  while(res->next())
  {
    m_currentPlantID = res->getInt("plant_id");
    if(m_currentPlantID != m_previousPlantID)
    {
      m_plant.SetID(res->getInt("plant_id"));
      m_plant.SetName(res->getString("plant_name"));
      m_plant.SetVariety(res->getString("plant_variety"));
      m_plant.SetSpacing(res->getInt("plant_spacing_width"));
      m_plant.SetRowSpacing(res->getInt("plant_spacing_length"));
      m_plant.SetRGBColors(res->getInt("red_color_value"), res->getInt("green_color_value"), res->getInt("blue_color_value"));
      m_previousPlantID = m_currentPlantID;
    }
  }

  delete stmt;
  delete con;
}

//Grabs tiles from database associated with currently selected map and pushes them to the m_tileList vector.
void MapDisplay::SetTiles(int mapID)
{
  m_tileList.clear();
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  prep_stmt = con->prepareStatement("SELECT * FROM tiles JOIN maps ON tiles.map_id = ? JOIN plants ON tiles.plant_id = plants.plant_id");
  prep_stmt->setInt(1, mapID);
  res = prep_stmt->executeQuery();

  while(res->next())
  {
    int plantNumber = (res->getInt("plant_spacing_length") * 12) / res->getInt("plant_spacing_width");
    m_tileSelector.setSize({static_cast<float>(m_plant.GetRowSpacing()) * m_gridUnitSize, static_cast<float>(m_plant.GetRowSpacing()) * m_gridUnitSize});
    m_tile.SetTileSize({static_cast<float>(res->getInt("plant_spacing_length")) * m_gridUnitSize, static_cast<float>(res->getInt("plant_spacing_length")) * m_gridUnitSize}/*m_tileSelector.getSize()*/);
    m_tile.SetTilePosition({static_cast<float>(res->getInt("xpos")), static_cast<float>(res->getInt("ypos"))});
    m_tile.SetTileColor(sf::Color(res->getInt("red_color_value"), res->getInt("green_color_value"), res->getInt("blue_color_value")));
    m_tile.SetText(res->getString("plant_variety"), res->getString("plant_name"), plantNumber);
    m_tile.SetTileID(res->getInt("tile_id"));

    m_tileList.push_back(m_tile);
  }
  delete con;
  delete prep_stmt;
}

//Removes specified tile from the map and the MySQL garden_space_planner database in the tiles table.
void MapDisplay::RemoveFromDb(int tileid)
{
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  prep_stmt = con->prepareStatement("DELETE FROM tiles WHERE tile_id=? LIMIT 1");
  prep_stmt->setInt(1, tileid);
  prep_stmt->executeUpdate();
  delete con;
  delete prep_stmt;
}
