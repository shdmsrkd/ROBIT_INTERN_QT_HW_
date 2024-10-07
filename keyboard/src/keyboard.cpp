#include "keyboard.h"
#include "./ui_keyboard.h"
#include <cctype>
#include <QClipboard>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>

#define Status int
extern "C"
{
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
}
#undef Status
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , CapsState(1)
    , korState(0)
{
    ui->setupUi(this);

    ui->label->setText("_");



    ui->pushButton->setText("~\n`");
    ui->pushButton_2->setText("!\n1");
    ui->pushButton_3->setText("@\n2");
    ui->pushButton_4->setText("#\n3");
    ui->pushButton_5->setText("$\n4");
    ui->pushButton_7->setText("%\n5");
    ui->pushButton_6->setText("^\n6");
    ui->pushButton_8->setText("&&\n7");
    ui->pushButton_9->setText("*\n8");
    ui->pushButton_12->setText("(\n9");
    ui->pushButton_11->setText(")\n0");
    ui->pushButton_14->setText("_\n-");
    ui->pushButton_13->setText("+\n=");

    ui->pushButton_10->setText("Backspace");
    ui->pushButton_21->setText("Tab");
    ui->pushButton_19->setText("Q\nq");
    ui->pushButton_26->setText("W\nw");
    ui->pushButton_25->setText("E\ne");
    ui->pushButton_17->setText("R\nr");
    ui->pushButton_22->setText("U\nu");
    ui->pushButton_24->setText("I\ni");
    ui->pushButton_16->setText("O\no");
    ui->pushButton_23->setText("P\np");
    ui->pushButton_20->setText("{\n[");
    ui->pushButton_15->setText("}\n]");
    ui->pushButton_18->setText("\\\n|");

    ui->pushButton_27->setText("T\nt");
    ui->pushButton_28->setText("Y\ny");
    ui->pushButton_29->setText("K\nk");
    ui->pushButton_30->setText("A\na");
    ui->pushButton_31->setText("Z\nz");
    ui->pushButton_32->setText("Caps");
    ui->pushButton_33->setText("\"\n'");
    ui->pushButton_34->setText("D\nd");
    ui->pushButton_35->setText("F\nf");
    ui->pushButton_36->setText(":\n;");
    ui->pushButton_37->setText("S\ns");
    ui->pushButton_38->setText("J\nj");

    ui->pushButton_39->setText("L\nl");
    ui->pushButton_40->setText("G\ng");
    ui->pushButton_41->setText("H\nh");
    ui->pushButton_42->setText("Enter");
    ui->pushButton_43->setText("Fn");
    ui->pushButton_44->setText("<\n,");
    ui->pushButton_45->setText("M\nm");
    ui->pushButton_46->setText("?\n/");
    ui->pushButton_47->setText("C\nc");
    ui->pushButton_48->setText("V\nv");
    ui->pushButton_49->setText("Shift");
    ui->pushButton_50->setText("B\nb");
    ui->pushButton_53->setText("N\nn");
    ui->pushButton_52->setText("X\nx");
    ui->pushButton_51->setText(">\n.");
    ui->pushButton_54->setText("Shift");

    ui->pushButton_60->setText("Ctrl");
    ui->pushButton_56->setText("Alt");
    ui->pushButton_57->setText(" ");
    ui->pushButton_59->setText("Kor");
    ui->pushButton_65->setText("Win");
    ui->pushButton_64->setText("Menu");
    ui->pushButton_61->setText("Shift");

    ui->pushButton_63->setText("Copy");
    ui->pushButton_62->setText("Clear");
}



