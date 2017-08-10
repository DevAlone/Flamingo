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

void Parser::setLogger(std::shared_ptr<ParserLogger>& logger)
{
    this->logger = logger;
}

std::shared_ptr<ParserLogger> Parser::getLogger()
{
    return logger;
}

std::pair<QString, QString> getKeyValueFromString(const QString& str, bool* isOk, QChar delimiter)
{
    int indexOfDelimiter = str.indexOf(delimiter);
    if (indexOfDelimiter < 0) {
        *isOk = false;
        return std::pair<QString, QString>();
    }
    *isOk = true;
    return std::make_pair(
        str.left(indexOfDelimiter).simplified().toLower(),
        str.mid(indexOfDelimiter + 1).trimmed());
}
}
