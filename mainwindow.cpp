#include "mainwindow.h"
#include <QApplication>
#include <QScreen>
#include <QPainter>
#include <QLinearGradient>
#include <QMouseEvent>
#include <QEnterEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , centralWidget(nullptr)
    , fadeAnimation(nullptr)
{
    setupUI();
    setupStyleSheets();

    // Set window properties
    setWindowTitle("DSA Visualizer - Interactive Learning Tool");
    setMinimumSize(600, 400);
    //resize(1400, 900);

    // Center the window
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    setupLeftPanel();
    setupRightPanel();

    mainLayout->addWidget(leftPanel, 1);
    mainLayout->addWidget(rightPanel, 1);
}

void MainWindow::setupLeftPanel()
{
    leftPanel = new QWidget();
    leftPanel->setObjectName("leftPanel");
    leftPanel->setFixedWidth(600);

    leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(30, 30, 30, 30);
    leftLayout->setSpacing(20);

    // Logo and title section
    logoLabel = new QLabel();
    logoLabel->setText("🔬");
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setStyleSheet("font-size: 48px; margin: 10px;");

    titleLabel = new QLabel("DSA Visualizer");
    titleLabel->setObjectName("titleLabel");
    titleLabel->setAlignment(Qt::AlignCenter);

    leftLayout->addWidget(logoLabel);
    leftLayout->addWidget(titleLabel);
    leftLayout->addSpacing(20);

    // Navigation cards
    setupNavigationCards();

    leftLayout->addStretch();
}

void MainWindow::setupRightPanel()
{
    rightPanel = new QWidget();
    rightPanel->setObjectName("rightPanel");

    rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(50, 50, 50, 50);
    rightLayout->setSpacing(30);

    setupWelcomeSection();
}

void MainWindow::setupNavigationCards()
{
    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setObjectName("scrollArea");

    cardsWidget = new QWidget();
    cardsLayout = new QGridLayout(cardsWidget);
    cardsLayout->setContentsMargins(10, 10, 10, 10);
    cardsLayout->setSpacing(15);

    // Create navigation cards
    struct CardData {
        QString title;
        QString description;
        QString icon;
        std::function<void()> slot;
    };

    std::vector<CardData> cardData = {
        {"Arrays", "Insert, Delete, Search & Traverse operations", "📊", [this]() { onArrayClicked(); }},
        {"Linked Lists", "Singly & Doubly linked list operations", "🔗", [this]() { onLinkedListClicked(); }},
        {"Stacks", "Push, Pop & Peek operations (LIFO)", "📚", [this]() { onStackClicked(); }},
        {"Queues", "Enqueue & Dequeue operations (FIFO)", "🚶", [this]() { onQueueClicked(); }},
        {"Trees", "Binary Trees & BST operations", "🌳", [this]() { onTreeClicked(); }},
        {"Heaps", "Min/Max Heap & Heapify operations", "⛰️", [this]() { onHeapClicked(); }},
        {"Graphs", "BFS, DFS & Shortest Path algorithms", "🕸️", [this]() { onGraphClicked(); }},
        {"Sorting", "Bubble, Quick, Merge & more algorithms", "📈", [this]() { onSortingClicked(); }},
        {"Searching", "Linear & Binary search algorithms", "🔍", [this]() { onSearchingClicked(); }}
    };

    int row = 0, col = 0;
    for (const auto& data : cardData) {
        NavigationCard *card = new NavigationCard(data.title, data.description, data.icon);
        connect(card, &NavigationCard::clicked, data.slot);

        navCards.append(card);
        cardsLayout->addWidget(card, row, col);

        col++;
        if (col >= 2) {
            col = 0;
            row++;
        }
    }

    scrollArea->setWidget(cardsWidget);
    leftLayout->addWidget(scrollArea, 1);
}

