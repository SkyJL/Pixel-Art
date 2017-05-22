#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tile.h"
#include <QPixmap>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    locked = false;

    // Background activities, data, and properties.
    ui -> setupUi(this);

    // Standard picture size in UI label.
    ui->picture_label->setMinimumSize(278,302);

    // Width of picture_label frame.
    width = ui->picture_label -> width();

    // Height of picture_label frame.
    height = ui->picture_label -> height();


    // Size of tile for pixelation iteration.
    // tileSize = 15;


}
MainWindow::~MainWindow()
{
    delete ui;
}

//// Push button for pixelation.
//void MainWindow::on_pixel_push_clicked()
//{

//    // Transform a QPixel picture into a QImage picture.
//    // pixel_picture = picture.toImage();


//    // Assess horizontal axis via iteration, steps of tile's size.
//    for(int iteration_x = 0; iteration_x < pixel_picture.width(); iteration_x += tileSize)
//            // Assess vertical axis via iteration, steps of tile's size.
//            for(int iteration_y = 0; iteration_y < pixel_picture.height(); iteration_y += tileSize)
//            {

//                // Iteration counter and red, green, blue, alpha, qualities of pixel at iteration.
//                int count = 0, red = 0, green = 0, blue = 0, alpha = 0;

//                // Subloop: Iterate through the pixels within the main loop iteration.
//                for(int sub_iteration_x = 0; sub_iteration_x < tileSize; sub_iteration_x++)
//                    for(int sub_iteration_y = 0; sub_iteration_y < tileSize; sub_iteration_y++){

//                        // Stopping criterion: For boundary pixels.
//                        if (iteration_x + sub_iteration_x < pixel_picture.width() && iteration_y + sub_iteration_y <pixel_picture.height())
//                        {

//                            // Function: From QRgb to QColor.
//                            QColor color(pixel_picture.pixel(iteration_x + sub_iteration_x, iteration_y + sub_iteration_y));

//                            // The step is important for identifying the color of the specific pixel via QColor functionality.
//                            // With coordinates: iteration_x + sub_iteration_x, and iteration_y + sub_iteration_y.
//                            red += color.red();
//                            green += color.green();
//                            blue += color.blue();
//                            alpha += color.alpha();

//                            // Iteration counter: Pixels in tile.
//                            count++;
//                        }
//                    }

//                // Calculate the mean of the color channels.
//                red /= count; green /= count; blue /= count; alpha /= count;

//                // Create an instance of the QRGB data type, from QColor data type.
//                QRgb meanColor = qRgba(red, green, blue, alpha);

//                // With the mean color (as assessed via the tile iteration) place a tile.
//                for(int sub_iteration_x = 0; sub_iteration_x < tileSize; sub_iteration_x++)
//                    for(int sub_iteration_y = 0; sub_iteration_y < tileSize; sub_iteration_y++)

//                        // If the iterators of the horizontal and vertical axis (of the picture loop and the tile loop) span beyond the picture size, end the loop.
//                        if (iteration_x + sub_iteration_x < pixel_picture.width() && iteration_y + sub_iteration_y <pixel_picture.height())
//                            pixel_picture.setPixel(iteration_x + sub_iteration_x, iteration_y + sub_iteration_y, meanColor);



//            }
//    // From the pixelized picture, transform from a QImage into a QPixmap: pixel_picture to "pixmap_picture".
//    QPixmap pixmap_picture = QPixmap :: fromImage(pixel_picture);

//    // Display the picture with an applied pixelation filter.
//    // Maintain scale with "pixel_label" width and height (global variables, see mainwindow.h), and keep the aspect ratio.
//    ui -> pixel_label -> setPixmap(pixmap_picture.scaled(width, height, Qt :: KeepAspectRatio));

//}

// From the UI, when the “Load a picture” button is pushed:
void MainWindow::on_picture_push_clicked()
{
    // Picture location: Select a photo.
    QString fileName = QFileDialog :: getOpenFileName(this,
        tr("Open Image"), " Pictures ", tr("Image Files (*.png *.jpg *.bmp)"));

    picture.load(fileName);
    pixel_picture.load(fileName);

    // Arrange the photo and the label (widget). Note that picture_label is the widget label name.
    // The ".scaled" and "KeepAspectRatio" ensures that the picture maintains the proper aspect ratio within the frame.
    // Note that if the scale is set beyond the window size, further challenges arise. The scale is arranged with the picture_label width and height.
    ui -> picture_label -> setPixmap(picture.scaled(width, height, Qt :: KeepAspectRatio));
}

