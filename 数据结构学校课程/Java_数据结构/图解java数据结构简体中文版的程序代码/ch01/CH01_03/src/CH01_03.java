// =============== Program Description ===============
// �������ƣ� CH01_03.java                               
// ����Ŀ�ģ������̬
// ===================================================

//����
class myComputer
{ 	//�෽��
	public void Run(){};
}
//������һ
class myScanner extends myComputer
{ 	//��Ա����
	private String paperScan;
	//���캯��
	public myScanner(String inData){this.paperScan = new String(inData);}
	//���¶����෽��
	public void Run(){System.out.println("ʹ��ɨ����ɨ��" + paperScan + "���");}
}
//�������
class myPrinter extends myComputer
{ 	//��Ա����
	private String paperPrint;
	//���캯��
	public myPrinter(String inData){this.paperPrint = new String(inData);}
	//���¶����෽��
	public void Run(){System.out.println("ʹ�ô�ӡ����ӡ" + paperPrint + "���");}
}
//��Ҫ��
public class CH01_03
{ 	//��Ա����
	private String inputData;
	//���캯��
	public CH01_03()
	{
		System.out.println("�û���Ҫ��ɨ���ļ�A!!�ٽ��ļ�A��ӡ!!");
		System.out.println("��������Ϊ��");
		inputData = "�ļ�A";
	}    
	public static void main(String args[])
	{ 	//ʵ�ֶ���
		CH01_03 computerUser = new CH01_03();
		myComputer MyComputer;
		myScanner MyScanner = new myScanner("����A");
		myPrinter MyPrinter = new myPrinter("����A");
		System.out.println("�����󡰼������ת��ɶ���ɨ���ǡ�ִ��Run()����!!");
		//ʵ�ֶ�̬
		MyComputer = MyScanner;
		MyComputer.Run();   
		System.out.println("�����󡰼������ת��ɶ��󡰴�ӡ����ִ��Run()����!!");
		//ʵ�ֶ�̬
		MyComputer = MyPrinter;
		MyComputer.Run();
	}
}
