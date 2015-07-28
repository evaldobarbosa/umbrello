/*
    Copyright 2011  Andi Fischer  <andi.fischer@hispeed.ch>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License or (at your option) version 3 or any later version
    accepted by the membership of KDE e.V. (or its successor approved
    by the membership of KDE e.V.), which shall act as a proxy 
    defined in Section 14 of version 3 of the license.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "TEST_pythonwriter.h"

// app includes
#include "classifier.h"
#include "pythonwriter.h"

const bool IS_NOT_IMPL = false;

//-----------------------------------------------------------------------------

class PythonWriterTest : public PythonWriter
{
public:
    QString findFileName(UMLPackage* concept, const QString &ext)
    {
       return PythonWriter::findFileName(concept,ext);
    }
};

void TEST_pythonwriter::test_language()
{
    PythonWriter* py = new PythonWriter();
    Uml::ProgrammingLanguage::Enum lang = py->language();
    QCOMPARE(lang, Uml::ProgrammingLanguage::Python);
}

void TEST_pythonwriter::test_writeClass()
{
    PythonWriterTest* py = new PythonWriterTest();
    UMLClassifier* c = new UMLClassifier("Customer", "12345678");
    UMLAttribute* attr;
    attr = c->createAttribute("name_");
    attr = c->createAttribute("address_");

    py->writeClass(c);
    // does the just created file exist?
    QFile file(temporaryPath() + py->findFileName(c, QLatin1String(".py")));
    QCOMPARE(file.exists(), true);
}

void TEST_pythonwriter::test_reservedKeywords()
{
    PythonWriter* py = new PythonWriter();
    QStringList list = py->reservedKeywords();
    QCOMPARE(list.empty(), false);
    QCOMPARE(list[0], QLatin1String("abs"));
    QCOMPARE(list[11], QLatin1String("class"));
    QCOMPARE(list.last(), QLatin1String("zip"));
}

QTEST_MAIN(TEST_pythonwriter)
