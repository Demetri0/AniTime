#include <QApplication>
#include <QtWebKitWidgets>

#include <QDir>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("AniTime");

    QWebView *view = new QWebView;

    {
        const QSettings cfg("settings.ini", QSettings::IniFormat);

        app.setApplicationVersion( cfg.value("app_version", "0.0.0").toString() );

        QString htmlDir   = cfg.value("html_dir", "html").toString();
        QString startPage = cfg.value("start_page", "index.html").toString();

        QString url;
        url += QDir::currentPath()
            +  QDir::separator()
            +  htmlDir
            +  QDir::separator()
            +  startPage;

        view->load( QUrl::fromLocalFile( url ) );

        QString window_icon = QDir::currentPath()
                            +  QDir::separator();
        QIcon icon( window_icon + cfg.value("window_icon", "icon.png").toString() );
        view->setWindowIcon( icon );
        view->setWindowTitle( cfg.value("window_title", "AniTime").toString() );
        Qt::ContextMenuPolicy context_menu;
        context_menu = ( cfg.value("context_menu", true).toBool() )
                       ? Qt::DefaultContextMenu
                       : Qt::NoContextMenu;
        view->setContextMenuPolicy( context_menu );
    }

    view->show();

    return app.exec();
}
