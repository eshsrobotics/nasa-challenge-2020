#include "view.h"

bool View::mouseOver() const {
    SDL_Rect rect = boundary();
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY)
    if (rect.x < mouseX && rect.x + rect.w > mouseX && rect.y < mouseY && rect.y + rect.h > mouseY) {
        return true;
    }
    return false;
}
View::~View() {

}
