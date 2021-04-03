#ifndef SELECTINGFORM_H
#define SELECTINGFORM_H

#include <QWidget>
namespace Ui {
class SelectingForm;
}

class SelectingForm : public QWidget {
  Q_OBJECT

public:
  explicit SelectingForm(QWidget *parent = 0);
  ~SelectingForm();
signals:
  void sendingChoice(int i);
public slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();

private:
  Ui::SelectingForm *ui;
};

#endif // SELECTINGFORM_H
