// =============== Program Description ===============
// �������ƣ� CH01_05.java                               
// ����Ŀ�ģ��ӿڲ���
// ===================================================

//�����ӿ�һ
interface autoMobile_setData
{ //��Ա����
  void setData();
}
//�����ӿڶ�
interface autoMobile_showData
{ 	//��Ա����
	void showData();
}
//�ӿ�ʵ����
class CH01_05 implements autoMobile_setData, autoMobile_showData
{ 	//��Ա����
	int carLength, engCC, maxSpeed;
	//���캯��
	public CH01_05(String modelName)
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
	//����������
	public static void main(String args[])
	{ 
		CH01_05 SLK2000 = new CH01_05("SLK2000");
		SLK2000.setData();
		SLK2000.showData();
	}
}
