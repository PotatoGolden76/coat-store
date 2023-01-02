#pragma once
#include <qwidget.h>
#include "coat.h"
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include "service.h"
#include "repo.h"
#include "HTMLHandler.h"
#include "CSVHandler.h"
#include <windows.h>
#include <shellapi.h>

class GUI: public QWidget
{
Q_OBJECT

public:
    GUI(Service& serv, QWidget *parent = 0);

    ~GUI();

private:
    HTMLHandler html_handler = HTMLHandler();
    CSVHandler csv_handler = CSVHandler();

    std::vector<Coat> basket_vector;

    int current_basket_index = 0;
    int current_list_index = 0;

    Service& service;

    QListWidget* coat_list;
    QListWidget* basket_list;

    QLineEdit* size_field;
    QLineEdit* color_field;
    QLineEdit* price_field;
    QLineEdit* quantity_field;
    QLineEdit* photo_field;

    QPushButton* add_coat;
    QPushButton* remove_coat;
    QPushButton* update_coat;

    QPushButton* html;
    QPushButton* csv;

    QPushButton* b_add_to_basket;
    QPushButton* b_open_photo;
    QPushButton* b_next;

    QLineEdit* filter_bar;

    void initGUI();
    void populate_coat_list();
    void populate_basket_list();

    void read_data();
    void write_data();

    void currentTextChanged(const QString &currentText);
    void textEdited(const QString &new_text);
    void addToBasket();

    void add();
    void update_button_function_too_many_names_aaaaa();
    void remove();

    void open_photo();
    void next();

    Coat get_coat_from_string(std::string selection);
    void close_app();

    void save_html();
    void save_csv();
};
