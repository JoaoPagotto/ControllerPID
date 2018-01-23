#ifndef PIDCTRLMODEL_H
#define PIDCTRLMODEL_H

#include <QObject>

#include "PidCtrl.h"

//-----------------------------------------------------------------------------

class PidCtrlModel : public QObject
{
   Q_OBJECT

public:
   explicit PidCtrlModel(QObject *parent = 0);

   void setPidCtrl(PidCtrl *pidCtrl) { this->pidCtrl = pidCtrl; }

   void setFileName(const QString &fileName) { this->fileName = fileName; }
   QString getFileName() { return this->fileName; }

   void fileNew();
   void fileOpen();
   void fileSave();

private:
   PidCtrl *pidCtrl;
   QString fileName;

};

//-----------------------------------------------------------------------------

#endif // PIDCTRLMODEL_H
