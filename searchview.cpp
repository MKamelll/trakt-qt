#include "searchview.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "showdetailsview.hpp"

SearchView::SearchView(QWidget *parent) : QWidget(parent) {
    m_searchBar = new QLineEdit;
    m_searchBtn = new QPushButton("Search");
    m_listWidget = new QListWidget;
    m_progressBar = new QProgressBar;
    m_progressBar->setRange(0, 0);
    m_progressBar->hide();

    m_searchBar->setPlaceholderText("show name...");

    auto vbox = new QVBoxLayout;
    auto searchBoxRow = new QHBoxLayout;

    searchBoxRow->addWidget(m_searchBar, 90);
    searchBoxRow->addWidget(m_searchBtn, 10);

    connect(m_searchBar, &QLineEdit::returnPressed, this, [=]() {
        if (!m_searchBar->text().isEmpty()) {
            m_progressBar->show();
            TraktClient::instance()->search(m_searchBar->text());
        }
    });

    connect(m_searchBtn, &QPushButton::clicked, this, [=]() {
        if (!m_searchBar->text().isEmpty()) {
            m_progressBar->show();
            TraktClient::instance()->search(m_searchBar->text());
        }
    });

    connect(TraktClient::instance(), &TraktClient::searchDone, this,
            &SearchView::onSearchDone);

    connect(TraktClient::instance(), &TraktClient::showDetailsReady, this,
            &SearchView::onShowDetails);

    vbox->addLayout(searchBoxRow);
    vbox->addWidget(m_listWidget);
    vbox->addWidget(m_progressBar);
    vbox->setAlignment(Qt::AlignTop);
    setLayout(vbox);
}

void SearchView::onSearchDone(QList<StandardShow> results) {
    m_progressBar->hide();
    for (auto &show : results) {
        auto *item = new QWidget;
        auto *hbox = new QHBoxLayout(item);
        auto *vbox = new QVBoxLayout;
        auto *title = new QLabel(show.title);
        auto *year = new QLabel(QString::number(show.year));
        auto *showDetailsBtn = new QPushButton("Show Details");
        vbox->addWidget(title);
        vbox->addWidget(year);
        hbox->addLayout(vbox, 90);
        hbox->addWidget(showDetailsBtn, 10);

        connect(showDetailsBtn, &QPushButton::clicked, this, [=]() {
            TraktClient::instance()->getShowDetails(show.ids.trakt);
        });

        auto *listitem = new QListWidgetItem(m_listWidget);
        listitem->setSizeHint(QSize(0, 60));
        m_listWidget->setItemWidget(listitem, item);
    }
}

void SearchView::onShowDetails(ShowDetails result) {
    auto *showView = new ShowDetailsView(result);
    showView->setAttribute(Qt::WA_DeleteOnClose);
    showView->show();
}
