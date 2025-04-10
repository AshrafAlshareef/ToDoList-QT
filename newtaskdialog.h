#pragma once

#include <QDialog>
#include <string>
#include <QMessageBox>
#include "mainwindow.h"


namespace Ui {
class NewTaskDialog;
}


class NewTaskDialog : public QDialog
   {
      Q_OBJECT

   public:
      explicit NewTaskDialog(QWidget *parent = 0);
      void setData(std::string duedate, std::string title, std::string percent, std::string description);
      void setPath(std::string path);
      inline void setOrigin(MainWindow *origin){ this->origin = origin; }
      std::string oldDuedate;
      std::string oldTitle;
      std::string oldPercent;
      std::string oldDescription;
      ~NewTaskDialog();

   private slots:
      void on_slider_valueChanged(int value);
      void on_description_ed_textChanged();
      void on_title_et_textChanged(const QString &arg1);
      void on_datepicker_userDateChanged(const QDate &date);
      void on_savebtn_clicked();
      void on_cancelbtn_clicked();

      void on_deletebtn_clicked();

   private:
      void checkFields();
      Ui::NewTaskDialog *ui;
      bool newTask;
      std::string path;
      MainWindow *origin;
   };
