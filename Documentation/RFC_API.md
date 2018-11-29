# RFC protocol between client and Server

1. Connection
    - Connection
        * CONNECT [Client Name]
    - Response from Server : List of games
        * LIST GAME LIST\n ...
    - Join or Create Game 
        * JOIN [GAME NAME] [GAME PASSWORD=Empty]
        * CREATE [GAME NAME] [GAME PASSWORD=Empty] [GAME SLOT=4]
    - Response from server: give ip:port to connect
        * SERVER [IP]:[PORT]
    - Connect to party
        * CONNECT [Client Name]
    - LIST ENTITY and TYPE
        * GAME INFO\ntype: [Int] sprite: [PATH]\n ...
    
2. Game
    - Updates Entity with modification every x seconds
        * GAME UPDATE\nid: [Int] type: [Int], pos: []\n ...
    - Send Entity modification (Never modify entity on the client, just show what the server send)
        * MOVE PLAYER [X] [Y] / le serveur valide le move
        * FIRE CHARGING (a envoyer toute les x secondes)
        * FIRE SHOT charge / 3 (le serveur valide la charge)
    - Leave party
        * GAME LEAVE
    - Game over
        * GAME OVER
    - Game stats 
        * GAME stats 
