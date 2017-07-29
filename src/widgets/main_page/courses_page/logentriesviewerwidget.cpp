#include "logentriesviewerwidget.h"

LogEntriesViewerWidget::LogEntriesViewerWidget(QWidget* parent)
    : QWidget(parent)
{
    for (auto& item : activeFilters)
        item = false;

    ui = std::make_unique<LogEntriesViewerWidgetUi>(this);

    ui->errorFilterCheckbox->setChecked(true);
    //    activeFilters.at(size_t(LOG_ENTRIES_FILTER::ERROR)) = true;
}

void LogEntriesViewerWidget::updateItems(std::shared_ptr<parser::ParserLogger> _logger)
{
    if (_logger) {
        logger = _logger;
    }

    if (!logger)
        return;

    ui->logEntries->clear();

    bool skip = true;
    for (auto& filter : activeFilters) {
        if (filter) {
            skip = false;
            break;
        }
    }
    if (skip)
        return;

    for (auto& entry : logger->getEntries()) {
        if (activeFilters.at(size_t(LOG_ENTRIES_FILTER::ALL))) {
            ui->logEntries->addItem(entry->toString());
            continue;
        }

        switch (entry->getType()) {
        case parser::LOG_ENTRY_TYPE::DEBUG:
            if (!activeFilters.at(size_t(LOG_ENTRIES_FILTER::DEBUG)))
                continue;
            break;
        case parser::LOG_ENTRY_TYPE::INFO:
            if (!activeFilters.at(size_t(LOG_ENTRIES_FILTER::INFO)))
                continue;
            break;
        case parser::LOG_ENTRY_TYPE::WARNING:
            if (!activeFilters.at(size_t(LOG_ENTRIES_FILTER::WARNING)))
                continue;
            break;
        case parser::LOG_ENTRY_TYPE::ERROR:
            if (!activeFilters.at(size_t(LOG_ENTRIES_FILTER::ERROR)))
                continue;
            break;
        }
        ui->logEntries->addItem(entry->toString());
    }
}

void LogEntriesViewerWidget::filterCheckboxClicked()
{
    FilterCheckbox* obj = qobject_cast<FilterCheckbox*>(sender());

    if (!obj)
        return;

    activeFilters.at(size_t(obj->getFilter())) = obj->isChecked();

    if (obj->getFilter() == LOG_ENTRIES_FILTER::ALL) {
        ui->debugFilterCheckbox->setChecked(true);
        ui->infoFilterCheckbox->setChecked(true);
        ui->warningFilterCheckbox->setChecked(true);
        ui->errorFilterCheckbox->setChecked(true);
    } else {
        if (ui->debugFilterCheckbox->isChecked()
            && ui->infoFilterCheckbox->isChecked()
            && ui->warningFilterCheckbox->isChecked()
            && ui->errorFilterCheckbox->isChecked()) {
            ui->allFilterCheckbox->setChecked(true);
        }
    }

    updateItems();
}
