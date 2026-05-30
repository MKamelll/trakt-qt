#include "searchview.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "showdetailsview.hpp"

SearchView::SearchView(QWidget *parent) : QWidget(parent) {
    m_searchBar = new QLineEdit;
    m_searchBtn = new QPushButton("Search");
    m_listWidget = new QListWidget;
    m_loadingDialog = new LoadingDialog;
    m_searchBar->setPlaceholderText("show name...");

    auto vbox = new QVBoxLayout;
    auto searchBoxRow = new QHBoxLayout;

    searchBoxRow->addWidget(m_searchBar, 90);
    searchBoxRow->addWidget(m_searchBtn, 10);

    connect(m_searchBar, &QLineEdit::returnPressed, this, &SearchView::search);

    connect(m_searchBtn, &QPushButton::clicked, this, &SearchView::search);

    connect(m_searchBar, &QLineEdit::returnPressed, m_loadingDialog,
            &LoadingDialog::show);

    connect(m_searchBtn, &QPushButton::clicked, m_loadingDialog,
            &LoadingDialog::show);

    connect(m_searchBar, &QLineEdit::returnPressed, m_listWidget,
            &QListWidget::clear);

    connect(m_searchBtn, &QPushButton::clicked, m_listWidget,
            &QListWidget::clear);

    connect(TraktClient::instance(), &TraktClient::searchDone, m_loadingDialog,
            &LoadingDialog::hide);

    connect(TraktClient::instance(), &TraktClient::showSeasonsReady,
            m_loadingDialog, &LoadingDialog::hide);

    connect(TraktClient::instance(), &TraktClient::searchDone, this,
            &SearchView::onSearchDone);

    connect(TraktClient::instance(), &TraktClient::showDetailsReady, this,
            &SearchView::onShowDetails);

    connect(TraktClient::instance(), &TraktClient::showSeasonsReady, this,
            &SearchView::onShowSeasons);

    vbox->addLayout(searchBoxRow);
    vbox->addWidget(m_listWidget);
    vbox->setAlignment(Qt::AlignTop);
    setLayout(vbox);
}

void SearchView::search() {
    if (!m_searchBar->text().isEmpty()) {
        TraktClient::instance()->search(m_searchBar->text());
    }
}

void SearchView::onSearchDone(QList<StandardShow> results) {
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
            m_loadingDialog->show();
            TraktClient::instance()->getShowDetails(show.ids.trakt);
            TraktClient::instance()->getShowSeasons(show.ids.trakt);
        });

        auto *listitem = new QListWidgetItem(m_listWidget);
        listitem->setSizeHint(QSize(0, 60));
        m_listWidget->setItemWidget(listitem, item);
    }
}

void SearchView::onShowDetails(ShowDetails show) { m_show = show; }
void SearchView::onShowSeasons(QList<SeasonDetails> seasons) {
    m_seasons = seasons;
    auto *showView = new ShowDetailsView(m_show, m_seasons);
    showView->setAttribute(Qt::WA_DeleteOnClose);
    showView->show();
}
