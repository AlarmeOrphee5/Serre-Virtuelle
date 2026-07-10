#include "Exporter/exportpdf.h"


#include <QPdfWriter>
#include <QPainter>
#include <QDateTime>
#include <QFont>
#include <QMessageBox>


#include "Exporter/exportpdf.h"


#include <QPdfWriter>
#include <QPainter>
#include <QDateTime>
#include <QFont>


bool PdfExporter::exporterSerre(
    const QVector<TableCultureData*>& tables,
    const QString& chemin
    )
{
    QPdfWriter writer(chemin);

    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(96);


    QPainter painter(&writer);

    if (!painter.isActive())
        return false;


    int y = 100;


    QFont titleFont;
    titleFont.setPointSize(22);
    titleFont.setBold(true);

    painter.setFont(titleFont);

    painter.drawText(
        100,
        y,
        "Serre Virtuelle"
        );


    y += 50;


    QFont subtitleFont;
    subtitleFont.setPointSize(14);

    painter.setFont(subtitleFont);

    painter.drawText(
        100,
        y,
        "Rapport des cultures"
        );


    y += 60;


    QFont normalFont;
    normalFont.setPointSize(11);

    painter.setFont(normalFont);


    painter.drawText(
        100,
        y,
        "Généré le : "
            + QDateTime::currentDateTime()
                  .toString("dd/MM/yyyy hh:mm")
        );


    y += 60;


    //--------------------------------------------------
    // Résumé
    //--------------------------------------------------

    int tablesActives = 0;
    int potsTotal = 0;
    int potsActifs = 0;


    for(const TableCultureData* table : tables)
    {
        if (!table)
            continue;


        if(table->estActive())
            tablesActives++;


        potsTotal += table->nombrePots();
        potsActifs += table->nombrePotsActifs();
    }


    painter.drawText(
        100,
        y,
        QString("Nombre de tables : %1")
            .arg(tables.size())
        );

    y += 25;


    painter.drawText(
        100,
        y,
        QString("Tables actives : %1")
            .arg(tablesActives)
        );


    y += 25;


    painter.drawText(
        100,
        y,
        QString("Pots utilisés : %1 / %2")
            .arg(potsActifs)
            .arg(potsTotal)
        );


    y += 60;



    //--------------------------------------------------
    // Tables
    //--------------------------------------------------

    QFont tableFont;
    tableFont.setPointSize(14);
    tableFont.setBold(true);

    for(const TableCultureData* table : tables)
    {
        if (!table)
            continue;


        // nouvelle page si nécessaire
        if(y > 1000)
        {
            writer.newPage();
            y = 100;
        }


        painter.setFont(tableFont);


        painter.drawText(
            100,
            y,
            table->name()
            );


        y += 30;


        painter.setFont(normalFont);


        painter.drawText(
            120,
            y,
            QString("Statut : %1")
                .arg(table->estActive()
                         ? "Active"
                         : "Inactive")
            );


        y += 25;


        painter.drawText(
            120,
            y,
            QString("Pots utilisés : %1 / %2")
                .arg(table->nombrePotsActifs())
                .arg(table->nombrePots())
            );


        y += 35;



        //--------------------------------------------------
        // Pots
        //--------------------------------------------------

        for(const PotData& pot : table->pots())
        {

            if(y > 1000)
            {
                writer.newPage();
                y = 100;
            }


            QString ligne =
                QString("Pot %1 | Etat : %2")
                    .arg(pot.numeroPot(),2,10,QChar('0'))
                    .arg(labelFromEtat(pot.etat()));


            painter.drawText(
                140,
                y,
                ligne
                );


            y += 20;


            if(!pot.nomPlante().isEmpty())
            {
                painter.drawText(
                    160,
                    y,
                    "Plante : " + pot.nomPlante()
                    );

                y += 20;
            }


            if(!pot.datePlantation().isEmpty())
            {
                painter.drawText(
                    160,
                    y,
                    "Planté le : "
                        + pot.datePlantation()
                    );

                y += 20;
            }


            y += 10;
        }


        y += 20;
    }


    painter.end();

    return true;
}


bool PdfExporter::exporterTable(
    const TableCultureData& table,
    const QString& chemin
    )
{
    QPdfWriter writer(chemin);

    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(96);


    QPainter painter(&writer);

    if (!painter.isActive())
        return false;


    int y = 100;


    //--------------------------------------------------
    // Titre
    //--------------------------------------------------

    QFont titleFont;
    titleFont.setPointSize(22);
    titleFont.setBold(true);

    painter.setFont(titleFont);

    painter.drawText(
        100,
        y,
        "Serre Virtuelle"
        );


    y += 50;


    QFont subtitleFont;
    subtitleFont.setPointSize(14);

    painter.setFont(subtitleFont);

    painter.drawText(
        100,
        y,
        "Rapport d'une table de culture"
        );


    y += 60;


    QFont normalFont;
    normalFont.setPointSize(11);

    painter.setFont(normalFont);


    painter.drawText(
        100,
        y,
        "Généré le : "
            + QDateTime::currentDateTime()
                  .toString("dd/MM/yyyy hh:mm")
        );


    y += 60;


    //--------------------------------------------------
    // Informations table
    //--------------------------------------------------

    QFont tableFont;
    tableFont.setPointSize(14);
    tableFont.setBold(true);

    painter.setFont(tableFont);

    painter.drawText(
        100,
        y,
        table.name()
        );


    y += 35;


    painter.setFont(normalFont);


    painter.drawText(
        120,
        y,
        QString("Statut : %1")
            .arg(table.estActive()
                     ? "Active"
                     : "Inactive")
        );


    y += 25;


    painter.drawText(
        120,
        y,
        QString("Pots utilisés : %1 / %2")
            .arg(table.nombrePotsActifs())
            .arg(table.nombrePots())
        );


    y += 50;



    //--------------------------------------------------
    // Pots
    //--------------------------------------------------

    QFont potFont;
    potFont.setPointSize(11);

    painter.setFont(potFont);


    for(const PotData& pot : table.pots())
    {

        if(y > 1000)
        {
            writer.newPage();
            y = 100;
        }


        QString ligne =
            QString("Pot %1 | Etat : %2")
                .arg(pot.numeroPot(),2,10,QChar('0'))
                .arg(labelFromEtat(pot.etat()));


        painter.drawText(
            140,
            y,
            ligne
            );


        y += 20;



        if(!pot.nomPlante().isEmpty())
        {
            painter.drawText(
                160,
                y,
                "Plante : " + pot.nomPlante()
                );

            y += 20;
        }



        if(!pot.datePlantation().isEmpty())
        {
            painter.drawText(
                160,
                y,
                "Planté le : " + pot.datePlantation()
                );

            y += 20;
        }


        y += 10;
    }


    painter.end();

    return true;
}


