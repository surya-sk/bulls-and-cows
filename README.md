## Bulls and Cows - Word Guessing Game
A simple word guessing game made in Unreal Engine 4 to learn C++ and UE.
  
## Description
This game is an isogram guessing game. Isograms are words with no repeating letter. The game gives you two letters as a hint and some lives to guess the word. A Bull means you the right letter is in the right place. A Cow means the right letter but in the wrong place. It's really simple! 
 
 The game is free of any UI. Everything you want is accessed via commands in the terminal. 
 
 [![Desktop-Screenshot.png](https://i.postimg.cc/mDJCZ9Zq/Desktop-Screenshot.png)](https://postimg.cc/hz8fpfdb)
 
 ## Installation
The game is free to install on Windows. The game is available on the [Microsoft Store](https://www.microsoft.com/store/productId/9NWK9KJ62HMP) for Windows 10 PCs. It is highly recommneded to download from the Store, as updates are automatically installed.
You can also find the .exe file in the [Releases](https://github.com/surya-sk/bull-cow-ue4/releases) if you're running an earlier version of Windows, or prefer an install wizard. You won't recieve automatic updates if you download the .exe.

## Feedback
All feedback, especially constructive, is appreciated. To report bugs or request features, create an issue on GitHub or [email me](surya.sk05@outlook.com) if you don't have a GitHub account. Please be as specific as possible when creating issues and be sure to provide steps to reproduce when reporting bugs. PRs are welcome.  
 
## Logic
The game read a list of 1000 common English words, filtering the isograms, stores them in an array and gives the user a random isogram to guess. The hints are displayed at two random palces in the word. Guesses are checked for length and accuracy. The player is given an option to skip a word if they choose to, which restarts the game loop. Repeating words are possible at this stage, however. 
 
