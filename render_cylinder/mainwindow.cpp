#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "vtkCylinderSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "QVTKWidget.h"
#include "vtkAutoInit.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PB_load_clicked()
{
    vtkSmartPointer<vtkCylinderSource>cylinder=vtkSmartPointer<vtkCylinderSource>::New();
    cylinder->SetResolution(8);

    vtkSmartPointer<vtkPolyDataMapper>cylindermapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    cylindermapper->SetInputConnection(cylinder->GetOutputPort());

    vtkSmartPointer<vtkActor>cylinderactor=vtkSmartPointer<vtkActor>::New();
    cylinderactor->SetMapper(cylindermapper);
    cylinderactor->GetProperty()->SetColor(1.000,0.3882,0.2784);
    cylinderactor->RotateX(30.0);
    cylinderactor->RotateY(-45.0);

    vtkSmartPointer<vtkRenderer>ren1=vtkSmartPointer<vtkRenderer>::New();

    ren1->AddActor(cylinderactor);
    ren1->SetBackground(0.1,0.2,0.4);
//    renWin->SetSize(200,200);

    vtkWidget = new QVTKWidget(this);
    ui->verticalLayout->addWidget(vtkWidget);
    vtkWidget->GetRenderWindow()->AddRenderer(ren1);

    ren1->ResetCamera();

    vtkWidget->GetRenderWindow()->Render();
    vtkWidget->update();
}
