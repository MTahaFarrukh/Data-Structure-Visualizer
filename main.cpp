#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include <QFontDatabase>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Set application properties
    app.setApplicationName("DSA Visualizer");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("DSA Learning Tools");
    app.setApplicationDisplayName("Data Structure & Algorithm Visualizer");


    // Set a modern style
    app.setStyle(QStyleFactory::create("Fusion"));

    // Apply global application stylesheet for better consistency
    app.setStyleSheet(R"(
        QScrollBar:vertical {
            background-color: #f1f1f1;
            width: 12px;
            border-radius: 6px;
        }

        QScrollBar::handle:vertical {
            background-color: #c1c1c1;
            border-radius: 6px;
            min-height: 20px;
            margin: 2px;
        }

        QScrollBar::handle:vertical:hover {
            background-color: #a8a8a8;
        }

        QScrollBar::handle:vertical:pressed {
            background-color: #8f8f8f;
        }

        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            border: none;
            background: none;
        }

        QScrollBar:horizontal {
            background-color: #f1f1f1;
            height: 12px;
            border-radius: 6px;
        }

        QScrollBar::handle:horizontal {
            background-color: #c1c1c1;
            border-radius: 6px;
            min-width: 20px;
            margin: 2px;
        }

        QScrollBar::handle:horizontal:hover {
            background-color: #a8a8a8;
        }

        QScrollBar::handle:horizontal:pressed {
            background-color: #8f8f8f;
        }

        QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
            border: none;
            background: none;
        }

        QToolTip {
            background-color: #2c3e50;
            color: white;
            border: 1px solid #34495e;
            border-radius: 4px;
            padding: 5px;
            font-size: 12px;
        }
    )");

    // Create and show main window
    MainWindow window;
    window.show();

    return app.exec();
}