// Picturize.
void MainWindow::on_picturize_Button_clicked()
{

    // Open file (images).
    QStringList fileNames = QFileDialog :: getOpenFileNames(this,
        tr("Open Images"), " Picture ", tr("Image Files (*.png *.jpg *.bmp)"));

    // Specify criterion.
    for(int e = 0; e < fileNames.length(); e++){\
        QPixmap pix(fileNames[e]);

        // Append sample pictures in a picture list.
        pictures.append(pix);
    }


// Calculate the mean color of the sample images.


    // Criterion length of sample picture list (iteration I).
    for(int c = 0 ; c < pictures.size(); c ++)
    {
        int count_picture = 0, r_picture = 0, g_picture = 0, b_picture = 0, a_picture = 0;

        // Transform the sample picture class type into a QImage Picture.
        QImage samplepicture = pictures[c].toImage();

        // Assess pixels within images of iteration I (Iteration II).
        for(int m = 0; m < samplepicture.width(); m ++){

                // Assess vertical axis via iteration, steps of tile's size.
                for(int n = 0; n < samplepicture.height(); n ++)
                {
                    // The pixel color at "m" and "n" of sample picture.
                    QColor color_picture(samplepicture.pixel(m, n));

                    // Identify the color of the specific pixel via QColor functionality (with coordinates: m, and n).
                    r_picture += color_picture.red();
                    g_picture += color_picture.green();
                    b_picture += color_picture.blue();
                    a_picture += color_picture.alpha();

                    // Iteration counter: Pixels in tile.
                    count_picture ++;

                }
        }


        // Average the color chanels by calculating the total color intensity per channel for the sample picture and divide by the count.
        r_picture /= count_picture; g_picture /= count_picture; b_picture /= count_picture; a_picture /= count_picture;

        // With QColor, store the mean color of the sample picture.
        QColor sampleMean = qRgba(r_picture, g_picture,b_picture,a_picture);

        // Append the QColor of the sample picture onto the QColor sample picture list.
        meancolors.append(sampleMean);

    // End loop.
    }


// Calculate four channel average: r g b a.


    // Make a Lithograph of the pixelized picture.
    QImage lithograph = pixel_picture;

    // Location at iteration of pixelization process:
    for(int i = 0; i < pixel_picture.width(); i += tileSize)
    {
            // Assess vertical axis via iteration, steps of tile's size.
            for(int j = 0; j < pixel_picture.height(); j += tileSize)
            {

                // Iteration counter and r, g, b, a, qualities of pixel at iteration.
                int count_tile = 0, r_tile = 0, g_tile = 0, b_tile = 0, a_tile = 0;

                // Subloop: Iterate through the pixels within the main loop iteration.
                for(int k = 0; k < tileSize; ++k){
                    for(int l = 0; l < tileSize; ++l){

                        // Stopping criterion: For boundary pixels.
                        if (i + k < pixel_picture.width() && j + l <pixel_picture.height())
                        {

                            // Function: From QRgb to QColor.
                            QColor color(pixel_picture.pixel(i + k, j + l));

                            // Identify the color of the specific pixel via QColor functionality (with coordinates: i + k, and j + l).
                            r_tile += color.red();
                            g_tile += color.green();
                            b_tile += color.blue();
                            a_tile += color.alpha();

                            // Iteration counter: Pixels in tile.
                            count_tile ++;
                        }
                    }
                }

                // Calculate the mean of the color channels.
                r_tile /= count_tile; g_tile /= count_tile; b_tile /= count_tile; a_tile /= count_tile;

                // Calling Tile class, make a tile.
                Tile *tile = new Tile(r_tile,g_tile,b_tile,a_tile, i, j);

                // Call the findBestPicture function to calculate the appropriate sample picture with via minimum color range calculation (Tile class function).
                int bestIndex = tile->findBestPicture(meancolors);

                // Draw the appropriate picture onto the the lithograph.
                lithograph = tile->applyBestPicture(lithograph, pictures[bestIndex].toImage(), tileSize);

            // End loop.
            }
    }

    // Show the lithograph with the appropriate sample picture drawn.
    QPixmap picturized_picture = QPixmap :: fromImage(lithograph);

    // Protect aspect ratio properties.
    ui -> picturize_label -> setPixmap(picturized_picture.scaled(width, height, Qt :: KeepAspectRatio));

    // Save the picturized lithograph in the Pixel Art folder.
    picturized_picture.save("Picture.jpg");
}


