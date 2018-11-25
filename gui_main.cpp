#include "gui_main.h"
#include "ui_gui_main.h"


#define ENMESSAGE_VERSION ("1.1.0")
#define ENMESSAGE_BUILD_DATE (__DATE__)
//#define MAX_KEY_BYTES_SIZE 32
//#define MAX_IV_BYTES_SIZE 16

MainWindow_UI::MainWindow_UI(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow_UI)
{
	ui->setupUi(this);

    //手动设置comboBox_Key_Mode
    ui->comboBox_Key_Mode->clear();
    //编号0
    ui->comboBox_Key_Mode->addItem(QObject::tr("Text"),QVariant("Text"));
    ui->comboBox_Key_Mode->addItem(QObject::tr("BinaryFile"),QVariant("BinaryFile"));
    ui->comboBox_Key_Mode->addItem(QObject::tr("Base64File"),QVariant("Base64File"));
    ui->comboBox_Key_Mode->addItem(QObject::tr("HexFile"),QVariant("HexFile"));
    ui->comboBox_Key_Mode->addItem(QObject::tr("FileHash"),QVariant("FileHash"));
    ui->comboBox_Key_Mode->setCurrentIndex(0);

    UpdateRandKeyText();

	QString qstr_statusbar_tip;
	qstr_statusbar_tip.sprintf(
		"Version : %s Build Date : %s"
		, ENMESSAGE_VERSION
		, ENMESSAGE_BUILD_DATE
	);
	//ui->statusbar->setStatusTip(qstr_statusbar_tip);
	ui->statusbar->showMessage(qstr_statusbar_tip);
}

MainWindow_UI::~MainWindow_UI()
{
	delete ui;
}

void MainWindow_UI::on_actionExchange_Key_triggered()
{
    Key_Exchange_Wizard exc_wizard;
    exc_wizard.exec();
}

void MainWindow_UI::UpdateRandKeyText()
{
    std_rand rd;
    std::string str_rand_password = rd.safe_string(32);
    QString qstr_password = QString::fromStdString(str_rand_password);
    ui->LineEdit_Key_Text->setText(qstr_password);
}

void MainWindow_UI::on_actionRandom_Text_Key_triggered()
{
    UpdateRandKeyText();
}

void MainWindow_UI::on_Button_Save_Key_clicked()
{
    //获取列表选择的项保存的数据
    int n_key_mode_combobox_index = ui->comboBox_Key_Mode->currentIndex();
    QString qstr_key_mode = ui->comboBox_Key_Mode->itemData(n_key_mode_combobox_index).toString();

    if(qstr_key_mode != "Text")
    {
        //如果不是Text模式那么表示密钥已经以文件形式存在，所以无需保存
        return;
    }
    QString qstr_key = ui->LineEdit_Key_Text->text();
    QByteArray q_array_key = qstr_key.toLatin1();
    QString qstr_save_path = SaveKeyFileDialog(this);
    if(qstr_save_path.isEmpty() == true)
    {
        return;
    }
    bool bSaved = SaveKeyToFileWithExtension(qstr_save_path,q_array_key);
    if(bSaved == false)
    {
        qDebug() << "Save failed.";
    }
    return;
}

void MainWindow_UI::SetKeyModeComboBox(QString qstr_mode)
{
    QVariant var_data = qstr_mode;
    int n_index = ui->comboBox_Key_Mode->findData(var_data);
    ui->comboBox_Key_Mode->setCurrentIndex(n_index);
}

void MainWindow_UI::on_Button_Load_Key_clicked()
{
    QString qstr_load_path = OpenKeyFileDialog(this);
    if(qstr_load_path.isEmpty() == true)
    {
        return;
    }
    //设置密码框为文件路径
    ui->LineEdit_Key_Text->setText(qstr_load_path);

    QByteArray q_array_key;
    if(IsFilePathExtension(qstr_load_path,"key") == true)
    {
        q_array_key = ReadKeyFromFile(qstr_load_path);
        SetKeyModeComboBox("BinaryFile");
    }
    else if(IsFilePathExtension(qstr_load_path,"txt") == true)
    {
        q_array_key = ReadKeyFromFile(qstr_load_path);
        SetKeyModeComboBox("BinaryFile");
    }
    else if(IsFilePathExtension(qstr_load_path,"bin") == true)
    {
        q_array_key = ReadKeyFromFile(qstr_load_path);
        SetKeyModeComboBox("BinaryFile");
    }
    else if(IsFilePathExtension(qstr_load_path,"hex") == true)
    {
        q_array_key = ReadHexKeyFromFile(qstr_load_path);
        SetKeyModeComboBox("HexFile");
    }
    else if(IsFilePathExtension(qstr_load_path,"base64") == true)
    {
        q_array_key = ReadBase64KeyFromFile(qstr_load_path);
        SetKeyModeComboBox("Base64File");
    }
    else
    {
        std::string str_path = qstr_load_path.toStdString();
        q_array_key = QByteArray::fromHex(QByteArray::fromStdString(CalcFileSHA256(str_path)));
        SetKeyModeComboBox("FileHash");
    }
    m_key_bytes = q_array_key;
}

