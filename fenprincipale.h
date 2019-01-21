#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QMainWindow>
#include <QtWebEngine>
#include <QCoreApplication>
#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QLineEdit>
#include <QTabWidget>
#include <QWidget>
#include <QWebEngineHistory>
#include <QWebEngineHistoryItem>
#include <QWebEnginePage>
#include <QWebEngineView>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QUrl>
#include <QProgressBar>
#include <QStatusBar>

class FenPrincipale : public QMainWindow
{
    Q_OBJECT

public:
    FenPrincipale();


public slots:
    void chargerPageWeb();
    void ouvrirDialogAPropos();
    void chargerPagePrecedente();
    void chargerPageSuivante();
    void updateUrl(QUrl newUrl);
    void updateTitle(QString newTitle);
    void loadHomepage();
    void addNewTab();
    void updateUrlWithTabIndex(int index);
    void actualiserPage();
    void closeCurrentTab();
    void stopLoading();
    void updateProgressBar(int progressValue);

signals:
    void newTabAdded(int indexNewTab);

private:
    QAction *actionPagePrecedente;
    QAction *actionPageSuivante;
    QAction *actionStop;
    QAction *actionActualiser;
    QAction *actionPageAccueil;
    QAction *actionGo;
    QAction *actionAProposQt;
    QAction *actionAPropos;
    QAction *actionQuitter;
    QAction *actionNewTab;
    QAction *actionCloseTab;

    QLineEdit *barreAdresse;
    QTabWidget *onglets;
    QProgressBar *statusProgressBar;


    void creerActions();
    void creerMenus();
    void creerBarresOutils();
    void creerStatusBar();
    QVBoxLayout *ongletsLayout();

    static QString homeUrl;
    static QString homeTitle;
};

QWebEnginePage *actualPage(QTabWidget *onglets);

#endif // FENPRINCIPALE_H
