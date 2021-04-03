#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog {
  Q_OBJECT

public:
  explicit InputDialog(QWidget *parent = 0);
  ~InputDialog();
  float height() const;
  float thickness() const;
public slots:

  void accept();

signals:

  void accepted();
  void isFinished();

private:
  Ui::InputDialog *ui;
  float _height;
  float _thickness;
};

#endif // INPUTDIALOG_H
