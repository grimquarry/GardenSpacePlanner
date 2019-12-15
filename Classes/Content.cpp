/**
    SDEV435-81 Capstone Project
    Content.cpp
    Purpose: Code file for the Content class.  This class provides
      functionality for creating varioius types of content that can
      be selected and viewed by the user.  It's focus is more on the
      main content display of the Garden Space Planner program.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#include "Content.h"

//Default Constructor.
Content::Content()
{
  //New objects should not be active, scrolling or clicked until user selects them
  m_isActive = false;
  m_isScrolling = false;
  m_firstClick = false;

  if(!m_ubuntu.loadFromFile("Fonts/Ubuntu-M.ttf"))
  {
    std::cout << "Unable to load Ubuntu-M.ttf font file" << std::endl;
  };
  //Default settings for sf::Text objects
  m_mapTxtName.setFont(m_ubuntu);
  m_mapTxtName.setFillColor(sf::Color::Black);
  m_mapTxtYear.setFont(m_ubuntu);
  m_mapTxtYear.setFillColor(sf::Color::Black);
  m_mapTxtLength.setFont(m_ubuntu);
  m_mapTxtLength.setFillColor(sf::Color::Black);
  m_mapTxtWidth.setFont(m_ubuntu);
  m_mapTxtWidth.setFillColor(sf::Color::Black);
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

//Add a section of the Content display for user input boxes.
void Content::AddInputArea(float width, float height, float posX, float posY)
{
  m_input_container.setSize(sf::Vector2f(width, height));
  m_input_container.setPosition(sf::Vector2f(posX, posY));
  m_input_container.setFillColor(sf::Color::White);
  m_input_container.setOutlineColor(sf::Color(42, 85, 34, 255));
	m_input_container.setOutlineThickness(1.0f);
}

//Draw all Content text to the window.
void Content::DrawText(sf::RenderWindow &window)
{
  window.draw(m_contentText);
}

//Add InputBox objects to the Content object for user input.
void Content::AddInputBoxes(std::string header1, sf::Vector2f pos1,
  std::string header2, sf::Vector2f pos2,
  std::string header3, sf::Vector2f pos3,
  std::string header4, sf::Vector2f pos4)
{
  m_inputBox1.SetPosition(pos1);
  m_inputBox1.SetHeader(header1 + ":");
  m_inputBox2.SetPosition(pos2);
  m_inputBox2.SetHeader(header2 + ":");
  m_inputBox3.SetPosition(pos3);
  m_inputBox3.SetHeader(header3 + ":");
  m_inputBox4.SetPosition(pos4);
  m_inputBox4.SetHeader(header4 + ":");
}

//Focus on InputBox object the user has selected for inputing data.
void Content::FocusOnBox(sf::RenderWindow &window)
{
  m_inputBox1.clickedOn(window);
  m_inputBox2.clickedOn(window);
  m_inputBox3.clickedOn(window);
  m_inputBox4.clickedOn(window);
}

//Dismiss pop-ups called by the Content object to convey important messages to the user.
void Content::MessageDismissed(sf::RenderWindow &window)
{
  m_messageDisplay.clickedOn(window);
}

//Checks to see if user is typing, and if so displays text the user is typing into the InputBox object.
void Content::EnterText(sf::Event input)
{
  if(m_inputBox1.m_isSelected)
  {
    m_inputBox1.typedOn(input);
  }
  else if(m_inputBox2.m_isSelected)
  {
    m_inputBox2.typedOn(input);
  }
  else if(m_inputBox3.m_isSelected)
  {
    m_inputBox3.typedOn(input);
  }
  else if(m_inputBox4.m_isSelected)
  {
    m_inputBox4.typedOn(input);
  }
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

//Adds a Button object to the Content display so users can submit data they've entered into InputBox objects.
void Content::AddInputButton(std::string name, sf::RenderWindow& window,
  sf::Vector2f area, float ratioX, float ratioY)
{
  m_inputButton.SetButton(name, window);
  m_inputButton.SetPosition(area, ratioX, ratioY);
}

//Submits user input to the specified MySQL database.
void Content::SubmitData(sf::RenderWindow &window, std::string databaseName, MapDisplay &mapDisplay, sf::View &view)
{
  try
  {
    if(m_inputButton.ContentBtnMouseOver(window))
    {
      std::string box1 = m_inputBox1.GetText();
      std::string box2 = m_inputBox2.GetText();
      std::string box3 = m_inputBox3.GetText();
      std::string box4 = m_inputBox4.GetText();

      //Input validation
      if(box1.length() < 1 || box2.length() < 1 || box3.length() < 1 || box4.length() < 1)
      {
        m_messageDisplay.SetDisplay(true);
        m_messageDisplay.AddMessage("One or more fields haven't been filled in. \n All fields are required.");
      }
      else if (std::stoi(box3) < 1 || std::stoi(box4) < 1)
      {
        m_messageDisplay.SetDisplay(true);
        m_messageDisplay.AddMessage("Number fields can't be less than 1.  Check to make \n sure no fields are less than 1.");
      }
      else if (std::stoi(box3) > 120 || std::stoi(box4) > 120)
      {
        m_messageDisplay.SetDisplay(true);
        m_messageDisplay.AddMessage("This program can't process gardens larger\nthan 120 square feet.  Therefore all numerical\nvalues must be less than 120");
      }
      else
      {
        if(databaseName == "plants")
        {
          m_plant.SetName(box1);
          m_plant.SetVariety(box2);
          m_plant.SetSpacing(std::stoi(box3));
          m_plant.SetRowSpacing(std::stoi(box4));
          m_plant.AddToDatabase();
          m_messageDisplay.SetDisplay(true);
          m_messageDisplay.AddMessage("The Database has been successfully updated\nwith the following info\nPlant Name: " + box1 +"\nPlant Variety: " + box2 + "\nPlant Spacing: " + box3 + "\nRow Spacing: " + box4);
        }
        else if(databaseName == "maps")
        {
          m_map.SetName(box1);
          m_map.SetYear(box2);
          m_map.SetLength(std::stoi(box3));
          m_map.SetWidth(std::stoi(box4));
          m_map.AddToDatabase();
          Map newMap = mapDisplay.GetNewMap();
          mapDisplay.SetMap(newMap, view);
          mapDisplay.SetDisplay(true);
        }
        else if(databaseName == "edit_plants")
        {
          m_plant.SetName(box1);
          m_plant.SetVariety(box2);
          m_plant.SetSpacing(std::stoi(box3));
          m_plant.SetRowSpacing(std::stoi(box4));
          m_plant.UpdateDatabase();
          m_messageDisplay.SetDisplay(true);
          m_messageDisplay.AddMessage("The Database has been successfully updated\nwith the following info\nPlant Name: " + box1 +"\nPlant Variety: " + box2 + "\nPlant Spacing: " + box3 + "\nRow Spacing: " + box4);
        }
        m_inputBox1.ClearContent();
        m_inputBox2.ClearContent();
        m_inputBox3.ClearContent();
        m_inputBox4.ClearContent();
      }
    }
  }
  //catch invalid arguments when users try to enter chars to int fields
  catch(std::invalid_argument)
  {
    m_messageDisplay.SetDisplay(true);
    m_messageDisplay.AddMessage("You entered text into a field that requires a number!");
  }
  //catch unanticipated errors
  catch(...)
  {
    m_messageDisplay.SetDisplay(true);
    m_messageDisplay.AddMessage("An Unexpected Error Occured!");
  }
}

//Finds the currently selected Plant in the garden_space_planner.plants MySQL table;
void Content::GetSelectedPlant()
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
      m_inputBox1.AddText(res->getString("plant_name"));
      m_inputBox2.AddText(res->getString("plant_variety"));
      m_inputBox3.AddText(res->getString("plant_spacing_width"));
      m_inputBox4.AddText(res->getString("plant_spacing_length"));
      m_previousPlantID = m_currentPlantID;
    }
  }

  delete stmt;
  delete con;
}

//Populates the m_mapList vector with a list of maps from the MySQL database.
void Content::SetMapList()
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

/*Sets the size of m_mapSelectContainer data member and sets the size and position of the m_displayArea data member
  based on the m_contentView data member sf::View object.*/
