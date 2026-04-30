#ifndef QVTKDICOMVIEWER_H
#define QVTKDICOMVIEWER_H
#include "ui_QvtkDicomViewer.h"
//Qt
#include <QtWidgets/QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QTimer>
//vtk
#include <vtkRenderWindow.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageActor.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkImageViewer2.h>
#include <vtkEventQtSlotConnect.h>
#include <vtkAutoInit.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDICOMImageReader.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkActor2D.h>
#include <myVtkInteractorStyleImage.h>
#include <vtkDistanceWidget.h>
#include <vtkAngleWidget.h>
#include <vtkContourWidget.h>
#include <vtkOrientedGlyphContourRepresentation.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkBiDimensionalWidget.h>
#include "vtkBiDimensionalCallback.h"
#include "DicomPatient.h"
#include "DicomDirTreeModel.h"
#include <vtkImageCast.h>

#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredPoints.h>
#include <vtkStructuredPointsReader.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolume.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include "vtkUnsignedCharArray.h"
#include "vtkPiecewiseFunction.h"
#include "vtkColorTransferFunction.h"
#include "vtkVolumeRayCastCompositeFunction.h"
#include "vtkVolumeRayCastMapper.h"
#include "vtkImageData.h"
#include "vtkRenderWindow.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include "vtkInteractorStyleTrackballActor.h"
#include "vtkImageChangeInformation.h"
#include "vtkGPUVolumeRayCastMapper.h"
#include "vtkGPUInfoList.h"
#include "vtkGPUInfo.h"
#include <vtkStructuredPoints.h>
#include <vtkStructuredPointsReader.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolumeProperty.h>
#include <vtkVolumeRayCastIsosurfaceFunction.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <QComboBox>
#include "vtkMyDICOMImageReader.h"
#include "Register.h"

class DicomDataBase;

VTK_MODULE_INIT(vtkRenderingFreeType)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2)
#include <vtkAutoInit.h>
#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeType,vtkRenderingOpenGL2)
//#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL2)

class QvtkDicomViewer : public QMainWindow
{
    Q_OBJECT

public:
    QvtkDicomViewer(QWidget *parent = Q_NULLPTR);
    //QComboBox* reg_combo;
    Register * m_Reg_Window;
    enum CURSOR
    {	POINTRE,
        ZOOM,
        GRAYLEVEL,
        PROTRACTOR,
        RULER,
        CONTOUR,
        BIDI,
        MOVE
    }CursorType;
    enum WINDOWWL
    {
        Default,
        All,
        Abdomen,
        BloodVessel,
        Bones,
        Brain,
        Medias,
        Lungs
    }ImageWindow;
    enum STATE
    {
        Idel,
        SingleImage,
        Folder,
        Dir,
        Err,
        Debug
    }AppState;
private:
    //CURSOR CursorType;
    Ui::QvtkDicomViewerClass ui;
    vtkSmartPointer<vtkImageViewer2 > m_pImageViewer;
    vtkSmartPointer<vtkRenderer > m_pRenderder;
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
    vtkSmartPointer<vtkDICOMImageReader> reader;
    //vtkSmartPointer<vtkTextProperty> sliceTextProp;
    //vtkSmartPointer<vtkTextMapper> sliceTextMapper;
    vtkSmartPointer<vtkActor2D> sliceTextActor;
    //vtkSmartPointer<vtkTextProperty> usageTextProp;
    //vtkSmartPointer<vtkTextMapper> usageTextMapper;
    vtkSmartPointer<vtkActor2D> usageTextActor1;
    vtkSmartPointer<vtkActor2D> usageTextActor2;
    vtkSmartPointer<vtkActor2D> usageTextActor3;
    vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle;
    vtkSmartPointer<vtkDistanceWidget> distanceWidget;
    vtkSmartPointer<vtkAngleWidget> angleWidget;
    vtkSmartPointer<vtkContourWidget> contourWidget;
    vtkSmartPointer<vtkAxesActor> axes;
    vtkSmartPointer<vtkOrientedGlyphContourRepresentation> contourRepresentation;
    vtkSmartPointer<vtkOrientationMarkerWidget> widget;
    vtkSmartPointer<vtkBiDimensionalWidget> biDimensionalWidget;
    vtkSmartPointer<vtkBiDimensionalCallback> biDimensionalCallback;

    QIcon icon_Play;
    QIcon icon_Pause;
    bool PlayFlag;
    QTimer * m_pTimer;
    int min;
    int max;
    int current;

    QPoint PrePosition;
    QMenu * TreeViewMenu_OnEmpty;
    QMenu * TreeViewMenu_OnPatient;
    QMenu * TreeViewMenu_OnSeries;
    QMenu * TreeViewMenu_OnImage;

    std::string Current_patientId;
    DicomPatient * CurrentPatient;
    QModelIndex indexSelect;
    DicomDirTreeModel *m_dicomdirtreemodel;

private:
    ///ÄÚ²¿²Ù×÷
    void setCursor(CURSOR newValue);
    void setWindowWL(WINDOWWL newWL);
    void setAppState(STATE new_state);
    void RenderInitializer(std::string folder, int NumOfImage = 1);
    void RenderRefresh(std::string imagefilename, int currentPagenumber, int maxPageNumber);
    void DirTreeRefresh(DicomPatient * patient);
    void addDistanceWidget();
    void addAngleWidget();
    void addContourWidget();
    void SetSliceText(int current, int max);
    void SetUsageText(std::string imagefilename);
    void addOrientationMarker();
    void addBiDimensionalWidget();
    void CreateContextMenu();
    void ShowImageByIndex(int Index);
signals :
    void CursorValueChanged();
    void WindowWLChanged();
    void AppStateChanged();

public slots:
    void OnPlayerTimerOut();
    void OnChangeAppState();
    void OnChangeCursorValue();
    void OnChangeWindowsWL();
    void OnOpenSeriesFolder();
    void OnOpenDicomFile();
    void OnOpenDicomDirFile();
    void OnForward();
    void OnBackward();
    void OnResetToFirst();
    void OnSelectedPointer();
    void OnSelectedProtractor();
    void OnSelectedRuler();
    void OnSelectedContour();
    void OnSelectedBiDimensional();
    void OnSelectedGrayLevel();
    void OnSelectedZoom();
    void OnSelectedMove();
    void OnNegative();
    void OnReset();
    void OnPlay();
    void OnStop();
    void OnSwitchProperty();
    void on_treeView_customContextMenuRequested(QPoint pos);
    void OnShowDicomCurrentTags();
    void OnShowSelectedSeries();
    void OnShowSelectedImage();
    void OnSliceScrollBarValueChange(int a);
    void receiveData(QString data);
    void OnLatterPatient();
    void OnPreviousPatient();

    void OnWindowWL_Defaut();
    void OnWindowWL_All();
    void OnWindowWL_CT_Abdomen();
    void OnWindowWL_CT_BloodVessel();
    void OnWindowWL_CT_Bones();
    void OnWindowWL_CT_Brain();
    void OnWindowWL_CT_Medias();
    void OnWindowWL_CT_Lungs();

    void OnTestEntrance_01();
    void OnTestEntrance_02();

    void On3D_Reconstruction();
    void OnSegmentImage();
    void OnRegistration();
};

#endif // QVTKDICOMVIEWER_H
