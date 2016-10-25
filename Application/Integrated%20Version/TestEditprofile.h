#include <QtWidgets>
#include <QtTest/QtTest>


class TestEditprofile : public Editprofile
{
	Q_OBJECT
private slots:
	void SetUpTestAddBug()
	{
		qDebug("Now testing Editprofile");
		
		
	}
		
	void testGui()
	{
		QLineEdit lineEdit;

		QTest::keyClicks(&lineEdit, "hello world");

		QCOMPARE(lineEdit.text(), QString("hello world"));
	}
	
	void cleanupTestCase()
    { 
		qDebug("Finish test Editprofile"); 
	}

};