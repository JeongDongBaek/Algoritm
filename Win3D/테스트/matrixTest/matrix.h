#pragma once
class vector3;

class matrix
{
public:
	matrix();
	matrix(int dimension); // ����� ����� ���Ѵ�. 4x4 ���
	~matrix();

private:
	class row // ��
	{
	private:
		vector<float>	m_vecData;

	public:
		row();
		~row();

		void Resize(int dimension); // ���� ����� ���Ѵ�.
		float& operator[](int index); // ���� []��° ����Ÿ�� ��ȯ�Ѵ�.
	};

	vector<row> m_vecData;

public:
	void Resize(int dimension); // ������ ũ�⸦ �ִ�ũ�⸦ �����Ѵ�. (reserver)�� ��������� ���������� 0.0f�� �ʱ�ȭ�Ѵ�.
	int Dimension(); // ���� ũ�⸦ ��ȯ�Ѵ�. 

	static matrix Identity(int dimension); // 

	row& operator[](int index); // ���� []��° ����Ÿ�� ��ȯ�Ѵ�.

	//arr.operator[](1);
	//arr[1][2];

	bool operator==(matrix& mat);
	bool operator!=(matrix& mat);
	matrix operator+(matrix& mat);
	matrix operator-(matrix& mat);
	matrix operator*(matrix& mat);
	matrix operator*(float f);
	matrix Transpose();

	matrix Inverse(OUT float& determinent);		// �����
	float Determinent(); // ���					// �Ǻ���
	matrix Adjoint();							// ������� // ���μ������ ��ġ�Ѱ� ( �밢�� �߽����� �¿츦 ������Ŵ)
	float getCofactor(int row, int col);			// ���μ���� ���ϱ�
	float getMinor(int row, int col);				// ����� ���ϱ� (�ش�Ǵ� ��� ���� ������ ������ ��

	void Print();
};

