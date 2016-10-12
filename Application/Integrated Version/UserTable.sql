USE BugTracker;

DROP TABLE IF EXISTS ATTACHMENT;
DROP TABLE IF EXISTS NOTIFICATION;
DROP TABLE IF EXISTS SUBSCRIPTION;
DROP TABLE IF EXISTS COMMENT;
DROP TABLE IF EXISTS HISTORY;
DROP TABLE IF EXISTS BUG;
DROP TABLE IF EXISTS PLATFORM;
DROP TABLE IF EXISTS COMPONENT;
DROP TABLE IF EXISTS APPLICATION;
DROP TABLE IF EXISTS USER;

CREATE TABLE USER
(
	ID INT AUTO_INCREMENT PRIMARY KEY,
	First_Name VARCHAR(20),
	Family_Name VARCHAR(20),
	Username VARCHAR(30) UNIQUE,
	Email_Address VARCHAR(50) UNIQUE,
	Password CHAR(32),
	Gender VARCHAR(10),
	Reputation INT,
	Role VARCHAR(20),
	MemberSince DATETIME DEFAULT CURRENT_TIMESTAMP,
    lastLoggedIn DATETIME DEFAULT CURRENT_TIMESTAMP,
	ProfilePicture VARCHAR(50),
    Status BOOLEAN DEFAULT TRUE
);

CREATE TABLE APPLICATION
(
	Name VARCHAR(30),
	Version DOUBLE(4, 2),
    PRIMARY KEY(Name, Version)
);

CREATE TABLE COMPONENT
(
	Application VARCHAR(30),
	Name VARCHAR(30),
    PRIMARY KEY (Application, Name),
    FOREIGN KEY (Application) REFERENCES APPLICATION(Name) ON DELETE CASCADE
);

CREATE TABLE PLATFORM
(
	Name VARCHAR(30) PRIMARY KEY
);


CREATE TABLE BUG
(
	ID INT AUTO_INCREMENT PRIMARY KEY,
	Title VARCHAR(50) UNIQUE,
	Status ENUM('NEW', 'VERIFIED', 'UNDER REVIEW', 'PATCH UPLOADED', 'FIXED', 'CLOSED'),
	Application VARCHAR(30),
	Version DOUBLE(4, 2),
	Description VARCHAR(200),
	Platform VARCHAR(30),
	Component VARCHAR(30),
	Priority ENUM('HIGH', 'MEDIUM','LOW'),
	Severity ENUM('CRITICAL','MAJOR','MINOR'),	
	Walkthrough TEXT,
	AssignedTo VARCHAR(30) DEFAULT 'Unassigned',
	IdentifiedBy VARCHAR(30),
	DateSubmitted DATETIME DEFAULT CURRENT_TIMESTAMP,
	FOREIGN KEY (Application) REFERENCES APPLICATION(Name)  ON DELETE CASCADE,
    FOREIGN KEY (Platform) REFERENCES PLATFORM(Name)  ON DELETE CASCADE,
	FOREIGN KEY (IdentifiedBy) REFERENCES USER(Username) ON DELETE CASCADE
);
CREATE TABLE HISTORY
(
	BugID INT,
    History TEXT,
    FOREIGN KEY (BugID) REFERENCES BUG(ID)
);

CREATE TABLE COMMENT
(
	BugID INT,
	UserID INT,
    Comment TEXT,
	Submitted DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (BugID) REFERENCES BUG(ID),
    FOREIGN KEY (UserID) REFERENCES USER(ID)
);

CREATE TABLE SUBSCRIPTION
(
	BugID INT,
	UserID INT,
    PRIMARY KEY (BugID, UserID),
    FOREIGN KEY (BugID) REFERENCES BUG(ID),
    FOREIGN KEY (UserID) REFERENCES USER(ID)
);

CREATE TABLE NOTIFICATION
(
	UserID INT,
	Notification TEXT,
    Date DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (UserID) REFERENCES USER(ID)
);

CREATE TABLE ATTACHMENT
(
	BugID INT,
	Path VARCHAR(100),
    FOREIGN KEY (BugID) REFERENCES BUG(ID)
);

INSERT INTO USER (First_Name, Family_Name, Username, Email_Address, Password, Gender, Reputation, Role, MemberSince, ProfilePicture)
VALUES
('Nathaniel', 'Smith', 'njs109', 'njs109@uowmail.edu.au', 'mypass', 'M', 0, 'System Administrator', CURDATE(), "Blank"),
('Bob', 'Smith', 'bob109', 'bob@uowmail.edu.au', 'mypass', 'M', 0, 'Developer', CURDATE(), "Blank");

INSERT INTO APPLICATION(Name, Version)
VALUES
('Photoshop', 1.0),
('Photoshop', 1.1),
('Photoshop', 1.2),
('Photoshop', 1.3),
('Chrome', 11.0),
('Chrome', 11.1),
('Chrome', 11.2),
('Chrome', 11.5),
('FireFox', 1.0),
('FireFox', 1.1),
('MineCraft', 1.2);

INSERT INTO COMPONENT(Application, Name)
VALUE
('Photoshop', 'TaskBar'),
('Photoshop', 'MenuBar'),
('FireFox', 'JMC_Tab');

INSERT INTO PLATFORM(Name)
VALUES
('Windows 7'),
('Windows Vista'),
('Windows XP'),
('MAC OS'),
('Windows 8.1'),
('Windows 10');

INSERT INTO BUG (Title, Status, Application, Version, Description, Priority, Severity, IdentifiedBy)
VALUES
('Bug10', 'NEW', 'Photoshop', 1.2, 'Description of the bug', 'HIGH', 'CRITICAL', 'njs109'),
('Bug2', 'VERIFIED', 'Chrome', 11.2, 'Description of the bug','HIGH', 'MAJOR', 'njs109'),
('Bug3', 'CLOSED', 'FireFox', 1.1, 'Description of the bug','LOW', 'MINOR', 'njs109'),
('Bug4', 'NEW', 'MineCraft', 1.2, 'Description of the bug','HIGH', 'CRITICAL', 'njs109'),
('Bug5', 'NEW', 'Photoshop', 1.2, 'Description of the bug', 'HIGH', 'CRITICAL', 'njs109');

INSERT INTO NOTIFICATION(UserID, Notification)
VALUES
(1, "Hello");

