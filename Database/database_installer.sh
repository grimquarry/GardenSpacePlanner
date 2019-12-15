#!/bin/bash

read -sp "Please enter root user MySQL password: " rootpasswd
echo ""
mysql -u root -prootpasswd -e "CREATE USER IF NOT EXISTS 'garden_planner_user'@'localhost' IDENTIFIED BY 'spaceplanner';" 2>&1 | grep -v "Using a password"
mysql -u root -prootpasswd -e "CREATE DATABASE IF NOT EXISTS garden_space_planner;" 2>&1 | grep -v "Using a password"
mysql -u root -prootpasswd -e "GRANT ALL PRIVILEGES ON garden_space_planner.* TO 'garden_planner_user'@'localhost';" 2>&1 | grep -v "Using a password"
mysql -u root -prootpasswd -e "FLUSH PRIVILEGES;" 2>&1 | grep -v "Using a password"
mysql -u root -prootpasswd -e "CREATE TABLE IF NOT EXISTS garden_space_planner.maps (map_id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, map_name VARCHAR(30), map_year VARCHAR(30), map_length INT, map_width INT, is_selected BOOLEAN DEFAULT false);" 2>&1 | grep -v "Using a password"
mysql -u root -prootpasswd -e "CREATE TABLE IF NOT EXISTS garden_space_planner.plants (plant_id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, plant_name VARCHAR(30), plant_variety VARCHAR(30), plant_spacing_width INT, plant_spacing_length INT, red_color_value INT, green_color_value INT, blue_color_value INT, is_selected BOOLEAN DEFAULT false);" 2>&1 | grep -v "Using a password"
mysql -u root -prootpasswd -e "CREATE TABLE IF NOT EXISTS garden_space_planner.tiles (tile_id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, map_id INT, FOREIGN KEY (map_id) REFERENCES maps(map_id), plant_id INT, FOREIGN KEY (plant_id) REFERENCES plants(plant_id), xpos INT, ypos INT);" 2>&1 | grep -v "Using a password"

#mysql -u root -prootpasswd -e "INSERT INTO garden_space_planner.maps(map_name) VALUES('SELECT A MAP TO EDIT')" 2>&1 | grep -v "Using a password"
mysql -u root -prootpasswd "garden_space_planner" < "garden_space_planner.sql" 2>&1 | grep -v "Using a password"
