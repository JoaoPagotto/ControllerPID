#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "PidCtrl.h"
#include "PidCtrlModel.h"

#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <QHBoxLayout>

QT_CHARTS_USE_NAMESPACE

//-----------------------------------------------------------------------------

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

   void process(bool refresh);

private slots:
   void slotDoubleChanged(double value);
   void slotIntegerChanged(int value);
   void slotCheckboxChanged(bool value);
   void slotMenuTriggered(bool value);

private:
   Ui::MainWindow *ui;

   PidCtrl pid;
   PidCtrlModel pidModel;

   QLineSeries *chartSeries1;
   QLineSeries *chartSeries2;
   QLineSeries *chartSeries3;

   QLineSeries *chartSeriesRangeUpper;
   QLineSeries *chartSeriesRangeLower;

   QChart *chart;
   QChartView *chartView;
   QHBoxLayout *hbox;
};

//-----------------------------------------------------------------------------

#endif // MAINWINDOW_H
