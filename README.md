# BurgerTime
DAE Programming 4 Project: Engine + Game

## Engine Features:
Components Pattern: 
- defining different behaviors or capabilities for gameObject
- components are decoupled and can be reused for different gameObjects

Observer Pattern:  
- Subject own a list Observers
- PeterPepper is the Subject and score and healtComponent are the observers
- notify the Observer with user defined Event enum 

GameObject: 
- has a Transform Component 
- can Add Components and children

Inputs: 
- supports controller buttons 
- allows multiplayer with multiple controllers
- use Command Pattern for executing actions when any inputs are triggered
- Command pattern is used to execute all task of Peter Pepper

State:
- Both PeterPepper and the hotdog enemy use a state Pattern to change their movement direction.

Other:
- Load the game levels with text Files
- TextComponent, FpsComponent, ServiceLocator,...