// Pixelize.
void MainWindow::on_size_tile_valueChanged(int value)
{
    // Fast sliding could be computationally heavy. The lock promotes the program to successfully function.
    if(locked) return;

    // Begin process, lock on.
    locked = true;

    // The pixelized tile size is equal to the (status of the GUI bar * the width of the loaded picture) / 100 plus one.
    // The plus one compensates for the zero starting point of the slider.
    tileSize = ((value) * picture.width())/100+1;

    // Transform a QPixel picture into a QImage picture.
    QImage pixel_picture = picture.toImage();


    // Assess horizontal axis via iteration, steps of tile's size.
    for(int iteration_x = 0; iteration_x < pixel_picture.width(); iteration_x += tileSize)
            // Assess vertical axis via iteration, steps of tile's size.
            for(int iteration_y = 0; iteration_y < pixel_picture.height(); iteration_y += tileSize)
            {

                // Iteration counter and red, green, blue, alpha, qualities of pixel at iteration.
                int count = 0, red = 0, green = 0, blue = 0, alpha = 0;

                // Subloop: Iterate through the pixels within the main loop iteration.
                for(int sub_iteration_x = 0; sub_iteration_x < tileSize; sub_iteration_x++)
                    for(int sub_iteration_y = 0; sub_iteration_y < tileSize; sub_iteration_y++){

                        // Stopping criterion: For boundary pixels.
                        if (iteration_x + sub_iteration_x < pixel_picture.width() && iteration_y + sub_iteration_y <pixel_picture.height())
                        {

                            // Function: From QRgb to QColor.
                            QColor color(pixel_picture.pixel(iteration_x + sub_iteration_x, iteration_y + sub_iteration_y));

                            // The step is important for identifying the color of the specific pixel via QColor functionality.
                            // With coordinates: iteration_x + sub_iteration_x, and iteration_y + sub_iteration_y.
                            red += color.red();
                            green += color.green();
                            blue += color.blue();
                            alpha += color.alpha();

                            // Iteration counter: Pixels in tile.
                            count++;
                        }
                    }

                // Calculate the mean of the color channels.
                red /= count; green /= count; blue /= count; alpha /= count;

                // Create an instance of the QRGB data type, from QColor data type.
                QRgb meanColor = qRgba(red, green, blue, alpha);

                // With the mean color (as assessed via the tile iteration) place a tile.
                for(int sub_iteration_x = 0; sub_iteration_x < tileSize; sub_iteration_x++)
                    for(int sub_iteration_y = 0; sub_iteration_y < tileSize; sub_iteration_y++)

                        // If the iterators of the horizontal and vertical axis (of the picture loop and the tile loop) span beyond the picture size, end the loop.
                        if (iteration_x + sub_iteration_x < pixel_picture.width() && iteration_y + sub_iteration_y <pixel_picture.height())
                            pixel_picture.setPixel(iteration_x + sub_iteration_x, iteration_y + sub_iteration_y, meanColor);



            }
    // From the pixelized picture, transform from a QImage into a QPixmap: pixel_picture to "pixmap_picture".
    QPixmap pixmap_picture = QPixmap :: fromImage(pixel_picture);

    // Display the picture with an applied pixelation filter.
    // Maintain scale with "pixel_label" width and height (global variables, see mainwindow.h), and keep the aspect ratio.
    ui -> pixel_label -> setPixmap(pixmap_picture.scaled(width, height, Qt :: KeepAspectRatio));


    locked = false;

}
