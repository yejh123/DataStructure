// =============== Program Description ===============
// �������ƣ� CH01_04.java                               
// ����Ŀ�ģ�������
// ===================================================

//������
abstract class autoMobile
{ 	//���󷽷�
	abstract public void setData();
	abstract public void showData();
}
//������
class BENZ_Serial extends autoMobile
{ 	//��Ա����
	private int carLength, engCC, maxSpeed;
	//���캯��
	public BENZ_Serial(String modelName)
	{
		System.out.println("BENZϵ�У�"+ modelName +"��������");
	}
  //���¶�����󷽷�
	public void setData()
	{
		carLength = 400;
		engCC = 3200;
		maxSpeed = 280;
	}
	public void showData()
	{
		System.out.println("�����ȣ�" + carLength);
		System.out.println("����CC����" + engCC);
		System.out.println("��߳��٣�" + maxSpeed);
	}
}
//��Ҫ��
public class CH01_04
{
  public static void main(String args[])
  {   //ʵ�ֳ��������
	  	autoMobile myCar = null;
	  //ʵ�����������
	  	BENZ_Serial SLK2000 = new BENZ_Serial("SLK2000");
	  //ʵ�ֶ�̬
		myCar = SLK2000;
		myCar.setData();
		myCar.showData();
  }
}

