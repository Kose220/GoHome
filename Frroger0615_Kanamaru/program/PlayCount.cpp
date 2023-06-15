#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	// 1. �t�@�C�����J��
	// 1-1. fstream�N���X�̃R���X�g���N�^�Ɏw��
	fstream file("sample.txt", ios::in);
	// 1-2. fstream�N���X��open�����o�֐��𗘗p
	//fstream file;
	//file.open("sample.txt", ios::in);
	// 1-3. ifstream�N���X���g�p
	//ifstream file("sample.txt");

	// �G���[����: �t�@�C��������ɊJ�������ǂ����`�F�b�N
	if (!file.is_open())
	{
		cerr << "ERROR: cannot open file." << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// 2. �t�@�C������f�[�^���擾
	//int num;
	//file >> num;

	//float num2;
	//file >> num2;

	// �t�@�C���I�[�܂łP�s���ǂݍ���
	vector<string> file_lines;
	while (true)
	{
		string line;
		getline(file, line);
		if (file.eof())
			break;

		file_lines.emplace_back(line);
	}

	// 3. �t�@�C�������
	file.close();

	// 4. �擾�����f�[�^������
	for (const auto& line : file_lines)
	{
		cout << line << endl;
		// �擾�����f�[�^��string�^����int�^�֕ϊ�
		//int num = line;	// ��肭�����Ȃ�
		//try
		//{
		//	int num = stoi(line);	// stoi�֐�(int�^�ɂ�����string�^�̕ϐ�);
		//	cout << num << endl;
		//}
		//catch (const std::exception&)
		//{
		//}
	}

	system("pause");
	return EXIT_SUCCESS;
}