/**
    SDEV435-81 Capstone Project
    main.cpp
    Purpose: Allows users to create grids representing garden space
			that they can drop plant tiles into to help plan their garden.
			It allows users to add new plants and edit existing plants as needed.

    @author Jeremiah Kellogg
    @version 1.0 12/08/19
*/

#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Classes/ContentContainer.h"
#include "Classes/Button.h"
#include "Classes/Content.h"
#include "Classes/InputBox.h"
#include "Classes/ContentToDisplay.h"
#include "Classes/LeftColumnContent.h"
#include "Classes/MapDisplay.h"

int main()
{
	//Create Window to display program and set clock object for timing updates
	sf::RenderWindow mainWindow;
	sf::VideoMode currentMode = sf::VideoMode::getDesktopMode();
	mainWindow.setFramerateLimit(60);
	mainWindow.create(sf::VideoMode(currentMode), "Garden Space Planner");
	float deltaTime = 0.f;
	sf::Clock dtClock;

	//Set values for program color palate variables
	sf::Color background = sf::Color(228, 243, 127, 255);
	sf::Color foreground = sf::Color(86, 225, 58, 255);
	sf::Color onHover = sf::Color(238, 244, 177, 255);

	//Set Container objects for containing main display areas
	ContentContainer topNavBar(mainWindow, .98f, .08f, .02f, .02f, foreground);
	ContentContainer leftColumn(mainWindow, .25f, .86f, .02f, .12f, foreground);
	ContentContainer mainContent(mainWindow, .72f, .86f, .54f, .12f, background);
	ContentContainer mapNavBar(mainWindow, .72f, .1f, .54f, .12f, foreground);

	//Display in mapNavBar providing current map information
	sf::RectangleShape mapInfoContainer;
	mapInfoContainer.setFillColor(sf::Color::White);
	mapInfoContainer.setSize({mapNavBar.GetSize().x * .4f, mapNavBar.GetSize().y * .9f});
	mapInfoContainer.setPosition(mapNavBar.GetPosition().x * 1.05f, mapNavBar.GetPosition().y * 1.04f);

	//Button for deleting maps that lives in the mapNavBar ContentContainer.
	Button deleteMapBtn("Delete Map", mainWindow, background, sf::Color::Black);
	deleteMapBtn.SetPosition(mapNavBar.GetSize(), 1.13f, 3.5f);

	//Instantiate views for displaying all kinds of content.
	sf::View staticView;
	staticView.reset(sf::FloatRect(0, 0, (float)mainWindow.getSize().x, (float)mainWindow.getSize().y));

	sf::View leftColumnView;
	leftColumnView.setSize(leftColumn.GetSize().x * .99f, leftColumn.GetSize().y * .99f);
	leftColumnView.setViewport(sf::FloatRect(.0172f, .133f, .235f, .835f));
	//Instantiate border for containing the leftColumnView.
	sf::RectangleShape leftColumnViewBorder;
	leftColumnViewBorder.setSize({leftColumn.GetSize().x * .94f, leftColumn.GetSize().y * .968f});
	leftColumnViewBorder.setPosition({leftColumn.GetPosition().x * 1.7f, leftColumn.GetPosition().y * 1.13f});
	leftColumnViewBorder.setOutlineColor(sf::Color(42, 85, 34, 255));
	leftColumnViewBorder.setOutlineThickness(1);

	sf::View contentView;
	contentView.setSize(mainContent.GetSize().x, mainContent.GetSize().y);
	contentView.setCenter(mainContent.GetSize().x / 2, mainContent.GetSize().y / 2);
	contentView.setViewport(sf::FloatRect(.27f, .12f, .7199f, .86f));

	sf::View mapView;
	mapView.setSize(mainContent.GetSize().x, mainContent.GetSize().y);
	mapView.setCenter(mainContent.GetSize().x / 2, mainContent.GetSize().y / 2);
	mapView.setViewport(sf::FloatRect(.27f, .223f, .7199, .757f));

	//Instantiate an interactive map display.
	MapDisplay displayMap;
	sf::Text mapInfo;
	sf::Font ubuntu;
	ubuntu.loadFromFile("Fonts/Ubuntu-M.ttf");
	mapInfo.setFont(ubuntu);
	mapInfo.setFillColor(sf::Color::Black);
	mapInfo.setCharacterSize(mapNavBar.GetSize().y * .25);
	mapInfo.setPosition(mapInfoContainer.getPosition().x + 10.f, mapInfoContainer.getPosition().y + 5);

	//Instantiate Content objects for each screen the user can select.
	Content WelcomeScreen;
	WelcomeScreen.AddText("Text/WelcomeScreen.txt");
	WelcomeScreen.MakeActive();

	Content SelectMapScreen;
	SelectMapScreen.SetView(contentView);
	SelectMapScreen.SetMapList();
	SelectMapScreen.AddScrollArea();
	SelectMapScreen.AddScrollBar();
	SelectMapScreen.SetMapContainerVector();

	Content CreateMapScreen;
	CreateMapScreen.AddText("Text/CreateMapScreen.txt");
	CreateMapScreen.SetView(contentView);
	CreateMapScreen.AddInputArea(mainContent.GetSize().x - 20.f, mainContent.GetSize().y * .6f, 10.f, mainContent.GetSize().y * .3f);
	CreateMapScreen.AddInputBoxes("Name", {70.f, mainContent.GetSize().y * .32f + 20.f},
	"Year", {70.f, mainContent.GetSize().y * .32f + 90.f},
	"Length/foot", {70.f, mainContent.GetSize().y * .32f + 160.f},
	"Width/foot", {70.f, mainContent.GetSize().y * .32f + 230.f});
	CreateMapScreen.AddInputButton("CREATE MAP", mainWindow, mainContent.GetSize(), .4f, 1.96f);

	Content AddPlantScreen;
	AddPlantScreen.AddText("Text/AddPlantScreen.txt");
	AddPlantScreen.AddInputArea(mainContent.GetSize().x - 20.f, mainContent.GetSize().y * .6f, 10.f, mainContent.GetSize().y * .35f - 10.f);
	AddPlantScreen.AddInputBoxes("Plant Name", {70.f, mainContent.GetSize().y * .4f + 20.f},
	"Plant Variety", {70.f, mainContent.GetSize().y * .4f + 90.f},
	"Plant Spacing/inch", {70.f, mainContent.GetSize().y * .4f + 160.f},
	"Row Spacing/foot", {70.f, mainContent.GetSize().y * .4f + 230.f});
	AddPlantScreen.AddInputButton("ADD PLANT", mainWindow, mainContent.GetSize(), .4f, 2.11f);

	Content EditPlantScreen;
	EditPlantScreen.AddText("Text/EditPlantScreen.txt");
	EditPlantScreen.AddInputArea(mainContent.GetSize().x - 20.f, mainContent.GetSize().y * .6f, 10.f, mainContent.GetSize().y * .3f - 10.f);
	EditPlantScreen.AddInputBoxes("Plant Name", {70.f, mainContent.GetSize().y * .32f + 20.f},
	"Plant Variety", {70.f, mainContent.GetSize().y * .32f + 90.f},
	"Plant Spacing/inch", {70.f, mainContent.GetSize().y * .32f + 160.f},
	"Row Spacing/foot", {70.f, mainContent.GetSize().y * .32f + 230.f});
	EditPlantScreen.AddInputButton("SUBMIT EDIT", mainWindow, mainContent.GetSize(), .4f, 1.96f);

	//Instantiate object that handles what content should be displayed.
	ContentToDisplay contentDisplay;

	//Instantiate object for displaying left column content.
	LeftColumnContent leftColumnDisplay(leftColumnView);
	leftColumnDisplay.SetPlantVector();
	leftColumnDisplay.AddDisplayArea();
	leftColumnDisplay.AddScrollBar();
	leftColumnDisplay.SetPlantContainerVector();

	//Instantiate button objects for the topNavBar ContentContainer object and add them to an array.
	Button selectMapBtn("Select Map", mainWindow, background, sf::Color::Black);
	selectMapBtn.SetPosition(topNavBar.GetSize(), .08f, .96f);
	Button createMapBtn("Create Map", mainWindow, background, sf::Color::Black);
	createMapBtn.SetPosition(topNavBar.GetSize(), .3f, .96f);
	Button addPlantBtn("Add Plant", mainWindow, background, sf::Color::Black);
	addPlantBtn.SetPosition(topNavBar.GetSize(), .52f, .96f);
	Button editPlantBtn("Edit Plant", mainWindow, background, sf::Color::Black);
	editPlantBtn.SetPosition(topNavBar.GetSize(), .74f, .96f);
	Button navButtons [4] = {selectMapBtn, createMapBtn, addPlantBtn, editPlantBtn};

	//Instantiate an event object for polling events.
	sf::Event event;

	//Begin main program loop.
	while (mainWindow.isOpen())
	{
		//Set delta time to circumvent differences between computer processor speeds
		deltaTime = dtClock.restart().asSeconds();

		//Check to see if a map has been selected by the user.
		if(displayMap.GetDisplay())
		{
			displayMap.UpdateKeys(mapView, deltaTime);
			mapInfo.setString("Map: " + displayMap.GetMap().GetName() + "\nYear: " + displayMap.GetMap().GetYear() +
			"\nSize(feet): " + std::to_string(displayMap.GetMap().GetLength()) + "x" + std::to_string(displayMap.GetMap().GetWidth()));
		}
		//Begin Polling for user initiated events.
		while (mainWindow.pollEvent (event))
		{
			switch(event.type) {
				case sf::Event::Closed:
					mainWindow.close();
				case sf::Event::MouseButtonPressed:
					//Begin left mouse button events.
					if(event.mouseButton.button == sf::Mouse::Left)
					{
						CreateMapScreen.FocusOnBox(mainWindow);
						CreateMapScreen.MessageDismissed(mainWindow);
						AddPlantScreen.FocusOnBox(mainWindow);
						AddPlantScreen.MessageDismissed(mainWindow);
						EditPlantScreen.FocusOnBox(mainWindow);
						EditPlantScreen.MessageDismissed(mainWindow);

						if(deleteMapBtn.mouseOver(mainWindow))
						{
							displayMap.DeleteMap();
							SelectMapScreen.MakeInactive();
							CreateMapScreen.MakeInactive();
							AddPlantScreen.MakeInactive();
							WelcomeScreen.MakeActive();
							EditPlantScreen.MakeInactive();
							displayMap.SetDisplay(false);
						}
						else if(selectMapBtn.mouseOver(mainWindow))
						{
							SelectMapScreen.MakeActive();
							SelectMapScreen.SetMapList();
							CreateMapScreen.MakeInactive();
							AddPlantScreen.MakeInactive();
							WelcomeScreen.MakeInactive();
							EditPlantScreen.MakeInactive();
							displayMap.SetDisplay(false);
						}
						else if(createMapBtn.mouseOver(mainWindow))
						{
							CreateMapScreen.MakeActive();
							AddPlantScreen.MakeInactive();
							WelcomeScreen.MakeInactive();
							SelectMapScreen.MakeInactive();
							EditPlantScreen.MakeInactive();
							displayMap.SetDisplay(false);
						}
						else if(addPlantBtn.mouseOver(mainWindow))
						{
							AddPlantScreen.MakeActive();
							WelcomeScreen.MakeInactive();
							SelectMapScreen.MakeInactive();
							CreateMapScreen.MakeInactive();
							EditPlantScreen.MakeInactive();
							displayMap.SetDisplay(false);
						}
						else if(editPlantBtn.mouseOver(mainWindow))
						{
							EditPlantScreen.MakeActive();
							AddPlantScreen.MakeInactive();
							WelcomeScreen.MakeInactive();
							SelectMapScreen.MakeInactive();
							CreateMapScreen.MakeInactive();
							displayMap.SetDisplay(false);
						}
						else if(leftColumnDisplay.MouseOverScroll(mainWindow))
						{
							leftColumnDisplay.ChangeColor(sf::Color(150, 150, 150, 255));
							leftColumnDisplay.SetScrolling(true);
							leftColumnDisplay.SetFirstClick(true);
						}
						else if(SelectMapScreen.MouseOverScroll(mainWindow))
						{
							SelectMapScreen.ChangeColor(sf::Color(150, 150, 150, 255));
							SelectMapScreen.SetScrolling(true);
							SelectMapScreen.SetFirstClick(true);
						}
						if(displayMap.GetDisplay())
						{
							if(displayMap.MouseInBounds(mainWindow, mainContent, mapNavBar))
							{
								displayMap.BuildTile();
							}
						}
					}  //End left mouse button events.
					else if(event.mouseButton.button == sf::Mouse::Right)
					{
						if(displayMap.GetDisplay())
						{
							displayMap.RemoveTile(mainWindow, mapView);
						}
					}
					break;
				case sf::Event::TextEntered:
					if(AddPlantScreen.GetActiveStatus())
						{
							AddPlantScreen.EnterText(event);
						}
					else if(CreateMapScreen.GetActiveStatus())
					{
						CreateMapScreen.EnterText(event);
					}
					else if(EditPlantScreen.GetActiveStatus())
					{
						EditPlantScreen.EnterText(event);
					}
					break;
				case sf::Event::MouseButtonReleased:
					leftColumnDisplay.SetScrolling(false);
					leftColumnDisplay.ChangeColor(sf::Color(175, 175, 175, 255));
					SelectMapScreen.SetScrolling(false);
					SelectMapScreen.ChangeColor(sf::Color(175, 175, 175, 255));
					if(AddPlantScreen.GetActiveStatus())
					{
						AddPlantScreen.SubmitData(mainWindow, "plants", displayMap, contentView);
					}
					else if(CreateMapScreen.GetActiveStatus())
					{
						CreateMapScreen.SubmitData(mainWindow, "maps", displayMap, contentView);
					}
					else if(EditPlantScreen.GetActiveStatus())
					{
						EditPlantScreen.SubmitData(mainWindow, "edit_plants", displayMap, contentView);
					}
					break;
			}
			//Update mouse postion if an interactive map is being displayed
			if(displayMap.GetDisplay())
			{
				if(displayMap.MouseInBounds(mainWindow, mainContent, mapNavBar))
				{
					displayMap.UpdateMouse(mainWindow, mapView);
				}
			}
		}//End Polling for user initiated events.

		//Begin Render all objects to the window.
		mainWindow.clear(background);
		//Render proper objects to the static view (main view of program).
		mainWindow.setView(staticView);
		topNavBar.Draw(mainWindow);
		for (Button btn : navButtons)
		{
			if(btn.mouseOver(mainWindow))
			{
				btn.SetColor(onHover);
			}
			else
			{
				btn.SetColor(background);
			}
			btn.Draw(mainWindow);
		}
		leftColumn.Draw(mainWindow);
		mainContent.Draw(mainWindow);
		mainWindow.draw(leftColumnViewBorder);

		//Render logic if a map has been selected by user and is being viewed
		if(displayMap.GetDisplay())
		{
			if(deleteMapBtn.mouseOver(mainWindow))
			{
				deleteMapBtn.SetColor(onHover);
			}
			else
			{
				deleteMapBtn.SetColor(background);
			}
			mapNavBar.Draw(mainWindow);
			mainWindow.draw(mapInfoContainer);
			deleteMapBtn.Draw(mainWindow);
			mainWindow.draw(mapInfo);
			//Draw selected map to the mapView.
			mainWindow.setView(mapView);
			displayMap.DrawMap(mainWindow);
			displayMap.DrawTiles(mainWindow);
		}
		else
		{
			//Draw selected content to view to the contentView
			mainWindow.setView(contentView);
			if(SelectMapScreen.GetActiveStatus())
			{
				contentView.setCenter(SelectMapScreen.GetScrollPosition(mainContent));
			}
			else
			{
				contentView.setCenter(mainContent.GetSize().x / 2, mainContent.GetSize().y / 2);
			}
			contentDisplay.DisplayContent(mainWindow, WelcomeScreen, SelectMapScreen,
				CreateMapScreen, AddPlantScreen, EditPlantScreen, event, displayMap, mapView);
		}
		//Left column Content to display in leftColumnView.
		mainWindow.setView(leftColumnView);
		leftColumnView.setCenter(leftColumnDisplay.GetScrollPosition(leftColumn));
		if(leftColumnDisplay.GetScrolling())
		{
			leftColumnDisplay.Scroll(mainWindow, leftColumnViewBorder);
		}

		leftColumnDisplay.Draw(mainWindow, event);

		mainWindow.display();
		//End render all objects to window.
	}//End main program loop
}
