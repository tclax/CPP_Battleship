# CPP_Battleship
Classic game of battleship coded to develop a smart computer to play against. Computer has different attack strategies coded to sink the opponents ships in the least amount of turns.

Run the Battleship Console App to run the Battleship simulations. The current simulation attack strategies are the following:

Random attack: Randomly generates coordinates to attack with until all ships are sunk.
Linear Horizontal: Moves left to right from top to bottom until all ships are sunk.
Linear Vertical: Move top to bottom from left to right until all ships are sunk.
Linear Diagonal: Moves in a diagonal pattern from top left to bottom right of the board until all ships are sunk.
Search and Destroy: The start of building a 'smart' computer. Search and Destroy (S&D) will use the linear horizontal at first to attack. When a hit is registered, it will attack that coordinate from the north, south, west, and east until each direction registers a miss. This is the 'smart' computer attack strategy because once it finds a hit will 'search and destroy' until all hits in that cooridnate are found.
