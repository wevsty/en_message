#ifndef KEY_EXCHANGE_WIZARD_H
#define KEY_EXCHANGE_WIZARD_H

#include "cryptopp_ecdh_algorithm.h"
#include "os_clipboard.h"
#include "qt_keyfile.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QWizard>
#include <QDebug>

namespace Ui {
class Key_Exchange_Wizard;
}

class Key_Exchange_Wizard : public QWizard
{
    Q_OBJECT

public:
    explicit Key_Exchange_Wizard(QWidget *parent = 0);
    ~Key_Exchange_Wizard();

    bool validateCurrentPage() override;



private slots:
    void on_Key_Exchange_Wizard_currentIdChanged(int id);

    void on_pushButton_Create_Myself_Key_Pair_clicked();

    void on_pushButton_Copy_Myself_Public_Key_clicked();

    void on_pushButton_Paste_Other_Public_Key_clicked();

    void on_pushButton_Key_Save_Browse_clicked();

    void on_Key_Exchange_Wizard_accepted();

private:
    Ui::Key_Exchange_Wizard *ui;
    bool b_is_have_myself_key_pair;
    ECDH_Algorithm m_ecdh_algorithm;
    std::string m_other_ecdh_public_key;
    QString m_qstr_save_key_path;

    enum{
        KEY_EXCHANGE_WIZARD_PAGE_EXCHANGE_TIPS = 0,
        KEY_EXCHANGE_WIZARD_PAGE_CREATE_MYSELF_KEY_PAIR,
        KEY_EXCHANGE_WIZARD_PAGE_GET_OTHER_PUBLIC_KEY,
        KEY_EXCHANGE_WIZARD_PAGE_SAVE_KEY
    };
};

#endif // KEY_EXCHANGE_WIZARD_H
