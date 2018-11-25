#ifndef ENMSG_MAIN_WINDOW_H
#define ENMSG_MAIN_WINDOW_H

#include "std_rand.h"
#include "qt_keyfile.h"
#include "os_clipboard.h"
#include "cryptopp_aes_algorithm.h"
#include "cryptopp_hash_algorithm.h"
#include "gui_key_exchange_wizard.h"
#include "qt_gen_filedialog.h"
#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QDebug>

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
    void on_actionExchange_Key_triggered();

    void on_actionRandom_Text_Key_triggered();

    void on_Button_Save_Key_clicked();

    void on_Button_Load_Key_clicked();

    void on_Button_Raw_Text_Copy_clicked();

    void on_Button_Raw_Text_Paste_clicked();

    void on_Button_Raw_Text_Clear_clicked();

    void on_Button_Cipher_Text_Copy_clicked();

    void on_Button_Cipher_Text_Paste_clicked();

    void on_Button_Cipher_Text_Clear_clicked();

    void on_Button_Text_Up_clicked();

    void on_Button_Text_Down_clicked();

    void on_Button_Encrypt_Text_clicked();

    void on_Button_Decrypt_Text_clicked();

    void on_Button_Source_File_Browse_clicked();

    void on_Button_Output_File_Browse_clicked();

    void on_Button_Encrypt_File_clicked();

    void on_Button_Decrypt_File_clicked();

private:
    void UpdateRandKeyText();
    void SetKeyModeComboBox(QString qstr_mode);
    void ReadTextKey();
    void UpdateKeyBytes();

    QByteArray m_key_bytes;
    Ui::MainWindow_UI *ui;
};

#endif // ENMSG_MAIN_WINDOW_H
