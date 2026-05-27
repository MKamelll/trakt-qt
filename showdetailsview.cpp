#include "showdetailsview.hpp"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>

ShowDetailsView::ShowDetailsView(ShowDetails show, QWidget *parent)
    : QWidget(parent) {

    setWindowTitle(show.title);
    resize(640, 420);

    auto *content = new QWidget;
    auto *layout = new QVBoxLayout(content);
    auto *scroll = new QScrollArea;
    scroll->setWidget(content);
    scroll->setWidgetResizable(true);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_titleGroup = createGroup("Title", show.title);
    m_yearGroup = createGroup("Year", show.year);
    m_overviewGroup = createGroup("Overview", show.overview, true);
    m_taglineGroup = createGroup("TagLine", show.tagLine);
    m_firstAiredGroup = createGroup("First Aired", show.firstAired);
    m_runtimeGroup = createGroup("Runtime (minutes)", show.runtime);
    m_networkGroup = createGroup("Network", show.network);
    m_countryGroup = createGroup("Country", show.country);
    m_ratingGroup = createGroup("Rating/10", show.rating);
    m_languagesGroup = createGroup("Languages", show.languages);
    m_genresGroup = createGroup("Genres", show.genres);
    m_originalTitleGroup = createGroup("Original Title", show.originalTitle);

    QList<QGroupBox *> infoGroups = {
        m_titleGroup,     m_yearGroup,       m_taglineGroup,
        m_overviewGroup,  m_firstAiredGroup, m_runtimeGroup,
        m_networkGroup,   m_countryGroup,    m_ratingGroup,
        m_languagesGroup, m_genresGroup,     m_originalTitleGroup};

    for (const auto &gp : infoGroups) {
        layout->addWidget(gp);
    }

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scroll);
}

QGroupBox *ShowDetailsView::createGroup(QString title, QString labelTxt,
                                        bool wrap) {
    auto *gp = new QGroupBox(title);
    auto *vbox = new QVBoxLayout(gp);
    auto *label = new QLabel(labelTxt);
    label->setWordWrap(wrap);
    vbox->addWidget(label);
    return gp;
}

QGroupBox *ShowDetailsView::createGroup(QString title, int labelTxt,
                                        bool wrap) {
    auto *gp = new QGroupBox(title);
    auto *vbox = new QVBoxLayout(gp);
    auto *label = new QLabel(QString::number(labelTxt));
    label->setWordWrap(wrap);
    vbox->addWidget(label);
    return gp;
}

QGroupBox *ShowDetailsView::createGroup(QString title, QDateTime labelTxt,
                                        bool wrap) {
    auto *gp = new QGroupBox(title);
    auto *vbox = new QVBoxLayout(gp);
    auto *label =
        new QLabel(labelTxt.toString("dddd, MMMM d, yyyy - hh:mm AP t"));
    label->setWordWrap(wrap);
    vbox->addWidget(label);
    return gp;
}

QGroupBox *ShowDetailsView::createGroup(QString title, QList<QString> labelTxt,
                                        bool wrap) {
    auto *gp = new QGroupBox(title);
    auto *vbox = new QVBoxLayout(gp);
    QString st("");
    for (const auto &lang : labelTxt) {
        st.append(lang + ", ");
    }
    st.chop(2);
    auto *label = new QLabel(st);
    label->setWordWrap(wrap);
    vbox->addWidget(label);
    return gp;
}
