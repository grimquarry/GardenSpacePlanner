/**
    SDEV435-81 Capstone Project
    Plant.cpp
    Purpose: Code file for the Tile class.  This class creates tile
      objects associated with specific maps.  Each object has its
      data stored in the tiles table of the MySQL garden_space_planner
      database.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#include "Tile.h"

//Default Constructor that sets default for all sf::RectangleShape and sf::Text objects.
Tile::Tile()
{
  m_tileContainer.setOutlineColor(sf::Color::Black);
  m_tileContainer.setOutlineThickness(1);
  m_textContainer.setFillColor(sf::Color::White);
  m_textContainer.setOutlineColor(sf::Color::Black);
  m_textContainer.setOutlineThickness(1);
  if(!m_tahoma.loadFromFile("Fonts/Tahoma.ttf"))
  {
    std::cout << "Unable to load Tahoma.ttf font file" << std::endl;
  };
  m_plantName.setFont(m_tahoma);
  m_plantName.setFillColor(sf::Color::Black);

  m_plantVariety.setFont(m_tahoma);
  m_plantVariety.setFillColor(sf::Color::Black);

  m_plantNumber.setFont(m_tahoma);
  m_plantNumber.setFillColor(sf::Color::Black);
}

//Default Destructor.
Tile::~Tile() { }

//Set the size of a tile.
void Tile::SetTileSize(sf::Vector2f tilesize)
{
  m_tileContainer.setSize(tilesize);
}

//Set the position of a tile.
void Tile::SetTilePosition(sf::Vector2f tileposition)
{
  m_tileContainer.setPosition(tileposition);
}

//Returns an sf::Vector2f with the x and y coordinates of a tile's position.
sf::Vector2f Tile::GetTilePosition()
{
  return m_tilePosition;
}

//Returns an sf::Vector2f with the length and width of a tile.
sf::Vector2f Tile::GetTileSize()
{
  return m_tileSize;
}

//Set's the color of the tile container m_tileContainer.
void Tile::SetTileColor(sf::Color color)
{
  m_tileContainer.setFillColor(color);
}

//Set's the values for the m_plantName, m_plantVariety, and m_plantNumber object for displaying plant info on the tile.
void Tile::SetText(std::string plantvariety, std::string plantname, int number)
{
  //Check to see if the variety is more than 15 chars long to split the text so it will fit in the tile.
  if(plantvariety.size() > 15)
  {
    for(int i = 15; i < plantvariety.size(); i++)
    {
      if(isspace(plantvariety[i]))
      {
        std::string str1 = plantvariety.substr(0, i);
        std::string str2 = plantvariety.substr(i+1);
        m_plantVariety.setString(str1 + "\n" + str2);
        i = plantvariety.size();
      }
      else
      {
        m_plantVariety.setString(plantvariety);
      }
    }
  }
  else
  {
    m_plantVariety.setString(plantvariety);
  }
  m_plantNumber.setString(std::to_string(number) + " plants");
  m_plantName.setString(plantname);
}

//Returns true or false depending on where the mouse is hovering over the tile or not.
bool Tile::MouseOverTile(sf::RenderWindow &window, sf::View &view)
{
  window.setView(view);
  sf::Vector2i mouseWindowPostion = sf::Mouse::getPosition(window); //Grab mouse position in the content of the window.
  sf::Vector2f mouseViewPosition = window.mapPixelToCoords(mouseWindowPostion);  //Map mouse coordinate from the window to the view.

  float containerPosX = m_tileContainer.getPosition().x;
  float containerPosY = m_tileContainer.getPosition().y;

  float containerXPosWidth = containerPosX + m_tileContainer.getGlobalBounds().width;
  float containerYPosHeight = containerPosY + m_tileContainer.getGlobalBounds().height;

  if(mouseViewPosition.x < containerXPosWidth && mouseViewPosition.x > containerPosX && mouseViewPosition.y < containerYPosHeight && mouseViewPosition.y > containerPosY)
  {
    return true;
  }
  return false;
}

//Submit newly instantiated tile to the MySQL garden_space_planner database tiles table.
void Tile::SubmitToDb(int parentmapid, int plantid, int xpos, int ypos)
{
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  prep_stmt = con->prepareStatement("INSERT INTO tiles(map_id, plant_id, xpos, ypos) VALUES (?, ?, ?, ?)");
  prep_stmt->setInt(1, parentmapid);
  prep_stmt->setInt(2, plantid);
  prep_stmt->setInt(3, xpos);
  prep_stmt->setInt(4, ypos);
  prep_stmt->execute();
  delete con;
  delete prep_stmt;
}

//Returns the database id stored in the m_tileID member variable.
int Tile::GetTileID()
{
  return m_tileID;
}

//Stores a value for the tile id in the m_tileID member variable.
void Tile::SetTileID(int id)
{
  m_tileID = id;
}

//Draws the sf::RectangleShape m_tileContainer and m_textContainer objects, and sf::Text m_plantVariety, m_plantName and m_plantName objects to the window.
void Tile::Draw(sf::RenderWindow &window)
{
  m_textContainer.setSize({m_tileContainer.getSize().x * .8f, m_tileContainer.getSize().y * .5f});
  m_textContainer.setPosition(m_tileContainer.getPosition().x + (m_tileContainer.getSize().x * .1f), m_tileContainer.getPosition().y + (m_tileContainer.getSize().y * .25f));
  m_plantVariety.setPosition(m_textContainer.getPosition().x +((m_textContainer.getSize().x / 2) - m_plantVariety.getGlobalBounds().width / 2), m_textContainer.getPosition().y + 10);
  m_plantName.setPosition(m_textContainer.getPosition().x +((m_textContainer.getSize().x / 2) - m_plantName.getGlobalBounds().width / 2), m_textContainer.getPosition().y + (m_plantVariety.getGlobalBounds().height * 1.2f) + 10);
  m_plantNumber.setPosition(m_textContainer.getPosition().x +((m_textContainer.getSize().x / 2) - m_plantNumber.getGlobalBounds().width / 2), m_textContainer.getPosition().y + (m_plantVariety.getGlobalBounds().height * 1.2f) + m_plantNumber.getGlobalBounds().height + 10);
  m_plantName.setCharacterSize(m_textContainer.getSize().y * .17f);
  m_plantVariety.setCharacterSize(m_textContainer.getSize().y * .17f);
  m_plantNumber.setCharacterSize(m_textContainer.getSize().y * .17f);
  window.draw(m_tileContainer);
  window.draw(m_textContainer);
  window.draw(m_plantVariety);
  window.draw(m_plantName);
  window.draw(m_plantNumber);
}
