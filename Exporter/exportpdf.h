#pragma once

#include "tableculturedata.h"

#include <QString>
#include <QVector>


class PdfExporter
{
public:

    static bool exporterSerre(
        const QVector<TableCultureData*>& tables,
        const QString& chemin
        );

    static bool exporterTable(
        const TableCultureData& table,
        const QString& chemin
        );

};
