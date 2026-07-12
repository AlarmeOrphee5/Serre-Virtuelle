#include "Exporter/exportpdf.h"

#include "couleurconversion.h"

#include <QPdfWriter>
#include <QPainter>
#include <QDateTime>
#include <QFont>
#include <QPen>


bool PdfExporter::exporterSerre(
    const QVector<TableCultureData*>& tables,
    const QString& chemin
    )
{
    QPdfWriter writer(chemin);

    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(96);


    QPainter painter(&writer);


    if(!painter.isActive())
        return false;



    dessinerCouverture(
        painter,
        tables
        );



    for(const TableCultureData* table : tables)
    {
        if(!table)
            continue;


        writer.newPage();


        dessinerTable(
            painter,
            *table
            );
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


    writer.setPageSize(
        QPageSize(QPageSize::A4)
        );


    writer.setResolution(96);



    QPainter painter(&writer);


    if(!painter.isActive())
        return false;



    //--------------------------------------------------
    // Page unique de la table
    //--------------------------------------------------

    dessinerTable(
        painter,
        table
        );



    painter.end();


    return true;
}



void PdfExporter::dessinerCouverture(
    QPainter& painter,
    const QVector<TableCultureData*>& tables
    )
{

    painter.save();


    QFont titre;
    titre.setPointSize(24);
    titre.setBold(true);


    painter.setFont(titre);


    painter.drawText(
        100,
        150,
        "Serre Virtuelle"
        );



    QFont sousTitre;
    sousTitre.setPointSize(15);


    painter.setFont(sousTitre);


    painter.drawText(
        100,
        210,
        "Rapport de suivi des cultures"
        );



    int tablesActives = 0;
    int potsActifs = 0;
    int potsTotal = 0;



    for(const TableCultureData* table : tables)
    {
        if(!table)
            continue;


        if(table->estActive())
            tablesActives++;


        potsActifs += table->nombrePotsActifs();

        potsTotal += table->nombrePots();
    }



    QFont normal;
    normal.setPointSize(11);


    painter.setFont(normal);



    int y = 330;


    painter.drawText(
        100,
        y,
        "Généré le : "
            +
            QDateTime::currentDateTime()
                .toString("dd/MM/yyyy hh:mm")
        );


    y += 60;


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


    painter.restore();
}

void PdfExporter::dessinerTable(
    QPainter& painter,
    const TableCultureData& table
    )
{

    painter.save();


    // Etat propre du painter
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);



    int y = 100;



    QFont titre;
    titre.setPointSize(22);
    titre.setBold(true);


    painter.setFont(titre);


    painter.drawText(
        100,
        y,
        table.name()
        );


    y += 50;



    QFont normal;
    normal.setPointSize(11);


    painter.setFont(normal);



    int potsActifs = 0;
    int potsVides = 0;
    int potsHS = 0;



    for(const PotData& pot : table.pots())
    {

        switch(pot.etat())
        {

        case EtatPot::HorsService:
            potsHS++;
            break;


        case EtatPot::Inactif:
            potsVides++;
            break;


        default:
            potsActifs++;
            break;

        }

    }



    painter.drawText(
        100,
        y,
        "Pots totaux : 24"
        );


    y += 25;


    painter.drawText(
        100,
        y,
        QString("Pots utilisés : %1")
            .arg(potsActifs)
        );


    y += 25;


    painter.drawText(
        100,
        y,
        QString("Pots vides : %1")
            .arg(potsVides)
        );


    y += 25;


    painter.drawText(
        100,
        y,
        QString("Pots HS : %1")
            .arg(potsHS)
        );


    y += 50;



    //--------------------------------------------------
    // Représentation + légende
    //--------------------------------------------------

    int yRepresentation = y;


    dessinerRepresentationTable(
        painter,
        table,
        yRepresentation
        );


    dessinerLegende(
        painter,
        430,
        y
        );



    y = yRepresentation + 40;



    //--------------------------------------------------
    // Liste des plantes
    //--------------------------------------------------

    painter.setFont(normal);


    painter.drawText(
        100,
        y,
        "Liste des plantes"
        );


    y += 25;



    for(const PotData& pot : table.pots())
    {

        if(pot.nomPlante().isEmpty())
            continue;


        painter.drawText(
            120,
            y,
            QString("Pot %1 : %2")
                .arg(
                    pot.numeroPot(),
                    2,
                    10,
                    QChar('0')
                    )
                .arg(
                    pot.nomPlante()
                    )
            );


        y += 20;


        if(!pot.datePlantation().isEmpty())
        {

            painter.drawText(
                150,
                y,
                "Planté le : "
                    + pot.datePlantation()
                );


            y += 20;
        }


        y += 5;

    }



    painter.restore();

}


void PdfExporter::dessinerRepresentationTable(
    QPainter& painter,
    const TableCultureData& table,
    int& y
    )
{

    int x = 100;



    for(const PotData& pot : table.pots())
    {

        QRect rectanglePot(
            x,
            y,
            35,
            35
            );



        QColor couleur(
            colorFromEtat(
                pot.etat()
                )
            );



        painter.save();



        //--------------------------------------------------
        // Style du pot
        //--------------------------------------------------

        QPen contour(
            Qt::black
            );


        contour.setWidth(2);



        // Cas du noir : contour gris visible
        if(couleur.name() == "#000000")
        {
            contour.setColor(
                Qt::gray
                );
        }



        painter.setPen(
            contour
            );


        painter.setBrush(
            couleur
            );



        painter.drawEllipse(
            rectanglePot
            );



        painter.restore();



        x += 50;



        // 4 pots par ligne
        if((x - 100) >= 200)
        {
            x = 100;
            y += 50;
        }

    }

    y += 20;
}


void PdfExporter::dessinerLegende(
    QPainter& painter,
    int x,
    int y
    )
{

    painter.save();



    QFont titre;
    titre.setPointSize(11);
    titre.setBold(true);


    painter.setFont(titre);


    painter.drawText(
        x,
        y,
        "Légende"
        );


    y += 30;



    QFont normal;
    normal.setPointSize(10);


    painter.setFont(normal);



    for(const EtatPot etat : tousLesEtats())
    {

        QColor couleur(
            colorFromEtat(etat)
            );



        painter.save();



        QPen contour(
            Qt::black
            );


        contour.setWidth(2);



        if(couleur.name() == "#000000")
        {
            contour.setColor(
                Qt::gray
                );
        }



        painter.setPen(
            contour
            );


        painter.setBrush(
            couleur
            );



        painter.drawEllipse(
            QRect(
                x,
                y - 12,
                18,
                18
                )
            );



        painter.restore();



        painter.drawText(
            x + 30,
            y,
            labelFromEtat(etat)
            );



        y += 25;

    }



    painter.restore();

}
