#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QScrollArea>
#include <QStackedWidget>
#include <QPixmap>
#include <QIcon>
#include <QFont>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QTimer>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class NavigationCard;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onArrayClicked();
    void onLinkedListClicked();
    void onStackClicked();
    void onQueueClicked();
    void onTreeClicked();
    void onHeapClicked();
    void onGraphClicked();
    void onSortingClicked();
    void onSearchingClicked();
    void onAboutClicked();

private:
    void setupUI();
    void setupLeftPanel();
    void setupRightPanel();
    void setupNavigationCards();
    void setupWelcomeSection();
    void setupStyleSheets();

    // Main layout components
    QWidget *centralWidget;
    QHBoxLayout *mainLayout;

    // Left panel (navigation)
    QWidget *leftPanel;
    QVBoxLayout *leftLayout;
    QLabel *logoLabel;
    QLabel *titleLabel;
    QScrollArea *scrollArea;
    QWidget *cardsWidget;
    QGridLayout *cardsLayout;

    // Right panel (welcome/info)
    QWidget *rightPanel;
    QVBoxLayout *rightLayout;
    QLabel *welcomeLabel;
    QLabel *descriptionLabel;
    QLabel *featuresLabel;
    QFrame *featuresList;
    QPushButton *getStartedBtn;

    // Navigation cards
    QList<NavigationCard*> navCards;

    // Animation
    QPropertyAnimation *fadeAnimation;
};

// Custom Navigation Card Widget
class NavigationCard : public QFrame
{
    Q_OBJECT

public:
    NavigationCard(const QString &title, const QString &description,
                   const QString &iconPath, QWidget *parent = nullptr);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void clicked();

private:
    void setupCard();
    void animateHover(bool hover);

    QVBoxLayout *layout;
    QLabel *iconLabel;
    QLabel *titleLabel;
    QLabel *descriptionLabel;

    QPropertyAnimation *scaleAnimation;
    QGraphicsOpacityEffect *opacityEffect;

    bool isHovered;
    QString cardTitle;
    QString cardDescription;
    QString iconPath;
};

#endif // MAINWINDOW_H