void MainWindow::setupWelcomeSection()
{
    // Welcome title
    welcomeLabel = new QLabel("Welcome to DSA Visualizer!");
    welcomeLabel->setObjectName("welcomeLabel");
    welcomeLabel->setAlignment(Qt::AlignCenter);

    // Description
    descriptionLabel = new QLabel(
        "An interactive learning platform designed to help you understand "
        "Data Structures and Algorithms through step-by-step visual animations. "
        "Explore fundamental concepts with intuitive graphics and real-time demonstrations."
        );
    descriptionLabel->setObjectName("descriptionLabel");
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setAlignment(Qt::AlignCenter);

    // Features section
    featuresLabel = new QLabel("Key Features:");
    featuresLabel->setObjectName("featuresLabel");
    featuresLabel->setAlignment(Qt::AlignCenter);

    // Features list
    featuresList = new QFrame();
    featuresList->setObjectName("featuresList");
    QVBoxLayout *featuresLayout = new QVBoxLayout(featuresList);
    featuresLayout->setSpacing(15);

    QStringList features = {
        "🎯 Interactive step-by-step animations",
        "⚡ Real-time operation visualization",
        "🎮 Play/Pause controls with speed adjustment",
        "💡 Pseudocode highlighting during execution",
        "📱 User-friendly interface with modern design",
        "🔄 Support for all major data structures",
        "📊 Comprehensive algorithm demonstrations"
    };

    for (const QString &feature : features) {
        QLabel *featureLabel = new QLabel(feature);
        featureLabel->setObjectName("featureItem");
        featureLabel->setMargin(5);
        featuresLayout->addWidget(featureLabel);
    }

    // Get Started button
    getStartedBtn = new QPushButton("Get Started");
    getStartedBtn->setObjectName("getStartedBtn");
    getStartedBtn->setFixedHeight(50);
    connect(getStartedBtn, &QPushButton::clicked, [this]() {
        // Focus on the first navigation card or show a tutorial
        if (!navCards.isEmpty()) {
            navCards.first()->setFocus();
        }
    });

    // Add widgets to right layout
    rightLayout->addStretch(1);
    rightLayout->addWidget(welcomeLabel);
    rightLayout->addWidget(descriptionLabel);
    rightLayout->addSpacing(20);
    rightLayout->addWidget(featuresLabel);
    rightLayout->addWidget(featuresList);
    rightLayout->addSpacing(30);
    rightLayout->addWidget(getStartedBtn);
    rightLayout->addStretch(2);
}

void MainWindow::setupStyleSheets()
{
    setStyleSheet(R"(
        QMainWindow {
            background-color: #f5f7fa;
        }

        #leftPanel {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                      stop:0 #667eea, stop:1 #764ba2);
            border-top-right-radius: 20px;
            border-bottom-right-radius: 20px;
        }

        #rightPanel {
            background-color: #ffffff;
            border-left: 3px solid #e1e8ed;
        }

        #titleLabel {
            color: white;
            font-size: 32px;
            font-weight: bold;
            font-family: 'Segoe UI', Arial, sans-serif;
        }

        #scrollArea {
            background-color: transparent;
            border: none;
        }

        #welcomeLabel {
            color: #2c3e50;
            font-size: 36px;
            font-weight: bold;
            margin-bottom: 20px;
            font-family: 'Segoe UI', Arial, sans-serif;
        }

        #descriptionLabel {
            color: #5a6c7d;
            font-size: 18px;
            line-height: 1.6;
            font-family: 'Segoe UI', Arial, sans-serif;
        }

        #featuresLabel {
            color: #2c3e50;
            font-size: 24px;
            font-weight: bold;
            margin: 20px 0 10px 0;
            font-family: 'Segoe UI', Arial, sans-serif;
        }

        #featuresList {
            background-color: #f8f9fa;
            border-radius: 15px;
            border: 2px solid #e9ecef;
            padding: 20px;
        }

        #featureItem {
            color: #495057;
            font-size: 16px;
            font-family: 'Segoe UI', Arial, sans-serif;
            padding: 5px;
        }

        #getStartedBtn {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                                      stop:0 #667eea, stop:1 #764ba2);
            color: white;
            font-size: 18px;
            font-weight: bold;
            border: none;
            border-radius: 25px;
            padding: 15px 30px;
            font-family: 'Segoe UI', Arial, sans-serif;
        }

        #getStartedBtn:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                                      stop:0 #5a6fd8, stop:1 #6a4190);
        }

        #getStartedBtn:pressed {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                                      stop:0 #4e60c6, stop:1 #5e377e);
        }
    )");
}

// Slot implementations
void MainWindow::onArrayClicked() {
    // TODO: Navigate to Array page
    qDebug() << "Array page clicked";
}

