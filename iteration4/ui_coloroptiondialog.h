
#ifndef UI_COLOROPTIONDIALOG_H
#define UI_COLOROPTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_ColorOptionDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSlider *brightnessSlider;
    QLabel *label_2;
    QSlider *contrastSlider;
    QLabel *label_3;
    QSlider *hueSlider;
    QLabel *label_4;
    QSlider *sturationSlider;
    QPushButton *close;

    void setupUi(QDialog *ColorOptionDialog)
    {
        if (ColorOptionDialog->objectName().isEmpty())
            ColorOptionDialog->setObjectName(QStringLiteral("ColorOptionDialog"));
        ColorOptionDialog->resize(200, 182);
        gridLayout = new QGridLayout(ColorOptionDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(ColorOptionDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        brightnessSlider = new QSlider(ColorOptionDialog);
        brightnessSlider->setObjectName(QStringLiteral("brightnessSlider"));
        brightnessSlider->setMinimum(-100);
        brightnessSlider->setMaximum(100);
        brightnessSlider->setValue(0);
        brightnessSlider->setOrientation(Qt::Horizontal);
        brightnessSlider->setTickPosition(QSlider::NoTicks);

        gridLayout->addWidget(brightnessSlider, 0, 1, 1, 1);

        label_2 = new QLabel(ColorOptionDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        contrastSlider = new QSlider(ColorOptionDialog);
        contrastSlider->setObjectName(QStringLiteral("contrastSlider"));
        contrastSlider->setMinimum(-100);
        contrastSlider->setMaximum(100);
        contrastSlider->setValue(0);
        contrastSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(contrastSlider, 1, 1, 1, 1);

        label_3 = new QLabel(ColorOptionDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        hueSlider = new QSlider(ColorOptionDialog);
        hueSlider->setObjectName(QStringLiteral("hueSlider"));
        hueSlider->setMinimum(-100);
        hueSlider->setMaximum(100);
        hueSlider->setValue(0);
        hueSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(hueSlider, 2, 1, 1, 1);

        label_4 = new QLabel(ColorOptionDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        sturationSlider = new QSlider(ColorOptionDialog);
        sturationSlider->setObjectName(QStringLiteral("sturationSlider"));
        sturationSlider->setMinimum(-100);
        sturationSlider->setMaximum(100);
        sturationSlider->setValue(0);
        sturationSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sturationSlider, 3, 1, 1, 1);

        close = new QPushButton(ColorOptionDialog);
        close->setObjectName(QStringLiteral("close"));

        gridLayout->addWidget(close, 4, 0, 1, 2);


        retranslateUi(ColorOptionDialog);

        QMetaObject::connectSlotsByName(ColorOptionDialog);
    } // setupUi

    void retranslateUi(QDialog *ColorOptionDialog)
    {
        ColorOptionDialog->setWindowTitle(QApplication::translate("ColorOptionDialog", "Dialog", 0));
        label->setText(QApplication::translate("ColorOptionDialog", "Brightness", 0));
        label_2->setText(QApplication::translate("ColorOptionDialog", "Contrast", 0));
        label_3->setText(QApplication::translate("ColorOptionDialog", "Hue", 0));
        label_4->setText(QApplication::translate("ColorOptionDialog", "Saturation", 0));
        close->setText(QApplication::translate("ColorOptionDialog", "close", 0));
    } // retranslateUi

};

namespace Ui {
    class ColorOptionDialog: public Ui_ColorOptionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLOROPTIONDIALOG_H
