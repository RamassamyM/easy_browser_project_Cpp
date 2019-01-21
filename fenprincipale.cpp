#include "fenprincipale.h"

QString FenPrincipale::homeUrl = "http://www.poietis.com";
QString FenPrincipale::homeTitle = "Poietis";

FenPrincipale::FenPrincipale()
{
    QWidget *zoneCentrale = new QWidget;
    setCentralWidget(zoneCentrale);

    creerActions();
    creerMenus();
    creerBarresOutils();
    creerStatusBar();
    zoneCentrale->setLayout(ongletsLayout());

    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionAProposQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(actionAPropos, SIGNAL(triggered()), this, SLOT(ouvrirDialogAPropos()));
    connect(actionGo, SIGNAL(triggered()), this, SLOT(chargerPageWeb()));
    connect(actionPagePrecedente, SIGNAL(triggered()), this, SLOT(chargerPagePrecedente()));
    connect(actionPageSuivante, SIGNAL(triggered()), this, SLOT(chargerPageSuivante()));
    connect(barreAdresse, SIGNAL(returnPressed()), this, SLOT(chargerPageWeb()));
    connect(actionPageAccueil, SIGNAL(triggered()), this, SLOT(loadHomepage()));
    connect(actionNewTab, SIGNAL(triggered()), this, SLOT(addNewTab()));
    connect(this, SIGNAL(newTabAdded(int)), onglets, SLOT(setCurrentIndex(int)));
    connect(onglets, SIGNAL(currentChanged(int)), this, SLOT(updateUrlWithTabIndex(int)));
    connect(actionActualiser, SIGNAL(triggered()), this, SLOT(actualiserPage()));
    connect(actionCloseTab, SIGNAL(triggered()), this, SLOT(closeCurrentTab()));
    connect(actionStop, SIGNAL(triggered()), this, SLOT(stopLoading()));

}


void FenPrincipale::creerActions()
{
    actionPagePrecedente = new QAction("&Page précédente", this);
    actionPagePrecedente->setShortcut(QKeySequence("Ctrl+P"));
    actionPagePrecedente->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/prec.png"));

    actionPageSuivante = new QAction("Page &suivante", this);
    actionPageSuivante->setShortcut(QKeySequence("Ctrl+N"));
    actionPageSuivante->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/suiv.png"));

    actionStop = new QAction("&Arrêter le chargement", this);
    actionStop->setShortcut(QKeySequence("Ctrl+k"));
    actionStop->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/stop.png"));

    actionActualiser = new QAction("Act&ualiser la page", this);
    actionActualiser->setShortcut(QKeySequence("Ctrl+R"));
    actionActualiser->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/actu.png"));

    actionPageAccueil = new QAction("Page d'a&ccueil", this);
    actionPageAccueil->setShortcut(QKeySequence("Ctrl+H"));
    actionPageAccueil->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/home.png"));

    actionGo = new QAction("&Lancer le chargement", this);
    actionGo->setShortcut(QKeySequence("Ctrl+L"));
    actionGo->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/go.png"));

    actionAProposQt = new QAction("A propos de Qt...", this);
    actionAProposQt->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/apropos.png"));
    actionAPropos = new QAction("A propos...", this);
    actionQuitter = new QAction("Quitter", this);
    actionQuitter->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/quitter.png"));
    actionNewTab = new QAction("Nouvel onglet", this);
    actionNewTab->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/nouvelonglet.png"));
    actionCloseTab = new QAction("Fermer l'onglet", this);
    actionCloseTab->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/fermeronglet.png"));
}

void FenPrincipale::creerMenus()
{
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    menuFichier->addAction(actionNewTab);
    menuFichier->addAction(actionCloseTab);
    menuFichier->addSeparator();
    menuFichier->addAction(actionQuitter);

    QMenu *menuNavigation = menuBar()->addMenu("&Navigation");
    menuNavigation->addAction(actionPagePrecedente);
    menuNavigation->addAction(actionPageSuivante);
    menuNavigation->addAction(actionStop);
    menuNavigation->addAction(actionActualiser);
    menuNavigation->addAction(actionPageAccueil);
    menuNavigation->addAction(actionGo);

    QMenu *menuAide = menuBar()->addMenu("&Aide");
    menuAide->addAction(actionAPropos);
    menuAide->addAction(actionAProposQt);
}

void FenPrincipale::creerBarresOutils()
{
    QToolBar *navigationBar = addToolBar("Navigation");
    navigationBar->addAction(actionPagePrecedente);
    navigationBar->addAction(actionPageSuivante);
    navigationBar->addAction(actionStop);
    navigationBar->addAction(actionActualiser);
    navigationBar->addAction(actionPageAccueil);
    navigationBar->addSeparator();
    navigationBar->addAction(actionNewTab);
    navigationBar->addAction(actionCloseTab);
    navigationBar->addSeparator();
    barreAdresse = new QLineEdit;
    navigationBar->addWidget(barreAdresse);
    navigationBar->addSeparator();
    navigationBar->addAction(actionGo);
}

