// =============== Program Description ===============
// �������ƣ� CH01_01.java                               
// ����Ŀ�ģ���������
// ===================================================

//������
public class CH01_01
{ //��Ա����
  private int carLength, engCC, maxSpeed;
  private String modelName;
  //��������
  public CH01_01(String name)
  {
	carLength = 423;
	engCC = 3000;
	maxSpeed = 250;
	modelName = name;
  }
  //�෽��
  public void ShowData()
  {
	System.out.println(modelName + "��������");
	System.out.println("�����ȣ�" + carLength);
	System.out.println("����CC����" + engCC);
	System.out.println("��߳��٣�" + maxSpeed);
  }
  public void SetSpeed(int setSpeed)
  {
System.out.println("\nʹ�ö�����");
maxSpeed = setSpeed;
System.out.println("�����趨Ϊ��" + setSpeed);
System.out.println("Ŀǰ��߳���Ϊ��" + maxSpeed);
  }
  //������
  public static void main(String args[])
  {
	//ʵ�ֶ���
	CH01_01 BMW318 = new CH01_01("BMW 318i");
	//�����෽��
	BMW318.ShowData();
	BMW318.SetSpeed(160);
  }
}
