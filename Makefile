OBJS = main.cpp Classes/ContentContainer.cpp Classes/Button.cpp Classes/Content.cpp Classes/InputBox.cpp\
Classes/ContentToDisplay.cpp Classes/MessageWindow.cpp Classes/Plant.cpp Classes/Map.cpp Classes/LeftColumnContent.cpp\
Classes/MapDisplay.cpp Classes/Tile.cpp Classes/SelectMap.cpp Classes/ContentInput.cpp Classes/EditPlant.cpp\
Classes/CreateMap.cpp Classes/AddPlant.cpp Classes/ScrollBar.cpp 
CXX = g++
CPPFLAGS = -WALL
INCLUDES = -I /Classes
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lmysqlcppconn

app: $(OBJS)
	$(CXX) -o garden_planner $(INCLUDES) $(OBJS) $(LDLIBS)

clean:
	$(RM) garden_planner *.o
