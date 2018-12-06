RFC&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; &ensp;Bernard Erwan<br>
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp;&emsp;&emsp;&emsp;&emsp;ISI<br>
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; &emsp; &emsp; &emsp;&emsp;&emsp;&emsp;&ensp;&emsp;05 November 2018<br>

<br>
<br>
<br>
<br>
<br>
<br>
<div align="center">
                       R-type Protocole Documentation
</div>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>

Introduction
-----------
This is the User &ensp;documentation for the our EPITECH projet R-Type.&ensp;It define<br>
the &ensp;way the &ensp;Server and &ensp;Client &ensp; interact. &ensp; It &ensp;only &ensp;gives &ensp;important<br>
informations to the client.

This &ensp;&ensp;protocole provides a client side procedure to &ensp;&ensp;get &ensp;information<br>
about the runnings games on the server and the game it is connected to.<br>



<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
Bernard&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; &emsp; &emsp; &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [page 1]

******

Messages
-----------

<br>

## **1.1 Game manager**
<br>

### 1.1.1 MESSAGE Connection

Commande: Connection
Parameter: <nick>

It is the first message you send when connecting to the manager.

Reponse:
	LIST GAME

### 1.1.2 MESSAGE JOIN
Commande: JOIN 
Parameter: <GameName> [PASSWORD: <Password\>\]

Join a running game.

Reponse:
	SERVER

### 1.1.3 MESSAGE CREATE
Commande: CREATE
Parameter: <GameName> [PASSWORD: <Password\>\]

Create a game on the server manager and return the game server information

Response:
	SERVER

### 1.1.3 MESSAGE LIST GAME
Commande: LIST GAME
Parameter: <gamename> <gamename>...

Response that gives all game name lists on the&emsp;server manager separated by  a <br>line return.

<br>
<br>
<br>
<br>

Bernard&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; &emsp; &emsp; &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; \[page 2]
******

### 1.1.3 MESSAGE SERVER
Commande: SERVER
Parameter: <ip>:<port>

response that gives the port and ip to a game.

## **1.2 Game server**

<br>

### 1.2.1 MESSAGE Connect
Commande: Connect
Parameter: <Nick>

It is the first message you must send when you connect to a game.

Response:
	GAME INFO

### 1.2.2 MESSAGE MOVE PLAYER
Commande: MOVE PLAYER
Parameter: <UP|DOWN|RIGHT|LEFT>

Message that moves your player on the game.

### 1.2.3 MESSAGE FIRE SHOOT
Commande: FIRE SHOOT
Parameter: <1-3>

Message that shoot from your player.

### 1.2.4 MESSAGE GAME LEAVE
Commande: GAME LEAVE

Message you must send when you leave a game.


<br>
<br>
<br>
<br>
<br>
<br>
<br>
Bernard&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; &emsp; &emsp; &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [page 3]

******

### 1.2.5 MESSAGE GAME UPDATE
Commande: GAME UPDATE
Parameter: id: <EntityId> type: <EntityType> animTime: <EntitySpriteId>  pos: <Posx> <PosY>

Message sent by the server too update all entity on the client.

### 1.2.6 MESSAGE GAME INFO
Commande: GAME INFO
Parameter: type: <EntityType> sprite: <EntitySpritePath>  size: <Posx> <PosY>

Message sent by the server to init each sprite path by entity.

<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>

Bernard&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; &emsp; &emsp; &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; \[page 4]<br>
******
