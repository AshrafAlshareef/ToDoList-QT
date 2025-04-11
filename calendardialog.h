#pragma once

#include <QDateTime>
#include <QDialog>

namespace Ui {
class CalendarDialog;
}

class CalendarDialog : public QDialog
   {
      Q_OBJECT

   public:
      explicit CalendarDialog(QWidget *parent = nullptr);
      ~CalendarDialog();


   signals:
       void dateSelected(const QDate &date);

   private slots:
      void on_okPushButton_clicked();

      void on_cancelPushButton_clicked();

      void on_resetPushButton_clicked();

   private:
      Ui::CalendarDialog *ui;
      QDate selectedDate; // Store the selected date
   };

