#ifndef SRC_EVENTS_HANDLER_H
#define SRC_EVENTS_HANDLER_H
#include "Handler.h"
#include <SDL2/SDL.h>
#include <vector>
class EventsHandler : public Handler
{
private:
    SDL_Event event;
    std::vector<class EventCallback*> eventCallbacks;
    static void exitCallBack();
public:
    bool initalize();
    EventsHandler();
    ~EventsHandler();
    HandlerError* tick();
};



#endif