void MainWindow_UI::on_Button_Raw_Text_Copy_clicked()
{
    QString qstr_input_text = ui->TextEdit_Raw_Text->toPlainText();
    SetClipboard(qstr_input_text);
}

void MainWindow_UI::on_Button_Raw_Text_Paste_clicked()
{
    QString qstr_output_text = GetClipboard();
    ui->TextEdit_Raw_Text->setText(qstr_output_text);
}

void MainWindow_UI::on_Button_Raw_Text_Clear_clicked()
{
    ui->TextEdit_Raw_Text->clear();
}

void MainWindow_UI::on_Button_Cipher_Text_Copy_clicked()
{
    QString qstr_input_text = ui->TextEdit_Cipher_Text->toPlainText();
    SetClipboard(qstr_input_text);
}

void MainWindow_UI::on_Button_Cipher_Text_Paste_clicked()
{
    QString qstr_output_text = GetClipboard();
    ui->TextEdit_Cipher_Text->setText(qstr_output_text);
}

void MainWindow_UI::on_Button_Cipher_Text_Clear_clicked()
{
    ui->TextEdit_Cipher_Text->clear();
}

void MainWindow_UI::on_Button_Text_Up_clicked()
{
    QString qstr_data = ui->TextEdit_Cipher_Text->toPlainText();
    ui->TextEdit_Raw_Text->setText(qstr_data);
    ui->TextEdit_Cipher_Text->clear();
}

void MainWindow_UI::on_Button_Text_Down_clicked()
{
    QString qstr_data = ui->TextEdit_Raw_Text->toPlainText();
    ui->TextEdit_Cipher_Text->setText(qstr_data);
    ui->TextEdit_Raw_Text->clear();
}

void MainWindow_UI::ReadTextKey()
{
    QString qstr_key = ui->LineEdit_Key_Text->text();
    m_key_bytes = qstr_key.toLatin1();
}

void MainWindow_UI::UpdateKeyBytes()
{
    //获取Mode
    int n_key_mode_combobox_index = ui->comboBox_Key_Mode->currentIndex();
    QString qstr_key_mode = ui->comboBox_Key_Mode->itemData(n_key_mode_combobox_index).toString();

    if(qstr_key_mode == "Text")
    {
        ReadTextKey();
    }
    //其他情况下无需更新key
}

void MainWindow_UI::on_Button_Encrypt_Text_clicked()
{
    UpdateKeyBytes();
    if(m_key_bytes.isEmpty()==true)
    {
        return;
    }

    QString qstr_encrypt_data = ui->TextEdit_Raw_Text->toPlainText();

    std::string str_encrypt_data = qstr_encrypt_data.toStdString();
    std::string str_encrypted_data;
    std::string str_iv;

    AES_256_CFB_Algorithm alg;
    std::string str_key = m_key_bytes.toStdString();
    alg.SetKey(str_key);
    alg.GenerateIv();
    qDebug() << "enc key" << QByteArray::fromStdString(alg.GetIv());
    alg.EncryptString(str_encrypt_data,str_encrypted_data);
    str_iv = alg.GetIv();

    /*
    qDebug() << "enc key" << QByteArray::fromStdString(str_key);
    qDebug() << "enc iv" << QByteArray::fromStdString(str_iv);
    qDebug() << "enc data" << QByteArray::fromStdString(str_encrypt_data);
    */

    QString qstr_output = QString("%1,%2").arg(QString::fromStdString(Cryptopp_Base64::encode(str_iv,false)))
                                          .arg(QString::fromStdString(Cryptopp_Base64::encode(str_encrypted_data,false)));
    ui->TextEdit_Cipher_Text->setText(qstr_output);
}

