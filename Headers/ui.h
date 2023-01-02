#include "service.h"

class UI {
public:
    UI(Service service);
    void start_ui();
private:
    void generate();
    void handle_admin(int cmd);
    void handle_user(int cmd, const std::string &extension);
    void read_data();
    void write_data();
    
    int mode;
    bool running = true;
    Service service;
};