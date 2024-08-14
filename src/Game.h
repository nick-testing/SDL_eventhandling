#ifndef GAME_H
#define GAME_H

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Surface SDL_Surface;

// Key press surfaces constants
enum KeyPressSurface {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_MOUSE,
    KEY_PRESS_SURFACE_TOTAL
};

class Game {
public:
    Game();
    void Run();

private:
    static const int SCREEN_HEIGHT = 720;
    static const int SCREEN_WIDTH = 1280;

    // Window used for program rendering
    SDL_Window* window;

    // Surface contained by the window
    SDL_Surface* screenSurface;

    // Images that will be shown on the screen
    SDL_Surface* keyPressedSurfaces[KEY_PRESS_SURFACE_TOTAL];

    // Currently displayed surface
    SDL_Surface* currentSurface = nullptr;

    bool Init();
    bool LoadMedia();
    void EventHandler();
    SDL_Surface* LoadSurface(const char*);
    void Close();
};

#endif