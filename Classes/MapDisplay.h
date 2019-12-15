/**
    SDEV435-81 Capstone Project
    MapDisplay.h
    Purpose: Header file for the MapDisplay class.  This class
      creates an object that can be used to handle what user
      selected map should be displayed and what tiles should
      be displayed on that map.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "ContentContainer.h"
#include "Plant.h"
#include "Tile.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

class MapDisplay
{

public:

  //Default Constructor: sets defaults for m_display, m_gridUnitSize, m_gridUnit, m_viewSpeed, and m_tileSelector objects.
  MapDisplay();

  //Default Destructor.
  ~MapDisplay();

  /**
    Sets value for m_display variable to determine if the MapDisplay object should be displayed or not.

    @param display The value that should be passed to the m_display variable to determine if the MapDisplay object should be displayed or not.
  */
  void SetDisplay(bool display);

  /**
    Returns the value for m_display variable that determines if the MapDisplay object should be displayed or not.
  */
  bool GetDisplay();

  /**
    Sets the user created map to be displayed, and what view to display it in.

    @param &map References the map object the user has selected to be displayed.
    @param &view References the view the map the user selected should be diplayed in.
  */
  void SetMap(Map &map, sf::View &view);

  /**
    Returns the Map object data from MySQL garden_space_planner database in the maps table that was most recently instantiated.
  */
  Map GetNewMap();

  /**
    Returns the Map object most currently assigned to m_map.
  */
  Map GetMap();

  /**
    Draws grid to the window and sets the m_tileSelector object size.

    @param &window References the window the map should be drawn to.
  */
  void DrawMap(sf::RenderWindow &window);

  /**
    Draws all tiles associated with the map to the window.

    @param &window References the window the tiles should be drawn to.
  */
  void DrawTiles(sf::RenderWindow &window);

  /**
    Updates what keys were pressed by user for moving the view over the map/content.

    @param &view References the view to scroll over the map as the user presses keys to navigate.
    @param dt The delta time for animation.
  */
  void UpdateKeys(sf::View &view, float dt);

  /**
    Updates mouse position in the view and assigns the m_tileSelector object to be drawn to that location.

    @param &window References the window object the mouse is moving in.
    @param &view References the view the mouse position will need to be mapped to.
  */
  void UpdateMouse(sf::RenderWindow &window, sf::View &view);

  /**
    Returns true or false depending on whether the mouse is in bounds of the view (recreated position using a ContentContainer object).

    @param &window References the window object the mouse is moving in.
    @param &container References the map ContentContainer object for establishing boundaries of the view.
    @param &navbar References the mapNavBar ContentContainer object to remove from the view boundary (so it's position is static).
  */
  bool MouseInBounds(sf::RenderWindow &window, ContentContainer &container, ContentContainer &navbar);

  /**
    Instantiates a tile using m_plant object data and submits it to the MySQL garden_space_planner database tiles table.
  */
  void BuildTile();

  /**
    Removes tile from the map and the database.

    @param &window References the window object needed for detecting mouseovers.
    @param &view References the view needed for mapping mouse postion to the view.
  */
  void RemoveTile(sf::RenderWindow &window, sf::View &view);

  /**
    Removes currently displaying map from the MySQL garden_space_planner database in the maps table.
  */
  void DeleteMap();

private:
  bool m_display; //Member varaible for keeping track of when a map has been selected to display.
  Map m_map; //For holding map object data.
  Plant m_plant; //For holding plant object data.
  int m_currentPlantID; //Member variable for holding currently selected plant's database ID.
  int m_previousPlantID;  //Member variable for holding plant ID for object selected previous to the currently selected plant.
  float m_gridUnitSize;  //Member variable for storing the size of a single square block in the grid.
  sf::RectangleShape m_gridUnit;  //Object for storing a grid square
  float m_viewSpeed;  //Member variable for how fast the view will scroll over a map.
  sf::RectangleShape m_tileSelector;  //Object showing size a plant will take up on the grid (and follows the mouse position).
  sf::Vector2i m_mousePosWindow;  //Object for storing x and y coordinate the mouse is at in the window.
  sf::Vector2f m_mousePosView;  //Object for storing x and y coordinate the mouse is at in the view.
  sf::Vector2u m_mousePosGrid;  //Object for storing x and y position the mouse is at in the grid.
  Tile m_tile;  //Object for storing tile information.
  std::vector<Tile> m_tileList;  //List of tiles that should be displayed by teh MapDisplay object.

  //Pointers to MySQL Connector/C++ objects needed for communication with the MySQL garden_space_planner database.
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;

  /**
    Instantiates an m_plant object for the most currently selected plant.
  */
  void SetPlant();

  /**
    Grabs tiles from database associated with currently selected map and pushes them to the m_tileList vector.

    @param mapID The map ID for the map the tiles belong to.
  */
  void SetTiles(int mapID);

  /**
    Removes specified tile from the map and the MySQL garden_space_planner database in the tiles table.

    @param tileid The database ID for the tile to be removed.
  */
  void RemoveFromDb(int tileid);
};
