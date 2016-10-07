#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#define FPS 60.0f
#define PS (1.0f * FPS)      /** Physics Speed (steps/frame) **/

#define DEBUG
//#define HEAVY_DEBUG

#include <string>
#include <vector>
#include <iostream>
#include <SDL_stdinc.h>             //SDL types

enum MarioMode {MODE_QUIT, MODE_LEVEL, MODE_MENU, MODE_EDITOR};
class Mario;

enum MenuMode {MAIN_MENU = 0, LEVEL_SELECTION = 1};
class Menu;
class Editor;
class Level;

/** Entities **/
class Object;
class DynamicObject;
class Player;
class Enemy;
class Item;
class Projectile;
class Decor;
class Trigger;
class HPTrigger;
class StaticObject;
class CollisionHandler;
class Rectangle;
class Vect2;
class Vect2i;
enum PathType {LINEAR = 0, SQUARED = 1, AMORTIZED = 2};
class Path1D;
class Path2D;
class Timer;
class LoopingTimer;
class HandPattern;
struct HandPatternSection;
struct HandPatternEvent;
struct HandPatternQueue;

/** Input **/

class KeyStates;

/** UI **/
class Button;
class Dialog;

/** Graphics **/

namespace Graphics{

class Main;
class Animation;
class RenderCoin;
class RenderDialog;
class RenderEntity;
struct GfxData;
class ViewPort;
class Font;
class Write;
class Color;
class Surface;
class Texture;
class TextureSet;
class TextureSetHandler;
class Background;
class RenderBackground;
class RenderEditor;
}

namespace Physic{
    struct StaticParams;
    struct DynamicParams;
    struct CollisionParams;
}

class GfxParameters;

/** Sound **/
class Sound;
class SoundStack;

#endif // COMMON_H_INCLUDED
