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
-- Table `5charts`.`Chart`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `5charts`.`Chart` ;

CREATE  TABLE IF NOT EXISTS `5charts`.`Chart` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `Owns_Stock_id` INT NOT NULL ,
  `Owns_User_id` INT NOT NULL ,
  `date_added` DATETIME NOT NULL ,
  `start_date` DATETIME NOT NULL ,
  `end_date` DATETIME NOT NULL ,
  `period` INT(11)  NOT NULL ,
  `width` INT(11)  NOT NULL ,
  `height` INT(11)  NOT NULL ,
  PRIMARY KEY (`id`, `Owns_Stock_id`, `Owns_User_id`) ,
  INDEX `fk_Chart_User_has_Stock1` (`Owns_Stock_id` ASC, `Owns_User_id` ASC) ,
  CONSTRAINT `fk_Chart_User_has_Stock1`
    FOREIGN KEY (`Owns_Stock_id` , `Owns_User_id` )
    REFERENCES `5charts`.`Owns` (`Stock_id` , `User_id` )
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
-- Table `5charts`.`Feeds`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `5charts`.`Feeds` ;

CREATE  TABLE IF NOT EXISTS `5charts`.`Feeds` (
  `id` INT NOT NULL ,
  `name` VARCHAR(45) NULL ,
  `link` VARCHAR(45) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = MyISAM;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
