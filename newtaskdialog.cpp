#include "newtaskdialog.h"
#include "calendardialog.h"
#include "ui_newtaskdialog.h"
#include "iomanager.h"
#include <regex>

NewTaskDialog::NewTaskDialog(QWidget *parent)
   : QDialog(parent)
   , ui(new Ui::NewTaskDialog)
   {
   ui->setupUi(this);

   ui->datepicker->setDisplayFormat("yyyy/MM/dd");

   QDate date = QDate::currentDate();
   ui->datepicker->setDate(date);

   ui->slider->setRange(0, 100);
   ui->slider->setSingleStep(5);

   ui->savebtn->setEnabled(false);
   ui->deletebtn->setVisible(false);

   this->newTask = true;
   }


void NewTaskDialog::setPath(std::string path)
   {
   this->path = path;
   }


void NewTaskDialog::setData(std::string duedate, std::string title, std::string percent, std::string description)
   {
   this->oldDuedate = duedate;
   this->oldTitle = title;
   this->oldPercent = percent;
   this->oldDescription = description;

   std::string *sdate = IOManager::split(duedate, '/');
   QDate *sd = new QDate(stoi(sdate[0]), stoi(sdate[1]), stoi(sdate[2]));

   ui->datepicker->setDate(*sd);
   ui->title_et->setText(QString::fromStdString(title));
   ui->slider->setValue(stoi(percent));
   ui->description_ed->setPlainText(QString::fromStdString(description));

   this->newTask = false;

   ui->savebtn->setText("Modify");
   ui->deletebtn->setVisible(true);
   }


NewTaskDialog::~NewTaskDialog()
   {
   delete ui;
   }


void NewTaskDialog::on_slider_valueChanged(int value)
   {
   ui->percent_lbl->setText(QString::fromStdString(std::to_string(value)+"% Compl."));
   checkFields();
   }


void NewTaskDialog::checkFields()
   {
   std::string sdatepicker(ui->datepicker->text().toUtf8().constData());
   std::string stitle(ui->title_et->text().toUtf8().constData());
   std::string spercent(ui->percent_lbl->text().toUtf8().constData());
   spercent = spercent.substr(0, spercent.find('%'));
   std::string sdescr(ui->description_ed->toPlainText().toUtf8().constData());

   //We check all fields are completed
   if (
       sdatepicker.length()!=10 ||
       stitle.length()==0 ||
       spercent.length()==0 ||
       sdescr.length()==0
       )
      {
      ui->savebtn->setEnabled(false);
      }
   else
      {
      ui->savebtn->setEnabled(true);
      }
   }


void NewTaskDialog::on_description_ed_textChanged()
   {
   checkFields();
   }


void NewTaskDialog::on_title_et_textChanged(const QString &arg1)
   {
   checkFields();
   }


void NewTaskDialog::on_datepicker_userDateChanged(const QDate &date)
   {
   checkFields();
   }


void NewTaskDialog::on_savebtn_clicked()
   {
   std::vector<std::string*> lines = IOManager::readFile(path);
   std::string sdatepicker(ui->datepicker->text().toUtf8().constData());
   std::string stitle(ui->title_et->text().toUtf8().constData());
   std::string spercent(ui->percent_lbl->text().toUtf8().constData());
   spercent = spercent.substr(0, spercent.find('%'));

   // Get the description and replace newlines with a placeholder
   std::string sdescr(ui->description_ed->toPlainText().toUtf8().constData());
   std::string sdescr_placeholder = std::regex_replace(sdescr, std::regex("\n"), "|n|"); // Replace newlines with "|n|"

   std::string s;

   // If it is a new task
   if (newTask)
      {
      s += sdatepicker + ";" + stitle + ";" + spercent + ";" + sdescr_placeholder + "\n";
      }

   // Process all lines to ensure that existing tasks are updated correctly
   for (const auto& line : lines)
      {
      // Check if this line matches the old task details
      if (line[0] == oldDuedate && line[1] == oldTitle &&
          line[2] == oldPercent && line[3] == oldDescription)
         {
         // If it matches, replace it with the new task details
         s += sdatepicker + ";" + stitle + ";" + spercent + ";" + sdescr_placeholder + "\n";
         }
      else
         {
         // Otherwise, keep the existing line, replacing newlines in the description if necessary
         std::string existing_descr = line[3];
         std::string existing_descr_placeholder = std::regex_replace(existing_descr, std::regex("\n"), "|n|");
         s += line[0] + ";" + line[1] + ";" + line[2] + ";" + existing_descr_placeholder + "\n";
         }
      }

   IOManager::writeFile(path, s);
   origin->filter();
   this->close();
   }


void NewTaskDialog::on_cancelbtn_clicked()
   {
   this->close();
   }


void NewTaskDialog::on_deletebtn_clicked()
   {
   std::vector<std::string*> lines = IOManager::readFile(path);
   unsigned int i;

   QMessageBox::StandardButton reply;
   reply = QMessageBox::question(this, "Delete task", "Are you sure you want to permanently delete this task?",
                                 QMessageBox::Yes|QMessageBox::No);
   if (reply == QMessageBox::No)
      {
      return;
      }

   std::string s = "";

   for (i=0; i<lines.size(); i++)
      {
      if (!(lines.at(i)[0].compare(oldDuedate) == 0 && lines.at(i)[1].compare(oldTitle) == 0 &&
            lines.at(i)[2].compare(oldPercent) == 0 && lines.at(i)[3].compare(oldDescription) == 0))
         {
         s += lines.at(i)[0] + ";" + lines.at(i)[1] + ";" + lines.at(i)[2] + ";" + lines.at(i)[3] + "\n";
         }
      }

   IOManager::writeFile(path, s);
   lines.clear();
   origin->filter();
   this->close();
   }


void NewTaskDialog::on_openCalenderPushButton_clicked()
   {
   CalendarDialog dialog(this);
   connect(&dialog, &CalendarDialog::dateSelected, this, &NewTaskDialog::updateDate);
   dialog.exec();
   }


void NewTaskDialog::updateDate(const QDate &date)
   {
   ui->datepicker->setDate(date);
   }
