#include <QApplication>
#include <QWidget>



int main(int argc, char *argv[] ) {

    // Create a instance of my application
    QApplication app(argc, argv);

    // Create a instance of my widget
    QWidget mainWindow;
    // Display title of app
    mainWindow.setWindowTitle("Subtitles Creation App");

    //Change width and height of  (width,height)
    mainWindow.resize(400,300);

    //Show the application Window
    mainWindow.show();

    app.exec();



};