void Content::AddScrollArea()
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

//Updates size and position of scroll area when a new Map object is added to or removed from the m_mapsList vector.
void Content::UpdateScrollArea()
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

//Adds scrollbar functionality and objects to the screen users can select maps from.
void Content::AddScrollBar()
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

//Add clickable containers that hold map data to the m_mapContainerList vector.
void Content::SetMapContainerVector()
{
  m_mapContainerList.clear();
  m_mapContainerDisplayPos = (m_displayArea.getPosition());

  for(int i = 0; i < m_mapList.size(); i++)
  {
    m_mapContainerList.push_back(m_mapContainerDisplayPos);
    m_mapContainerDisplayPos.y += m_mapSelectContainer.getSize().y;
  }
}

//Draws the list of user created maps the user can choose from to the sf::View contentView object in the sf::RenderWindow mainWindow object.
void Content::DrawMapMenu(sf::RenderWindow &window, sf::Event &event, MapDisplay &display, sf::View &view)
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

//Set the view the Content object is associated with.
void Content::SetView(sf::View &view)
{
  m_contentView = view;
}

//Updates position of scroll bar and centered position of the view on each loop.
void Content::Scroll(sf::RenderWindow &window)
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

//Sets whether or not the user is currently using the scroll bar.
void Content::SetScrolling(bool toScroll)
{
  m_isScrolling = toScroll;
}

