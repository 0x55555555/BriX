#include "BxMainWindow.h"
#include <QtWidgets>


BxMainWindow::BxMainWindow() :
    QMainWindow()
{
    // create UI elements
    createToolBox(); // populates mainToolBox with widgets
    createActions();
    createMenus();
    createToolBars();

    // scene and view setup
    scene = new BxLevelScene();
    scene->setSceneRect(-4000, -4000, 8000, 8000);
    scene->setBackgroundBrush(Qt::gray);
    view = new BxLevelView(scene);
    view->centerOn(0,0);

    connect(scene, SIGNAL(selectionChanged()), this, SLOT(selectionChanged()));
    connect(scene, SIGNAL(itemInserted()), this, SLOT(clearButtons()));
    connect(scene, SIGNAL(itemDeleted()), this, SLOT(clearAttributeEditor()));
    connect(scene, SIGNAL(cameraComplete()), this, SLOT(clearButtons()));

    attributeEditor = new QWidget();
    attributeEditor->setMinimumWidth(200);
    populateAttributeEditor();

    QVBoxLayout* attributePane = new QVBoxLayout();
    attributePane->setAlignment(Qt::AlignTop);
    QLabel* label = new QLabel("Attribute Editor");
    attributePane->addWidget(label);

    attributePane->addWidget(attributeEditor);

    //layout setup
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(mainToolBox);
    layout->addWidget(view);
    layout->addLayout(attributePane);
//    layout->addWidget(attributeEditor);

    QWidget* mainWidget = new QWidget;
    mainWidget->setLayout(layout);

    setCentralWidget(mainWidget);
    setWindowTitle("Brix");
}

void BxMainWindow::createToolBox()
{
    // hook up button group click signals, so that main window can handle functionality
    actorButtonGroup = new QButtonGroup(this); // widgets need pointer to parent QObject
    actorButtonGroup->setExclusive(false); // not bullet-point mode
    connect(actorButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(actorButtonGroupClick(QAbstractButton *)));

    cameraButtonGroup = new QButtonGroup(this);
    cameraButtonGroup->setExclusive(false);
    connect(cameraButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(cameraButtonGroupClick(QAbstractButton *)));

    // build layouts of widgets
    QGridLayout* actorLayout = new QGridLayout;
    actorLayout->setAlignment(Qt::AlignTop);
    QPushButton* addActorButton = new QPushButton("Add Actor");
    addActorButton->setCheckable(true);
    actorButtonGroup->addButton(addActorButton);
    actorLayout->addWidget(addActorButton);

    QGridLayout* cameraLayout = new QGridLayout;
    cameraLayout->setAlignment(Qt::AlignTop);
    QPushButton* AddCameraPathButton = new QPushButton("Add Camera Path");
    AddCameraPathButton->setCheckable(true);
    cameraButtonGroup->addButton(AddCameraPathButton);
    cameraLayout->addWidget(AddCameraPathButton);



    // add layout to king widget
    QWidget* actorWidget = new QWidget;
    QWidget* cameraWidget = new QWidget;
//    cameraWidget->setSizePolicy(QSizePolicy(QSizePolicy::Maximum));
//    actorWidget->setSizePolicy(QSizePolicy(QSizePolicy::Maximum));
    cameraWidget->setLayout(cameraLayout);
    actorWidget->setLayout(actorLayout);

    mainToolBox = new QToolBox;
//    mainToolBox->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored));
    mainToolBox->setMinimumWidth(actorWidget->sizeHint().width());
    mainToolBox->addItem(actorWidget, tr("Create Actors"));
    mainToolBox->addItem(cameraWidget, tr("Camera"));
}

