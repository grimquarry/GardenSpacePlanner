/**
    SDEV435-81 Capstone Project
    Plant.h
    Purpose: Header file for the Tile class.  This class creates tile
      objects associated with specific maps.  Each object has its
      data stored in the tiles table of the MySQL garden_space_planner
      database.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

class Tile
{
public:

  //Default Constructor that sets default for all sf::RectangleShape and sf::Text objects.
  Tile();

  //Default Destructor.
  ~Tile();

  /**
    Set the size of a tile.

    @param tilesize An sf::Vector2f holding the length and width values of the tile.
  */
  void SetTileSize(sf::Vector2f tilesize);

  /**
    Set the position of a tile.

    @param tileposition An sf::Vector2f holding the x and y coordinates of the tile's position.
  */
  void SetTilePosition(sf::Vector2f tileposition);

  /**
    Returns an sf::Vector2f with the x and y coordinates of a tile's position.
  */
  sf::Vector2f GetTilePosition();

  /**
    Returns an sf::Vector2f with the length and width of a tile.
  */
  sf::Vector2f GetTileSize();

  /**
    Set's the color of the tile container m_tileContainer.

    @param color The color to set the m_tileContainer fill color to.
  */
  void SetTileColor(sf::Color color);

  /**
    Set's the values for the m_plantName, m_plantVariety, and m_plantNumber object for displaying plant info on the tile.

    @param plantvariety The plant's variety.
    @param plantname The name of the plant.
    @param number The number of plants that fit in a tile.
  */
  void SetText(std::string plantvariety, std::string plantname, int number);

  /**
    Returns true or false depending on where the mouse is hovering over the tile or not.

    @param &window The sf::RenderWindow object where the mouse movement should be polled.
    @param plantname The sf::View object needed to map coordinates from the window to the view.
  */
  bool MouseOverTile(sf::RenderWindow &window, sf::View &view);

  /**
    Submit newly instantiated tile to the MySQL garden_space_planner database tiles table.

    @param parentmapid From the maps table map_id column (the map the tile belongs to).
    @param plantidThe From the plants table plant_id column (the plant the tile is supposed to represent).
    @param xpos The x coordinate of the tile position.
    @param ypos The y coordinate of the tile position.
  */
  void SubmitToDb(int parentmapid, int plantid, int xpos, int ypos);

  /**
    Returns the database id stored in the m_tileID member variable.
  */
  int GetTileID();

  /**
    Stores a value for the tile id in the m_tileID member variable.

    @param id The ID number from the tile_id column of the tiles table in the MySQL garden_space_planner database.
  */
  void SetTileID(int id);

  /**
    Draws the sf::RectangleShape m_tileContainer and m_textContainer objects, and sf::Text m_plantVariety, m_plantName and m_plantName objects to the window.

    @param &window References the window that should be drawn to.
  */
  void Draw(sf::RenderWindow &window);



private:
  sf::RectangleShape m_tileContainer;  //Contains and gives borders to a tile.
  sf::RectangleShape m_textContainer;  //Contains and gives borders to the text in a tile.
  sf::Text m_plantName;  //The name of the plant the tile represents.
  sf::Text m_plantVariety;  //The variety of the plant the tile represents.
  sf::Text m_plantNumber;  //The number of plants that fit in a tile.
  sf::Vector2f m_tileSize;  //Length and Width of a tile.
  sf::Vector2f m_tilePosition;  // X and y coordinates where a tile is positioned.
  sf::Font m_tahoma;  //Object holding font data for the tahoma font.
  int m_tileID;  //The tile's ID pulled from the tiles table tile_id column.

  //Pointers to MySQL Connector/C++ objects needed for communication with the MySQL database.
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;
};