//Returns the value for the boolean data member m_isScrolling to indicate whether a user is trying to scroll or not.
bool Content::GetScrolling()
{
  return m_isScrolling;
}

/*Sets whether or not the user is initializing scroll functionality from a state where they were not using the scrollbar.
  This value is saved to the boolean data member m_firstClick.*/
void Content::SetFirstClick(bool click)
{
  m_firstClick = click;
}

//Returns the value for the boolean data member m_firstClick to indicate whether a user has clicked on the scrollbar or not.
bool Content::GetFirstClick()
{
  return m_firstClick;
}

//Returns a boolean value indicating whether or not the user's mouse is hovering over the scrollbar.
bool Content::MouseOverScroll(sf::RenderWindow &window)
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

/*Returns a boolean value indicating whether or not the user's mouse is hovering over an sf::RectangleShape m_mapContainer object
  that's used to contain map data for listing in the select map screen.*/
bool Content::MouseOverMapContainer(sf::RenderWindow &window)
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

//Returns sf::Vector2f object containing x and y coordinate for the current scrollbar position.
sf::Vector2f Content::GetScrollPosition(ContentContainer &container)
{
  return {m_centerScreen.getPosition().x, m_centerScreen.getPosition().y};
}

//Sets the color of the scrollbar (used for changing color when the user clicks on the scrollbar).
void Content::ChangeColor(sf::Color color)
{
  m_scrollElement.setFillColor(color);
}

//Draws InputBox objects to the sf::Renderwindow object.
void Content::DrawInputField(sf::RenderWindow &window)
{
  window.draw(m_input_container);
  m_inputBox1.Draw(window);
  m_inputBox2.Draw(window);
  m_inputBox3.Draw(window);
  m_inputBox4.Draw(window);
  if(m_inputButton.ContentBtnMouseOver(window))
  {
    m_inputButton.SetColor(sf::Color(238, 244, 177, 255));
  }
  else
  {
    m_inputButton.SetColor(sf::Color(228, 243, 127, 255));
  }
  m_inputButton.Draw(window);
  if(m_messageDisplay.GetDisplay())
  {
    if(m_messageDisplay.MessageDismissHover(window))
    {
      m_messageDisplay.SetButtonColor(sf::Color::White);
    }
    else
    {
      m_messageDisplay.SetButtonColor(sf::Color(200, 200, 200, 255));
    }
    m_messageDisplay.Draw(window);
  }
}
