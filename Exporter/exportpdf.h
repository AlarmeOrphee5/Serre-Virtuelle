#pragma once

#include "tableculturedata.h"

#include <QString>
#include <QVector>


class QPainter;
class QPdfWriter;


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


private:

    static void dessinerEntete(
        QPainter& painter,
        const QString& titre
        );


    static void dessinerCouverture(
        QPainter& painter,
        const QVector<TableCultureData*>& tables
        );


    static void dessinerTable(
        QPainter& painter,
        const TableCultureData& table
        );


    static void dessinerRepresentationTable(
        QPainter& painter,
        const TableCultureData& table,
        int& y
        );

    static void dessinerLegende(
        QPainter& painter,
        int& y
        );

    static void dessinerLegende(
        QPainter& painter,
        int x,
        int y
        );

};
