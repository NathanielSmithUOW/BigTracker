#include <QtWidgets>
#include <QtTest/QtTest>


class TestAddBug : public AddBug
{
	Q_OBJECT
private slots:
	void SetUpTestAddBug()
	{
		qDebug("Now testing AddBug");
		
		
	}
	
	void TestAdd()
	{
		//todo
		
	}
	
	void testGui()
	{
		QLineEdit lineEdit;

		QTest::keyClicks(&lineEdit, "hello world");

		QCOMPARE(lineEdit.text(), QString("hello world"));
	}
	
	void cleanupTestCase()
    { 
		qDebug("Finish test AddBug"); 
	}

};