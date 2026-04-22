#include "Viewer.h"

#include <V3d_Viewer.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <AIS_Shape.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>

Viewer::Viewer(QWidget* parent)
    : QWidget(parent)
{
    initViewer();
    createScene();
    generatePath();

    connect(&m_timer, &QTimer::timeout, this, &Viewer::updateSimulation);
    m_timer.start(500); // move every 0.5 sec
}

void Viewer::initViewer()
{
    Handle(Aspect_DisplayConnection) display = new Aspect_DisplayConnection();
    Handle(OpenGl_GraphicDriver) driver = new OpenGl_GraphicDriver(display);

    Handle(V3d_Viewer) viewer = new V3d_Viewer(driver);
    m_context = new AIS_InteractiveContext(viewer);

    m_view = viewer->CreateView();
}

void Viewer::createScene()
{
    // Create simple box (fake CAD model)
    TopoDS_Shape box = BRepPrimAPI_MakeBox(50, 50, 50).Shape();
    Handle(AIS_Shape) aisBox = new AIS_Shape(box);

    m_context->Display(aisBox, Standard_True);

    // Create robot dot
    TopoDS_Shape sphere = BRepPrimAPI_MakeSphere(2.0).Shape();
    m_robotDot = new AIS_Shape(sphere);

    m_context->Display(m_robotDot, Standard_True);
}

void Viewer::generatePath()
{
    // simple straight path
    for (int i = 0; i < 20; i++) {
        m_path.push_back(gp_Pnt(i * 2, 10, 10));
    }
}

void Viewer::updateSimulation()
{
    if (m_index >= m_path.size())
        return;

    gp_Pnt p = m_path[m_index];

    // fake feedback (noise)
    double noise = (rand() % 5);
    gp_Pnt noisy(p.X(), p.Y() + noise, p.Z());

    gp_Trsf trsf;
    trsf.SetTranslation(gp_Vec(noisy.X(), noisy.Y(), noisy.Z()));

    m_robotDot->SetLocalTransformation(trsf);

    m_context->Redisplay(m_robotDot, Standard_True);

    m_index++;
}

void Viewer::paintEvent(QPaintEvent*)
{
    if (!m_view.IsNull())
        m_view->Redraw();
}