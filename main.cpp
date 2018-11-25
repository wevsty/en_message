#include "gui_main.h"
#include <QApplication>

//QDesktopWidget
#include <QDesktopWidget>
#include <QPoint>

QPoint get_window_center(int window_width, int window_height)
{
	//获取桌面信息
	QDesktopWidget *pDesktopWidget = QApplication::desktop();
	//获取可用桌面大小
	QRect DeskRect = pDesktopWidget->availableGeometry();
	int new_width = (DeskRect.width() - window_width) / 2;
	int new_height = (DeskRect.height() - window_height) / 2;
	QPoint window_rect(new_width, new_height);
	return window_rect;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow_UI w;
	//让窗口居中显示
	QPoint window_center(0, 0);
	window_center += get_window_center(w.width(), w.height());
	w.move(window_center.x(), window_center.y());
	w.show();
	return a.exec();
}