void FenPrincipale::creerStatusBar()
{
    statusProgressBar = new QProgressBar(this);
    statusBar()->addPermanentWidget(statusProgressBar,1);
}

QVBoxLayout *FenPrincipale::ongletsLayout()
{
    QVBoxLayout *ongletsLayout = new QVBoxLayout;
    onglets = new QTabWidget(this);
    QWebEngineView *pageWeb = new QWebEngineView;
    pageWeb->load(QUrl(homeUrl));
    onglets->addTab(pageWeb, homeTitle);
    connect(pageWeb, SIGNAL(titleChanged(QString)), this, SLOT(updateTitle(QString)));
    connect(pageWeb, SIGNAL(urlChanged(QUrl)), this, SLOT(updateUrl(QUrl)));
//    barreAdresse->setText(homeUrl);
    ongletsLayout->addWidget(onglets);
    return ongletsLayout;
}

void FenPrincipale::chargerPageWeb()
{
    QWidget *actualTabWidget = onglets->currentWidget();
    QWebEngineView *actualView = (QWebEngineView*)actualTabWidget;
    actualView->page()->load(QUrl(barreAdresse->text(),QUrl::StrictMode));
}

QWebEnginePage *actualPage(QTabWidget *onglets)
{
    QWidget *actualTabWidget = onglets->currentWidget();
    QWebEngineView *actualView = (QWebEngineView*)actualTabWidget;
    return actualView->page();
}

void FenPrincipale::ouvrirDialogAPropos()
{
     QMessageBox::information(this, "A propos...", "Copyright Browser V1.0");
}

void FenPrincipale::chargerPagePrecedente()
{
    if (actualPage(onglets)->history()->canGoBack())
    {
        barreAdresse->setText(actualPage(onglets)->history()->backItem().url().toString(QUrl::None));
        actualPage(onglets)->history()->back();
    }
}

void FenPrincipale::chargerPageSuivante()
{
    if (actualPage(onglets)->history()->canGoForward())
    {
        barreAdresse->setText(actualPage(onglets)->history()->forwardItem().url().toString(QUrl::None));
        actualPage(onglets)->history()->forward();
    }
}

void FenPrincipale::updateTitle(QString newTitle)
{
    newTitle.truncate(20);
    newTitle += "...";
    onglets->setTabText(onglets->currentIndex(), newTitle);
}
    QAction *actionQuitter;

void FenPrincipale::updateUrl(QUrl newUrl)
{
    barreAdresse->setText(newUrl.toString(QUrl::None));
}

void FenPrincipale::loadHomepage()
{
    QWidget *actualTabWidget = onglets->currentWidget();
    QWebEngineView *actualView = (QWebEngineView*)actualTabWidget;
    actualView->page()->load(homeUrl);
}

void FenPrincipale::addNewTab()
{
    QWebEngineView *pageWeb = new QWebEngineView;
    pageWeb->load(QUrl(homeUrl));
    int indexNewTab = onglets->insertTab(onglets->currentIndex() + 1, pageWeb, homeTitle);
    emit newTabAdded(indexNewTab);
    barreAdresse->setText(homeUrl);
    connect(pageWeb, SIGNAL(titleChanged(QString)), this, SLOT(updateTitle(QString)));
    connect(pageWeb, SIGNAL(urlChanged(QUrl)), this, SLOT(updateUrl(QUrl)));
    connect(pageWeb, SIGNAL(loadProgress(int)), this, SLOT(updateProgressBar(int)));
}

void FenPrincipale::updateUrlWithTabIndex(int index)
{
    QWidget *tabWidget = onglets->widget(index);
    QWebEngineView *tabView = (QWebEngineView*)tabWidget;
    barreAdresse->setText(tabView->page()->url().toString(QUrl::None));
}

void FenPrincipale::actualiserPage()
{
    actualPage(onglets)->load(actualPage(onglets)->url());
}

void FenPrincipale::closeCurrentTab()
{
    onglets->removeTab(onglets->currentIndex());
}

void FenPrincipale::stopLoading()
{
    QWidget *tabWidget = onglets->currentWidget();
    QWebEngineView *tabView = (QWebEngineView*)tabWidget;
    tabView->page()->triggerAction(QWebEnginePage::Stop);
}

void FenPrincipale::updateProgressBar(int progressValue)
{
    statusProgressBar->setValue(progressValue);
}
