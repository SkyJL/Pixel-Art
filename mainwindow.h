#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPixmap>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QFileDialog>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <iostream>



#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pixel_push_clicked();

    void on_picture_push_clicked();

    void on_picturize_Button_clicked();

    void on_size_tile_valueChanged(int value);



private:
    Ui :: MainWindow *ui;

    // Global Variables:

    QPixmap picture;
    QImage pixel_picture;
    QList<QPixmap> pictures;
    QList<QColor> meancolors;

    int tileSize;
    int height;
    int width;

    bool locked;
};


#endif // MAINWINDOW_H
