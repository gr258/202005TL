#include "PassWord.h"

//检查密码强弱，返回需要经过几步才能更改成强密码
int PassWord::Strong(string s){
	//扫描字符串，获取已有的类型，和连续重复的字符
	Scan(s);

	//计算缺失的类型
	int nMissType = 3 - hasType_uppercase - hasType_lowercase - hasType_digital;

	//长度少于6个字符，优先按缺失的类型补齐：
	//1、若补齐类型后仍未满6字符，直接添加剩余的字符，总共添加6 - n个字符；
	//2、若补齐到6个字符后，还有某些类型未添加，将现有的类型替换成缺失的类型，总共添加和替换“缺失的类型”nMissType个字符；
	//3、由于至少添加1个字符，总能打破连续重复3个字符的情况，所以不用考虑重复。
	if (nLen < 6) return max(6 - nLen, nMissType);

	//长度满足6-20时，只需要简单的替换字符即可，如果有重复的字符，优先将重复字符替换成缺失的类型，合并操作，从而减少替换次数；
	//由于都是替换操作，总共需要操作步数为“缺失的类型”nMissType与“需要替换的重复字符”need_replace的最大值。
	if (nLen <= 20) return max(need_replace, nMissType);

	//长度大于20时，计算待删除的字符
	int nDelete = nLen - 20;

	//删除时，优先删除重复的字符，按以下优先级处理
	//一、重复字符模3余数为0时，可删除1个字符，变成余数为2类型，从而减少一次替换
	need_replace -= min(nDelete, remainder[0]);

	//二、重复字符模3余数为1时，可删除2个字符，变成余数为2类型，从而减少一次替换
	if (nDelete - remainder[0] > 0)
		need_replace -= min((nDelete - remainder[0]) / 2, remainder[1]);

	//三、重复字符模3余数为2时和普通字符一样，统一处理，每删除3个字符，减少一次替换
	if (nDelete - remainder[0] - 2 * remainder[1]> 0)
		need_replace -= (nDelete - remainder[0] - 2 * remainder[1]) / 3;

	//四、删除掉nDelete个字符后，剩余字符同6-20个字符处理
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
		//检查是否包含大写字母
		if (c >= 'A' && c <= 'Z')
			hasType_uppercase = 1;

		//检查是否包含小写字母
		if (c >= 'a' && c <= 'z')
			hasType_lowercase = 1;

		//检查是否包含数字
		if (c >= '0' && c <= '9')
			hasType_digital = 1;

		//计算连续重复字符长度
		int before_index = index;
		while (c == s[++index]);
		int repeat_len = index - before_index;
		//包含三个及以上重复字符，需要删除或者替换
		if (repeat_len >= 3){
			//每三个字符需要进行一次替换
			need_replace += repeat_len / 3;

			//当字符超长时，此处记录模3的余数，优先删除重复的字符，可以减少替换次数
			++remainder[repeat_len % 3];
		}
	}
}
