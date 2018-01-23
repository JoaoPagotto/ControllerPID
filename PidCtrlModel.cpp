#include "PidCtrlModel.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>

//-----------------------------------------------------------------------------

PidCtrlModel::PidCtrlModel(QObject *parent) : QObject(parent)
{
   this->pidCtrl = NULL;
}

//-----------------------------------------------------------------------------

void PidCtrlModel::fileNew()
{

}

//-----------------------------------------------------------------------------

void PidCtrlModel::fileOpen()
{
   QFile file(fileName);
   if ( file.open(QIODevice::ReadOnly) )
   {
      QJsonDocument doc;
      doc.fromJson(file.readAll());

      QJsonObject root = doc.object();
      root["dt"]  = 0.0;
      root["max"] = 0.0;
      root["min"] = 0.0;
      root["Kp"]  = 0.0;
      root["Kd"]  = 0.0;
      root["Ki"]  = 0.0;
   }
}

//-----------------------------------------------------------------------------

void PidCtrlModel::fileSave()
{
   QJsonDocument doc;

   QJsonObject root;
   root["dt"]  = 0.0;
   root["max"] = 0.0;
   root["min"] = 0.0;
   root["Kp"]  = 0.0;
   root["Kd"]  = 0.0;
   root["Ki"]  = 0.0;

   doc.setObject(root);

   //-------------------------------

   QFile jsonFile(fileName);
   if ( jsonFile.open(QFile::WriteOnly) ) {
      jsonFile.write(doc.toJson());
      jsonFile.close();
   }
}

//-----------------------------------------------------------------------------