void MainWindow_UI::on_Button_Decrypt_Text_clicked()
{
    UpdateKeyBytes();
    if(m_key_bytes.isEmpty()==true)
    {
        return;
    }

    QString qstr_decrypt_data = ui->TextEdit_Cipher_Text->toPlainText();

    QString qstr_output;
    QStringList qdata_list = qstr_decrypt_data.split(",");
    //QVector<QStringRef> qdata_list = qstr_decrypt_data.splitRef(",");
    if (qdata_list.isEmpty() == true)
    {
        qstr_output = QObject::tr("Input data error.");
    }
    else
    {
        QString qstr_iv = qdata_list.first();
        QString qstr_encrypted_data = qdata_list.last();

        AES_256_CFB_Algorithm alg;
        std::string str_key = m_key_bytes.toStdString();
        std::string str_iv = Cryptopp_Base64::decode(qstr_iv.toStdString());
        std::string str_encrypted_data = Cryptopp_Base64::decode(qstr_encrypted_data.toStdString());
        std::string str_decrypted_data;

        /*
        qDebug() << "dec key" << QByteArray::fromStdString(str_key);
        qDebug() << "dec iv" << QByteArray::fromStdString(str_iv);
        qDebug() << "dec data" << QByteArray::fromStdString(str_encrypted_data);
        */

        alg.SetKey(str_key);
        alg.SetIv(str_iv);
        if(alg.DecryptString(str_encrypted_data,str_decrypted_data) == false)
        {
            qstr_output = QObject::tr("Decrypt error.");
        }
        else
        {
            qstr_output = QString::fromStdString(str_decrypted_data);
        }
    }
    ui->TextEdit_Raw_Text->setText(qstr_output);
}

void MainWindow_UI::on_Button_Source_File_Browse_clicked()
{
    QString qstr_path = GenOpenFileDialog(this);
    ui->LineEdit_Source_File_Path->setText(qstr_path);
}

void MainWindow_UI::on_Button_Output_File_Browse_clicked()
{
    QString qstr_path = GenSaveFileDialog(this);
    ui->LineEdit_Output_File_Path->setText(qstr_path);
}

void MainWindow_UI::on_Button_Encrypt_File_clicked()
{
    UpdateKeyBytes();
    if(m_key_bytes.isEmpty()==true)
    {
        return;
    }

    QString qstr_source_path = ui->LineEdit_Source_File_Path->text();
    QString qstr_output_path = ui->LineEdit_Output_File_Path->text();


    AES_256_CFB_Algorithm alg;
    std::string str_key = m_key_bytes.toStdString();
    std::string str_iv;

    alg.GenerateIv();
    str_iv = alg.GetIv();
    alg.SetKey(str_key);
    alg.EncryptInit();

    QFile qfile_src(qstr_source_path);
    QFile qfile_out(qstr_output_path);
    qfile_src.open(QIODevice::ReadWrite);
    qfile_out.open(QIODevice::ReadWrite);

    if(qfile_src.isOpen() == false && qfile_out.isOpen() == false)
    {
        return;
    }

    qfile_out.write(str_iv.data(),str_iv.size());

    constexpr const int n_default_file_block_size = 4096;
    while(true)
    {
        QByteArray src_bytes = qfile_src.read(n_default_file_block_size);
        if (src_bytes.isEmpty() == true)
        {
            break;
        }
        QByteArray out_bytes;
        out_bytes.resize(src_bytes.size());
        alg.EncryptProcessData(out_bytes.data(),out_bytes.size(),src_bytes.data(),src_bytes.size());
        qfile_out.write(out_bytes);
    }
    qfile_src.close();
    qfile_out.close();
    return;
}

void MainWindow_UI::on_Button_Decrypt_File_clicked()
{
    UpdateKeyBytes();
    if(m_key_bytes.isEmpty()==true)
    {
        return;
    }

    QString qstr_source_path = ui->LineEdit_Source_File_Path->text();
    QString qstr_output_path = ui->LineEdit_Output_File_Path->text();

    QFile qfile_src(qstr_source_path);
    QFile qfile_out(qstr_output_path);
    qfile_src.open(QIODevice::ReadWrite);
    qfile_out.open(QIODevice::ReadWrite);

    if(qfile_src.isOpen() == false && qfile_out.isOpen() == false)
    {
        return;
    }

    QByteArray q_iv_bytes = qfile_src.read(AES_256_CFB_Algorithm::IvSize);
    if(q_iv_bytes.isEmpty() == true)
    {
        return;
    }

    AES_256_CFB_Algorithm alg;
    std::string str_key = m_key_bytes.toStdString();
    std::string str_iv = q_iv_bytes.toStdString();

    alg.SetKey(str_key);
    alg.SetIv(str_iv);
    alg.DecryptInit();

    constexpr const int n_default_file_block_size = 4096;
    while(true)
    {
        QByteArray src_bytes = qfile_src.read(n_default_file_block_size);
        if (src_bytes.isEmpty() == true)
        {
            break;
        }
        QByteArray out_bytes;
        out_bytes.resize(src_bytes.size());
        alg.DecryptProcessData(out_bytes.data(),out_bytes.size(),src_bytes.data(),src_bytes.size());
        qfile_out.write(out_bytes);
    }
    qfile_src.close();
    qfile_out.close();
    return;
}
