#include "calendardialog.h"
#include "ui_calendardialog.h"


CalendarDialog::CalendarDialog(QWidget *parent)
   : QDialog(parent)
   , ui(new Ui::CalendarDialog)
   {
   ui->setupUi(this);
   }


CalendarDialog::~CalendarDialog()
   {
   delete ui;
   }


void CalendarDialog::on_okPushButton_clicked()
   {
   selectedDate = ui->calendarWidget->selectedDate();
   emit dateSelected(selectedDate); // Emit the selected date
   accept(); // Close the dialog
   }


void CalendarDialog::on_cancelPushButton_clicked()
   {
   reject(); // Close the dialog without doing anything
   }


void CalendarDialog::on_resetPushButton_clicked()
   {
   ui->calendarWidget->setSelectedDate(QDate::currentDate()); // Reset to today's date
   }

