#include "PassWord.h"

//�������ǿ����������Ҫ�����������ܸ��ĳ�ǿ����
int PassWord::Strong(string s){
	//ɨ���ַ�������ȡ���е����ͣ��������ظ����ַ�
	Scan(s);

	//����ȱʧ������
	int nMissType = 3 - hasType_uppercase - hasType_lowercase - hasType_digital;

	//��������6���ַ������Ȱ�ȱʧ�����Ͳ��룺
	//1�����������ͺ���δ��6�ַ���ֱ�����ʣ����ַ����ܹ����6 - n���ַ���
	//2�������뵽6���ַ��󣬻���ĳЩ����δ��ӣ������е������滻��ȱʧ�����ͣ��ܹ���Ӻ��滻��ȱʧ�����͡�nMissType���ַ���
	//3�������������1���ַ������ܴ��������ظ�3���ַ�����������Բ��ÿ����ظ���
	if (nLen < 6) return max(6 - nLen, nMissType);

	//��������6-20ʱ��ֻ��Ҫ�򵥵��滻�ַ����ɣ�������ظ����ַ������Ƚ��ظ��ַ��滻��ȱʧ�����ͣ��ϲ��������Ӷ������滻������
	//���ڶ����滻�������ܹ���Ҫ��������Ϊ��ȱʧ�����͡�nMissType�롰��Ҫ�滻���ظ��ַ���need_replace�����ֵ��
	if (nLen <= 20) return max(need_replace, nMissType);

	//���ȴ���20ʱ�������ɾ�����ַ�
	int nDelete = nLen - 20;

	//ɾ��ʱ������ɾ���ظ����ַ������������ȼ�����
	//һ���ظ��ַ�ģ3����Ϊ0ʱ����ɾ��1���ַ����������Ϊ2���ͣ��Ӷ�����һ���滻
	need_replace -= min(nDelete, remainder[0]);

	//�����ظ��ַ�ģ3����Ϊ1ʱ����ɾ��2���ַ����������Ϊ2���ͣ��Ӷ�����һ���滻
	if (nDelete - remainder[0] > 0)
		need_replace -= min((nDelete - remainder[0]) / 2, remainder[1]);

	//�����ظ��ַ�ģ3����Ϊ2ʱ����ͨ�ַ�һ����ͳһ����ÿɾ��3���ַ�������һ���滻
	if (nDelete - remainder[0] - 2 * remainder[1]> 0)
		need_replace -= (nDelete - remainder[0] - 2 * remainder[1]) / 3;

	//�ġ�ɾ����nDelete���ַ���ʣ���ַ�ͬ6-20���ַ�����
	return max(need_replace, nMissType) + nDelete;
}

void PassWord::clear(){
	hasType_uppercase = 0;
	hasType_lowercase = 0;
	hasType_digital = 0;
	need_replace = 0;
	remainder[0] = 0;
	remainder[1] = 0;
	remainder[2] = 0;
	nLen = 0;
}

void PassWord::Scan(string &s){
	clear();
	nLen = s.size();

	int index = 0;
	while (char c = s[index]){
		//����Ƿ������д��ĸ
		if (c >= 'A' && c <= 'Z')
			hasType_uppercase = 1;

		//����Ƿ����Сд��ĸ
		if (c >= 'a' && c <= 'z')
			hasType_lowercase = 1;

		//����Ƿ��������
		if (c >= '0' && c <= '9')
			hasType_digital = 1;

		//���������ظ��ַ�����
		int before_index = index;
		while (c == s[++index]);
		int repeat_len = index - before_index;
		//���������������ظ��ַ�����Ҫɾ�������滻
		if (repeat_len >= 3){
			//ÿ�����ַ���Ҫ����һ���滻
			need_replace += repeat_len / 3;

			//���ַ�����ʱ���˴���¼ģ3������������ɾ���ظ����ַ������Լ����滻����
			++remainder[repeat_len % 3];
		}
	}
}
