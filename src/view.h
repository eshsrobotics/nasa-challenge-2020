#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include <SDL.h>

class View {
public:
    virtual void draw(SDL_Surface* screen) = 0;
    virtual SDL_Rect boundary() const = 0;
public:
    // Non-virtual functions.
    bool mouseOver() const;
};

#endif // VIEW_H_INCLUDED
