#ifndef BXMAINWINDOW_H
#define BXMAINWINDOW_H

#include <QMainWindow>
#include "BxNodeActor.h"
#include "BxLevelScene.h"
#include "BxLevelView.h"

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
QT_END_NAMESPACE


class BxMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    BxMainWindow();
    
signals:
    
public slots:
    void actorButtonGroupClick(QAbstractButton* );
    void cameraButtonGroupClick(QAbstractButton* );
    void aboutMessage();
    void selectionChanged();
    void clearAttributeEditor();
    void clearButtons();
    void newFile();
    void saveAs();
    void saveFile();
    void loadFile();

private:
    void createToolBox();
    void createActions();
    void createMenus();
    void createToolBars();
    void populateAttributeEditor();

    QString savePath;

    QToolBar* fileToolBar;
    QToolBar* aboutToolBar;
    QToolButton* toolButtonAbout;

    QMenu* fileMenu;
    QMenu* aboutMenu;

    QAction* aboutAction;
    QAction* newAction;
    QAction* saveAsAction;
    QAction* loadAction;

    QButtonGroup* actorButtonGroup;
    QButtonGroup* cameraButtonGroup;

    QToolBox* mainToolBox;
    QWidget* attributeEditor;

    BxLevelScene* scene;
    BxLevelView* view;

};

#endif // BXMAINWINDOW_H
