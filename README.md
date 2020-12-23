## Bulls and Cows - Word Guessing Game
<A simple word guessing game I am making in Unreal Engine 4 to learn C++ and UE.
  
## Description
This game is an isogram guessing game. Isograms are words with no repeating letter. The game gives you two letters as a hint and some lives to guess the word. A Bull means you the right letter is in the right place. A Cow means the right letter but in the wrong place. It's really simple! 
 
 The game is free of any UI. Everything you want is accessed via commands in the terminal. 
 
 [![Desktop-Screenshot.png](https://i.postimg.cc/mDJCZ9Zq/Desktop-Screenshot.png)](https://postimg.cc/hz8fpfdb)
 
 ## Installation
The game is free to install on Windows. You can find the .exe file in the releases section.
The game will soon be available in the Microsoft Store for Windows 10 PCs. It is highly recommneded to download from the Store, as updates are automatically installed.
 
##Logic
The game read a list of 1000 common English words, filtering the isograms, stores them in an array and gives the user a random isogram to guess. The hints are displayed at two random palces in the word. Guesses are checked for length and accuracy. The player is given an option to skip a word if they choose to, which restarts the game loop. Repeating words are possible, however. 
 
