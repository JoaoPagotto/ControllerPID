#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>

//-----------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   //----------------------------------

   pidModel.setFileName("");
   pidModel.setPidCtrl(&pid);

   //----------------------------------

   ui->defDt->setValue(0.10);
   ui->defMax->setValue(10.00);
   ui->defMin->setValue(-10.00);
   ui->defKp->setValue(0.10);
   ui->defKi->setValue(0.50);
   ui->defKd->setValue(0.00);
   ui->procIteractions->setValue(100);
   ui->procValue->setValue(0);
   ui->procSetPoint->setValue(50);

   //----------------------------------

   QPen penSeries1;
   penSeries1.setWidth(2);
   penSeries1.setColor(0x54B5E6);

   QPen penSeries2;
   penSeries2.setWidth(2);
   penSeries2.setColor(0x99CA53);

   QPen penSeries3;
   penSeries3.setWidth(2);
   penSeries3.setColor(0xF7B447);

   QPen penSeriesRangeUpper;
   penSeriesRangeUpper.setWidth(1);
   penSeriesRangeUpper.setColor(0xED3237);

   QPen penSeriesRangeLower;
   penSeriesRangeLower.setWidth(1);
   penSeriesRangeLower.setColor(0xED3237);

   chartSeries1 = new QLineSeries();
   chartSeries1->setPen(penSeries1);
   chartSeries2 = new QLineSeries();
   chartSeries2->setPen(penSeries2);
   chartSeries3 = new QLineSeries();
   chartSeries3->setPen(penSeries3);

   chartSeriesRangeUpper = new QLineSeries();
   chartSeriesRangeUpper->setPen(penSeriesRangeUpper);

   chartSeriesRangeLower = new QLineSeries();
   chartSeriesRangeLower->setPen(penSeriesRangeLower);

   process(false);

   chart = new QChart();
   chart->legend()->hide();
   chart->addSeries(chartSeries1);
   chart->addSeries(chartSeries2);
   chart->addSeries(chartSeries3);
   chart->addSeries(chartSeriesRangeUpper);
   chart->addSeries(chartSeriesRangeLower);
   chart->createDefaultAxes();

   chartView = new QChartView(chart);
   chartView->setRenderHint(QPainter::Antialiasing);

   hbox = new QHBoxLayout();
   hbox->addWidget(chartView);
   ui->frameChart->setLayout(hbox);

   //----------------------------------

   connect(ui->defDt, SIGNAL(valueChanged(double)), this, SLOT(slotDoubleChanged(double)));
   connect(ui->defMax, SIGNAL(valueChanged(double)), this, SLOT(slotDoubleChanged(double)));
   connect(ui->defMin, SIGNAL(valueChanged(double)), this, SLOT(slotDoubleChanged(double)));
   connect(ui->defKp, SIGNAL(valueChanged(double)), this, SLOT(slotDoubleChanged(double)));
   connect(ui->defKi, SIGNAL(valueChanged(double)), this, SLOT(slotDoubleChanged(double)));
   connect(ui->defKd, SIGNAL(valueChanged(double)), this, SLOT(slotDoubleChanged(double)));
   connect(ui->procIteractions, SIGNAL(valueChanged(int)), this, SLOT(slotIntegerChanged(int)));
   connect(ui->procValue, SIGNAL(valueChanged(double)), this, SLOT(slotDoubleChanged(double)));
   connect(ui->procSetPoint, SIGNAL(valueChanged(double)), this, SLOT(slotDoubleChanged(double)));
   connect(ui->cbPlotResultAtSetPoint, SIGNAL(toggled(bool)), this, SLOT(slotCheckboxChanged(bool)));
   connect(ui->cbPlotSetPointLine, SIGNAL(toggled(bool)), this, SLOT(slotCheckboxChanged(bool)));
   connect(ui->cbPlotRangeManipulatedVariable, SIGNAL(toggled(bool)), this, SLOT(slotCheckboxChanged(bool)));

   //----------------------------------

   connect(ui->actionFileNew, SIGNAL(triggered(bool)), this, SLOT(slotMenuTriggered(bool)));
   connect(ui->actionFileOpen, SIGNAL(triggered(bool)), this, SLOT(slotMenuTriggered(bool)));
   connect(ui->actionFileSave, SIGNAL(triggered(bool)), this, SLOT(slotMenuTriggered(bool)));
   connect(ui->actionFileExit, SIGNAL(triggered(bool)), this, SLOT(slotMenuTriggered(bool)));
   connect(ui->actionHelpAbout, SIGNAL(triggered(bool)), this, SLOT(slotMenuTriggered(bool)));

}

