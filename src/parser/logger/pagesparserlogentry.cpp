// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.



namespace parser {

PagesParserLogEntry::PagesParserLogEntry(LOG_ENTRY_TYPE type, const QString& message, const QString& path, long lineNumber, const QString& line, PagesParser::SECTION section)
    : ParserLogEntry(type, message, path, lineNumber, line)
{
    QString resultMessage = QString("(PagesParser) ") + this->message;
    switch (section) {
    case PagesParser::SECTION::INFO:
        resultMessage += "\n Current section is INFO\n";
        break;
    case PagesParser::SECTION::ANSWERS:
        resultMessage += "\n Current section is ANSWERS\n";
        break;
    default:
        break;
    }
    this->message = resultMessage;
}
}
