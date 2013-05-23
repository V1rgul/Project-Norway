#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "abstractcameramanager.h"

namespace Ui {
	class MainWindow;
}
class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void modifySubWindow(QMdiSubWindow* in, bool add);
	
private slots:
	void on_actionQuitter_triggered();
	void on_Detect_clicked();
	void on_CameraTree_customContextMenuRequested(const QPoint &pos);
	void on_actionMosaic_triggered();
	void on_createGroup_triggered();
	void on_SelectCameras_currentIndexChanged(int index);
	void on_CameraTree_itemClicked(const QModelIndex & index);
    void on_actionUpdateImages_triggered();
    void on_actionUpdateProperties_triggered();
    void on_actionLiveView_toggled(bool arg1);

    void on_addGroup_clicked();
    void on_editItem_clicked();
    void on_deleteGroup_clicked();

private:
	Ui::MainWindow *ui;
	QAction *addGroup;
	std::vector<AbstractCameraManager*> cameraManagers;
	int selectedCameraManager;
};

#endif // MAINWINDOW_H