//-----------------------------------------------------------------------------

MainWindow::~MainWindow()
{
   delete ui;
}

//-----------------------------------------------------------------------------

void MainWindow::slotDoubleChanged(double value)
{
   Q_UNUSED(value);
   process(true);
}

//-----------------------------------------------------------------------------

void MainWindow::slotIntegerChanged(int value)
{
   Q_UNUSED(value);
   process(true);
}

//-----------------------------------------------------------------------------

void MainWindow::slotCheckboxChanged(bool value)
{
   Q_UNUSED(value);
   process(true);
}

//-----------------------------------------------------------------------------

void MainWindow::slotMenuTriggered(bool value)
{
   Q_UNUSED(value);

   if ( sender() == ui->actionFileNew ) {

      pidModel.setFileName("");
      pidModel.fileNew();

   } else if ( sender() == ui->actionFileOpen ) {

      if ( pidModel.getFileName().isEmpty() ) {
         QString fileName = QFileDialog::getOpenFileName(
                  this,
                  tr("Open file PID Json"),
                  "",
                  tr("PID Json (*.json)"));

         if ( !fileName.isEmpty() ) {
            pidModel.setFileName(fileName);
            pidModel.fileOpen();
         }
      } else {
         pidModel.fileOpen();
      }

   } else if ( sender() == ui->actionFileSave ) {

      if ( pidModel.getFileName().isEmpty() ) {
         QString fileName = QFileDialog::getSaveFileName(
                  this,
                  tr("Save file PID Json"),
                  "",
                  tr("PID Json (*.json)"));

         if ( !fileName.isEmpty() ) {
            pidModel.setFileName(fileName);
            pidModel.fileOpen();
         }
      } else {
         pidModel.fileOpen();
      }

   } else if ( sender() == ui->actionFileExit ) {

      close();

   } else if ( sender() == ui->actionHelpAbout ) {

      QApplication::aboutQt();

   }
}

//-----------------------------------------------------------------------------

void MainWindow::process(bool refresh)
{
   pid.define(
            ui->defDt->value(),
            ui->defMax->value(),
            ui->defMin->value(),
            ui->defKp->value(),
            ui->defKi->value(),
            ui->defKd->value());

   //----------------------------------

   chartSeries1->clear();
   chartSeries2->clear();
   chartSeries3->clear();
   chartSeriesRangeUpper->clear();
   chartSeriesRangeLower->clear();

   double val = ui->procValue->value();
   for (int x = 0; x < ui->procIteractions->value(); x++)
   {
      double inc = pid.calculate(ui->procSetPoint->value(), val);

      chartSeries1->append(x, val);

      if (  ui->cbPlotResultAtSetPoint->isChecked() ) {
         chartSeries2->append(x, inc + ui->procSetPoint->value());
      } else {
         chartSeries2->append(x, inc);
      }

      if ( ui->cbPlotSetPointLine->isChecked() ) {
         chartSeries3->append(x, ui->procSetPoint->value());
      }

      if ( ui->cbPlotRangeManipulatedVariable->isChecked() ) {
         if (  ui->cbPlotResultAtSetPoint->isChecked() ) {
            chartSeriesRangeUpper->append(x, ui->procSetPoint->value() + ui->defMax->value());
            chartSeriesRangeLower->append(x, ui->procSetPoint->value() + ui->defMin->value());
         } else {
            chartSeriesRangeUpper->append(x, ui->defMax->value());
            chartSeriesRangeLower->append(x, ui->defMin->value());
         }
      }

      val += inc;
   }

   if ( refresh ) {
      chart->removeSeries(chartSeries1);
      chart->addSeries(chartSeries1);
      chart->removeSeries(chartSeries2);
      chart->addSeries(chartSeries2);
      chart->removeSeries(chartSeries3);
      chart->addSeries(chartSeries3);
      chart->removeSeries(chartSeriesRangeUpper);
      chart->addSeries(chartSeriesRangeUpper);
      chart->removeSeries(chartSeriesRangeLower);
      chart->addSeries(chartSeriesRangeLower);
      chart->createDefaultAxes();
   }
}

//-----------------------------------------------------------------------------
