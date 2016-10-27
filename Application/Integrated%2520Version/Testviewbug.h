#include <QtWidgets>
#include <QtTest/QtTest>


class Testviewbug : public viewbug
{
	Q_OBJECT
private slots:
	void SetUpTestAddBug()
	{
		qDebug("Now testing viewbug");
		
		
	}
		
	void testGui()
	{
		QLineEdit lineEdit;

		QTest::keyClicks(&lineEdit, "hello world");

		QCOMPARE(lineEdit.text(), QString("hello world"));
	}
	
	void cleanupTestCase()
    { 
		qDebug("Finish test viewbug"); 
	}

};