#ifndef ENMSG_MAIN_WINDOW_H
#define ENMSG_MAIN_WINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow_UI;
}

class MainWindow_UI : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_UI(QWidget *parent = 0);
    ~MainWindow_UI();

private slots:
    void on_Button_encrypt_clicked();

    void on_Button_decrypt_clicked();

    void on_Button_copy_clicked();

    void on_Button_paste_clicked();

    void on_Button_clear_clicked();

    void on_Button_up_clicked();

    void on_Button_load_clicked();

    void on_Button_copy_decrypted_clicked();

    void on_Button_save_clicked();

    void on_Button_SHA256_clicked();

private:
    Ui::MainWindow_UI *ui;
};

#endif // ENMSG_MAIN_WINDOW_H
