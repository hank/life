SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

CREATE SCHEMA IF NOT EXISTS `5charts` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci ;
USE `5charts` ;

-- -----------------------------------------------------
-- Table `5charts`.`User`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `5charts`.`User` ;

CREATE  TABLE IF NOT EXISTS `5charts`.`User` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `username` VARCHAR(45) NOT NULL ,
  `first_name` VARCHAR(45) NOT NULL ,
  `last_name` VARCHAR(45) NOT NULL ,
  `verified` TINYINT(1)  NOT NULL DEFAULT FALSE ,
  `password_hash` VARCHAR(1024) NOT NULL ,
  `admin` TINYINT(1)  NULL ,
  PRIMARY KEY (`id`) ,
  UNIQUE INDEX `username_UNIQUE` (`username` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `5charts`.`Stock`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `5charts`.`Stock` ;

CREATE  TABLE IF NOT EXISTS `5charts`.`Stock` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `ticker` VARCHAR(8) NOT NULL ,
  `name` VARCHAR(255) NULL ,
  `num_accesses` INT NOT NULL DEFAULT 0 ,
  PRIMARY KEY (`id`) ,
  UNIQUE INDEX `ticker_UNIQUE` (`ticker` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `5charts`.`Owns`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `5charts`.`Owns` ;

CREATE  TABLE IF NOT EXISTS `5charts`.`Owns` (
  `User_id` INT NOT NULL ,
  `Stock_id` INT NOT NULL ,
  `date_added` DATETIME NOT NULL ,
  `price_on_add` DECIMAL(9,3) NOT NULL ,
  `active` TINYINT(1)  NOT NULL ,
  PRIMARY KEY (`Stock_id`, `User_id`) ,
  INDEX `fk_User_has_Stock_Stock1` (`Stock_id` ASC) ,
  CONSTRAINT `fk_User_has_Stock_User`
    FOREIGN KEY (`User_id` )
    REFERENCES `5charts`.`User` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_User_has_Stock_Stock1`
    FOREIGN KEY (`Stock_id` )
    REFERENCES `5charts`.`Stock` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `5charts`.`OHLC`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `5charts`.`OHLC` ;

CREATE  TABLE IF NOT EXISTS `5charts`.`OHLC` (
  `Stock_id` INT NOT NULL ,
  `date` DATETIME NOT NULL ,
  `open` DECIMAL(9,3) NOT NULL ,
  `high` DECIMAL(9,3) NOT NULL ,
  `low` DECIMAL(9,3) NOT NULL ,
  `close` DECIMAL(9,3) NOT NULL ,
  `volume` BIGINT NOT NULL ,
  PRIMARY KEY (`Stock_id`, `date`) ,
  CONSTRAINT `fk_OHLC_Stock1`
    FOREIGN KEY (`Stock_id` )
    REFERENCES `5charts`.`Stock` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `5charts`.`Comment`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `5charts`.`Comment` ;

CREATE  TABLE IF NOT EXISTS `5charts`.`Comment` (
  `Owns_Stock_id` INT NOT NULL ,
  `Owns_User_id` INT NOT NULL ,
  `text` TEXT NOT NULL ,
  `mood` ENUM('Bullish', 'Bearish', 'Unsure') NULL ,
  `date` DATETIME NULL ,
  PRIMARY KEY (`Owns_Stock_id`, `Owns_User_id`) ,
  INDEX `fk_Comment_Owns1` (`Owns_Stock_id` ASC, `Owns_User_id` ASC) ,
  CONSTRAINT `fk_Comment_Owns1`
    FOREIGN KEY (`Owns_Stock_id` , `Owns_User_id` )
    REFERENCES `5charts`.`Owns` (`Stock_id` , `User_id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `5charts`.`Feed`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `5charts`.`Feed` ;

CREATE  TABLE IF NOT EXISTS `5charts`.`Feed` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `name` VARCHAR(45) NULL ,
  `link` VARCHAR(45) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = MyISAM;


-- -----------------------------------------------------
-- Table `5charts`.`Prediction`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `5charts`.`Prediction` ;

CREATE  TABLE IF NOT EXISTS `5charts`.`Prediction` (
  `User_id` INT NOT NULL ,
  `Stock_id` INT NOT NULL ,
  `id` INT NOT NULL AUTO_INCREMENT ,
  `date` DATETIME NOT NULL ,
  `text` TEXT NOT NULL ,
  PRIMARY KEY (`User_id`, `Stock_id`, `id`) ,
  INDEX `fk_Prediction_User1` (`User_id` ASC) ,
  INDEX `fk_Prediction_Stock1` (`Stock_id` ASC) ,
  CONSTRAINT `fk_Prediction_User1`
    FOREIGN KEY (`User_id` )
    REFERENCES `5charts`.`User` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Prediction_Stock1`
    FOREIGN KEY (`Stock_id` )
    REFERENCES `5charts`.`Stock` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `5charts`.`User_Feed`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `5charts`.`User_Feed` ;

CREATE  TABLE IF NOT EXISTS `5charts`.`User_Feed` (
  `User_id` INT NOT NULL ,
  `link_hash` VARCHAR(128) NOT NULL ,
  `link` VARCHAR(768) NOT NULL ,
  `name` VARCHAR(45) NULL ,
  PRIMARY KEY (`User_id`, `link_hash`) ,
  INDEX `fk_User_Feed_User1` (`User_id` ASC) ,
  CONSTRAINT `fk_User_Feed_User1`
    FOREIGN KEY (`User_id` )
    REFERENCES `5charts`.`User` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = MyISAM;


-- -----------------------------------------------------
-- Table `5charts`.`Sector`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `5charts`.`Sector` ;

CREATE  TABLE IF NOT EXISTS `5charts`.`Sector` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `name` VARCHAR(45) NOT NULL ,
  PRIMARY KEY (`id`) ,
  UNIQUE INDEX `name_UNIQUE` (`name` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `5charts`.`Sector_has_Stock`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `5charts`.`Sector_has_Stock` ;

CREATE  TABLE IF NOT EXISTS `5charts`.`Sector_has_Stock` (
  `Sector_id` INT NOT NULL ,
  `Stock_id` INT NOT NULL ,
  PRIMARY KEY (`Sector_id`, `Stock_id`) ,
  INDEX `fk_Sector_has_Stock_Stock1` (`Stock_id` ASC) ,
  CONSTRAINT `fk_Sector_has_Stock_Sector1`
    FOREIGN KEY (`Sector_id` )
    REFERENCES `5charts`.`Sector` (`id` )
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Sector_has_Stock_Stock1`
    FOREIGN KEY (`Stock_id` )
    REFERENCES `5charts`.`Stock` (`id` )
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `5charts`.`Friend`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `5charts`.`Friend` ;

CREATE  TABLE IF NOT EXISTS `5charts`.`Friend` (
  `User_from` INT NOT NULL ,
  `User_to` INT NOT NULL ,
  `added` DATETIME NOT NULL DEFAULT NOW() ,
  PRIMARY KEY (`User_from`, `User_to`) ,
  INDEX `fk_Friend_User2` (`User_to` ASC) ,
  CONSTRAINT `fk_Friend_User1`
    FOREIGN KEY (`User_from` )
    REFERENCES `5charts`.`User` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Friend_User2`
    FOREIGN KEY (`User_to` )
    REFERENCES `5charts`.`User` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
