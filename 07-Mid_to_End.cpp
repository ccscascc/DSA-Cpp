#include <iostream>
#include <string>
#include <stack>
using namespace std;
bool compare(char c1,char c2){//中缀表达式中的运算符优先级比较
	if((c1=='*'||c1=='/')&&(c2=='+'||c2=='-')){
		return true;
	}
	if(c2=='('){//若栈顶符号是"(" 返回true
		return true;
	}
	if(c1==')'){//若当前符号是")" 返回false
		return false;
	}
	return false;
}
string Mid_to_End(string str){//中缀表达式转后缀表达式（逆波兰表达式） 
	stack<char>st;
	string result;
	int n=str.size();
	for(int i=0;i<n;i++){//是数字，写入结果字符串中 
		if(str[i]>='0'&&str[i]<='9'){
			result.push_back(str[i]);
		}
		else // 处理运算符
		{
			if(st.empty()||str[i]=='('){//当前运算符是"(" 或运算符栈为空 将当前运算符入栈 
				st.push(str[i]);
			}
			else{
				//比较当前符号和栈顶符号的优先级
				while(!st.empty()){
				
					char ch=st.top();
					if(compare(str[i],ch)){//若优先级更高 入栈
						st.push(str[i]);
						break;
					}
					else{
						//若优先级更低，栈顶运算符出栈，并存入result中，当前运算符继续与栈顶元素比较 
						st.pop();
						if(ch=='('){//遇见右括号")"继续出栈，直到遇见左括号"(" 
							break;
						}
						if(ch!=')'&&ch!='('){
							result.push_back(ch);
						}
					}
				}
			} 
		} 
	}
	//for 循环结束后 若符号栈不为空，将运算符写入result中
	while(!st.empty()){
		if(st.top()!='('&&st.top()!=')')
		result.push_back(st.top());
		st.pop();
	} 
	return result;
}
int jisuan(string s){//逆波兰表达式计算
	stack<int>st;
	int n=s.size();
	for(int i=0;i<n;i++){
		if(s[i]>='0'&&s[i]<='9'){
			st.push(s[i]-'0');
		}
		else{
			int x=st.top();
			st.pop();
			int y=st.top();
			st.pop();
			if(s[i]=='+'){//根据栈后进先出的特性，先出栈的是右操作数，后出栈的是左操作数
				st.push(y+x);
			}
			else if(s[i]=='-'){
				st.push(y-x);
			}
			else if(s[i]=='*'){
				st.push(y*x);
			}
			else if(s[i]=='/'){
				st.push(y/x);
			}
		}
	}
	return st.top();
}

int main(){
	string str;
	str="(2+3)*2-1+3-1*1-1";
	cout<<Mid_to_End(str)<<endl;
	cout<<jisuan(Mid_to_End(str))<<endl;
	system("pause");
	return 0;
}












































