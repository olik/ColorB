/*
 * Test cases for class CBManger
*/
#ifndef CBTESTMANAGER_H
#define CBTESTMANAGER_H

#include <QtCore>
#include <QTest>
#include "../ColorB/CBManager.h"
#include "../ColorB/CBAreaOutput.h"

class CBTestManager : public QObject
{
    Q_OBJECT

private slots:
    void SimpleCreate_Test()
    {
	CBArea * area = new CBArea;
	area->AddPixel(CBPixel(0,0));
	QCOMPARE(area->GetArea().GetCount(), 1);
	QCOMPARE(area->GetArea().GetAt(0), CBPixel(0,0));
	QCOMPARE(area->GetBorder().GetCount(), 1);
	QCOMPARE(area->GetBorder().GetAt(0), CBPixel(0,0));
	delete area;
    }
    void SmarterCreate_Test()
    {
	CBArea * area = new CBArea;
	for (int i = 0; i  < 4; i++)
	{
	    for (int j = 0; j  < 4; j++) area->AddPixel(CBPixel(i,j));
	}
	QCOMPARE(area->GetArea().GetCount(), 16);
	QCOMPARE(area->GetBorder().GetCount(), 16);

	area->UpdateBorderPixels();
	QCOMPARE(area->GetArea().GetCount(), 16);
	QCOMPARE(area->GetBorder().GetCount(), 12);

	QCOMPARE((area->GetArea().Find(CBPixel(1,1)) != -1), true);
	QCOMPARE((area->GetBorder().Find(CBPixel(1,1)) == -1), true);

	delete area;
    }
    void DominateFail_Test()
    {
	CBArea * area1 = new CBArea;
	area1->AddPixel(CBPixel(0,0));
	CBArea * area2 = new CBArea;
	area2->AddPixel(CBPixel(1,1));
	area1->AddDominateArea(area2);
	int dominateResult = area1->Dominate();
	QCOMPARE(dominateResult, 0);

	delete area1;
	delete area2;
    }
    void DominateSuccesful_Test()
    {
	CBArea * area1 = new CBArea;
	area1->AddPixel(CBPixel(0,0));
	CBArea * area2 = new CBArea;
	area2->AddPixel(CBPixel(0,1));
	area1->AddDominateArea(area2);
	int dominateResult = area1->Dominate();
	QCOMPARE(dominateResult, 1);

	QCOMPARE(area1->GetArea().GetCount(), 2);
	QCOMPARE(area1->GetBorder().GetCount(), 2);
	QCOMPARE(area2->GetArea().GetCount(), 0);
	QCOMPARE(area2->GetBorder().GetCount(), 0);

	delete area1;
	delete area2;
    }
    void Dominate_Test()
    {
	CBArea * area1 = new CBArea;
	for (int i = 0; i  < 3; i++)
	{
	    for (int j = 0; j  < 3; j++) area1->AddPixel(CBPixel(i,j));
	}
	area1->UpdateBorderPixels();

	CBArea * area2 = new CBArea;
	area2->AddPixel(CBPixel(1,3));
	area1->AddDominateArea(area2);

	QCOMPARE(area1->GetArea().GetCount(), 9);
	QCOMPARE(area1->GetBorder().GetCount(), 8);
	QCOMPARE(area2->GetArea().GetCount(), 1);
	QCOMPARE(area2->GetBorder().GetCount(), 1);

	int dominateResult = area1->Dominate();
	QCOMPARE(dominateResult, 1);

	QCOMPARE(area1->GetArea().GetCount(), 10);
	QCOMPARE(area1->GetBorder().GetCount(), 8);
	QCOMPARE(area2->GetArea().GetCount(), 0);
	QCOMPARE(area2->GetBorder().GetCount(), 0);

	delete area1;
	delete area2;
    }
    void ToString_Test()
    {
	CBArea * area = new CBArea;
	for (int i = 0; i  < 3; i++)
	{
	    for (int j = 0; j  < 3; j++) area->AddPixel(CBPixel(i,j));
	}
	area->UpdateBorderPixels();
	CBAreaOutput * areaOutput = (CBAreaOutput *) area;
	QCOMPARE(QString(areaOutput->ToString().c_str()), QString("Area(9) = [0,0] [0,1] [0,2] [1,0] [1,1] [1,2] [2,0] [2,1] [2,2]\r\nBorder(8) = [0,0] [0,1] [0,2] [1,0] [1,2] [2,0] [2,1] [2,2]\r\n"));
	delete areaOutput;
    }

    void FullDominate_Test()
    {
	CBArea * area1 = new CBArea;
	for (int i = 0; i  < 3; i++)
	{
	    for (int j = 0; j  < 3; j++) area1->AddPixel(CBPixel(i,j));
	}
	area1->UpdateBorderPixels();

	CBArea * area2 = new CBArea;
	for (int i = 3; i  < 6; i++)
	{
	    for (int j = 0; j  < 3; j++) area2->AddPixel(CBPixel(i,j));
	}
	area2->UpdateBorderPixels();
	area1->AddDominateArea(area2);

	QCOMPARE(area1->GetArea().GetCount(), 9);
	QCOMPARE(area1->GetBorder().GetCount(), 8);
	QCOMPARE(area2->GetArea().GetCount(), 9);
	QCOMPARE(area2->GetBorder().GetCount(), 8);

	QCOMPARE(area1->Dominate(), 1);
	QCOMPARE(area1->Dominate(), 1);
	QCOMPARE(area1->Dominate(), 1);
	QCOMPARE(area1->Dominate(), 1);
	QCOMPARE(area1->Dominate(), 1);
	QCOMPARE(area1->Dominate(), 1);
	QCOMPARE(area1->Dominate(), 1);
	QCOMPARE(area1->Dominate(), 1);
	QCOMPARE(area1->Dominate(), 1);
	QCOMPARE(area1->Dominate(), 0);

	QCOMPARE(area2->GetArea().GetCount(), 0);
	QCOMPARE(area2->GetBorder().GetCount(), 0);
	QCOMPARE(area1->GetArea().GetCount(), 18);
	QCOMPARE(area1->GetBorder().GetCount(), 14);

	delete area1;
	delete area2;
   }

};

#endif // CBTESTMANAGER_H