void BxMainWindow::createActions() // actions connect UI to functions
{
    aboutAction = new QAction(tr("Info"),this);
    aboutAction->setShortcut(tr("Ctrl+T"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutMessage()));

    newAction = new QAction(tr("New"),this);
    newAction->setShortcut(tr("Ctrl+N"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    saveAsAction = new QAction(tr("Save As"),this);
    saveAsAction->setShortcut(tr("Ctrl+Shift+S"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    loadAction = new QAction(tr("Open File"),this);
    loadAction->setShortcut(tr("Ctrl+O"));
    connect(loadAction, SIGNAL(triggered()), this, SLOT(loadFile()));
}

void BxMainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(loadAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}


void BxMainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(saveAsAction);

    aboutToolBar = addToolBar(tr("Edit"));
    aboutToolBar->addAction(aboutAction);

//    toolButtonAbout = new QToolButton;

//    connect(toolButtonAbout, SIGNAL(clicked()), this, SLOT(aboutMessage());

}

void BxMainWindow::clearAttributeEditor()
{
    if(attributeEditor->layout() != NULL) // if attributeEditor is populated
    {
        QLayoutItem* item;
        while (( item = attributeEditor->layout()->takeAt(0)) != NULL )
        {
            delete item->widget();
            delete item;
        }
        delete attributeEditor->layout();
    }
}

void BxMainWindow::populateAttributeEditor()
{
    clearAttributeEditor();
    QVBoxLayout* attributeLayout = new QVBoxLayout();
    attributeLayout->setAlignment(Qt::AlignTop);

    if((scene) && !(scene->items().empty()))
    {
        BxNodeActor* item = dynamic_cast<BxNodeActor*>(scene->selectedItems().first());

        if(item)
        {
            QWidget* ctrlWidget = item->getControls();
            if(ctrlWidget)
                attributeLayout->addWidget(ctrlWidget);
        }
    }
    attributeEditor->setLayout(attributeLayout);
}

void BxMainWindow::selectionChanged() // UPDATES UI (ATTRIBUTE PANE) WHEN SELECTION CHANGES
{
    if(!(scene->selectedItems().empty()))
    {
        populateAttributeEditor();
    }
    else
    {
        clearAttributeEditor();
    }
}

void BxMainWindow::clearButtons() // RESETS BUTTON STATES TO DEFAULT
{
    QList<QAbstractButton *> buttons = actorButtonGroup->buttons();
    foreach (QAbstractButton *button, buttons)
    {
            button->setChecked(false);
    }
    buttons = cameraButtonGroup->buttons();
    foreach (QAbstractButton *button, buttons)
    {
            button->setChecked(false);
    }

}

void BxMainWindow::newFile()
{
    if (QMessageBox::question(
            this,
            "Are you sure?",
            "Are you sure you want a new file?",
            QMessageBox::Yes,
            QMessageBox::No) == QMessageBox::No)
    {
        return;
    }

    scene->clear();
}

void BxMainWindow::saveFile()
{
    if(savePath == "")
    {
        saveAs();
    }

}

void BxMainWindow::saveAs()
{
    QString path = QFileDialog::getSaveFileName(this, "Filename", QString(), "*.json");
    if (path.isEmpty())
    {
        return;
    }

    savePath = path;
    QFile saveFile(savePath);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonObject saveObject;
    QJsonArray actorArray;
    QJsonObject camJsonObject;

    foreach(auto item, scene->items())
    {
        auto actor = dynamic_cast<BxNodeActor*>(item);
        if (actor)
        {
            QJsonObject json;
            actor->writeToJson(json);
            actorArray.append(json);
        }
    }

    BxNodePath* camPath = scene->getCameraPath();
    if(camPath)
    {
        camPath->writeToJson(camJsonObject);
    }

    saveObject["actors"] = actorArray;
    saveObject["camPath"] = camJsonObject;

    QJsonDocument saveDoc(saveObject);
    saveFile.write(saveDoc.toJson());
}

void BxMainWindow::loadFile()
{
    QString path = QFileDialog::getOpenFileName(this, "Filename", QString(), "*.json");
    if(path.isEmpty())
    {
        return;
    }

    QFile loadFile(path);
    if (!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save file.");
        return;
    }

    scene->clear();

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    QJsonArray actorArray = loadDoc.object()["actors"].toArray(); // find "actors" in the doc and loop over them
    for (int i = 0; i < actorArray.size(); ++i)
    {
        QJsonObject obj(actorArray[i].toObject());

        auto first = obj.begin(); // work this out
        QJsonObject data = first.value().toObject();

        BxNodeActor* newActor = new BxNodeActor(data);
        scene->insertActor(newActor);
    }
    return;

}

// BUTTON ACTIONS

void BxMainWindow::actorButtonGroupClick(QAbstractButton* button)
{
    if(scene->getMode() == BxLevelScene::insertItem)
    {
        scene->setMode((BxLevelScene::moveItem));
    }
    else
    {
        scene->setMode(BxLevelScene::insertItem);
    }
}

void BxMainWindow::cameraButtonGroupClick(QAbstractButton* button)
{
    if(scene->getMode() == BxLevelScene::editCamera)
    {
        scene->setMode((BxLevelScene::moveItem));
    }
    else
    {
        scene->setMode(BxLevelScene::editCamera);
    }

}


void BxMainWindow::aboutMessage()
{
    QMessageBox::about(this,tr("About Brix"),tr("Brix Editor v0.01"));
}