void MainWindow::onLinkedListClicked() {
    // TODO: Navigate to Linked List page
    qDebug() << "Linked List page clicked";
}

void MainWindow::onStackClicked() {
    // TODO: Navigate to Stack page
    qDebug() << "Stack page clicked";
}

void MainWindow::onQueueClicked() {
    // TODO: Navigate to Queue page
    qDebug() << "Queue page clicked";
}

void MainWindow::onTreeClicked() {
    // TODO: Navigate to Tree page
    qDebug() << "Tree page clicked";
}

void MainWindow::onHeapClicked() {
    // TODO: Navigate to Heap page
    qDebug() << "Heap page clicked";
}

void MainWindow::onGraphClicked() {
    // TODO: Navigate to Graph page
    qDebug() << "Graph page clicked";
}

void MainWindow::onSortingClicked() {
    // TODO: Navigate to Sorting page
    qDebug() << "Sorting page clicked";
}

void MainWindow::onSearchingClicked() {
    // TODO: Navigate to Searching page
    qDebug() << "Searching page clicked";
}

void MainWindow::onAboutClicked() {
    // TODO: Show About dialog
    qDebug() << "About page clicked";
}

// NavigationCard Implementation
NavigationCard::NavigationCard(const QString &title, const QString &description,
                               const QString &iconPath, QWidget *parent)
    : QFrame(parent)
    , isHovered(false)
    , cardTitle(title)
    , cardDescription(description)
    , iconPath(iconPath)
{
    setupCard();
}

void NavigationCard::setupCard()
{
    setFixedSize(250, 140);
    setFrameStyle(QFrame::Box);
    setCursor(Qt::PointingHandCursor);
    setObjectName("navigationCard");

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 15, 20, 15);
    layout->setSpacing(8);

    // Icon
    iconLabel = new QLabel(iconPath);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setStyleSheet("font-size: 32px;");

    // Title
    titleLabel = new QLabel(cardTitle);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("cardTitle");

    // Description
    descriptionLabel = new QLabel(cardDescription);
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setObjectName("cardDescription");

    layout->addWidget(iconLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(descriptionLabel);

    // Setup animations
    scaleAnimation = new QPropertyAnimation(this, "geometry");
    scaleAnimation->setDuration(200);
    scaleAnimation->setEasingCurve(QEasingCurve::OutCubic);

    // Setup styling
    setStyleSheet(R"(
        #navigationCard {
            background-color: rgba(255, 255, 255, 0.95);
            border: 2px solid rgba(255, 255, 255, 0.3);
            border-radius: 15px;
        }

        #navigationCard:hover {
            background-color: rgba(255, 255, 255, 1.0);
            border: 2px solid rgba(255, 255, 255, 0.8);
        }

        #cardTitle {
            color: #2c3e50;
            font-size: 16px;
            font-weight: bold;
            font-family: 'Segoe UI', Arial, sans-serif;
        }

        #cardDescription {
            color: #5a6c7d;
            font-size: 12px;
            font-family: 'Segoe UI', Arial, sans-serif;
        }
    )");
}

void NavigationCard::enterEvent(QEnterEvent *event)
{
    Q_UNUSED(event)
    isHovered = true;
    animateHover(true);
}

void NavigationCard::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    isHovered = false;
    animateHover(false);
}

void NavigationCard::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    emit clicked();
}

void NavigationCard::animateHover(bool hover)
{
    QRect currentGeometry = geometry();
    QRect targetGeometry;

    if (hover) {
        targetGeometry = currentGeometry.adjusted(-5, -5, 5, 5);
    } else {
        targetGeometry = currentGeometry.adjusted(5, 5, -5, -5);
    }

    scaleAnimation->setStartValue(currentGeometry);
    scaleAnimation->setEndValue(targetGeometry);
    scaleAnimation->start();
}

void NavigationCard::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    if (isHovered) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Add subtle shadow effect
        QLinearGradient shadowGradient(0, 0, 0, height());
        shadowGradient.setColorAt(0, QColor(0, 0, 0, 30));
        shadowGradient.setColorAt(1, QColor(0, 0, 0, 10));

        painter.setBrush(shadowGradient);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect().adjusted(2, 2, 2, 2), 15, 15);
    }
}
