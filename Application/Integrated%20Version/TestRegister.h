#include <QtWidgets>
#include <QtTest/QtTest>


class TestRegister : public Register
{
	Q_OBJECT
private slots:
	void SetUpTestAddBug()
	{
		qDebug("Now testing Register");
		
		
	}
		
	void testGui()
	{
		QLineEdit lineEdit;

		QTest::keyClicks(&lineEdit, "hello world");

		QCOMPARE(lineEdit.text(), QString("hello world"));
	}
	
	void cleanupTestCase()
    { 
		qDebug("Finish test Register"); 
	}

};