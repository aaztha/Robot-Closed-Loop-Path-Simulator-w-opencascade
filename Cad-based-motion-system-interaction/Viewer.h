#pragma once

#include <QWidget>
#include <QTimer>

#include <AIS_InteractiveContext.hxx>
#include <V3d_View.hxx>
#include <AIS_Shape.hxx>

class Viewer : public QWidget
{
    Q_OBJECT

public:
    Viewer(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;

private slots:
    void updateSimulation();

private:
    void initViewer();
    void createScene();
    void generatePath();

private:
    Handle(V3d_View) m_view;
    Handle(AIS_InteractiveContext) m_context;

    std::vector<gp_Pnt> m_path;
    int m_index = 0;

    QTimer m_timer;
    Handle(AIS_Shape) m_robotDot;
};