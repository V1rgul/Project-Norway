#include <QMessageBox>
#include <QMenu>
#include <QStandardItem>
#include <QDebug>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QWidgetItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "abstractcameramanager.h"
#include "testcameramanager.h"
#include "emptycameramanager.h"
#include "flycameramanager.h"

bool Ui::crosshair = false, Ui::crosshairReal = false, Ui::forceHighQuality = false;


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow),
    cameraManagers(), selectedCameraManager(-1)
{
    propertiesIcons[0] = QIcon(":/icons/camera").pixmap(16,16);
    propertiesIcons[1] = QIcon(":/icons/folder").pixmap(16,16);
    propertiesIcons[2] = QIcon(":/icons/folder_camera").pixmap(16,16);

    ui->setupUi(this);


	cameraManagers.push_back(new EmptyCameraManager());
	cameraManagers.push_back(new TestCameraManager());
    cameraManagers.push_back(new FlyCameraManager());
    //cameraManagers.push_back(new IsCameraManager());


	for (unsigned int i=0 ; i < cameraManagers.size(); ++i){
		AbstractCameraManager* manager = cameraManagers.at(i);
		manager->setMainWindow(this);
		ui->SelectCameras->addItem(manager->getName().c_str());
	}

    ui->SelectCameras->setFixedHeight( ui->Detect->sizeHint().height()-2 );

	connect(ui->CameraTree, SIGNAL(clicked(const QModelIndex &)),
			this, SLOT(on_CameraTree_itemClicked(const QModelIndex &)));
}
MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::modifySubWindow(QMdiSubWindow* in, bool add){
	qDebug() << "modifySubWindow( " << in << ", " << add << ")";
    Q_CHECK_PTR(ui);
    Q_CHECK_PTR(ui->centralwidget);
    Q_CHECK_PTR(in);
	if(add){
		(ui->centralwidget->addSubWindow(in))->show();
	}else{
		ui->centralwidget->removeSubWindow(in);
	}
}

void MainWindow::on_actionQuitter_triggered()
{
	qApp->exit();
}

void MainWindow::on_Detect_clicked()
{
	ui->CameraTree->setExpanded(cameraManagers.at(selectedCameraManager)->detectNewCamerasAndExpand(), true);
}
void MainWindow::on_actionMosaic_triggered()
{
	ui->centralwidget->tileSubWindows();
}


void MainWindow::on_SelectCameras_currentIndexChanged(int index)
{
    if(selectedCameraManager >= 0){
        AbstractCameraManager* camManager = cameraManagers.at(selectedCameraManager);
        camManager->activateLiveView(false);
        camManager->desactiveAllCameras();
        camManager->getPropertiesWidget()->hide();
    }
	selectedCameraManager = index;
	AbstractCameraManager* cm = cameraManagers.at(selectedCameraManager);
	ui->CameraTree->setModel(cm->getModel());
	ui->propertiesContainer->addWidget(cm->getPropertiesWidget());
	cm->getPropertiesWidget()->show();
    on_Detect_clicked();
    if( ui->actionLiveView->isChecked() )
        cm->activateLiveView( true );
}

//need to be moved to AbstractCameraManager
void MainWindow::on_CameraTree_itemClicked(const QModelIndex & index){
    QString str = "";
    bool editable, deleteable;
    int icon = 0;
    cameraManagers.at(selectedCameraManager)->cameraTree_itemClicked(index, str, icon, editable, deleteable);

    ui->label->setText( str );
    ui->editItem->setEnabled( editable );
    ui->resetItem->setEnabled( editable );
    ui->deleteGroup->setEnabled( deleteable );

    if( icon>=0 && icon < 3 )
        ui->propertiesIcon->setPixmap(propertiesIcons[icon]);
}


void MainWindow::on_actionUpdateImages_triggered()
{
    cameraManagers.at(selectedCameraManager)->updateImages();
}

void MainWindow::on_actionLiveView_toggled(bool arg1)
{
    ui->actionUpdateImages->setEnabled(!arg1);
    cameraManagers.at(selectedCameraManager)->activateLiveView( arg1 );
}




void MainWindow::on_addGroup_clicked()
{
    ui->CameraTree->edit( cameraManagers.at(selectedCameraManager)->addGroup() );
}

void MainWindow::on_editItem_clicked()
{
    ui->CameraTree->edit( ui->CameraTree->currentIndex() );
}
void MainWindow::on_resetItem_clicked()
{
    cameraManagers.at(selectedCameraManager)->resetItem( ui->CameraTree->currentIndex() );
}

void MainWindow::on_deleteGroup_clicked()
{
    if( !ui->CameraTree->currentIndex().isValid() ) return;
    cameraManagers.at(selectedCameraManager)->removeGroup( ui->CameraTree->currentIndex() );
    on_CameraTree_itemClicked( ui->CameraTree->currentIndex() );
}

void MainWindow::on_actionCrosshair_toggled(bool arg1)
{
    Ui::crosshair = arg1;
    emit activateCrosshair(Ui::crosshair);
}

void MainWindow::on_actionCrosshairReal_toggled(bool arg1)
{
    Ui::crosshairReal = arg1;
}

void MainWindow::on_updatePropertiesButton_clicked()
{
    cameraManagers.at(selectedCameraManager)->updateProperties();
}

void MainWindow::on_actionHighQuality_toggled(bool arg1)
{
    Ui::forceHighQuality = arg1;
}


