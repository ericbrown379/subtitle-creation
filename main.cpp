#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QProcess>
#include <iostream>


int main(int argc, char *argv[] ) {

    // Create a instance of my application
    QApplication app(argc, argv);

    // Create a instance of my widget
    QWidget mainWindow;
    // Display title of app
    mainWindow.setWindowTitle("Subtitles Creation App");

    //Change width and height of  (width,height)
    mainWindow.resize(400,300);

    //Intilaze box layot, you have to pass in the main window because taht what we want the box to display in
    QVBoxLayout *layout = new QVBoxLayout(&mainWindow);

    //App title label
    QLabel *titleLabel = new QLabel("Subtitle Creator App");
    //Style it
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; color: blue");
    layout->addWidget(titleLabel);

    //App Instruction label
    QLabel *instructionLabel = new QLabel("Please select any video file to create subtitles");
    //Style it
    instructionLabel->setAlignment(Qt::AlignCenter);
    instructionLabel->setStyleSheet("font-size: 20px; color: red");
    layout->addWidget(instructionLabel);


    // Select Button
    QPushButton *selectButton = new QPushButton("Select");
    selectButton->setStyleSheet("font-size: 18px; color: white; background-color: gray");
    layout->addWidget(selectButton);

    //File Name label
    QLabel *fileNameLabel = new QLabel("");
    //Style it
    fileNameLabel->setAlignment(Qt::AlignCenter);
    fileNameLabel->setStyleSheet("font-size: 20px; color: green");
    layout->addWidget(fileNameLabel);

    // Create Subtitles Button
    QPushButton *createButton = new QPushButton("Create");
    createButton->setStyleSheet("font-size: 18px; color: white; background-color: green");
    createButton->hide();
    layout->addWidget(createButton);

    //Status label
    QLabel *statusLabel = new QLabel("");
    //Style it
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("font-size: 20px; color: green");
    statusLabel->hide();
    layout->addWidget(statusLabel);

        //anouymous lambda function Select Button Action
    QObject::connect(selectButton, &QPushButton::clicked, [&]() {
        QString filePath = QFileDialog::getOpenFileName(
            &mainWindow,
            "Choose Video or Audio File",
            "",
            "Media Files (*.mp4 *.avi *.mkv *.mp3 *.wav);;All Files (*.*)"
            );

        if (!filePath.isEmpty()) {
            fileNameLabel->setText(filePath);
            createButton->show();
            statusLabel->show();
        }
    });



    // Create Button Action
    QObject::connect(createButton, &QPushButton::clicked, [&]() {

        QString videoFile = fileNameLabel->text();
        // Will give you the directory and name of teh videoFile someone selected

        QFileInfo fileInfo(videoFile);
        QString subtitleFile = fileInfo.absolutePath()+"/"+fileInfo.completeBaseName()+".srt";

        QProcess process;
        QString command = "/Users/ericbrown/.pyenv/shims/python";
        QString pythonScript = "/Users/ericbrown/Documents/githubrepo/subtitle-creation/server.py";

        QStringList arguments;
        arguments << pythonScript << videoFile << subtitleFile;

        process.start(command, arguments);
        if(!process.waitForFinished(-1)){
            std::cout<< "Error executed successfully";

        }
        else {
            std::cout<< "Scripts executed successfully";
        }

        QFile file(subtitleFile);
        if(file.exists()){
            statusLabel->setText("Created successfully");
        }
        else{
            statusLabel->setText("Problem creating subtitles...Try again");
        }





    });



    //Show the application Window
    mainWindow.show();

    app.exec();


};
