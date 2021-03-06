#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

unsigned int isDigital(char ch)
{
	if (ch >= '0' && ch <= '9')
		return 1;
	else
		return 0;
}

int get_mix_num(int num1, int num2)
{
	int tmp = num2;
	while (tmp)
	{
		num1 *= 10;
		tmp /= 10;
	}
	return num1 + num2;
}

void doit(char **str_array, unsigned int num, unsigned int **out, unsigned int *out_num)
{
	/*遍历二维数组，取出每一个字符串*/
	vector<string> v_str;
	vector<int> num_list;
	vector<vector<int>> num_list_all;
	set<int> output_num;
	unsigned int str_count = 0;

	while (str_count < num)
	{
		cout << "get string: " << *str_array << endl;
		v_str.push_back(*str_array);
		str_array++;
		str_count++;
	}
	
	/*取出每一个字符串中的数字，并组成整数*/
	int num_tmp = 0;
	for (unsigned int i = 0; i < v_str.size(); i++)
	{
		const char *str = v_str[i].c_str();
		//cout << "analy str:  " << str << endl;
		int num_found = 0;
		int num_complete = 0;

		while (*str != '\0')
		{
			if (isDigital(*str))
			{
				//num_complete = 0;
				num_found = 1;
				num_tmp *= 10;
				num_tmp += (*str - '0');
			}
			else
			{
				if (num_found)
				{
					num_complete = 1;
					num_found = 0;
					num_list.push_back(num_tmp);
					num_tmp = 0;
				}

			}
			str++;
			//满足字符串末尾是数字,或者字符串没有数字的情况
			if ((num_found && *str == '\0')||(!num_found && !num_complete && *str == '\0'))
			{
				num_list.push_back(num_tmp);
			}
		}

		num_list_all.push_back(num_list);
		num_list.clear();
	}

	/*对每一个字符串中取出的整数进行排序,/*取最小的两个数进行拼接*/
	for (unsigned int i = 0; i<num_list_all.size(); i++)
	{
		sort(num_list_all[i].begin(), num_list_all[i].end());
		cout << "num: " << endl;
		for (unsigned int j = 0; j < num_list_all[i].size(); j++)
		{
			cout << num_list_all[i][j] << " ";
		}
		cout << endl;

		/*取最小的两个数进行拼接*/
		int mix_num = 0;
		if (num_list_all[i].size() >= 2)
		{
			mix_num = get_mix_num(num_list_all[i][0], num_list_all[i][1]);
		}
		else
		{
			mix_num = num_list_all[i][0];
		}

		/*将每一个字符串拼接出的整数进行去重*/
		cout << "mix num: " << mix_num << endl;
		output_num.insert(mix_num);
	}

	cout << "final output: ";
	for(set<int>::iterator it = output_num.begin(); it != output_num.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	//为输出指针分配内存
	//TODO:
}

int main()
{
	char *str_array[6] = {
	"hello128wor34ld",
	"nihao83a 03i  83i",
	"fji 829@##di",
	"fnsiu><klsj",
	"   797 jif)()78 jjj78 w78 jn1",
	"1222"
	};
	//char **str_array = 
	doit(str_array,6,NULL,NULL);
	return 0;
}

