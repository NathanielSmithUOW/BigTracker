#include <QtWidgets>
#include <QtTest/QtTest>


class Testlogin : public login
{
	Q_OBJECT
private slots:
	void SetUpTestAddBug()
	{
		qDebug("Now testing login");
		
		
	}
	
	void testGui()
	{
		QLineEdit lineEdit;

		QTest::keyClicks(&lineEdit, "hello world");

		QCOMPARE(lineEdit.text(), QString("hello world"));
	}
	
	void cleanupTestCase()
    { 
		qDebug("Finish test login"); 
	}

};