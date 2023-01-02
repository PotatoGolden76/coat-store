    #include <QApplication>
    #include <QPushButton>
    #include "Headers/gui.h"

    int main(int argc, char *argv[]) {
        QApplication a(argc, argv);

        auto repo = Repo();
        auto service = Service(repo);

        GUI gui{service};
        gui.show();

        return a.exec();
    }
