// =============== Program Description ===============
// �������ƣ� CH01_02.java                               
// ����Ŀ�ģ���̳�
// ===================================================
	
//����
class BMW_Serial
{ //��Ա����
  private int carLength, engCC, maxSpeed;
  public String modelName;
  //�෽��
  public void ShowData()
  {
	carLength = 423;
	engCC = 3000;
	maxSpeed = 250;
	System.out.println(modelName + "��������");
	System.out.println("�����ȣ�" + carLength);
	System.out.println("����CC����" + engCC);
	System.out.println("��߳��٣�" + maxSpeed);
  }
}
//������
public class CH01_02 extends BMW_Serial
{ //���캯��
  public CH01_02(String name)
  {
	modelName = name;
  }
  //����������
  public static void main(String args[])
  {
	//ʵ�ֶ���
	  CH01_02 BMW318= new CH01_02("BMW 318i");
	  BMW318.ShowData();
  }
 }