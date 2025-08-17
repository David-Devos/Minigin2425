# My Engine
This project is a variation upon the engine foundation given to me by DAE known as 'Minigin', as well as an attempted remake of the 1982 game 'Pengo'.


# Game Requirements
The game I was required to make had it's own requirements. Alas, despite my best efforts, not all have been met.
You CAN play as Pengo and move around, push and break blocks, splash water to stun SnoBees and die. However, there is no way ingame to restart a level.
Also, as soon as SnoBees come into contact with a sliding block, they immediately perish instead of being pushed and eventually squashed.
On top of that, despite there being a counter visually, I failed to implement a functioning score counter.
SnoBees move around on their own through a simple random chance behavior pattern and break blocks they come in contact with.
This pattern does result in them getting stuck on the outer boundaries from time to time as well as coincidental immaculate overlapping with their kin.
But they also spawn only once on start up and do not grow out of previously established blocks.
When SnoBees touch Pengo, Pengo dies.
When Pengo interacts with one of the outer boundaries, all SnoBees adjacent to that boundary will be stunned.
The game does not have a main menu or game over screen, nor does it have any kind of high score mechanic (partly due to there not being a functioning score counter).
There is no option for multiplayer. There is no controller support. All inputs are via keyboard.

# Design Choices
I purposefully kept States away from ingame functionality (i.e. movement, interaction, etc.) because I felt like this would replace the roll of Commands.
That being said, I had hoped to eventually get to States to handle a menu state of sorts, but as mentioned before, I didn't get that far.
For events, I chose to go for Observers/Subjects. While coupling was briefly an issue when trying to connect the engine to the game, this was solved when I
switched from defining an event type by enum class, to defining an event type by typeof(EventClass). This helped particularly with the following.
I chose to implement collisions (triggers, to be precise). I built these in engine, but to interact with the game through events, I required an in-engine not-game-specific event which is how I got to my choice for events. I wanted collisions because despite my following choice being 'making my game gridlocked', objects still slid between positions on that grid. If I were to design overlap through grid positions, I felt like this wouldn't come across very well.
As mentioned above, I chose to make my game gridlocked. This had it's ups and downs. All grid interaction became nicer because I had single point access to everything on my grid. The only challenge was to make my grid system engine bound. Even still, I think I managed fairly well.

# Consensus
Despite my best efforts, not all targets were met in this task. HOWEVER, I am glad to have been put through this and I am happy with my end result. It has broadened my understanding of not only C++, but design patterns needed to handle C++ appropriately.



link to the github page (if you're not there already): https://github.com/David-Devos/Minigin2425.git
