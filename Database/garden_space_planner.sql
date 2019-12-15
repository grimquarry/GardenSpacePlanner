-- MySQL dump 10.16  Distrib 10.1.41-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: garden_space_planner
-- ------------------------------------------------------
-- Server version	10.1.41-MariaDB-0+deb9u1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `maps`
--

DROP TABLE IF EXISTS `maps`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `maps` (
  `map_id` int(11) NOT NULL AUTO_INCREMENT,
  `map_name` varchar(30) DEFAULT NULL,
  `map_year` varchar(30) DEFAULT NULL,
  `map_length` int(11) DEFAULT NULL,
  `map_width` int(11) DEFAULT NULL,
  `is_selected` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`map_id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `maps`
--

LOCK TABLES `maps` WRITE;
/*!40000 ALTER TABLE `maps` DISABLE KEYS */;
INSERT INTO `maps` VALUES (1,'SELECT A MAP TO EDIT',NULL,NULL,NULL,0),(2,'Example Map','2020',20,20,0);
/*!40000 ALTER TABLE `maps` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `plants`
--

DROP TABLE IF EXISTS `plants`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `plants` (
  `plant_id` int(11) NOT NULL AUTO_INCREMENT,
  `plant_name` varchar(30) DEFAULT NULL,
  `plant_variety` varchar(30) DEFAULT NULL,
  `plant_spacing_width` int(11) DEFAULT NULL,
  `plant_spacing_length` int(11) DEFAULT NULL,
  `red_color_value` int(11) DEFAULT NULL,
  `green_color_value` int(11) DEFAULT NULL,
  `blue_color_value` int(11) DEFAULT NULL,
  `is_selected` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`plant_id`)
) ENGINE=InnoDB AUTO_INCREMENT=62 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `plants`
--

LOCK TABLES `plants` WRITE;
/*!40000 ALTER TABLE `plants` DISABLE KEYS */;
INSERT INTO `plants` VALUES (1,'Artichoke','Wonder F1',36,3,83,153,58,0),(2,'Bean','Gold Rush Yellow Wax',3,2,51,184,51,0),(3,'Bean','Provider',3,2,9,62,207,0),(4,'Bean','Royal Burgundy',3,2,231,99,144,0),(5,'Beet','Badger Flame Beet',3,2,234,179,3,0),(6,'Beet','Boro F1',3,2,7,2,64,0),(7,'Beet','Detroit Dark Red',3,2,120,251,55,0),(8,'Broccoli','Belstar F1',24,3,69,100,14,0),(9,'Broccoli','De Cicco',24,3,62,20,212,0),(10,'Brussels Sprouts','Doric F1',24,3,183,143,236,0),(11,'Cabbage','Carafliex F1',12,2,234,188,1,0),(12,'Cabbage','Red Express',24,2,124,173,214,0),(13,'Cabbage','Bilko F1 Napa',12,2,178,41,83,0),(14,'Carrot','Bangor F1',2,2,186,41,6,0),(15,'Carrot','Cosmic Purple',2,2,177,97,94,0),(16,'Carrot','Yellowstone',2,2,248,121,242,0),(17,'Cauliflower','Goodman',24,3,220,91,83,0),(18,'Cauliflower','SkyWalker F1',24,3,20,71,55,0),(19,'Celery','Tall Utah',6,2,24,121,53,0),(20,'Chard','Pink Passion',6,2,221,66,174,0),(21,'Corn','Fisher\'s Earliest',8,3,96,231,81,0),(22,'Corn','My Fair Lady F1',12,3,0,218,1,0),(23,'Cucumber','National Pickling',12,4,118,194,186,0),(24,'Cucumber','Saber F1',18,5,60,123,193,0),(25,'Eggplant','Traviata F1',18,3,13,13,36,0),(26,'Fennel','Solaris F1',6,2,32,200,227,0),(27,'Garlic','Chesnok Red',4,2,175,166,146,0),(28,'Greens','Mesclun Mix',6,1,31,140,252,0),(29,'Kale','Dwarf Green Curled',12,2,164,176,48,0),(30,'Kale','Lacinato',12,2,68,47,107,0),(31,'Leek','Chinook F1',6,2,244,253,232,0),(32,'Lettuce','Green Star',8,1,90,204,116,0),(33,'Lettuce','New Red Fire',8,1,87,143,28,0),(34,'Melon','Hale\'s Best',12,6,159,180,180,0),(35,'Onion','Cabernet F1 Red',4,2,103,151,237,0),(36,'Onion','Dakota Tears',4,2,92,96,107,0),(37,'Onion','New York Early',4,2,155,24,182,0),(38,'Onion','Red Baron',4,2,168,160,40,0),(39,'Pea','Cascadia Snap',2,1,33,226,77,0),(40,'Pea','Dwarf Grey Sugar Snow',2,1,96,89,204,0),(41,'Pea','Green Arrow Shell',2,1,81,205,183,0),(42,'Pepper','Ancho Poblano Hot',12,2,3,60,129,0),(43,'Pepper','Early Jalapeno Hot',12,2,196,209,218,0),(44,'Pepper','HMS Orange Picnic',12,2,117,197,193,0),(45,'Pepper','King of the North Bell',12,2,213,197,222,0),(46,'Potato','Burbank Russet',12,3,192,202,166,0),(47,'Potato','Dark Red Norland',12,3,110,72,119,0),(48,'Potato','Yukon Gold',12,3,145,166,241,0),(49,'Pumpkin','Howden',36,9,153,53,250,0),(50,'Pumpkin','New England Pie',24,6,186,37,49,0),(51,'Radish','Daikon',4,1,55,225,98,0),(52,'Rasish','French Breakfast',1,1,193,66,49,0),(53,'Rasish','Purple Plum',1,1,157,179,254,0),(54,'Spinach','Giant Winter',2,1,167,122,97,0),(55,'Spinach','Renegade F1',2,1,136,5,208,0),(56,'Summer Squash','Dark Green Zucchini',12,5,85,76,172,1),(57,'Summer Squash','Success PM Straightneck Yellow',12,5,135,181,118,0),(58,'Tomato','Amish Paste',24,4,28,149,160,0),(59,'Tomato','Brandywine',24,4,83,10,251,0),(60,'Winter Squash','Sugarbush F1 Acorn',24,6,112,70,46,0),(61,'Winter Squash','Waltham Butternut',24,9,207,184,225,0);
/*!40000 ALTER TABLE `plants` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tiles`
--

DROP TABLE IF EXISTS `tiles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tiles` (
  `tile_id` int(11) NOT NULL AUTO_INCREMENT,
  `map_id` int(11) DEFAULT NULL,
  `plant_id` int(11) DEFAULT NULL,
  `xpos` int(11) DEFAULT NULL,
  `ypos` int(11) DEFAULT NULL,
  PRIMARY KEY (`tile_id`),
  KEY `map_id` (`map_id`),
  KEY `plant_id` (`plant_id`),
  CONSTRAINT `tiles_ibfk_1` FOREIGN KEY (`map_id`) REFERENCES `maps` (`map_id`),
  CONSTRAINT `tiles_ibfk_2` FOREIGN KEY (`plant_id`) REFERENCES `plants` (`plant_id`)
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tiles`
--

LOCK TABLES `tiles` WRITE;
/*!40000 ALTER TABLE `tiles` DISABLE KEYS */;
INSERT INTO `tiles` VALUES (1,2,40,0,0),(2,2,40,0,100),(3,2,40,0,200),(4,2,40,0,300),(5,2,40,0,400),(6,2,40,0,500),(7,2,40,0,600),(8,2,40,0,700),(9,2,40,0,800),(10,2,1,100,0),(11,2,1,400,0),(12,2,1,700,0),(13,2,1,100,300),(14,2,1,400,300),(15,2,1,700,300),(16,2,42,100,600),(17,2,42,300,600),(18,2,42,500,600),(19,2,42,700,600),(20,2,52,900,600),(21,2,52,900,700),(22,2,52,900,800),(23,2,52,900,900),(24,2,52,900,1000),(25,2,52,900,1100),(26,2,58,1000,0),(27,2,58,1000,400);
/*!40000 ALTER TABLE `tiles` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-11-25 14:41:57