void MainWindow::change_pushButton_name()
{
    if (korState)
    {
        ui->pushButton_19->setText("ㅂ");
        ui->pushButton_26->setText("ㅈ");
        ui->pushButton_25->setText("ㄷ");
        ui->pushButton_17->setText("ㄱ");
        ui->pushButton_22->setText("ㅕ");
        ui->pushButton_24->setText("ㅑ");
        ui->pushButton_16->setText("ㅒ\nㅐ");
        ui->pushButton_23->setText("ㅖ\nㅔ");
        ui->pushButton_27->setText("ㅅ");
        ui->pushButton_28->setText("ㅛ");
        ui->pushButton_29->setText("ㅑ");
        ui->pushButton_30->setText("ㅁ");
        ui->pushButton_31->setText("ㅋ");
        ui->pushButton_34->setText("ㄷ");
        ui->pushButton_35->setText("ㅍ");
        ui->pushButton_37->setText("ㅅ");
        ui->pushButton_38->setText("ㅈ");
        ui->pushButton_39->setText("ㄹ");
        ui->pushButton_40->setText("ㄱ");
        ui->pushButton_41->setText("ㅎ");
        ui->pushButton_45->setText("ㅁ");
        ui->pushButton_47->setText("ㅊ");
        ui->pushButton_48->setText("ㅂ");
        ui->pushButton_50->setText("ㅂ");
        ui->pushButton_53->setText("ㄴ");
        ui->pushButton_52->setText("ㅋ");
    }
    else
    {
        ui->pushButton_19->setText("Q\nq");
        ui->pushButton_26->setText("W\nw");
        ui->pushButton_25->setText("E\ne");
        ui->pushButton_17->setText("R\nr");
        ui->pushButton_22->setText("U\nu");
        ui->pushButton_24->setText("I\ni");
        ui->pushButton_16->setText("O\no");
        ui->pushButton_23->setText("P\np");
        ui->pushButton_27->setText("T\nt");
        ui->pushButton_28->setText("Y\ny");
        ui->pushButton_29->setText("K\nk");
        ui->pushButton_30->setText("A\na");
        ui->pushButton_31->setText("Z\nz");
        ui->pushButton_34->setText("D\nd");
        ui->pushButton_35->setText("F\nf");
        ui->pushButton_37->setText("S\ns");
        ui->pushButton_38->setText("J\nj");
        ui->pushButton_39->setText("L\nl");
        ui->pushButton_40->setText("G\ng");
        ui->pushButton_41->setText("H\nh");
        ui->pushButton_45->setText("M\nm");
        ui->pushButton_47->setText("C\nc");
        ui->pushButton_48->setText("V\nv");
        ui->pushButton_50->setText("B\nb");
        ui->pushButton_53->setText("N\nn");
        ui->pushButton_52->setText("X\nx");
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::vectorPrint(QLabel* label, const std::vector<std::string>& vec)
{
    QString input_vec_result;


    for(int i = 0; i < vec.size(); i++)
    {
        input_vec_result += vec[i].c_str();
    }

    label->setText(input_vec_result + "_");
}


void MainWindow::on_pushButton_clicked()
{
    if (CapsState == 0)
    {
        input_vec.push_back("~");
    }
    else
    {
        input_vec.push_back("`");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_2_clicked()
{
    if (CapsState == 1)
    {
        input_vec.push_back("1");
    }
    else
    {
        input_vec.push_back("!");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_3_clicked()
{
    if (CapsState == 1)
    {
        input_vec.push_back("2");
    }
    else
    {
        input_vec.push_back("@");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_4_clicked()
{
    if (CapsState == 1)
    {
        input_vec.push_back("3");
    }
    else
    {
        input_vec.push_back("#");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_5_clicked()
{
    if (CapsState == 1)
    {
        input_vec.push_back("4");
    }
    else
    {
        input_vec.push_back("$");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_7_clicked()
{
    if (CapsState == 1)
    {
        input_vec.push_back("5");
    }
    else
    {
        input_vec.push_back("%");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_6_clicked()
{
    if (CapsState == 1)
    {
        input_vec.push_back("6");
    }
    else
    {
        input_vec.push_back("^");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_8_clicked()
{
    if (CapsState == 1)
    {
        input_vec.push_back("7");
    }
    else
    {
        input_vec.push_back("&");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_9_clicked()
{
    if (CapsState == 1)
    {
        input_vec.push_back("8");
    }
    else
    {
        input_vec.push_back("*");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_12_clicked()
{
    if (CapsState == 1)
    {
        input_vec.push_back("9");
    }
    else
    {
        input_vec.push_back("(");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_11_clicked()
{
    if (CapsState == 1)
    {
        input_vec.push_back("0");
    }
    else
    {
        input_vec.push_back(")");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_14_clicked()
{
    if (CapsState == 1)
    {
        input_vec.push_back("-");
    }
    else
    {
        input_vec.push_back("_");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_13_clicked()
{
    if (CapsState == 1)
    {
        input_vec.push_back("=");
    }
    else
    {
        input_vec.push_back("+");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_10_clicked()
{
    if (!input_vec.empty())
    {
        input_vec.pop_back();
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_21_clicked()
{
    input_vec.push_back("\t");

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_19_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("Q");
        }
        else
        {
            input_vec.push_back("q");
        }
    }
    else
    {
        input_vec.push_back("ㅂ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_26_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("W");
        }
        else
        {
            input_vec.push_back("w");
        }
    }
    else
    {
        input_vec.push_back("ㅈ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_25_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("E");
        }
        else
        {
            input_vec.push_back("e");
        }
    }
    else
    {
        input_vec.push_back("ㄷ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_17_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("R");
        }
        else
        {
            input_vec.push_back("r");
        }
    }
    else
    {
        input_vec.push_back("ㄱ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_22_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("U");
        }
        else
        {
            input_vec.push_back("u");
        }
    }
    else
    {
        input_vec.push_back("ㅕ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_24_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("I");
        }
        else
        {
            input_vec.push_back("i");
        }
    }
    else
    {
        input_vec.push_back("ㅑ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_16_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("O");
        }
        else
        {
            input_vec.push_back("o");
        }
    }
    else
    {

        if (CapsState == 0)
        {
            input_vec.push_back("ㅒ");
        }
        else
        {
            input_vec.push_back("ㅐ");
        }
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_23_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("P");
        }
        else
        {
            input_vec.push_back("p");
        }
    }
    else
    {
        if (CapsState == 0)
        {
            input_vec.push_back("ㅖ");
        }
        else
        {
            input_vec.push_back("ㅔ");
        }
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_20_clicked()
{

    if (CapsState == 0)
    {
        input_vec.push_back("{");
    }
    else
    {
        input_vec.push_back("[");
    }


    vectorPrint(ui->label, input_vec);
}


void MainWindow::on_pushButton_15_clicked()
{

    if (CapsState == 0)
    {
        input_vec.push_back("}");
    }
    else
    {
        input_vec.push_back("]");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_18_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("\\");
        }
        else
        {
            input_vec.push_back("|");
        }
    }
    else
    {
        input_vec.push_back("ㅊ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_27_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("T");
        }
        else
        {
            input_vec.push_back("t");
        }
    }
    else
    {
        input_vec.push_back("ㅅ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_28_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("Y");
        }
        else
        {
            input_vec.push_back("y");
        }
    }
    else
    {
        input_vec.push_back("ㅛ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_29_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("K");
        }
        else
        {
            input_vec.push_back("k");
        }
    }
    else
    {
        input_vec.push_back("ㅏ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_30_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("A");
        }
        else
        {
            input_vec.push_back("a");
        }
    }
    else
    {
        input_vec.push_back("ㅁ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_31_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("Z");
        }
        else
        {
            input_vec.push_back("z");
        }
    }
    else
    {
        input_vec.push_back("ㅋ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_32_clicked()
{
    CapsState = !CapsState;

    if (CapsState == 0)
    {
        ui->pushButton_32->setStyleSheet("background-color: black; color: white;");
    }
    else
    {
        ui->pushButton_32->setStyleSheet("background-color: gray; color: black;");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_33_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("\"");
        }
        else
        {
            input_vec.push_back("'");
        }
    }
    else
    {
        input_vec.push_back("ㅎ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_34_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("D");
        }
        else
        {
            input_vec.push_back("d");
        }
    }
    else
    {
        input_vec.push_back("ㅇ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_35_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("F");
        }
        else
        {
            input_vec.push_back("f");
        }
    }
    else
    {
        input_vec.push_back("ㄹ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_36_clicked()
{

    if (CapsState == 0)
    {
        input_vec.push_back(":");
    }
    else
    {
        input_vec.push_back(";");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_37_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("S");
        }
        else
        {
            input_vec.push_back("s");
        }
    }
    else
    {
        input_vec.push_back("ㄴ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_38_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("J");
        }
        else
        {
            input_vec.push_back("j");
        }
    }
    else
    {
        input_vec.push_back("ㅓ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_39_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("L");
        }
        else
        {
            input_vec.push_back("l");
        }
    }
    else
    {
        input_vec.push_back("ㅣ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_40_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("G");
        }
        else
        {
            input_vec.push_back("g");
        }
    }
    else
    {
        input_vec.push_back("ㅎ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_41_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("H");
        }
        else
        {
            input_vec.push_back("h");
        }
    }
    else
    {
        input_vec.push_back("ㅗ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_42_clicked()
{
    input_vec.push_back("\n");

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_43_clicked()
{
}

void MainWindow::on_pushButton_44_clicked()
{
    if (CapsState == 0)
    {
        input_vec.push_back("<");
    }
    else
    {
        input_vec.push_back(",");
    }
    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_45_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("M");
        }
        else
        {
            input_vec.push_back("m");
        }
    }
    else
    {
        input_vec.push_back("ㅡ");
    }

    vectorPrint(ui->label, input_vec);
}


void MainWindow::on_pushButton_46_clicked()
{
    if (CapsState == 0)
    {
        input_vec.push_back("?");
    }
    else
    {
        input_vec.push_back("/");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_47_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("C");
        }
        else
        {
            input_vec.push_back("c");
        }
    }
    else
    {
        input_vec.push_back("ㅊ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_48_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("V");
        }
        else
        {
            input_vec.push_back("v");
        }
    }
    else
    {
        input_vec.push_back("ㅍ");
    }

    vectorPrint(ui->label, input_vec);;
}

void MainWindow::on_pushButton_49_clicked()
{
    // Shift 버튼 기능 구현
}

void MainWindow::on_pushButton_50_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("B");
        }
        else
        {
            input_vec.push_back("b");
        }
    }
    else
    {
        input_vec.push_back("ㅠ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_53_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("N");
        }
        else
        {
            input_vec.push_back("n");
        }
    }
    else
    {
        input_vec.push_back("ㅜ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_52_clicked()
{
    if (korState == 0)
    {
        if (CapsState == 0)
        {
            input_vec.push_back("X");
        }
        else
        {
            input_vec.push_back("x");
        }
    }
    else
    {
        input_vec.push_back("ㅌ");
    }

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_51_clicked()
{
    if (CapsState == 0)
    {
        input_vec.push_back(">");
    }
    else
    {
        input_vec.push_back(".");
    }
    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_54_clicked()
{
}

void MainWindow::on_pushButton_60_clicked()
{
}

void MainWindow::on_pushButton_56_clicked()
{
}

void MainWindow::on_pushButton_57_clicked()
{
    input_vec.push_back(" ");

    vectorPrint(ui->label, input_vec);
}

void MainWindow::on_pushButton_59_clicked()
{
    korState = !korState;

    if(korState == 0)
    {
        ui->pushButton_59->setStyleSheet("background-color: black; color: white;");
    }
    else
    {
        ui->pushButton_59->setStyleSheet("background-color: gray; color: black;");
    }

    change_pushButton_name();
    vectorPrint(ui->label, input_vec);

}
void MainWindow::on_pushButton_65_clicked()
{
#define Status int
    Display* display = XOpenDisplay(NULL);
    if (display == NULL) {
        qDebug() << "Unable to open X display";
        return;
    }

    // Windows 키의 키심(keysym)
    KeySym winKeySym = XK_Super_L;  // 왼쪽 Windows 키
    KeyCode keycode = XKeysymToKeycode(display, winKeySym);

    // 키 누르기
    XTestFakeKeyEvent(display, keycode, True, 0);
    // 키 떼기
    XTestFakeKeyEvent(display, keycode, False, 0);

    XFlush(display);
    XCloseDisplay(display);
#undef Status
}

void MainWindow::on_pushButton_64_clicked()
{
}

void MainWindow::on_pushButton_61_clicked()
{
}


void MainWindow::on_pushButton_63_clicked()
{
    QString input_vec_result_2;
    QClipboard *clipboard = QApplication::clipboard();

    for (int i = 0; i < input_vec.size(); i++)
    {
        input_vec_result_2 += QString::fromStdString(input_vec[i]);
    }

    clipboard->setText(input_vec_result_2);
}




void MainWindow::on_pushButton_62_clicked()
{
    while (!input_vec.empty())
    {
        input_vec.pop_back();
    }

    vectorPrint(ui->label, input_vec);
}

