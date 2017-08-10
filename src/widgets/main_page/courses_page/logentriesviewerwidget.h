#ifndef LOGENTRIESVIEWERWIDGET_H
#define LOGENTRIESVIEWERWIDGET_H

#include <QtWidgets>

#include <memory>

#include <parser/logger/parserlogger.h>

enum class LOG_ENTRIES_FILTER : size_t {
    ALL = 0,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    LOG_ENTRIES_FILTERS_COUNT
};

class LogEntriesViewerWidgetUi;

class LogEntriesViewerWidget : public QWidget {
    Q_OBJECT

    friend class LogEntriesViewerWidgetUi;

public:
    explicit LogEntriesViewerWidget(QWidget* parent = nullptr);

signals:

public slots:
    void updateItems(std::shared_ptr<parser::ParserLogger> _logger = std::shared_ptr<parser::ParserLogger>());

private slots:
    void filterCheckboxClicked();

private:
    std::unique_ptr<LogEntriesViewerWidgetUi> ui;

    std::shared_ptr<parser::ParserLogger> logger;
    std::array<bool, size_t(LOG_ENTRIES_FILTER::LOG_ENTRIES_FILTERS_COUNT)> activeFilters;
};

class FilterCheckbox : public QCheckBox {
    Q_OBJECT
public:
    FilterCheckbox(LOG_ENTRIES_FILTER filter, const QString& text, QWidget* parent)
        : QCheckBox(text, parent)
        , filter(filter)
    {
    }
    LOG_ENTRIES_FILTER getFilter() const { return filter; }
private:
    LOG_ENTRIES_FILTER filter;

private:
};

class LogEntriesViewerWidgetUi {
    friend class LogEntriesViewerWidget;

public:
    LogEntriesViewerWidgetUi(LogEntriesViewerWidget* parent)
    {
        mainLayout = new QVBoxLayout;
        filterCheckboxesLayout = new QHBoxLayout;
        logEntries = new QListWidget;

        allFilterCheckbox = new FilterCheckbox(
            LOG_ENTRIES_FILTER::ALL,
            QObject::tr("all"), parent);
        debugFilterCheckbox = new FilterCheckbox(
            LOG_ENTRIES_FILTER::DEBUG,
            QObject::tr("debug"), parent);
        infoFilterCheckbox = new FilterCheckbox(
            LOG_ENTRIES_FILTER::INFO,
            QObject::tr("info"), parent);
        warningFilterCheckbox = new FilterCheckbox(
            LOG_ENTRIES_FILTER::WARNING,
            QObject::tr("warning"), parent);
        errorFilterCheckbox = new FilterCheckbox(
            LOG_ENTRIES_FILTER::ERROR,
            QObject::tr("error"), parent);

        filterCheckboxesLayout->addWidget(errorFilterCheckbox);
        filterCheckboxesLayout->addWidget(warningFilterCheckbox);
        filterCheckboxesLayout->addWidget(infoFilterCheckbox);
        filterCheckboxesLayout->addWidget(debugFilterCheckbox);
        filterCheckboxesLayout->addWidget(allFilterCheckbox);

        mainLayout->addLayout(filterCheckboxesLayout);
        mainLayout->addWidget(logEntries);

        parent->setLayout(mainLayout);

        QObject::connect(
            allFilterCheckbox, &FilterCheckbox::stateChanged,
            parent, &LogEntriesViewerWidget::filterCheckboxClicked);
        QObject::connect(
            debugFilterCheckbox, &FilterCheckbox::stateChanged,
            parent, &LogEntriesViewerWidget::filterCheckboxClicked);
        QObject::connect(
            infoFilterCheckbox, &FilterCheckbox::stateChanged,
            parent, &LogEntriesViewerWidget::filterCheckboxClicked);
        QObject::connect(
            warningFilterCheckbox, &FilterCheckbox::stateChanged,
            parent, &LogEntriesViewerWidget::filterCheckboxClicked);
        QObject::connect(
            errorFilterCheckbox, &FilterCheckbox::stateChanged,
            parent, &LogEntriesViewerWidget::filterCheckboxClicked);
    }

private:
    QVBoxLayout* mainLayout;
    QHBoxLayout* filterCheckboxesLayout;

    QListWidget* logEntries;

    FilterCheckbox* allFilterCheckbox;
    FilterCheckbox* debugFilterCheckbox;
    FilterCheckbox* infoFilterCheckbox;
    FilterCheckbox* warningFilterCheckbox;
    FilterCheckbox* errorFilterCheckbox;
};

#endif // LOGENTRIESVIEWERWIDGET_H
