import FgvBase;//导入自定义模块;
import std;//导入标准库模块

int main(void)
{
	using namespace FgvStringGroup;
	
	FgvString FgvStr = u8"你好,世界! 我爱这里!";//实例化字符串,写法就跟实例化C++标准的字符串类型或C标准的宽字符数组一样
	FgvStr.FgvStrSetConsoleToUTF8( );//设置控制台为UTF-8,并设置本地化为zh_CN.UTF-8 后将缓冲区清除并重置[只要设置一次,这个操作是全局的]
	FgvStr.FgvStrPutOut(ConPutFgvStrAct::NeedEndl);//输出字符串[并换行]

	FgvString FgvStr2 = u8"不换行 ==> ";//实例化字符串,写法就跟实例化C++标准的字符串类型或C标准的宽字符数组一样
	FgvStr2.FgvStrPutOut(ConPutFgvStrAct::NotEndl);//输出字符串[不换行]
	FgvStr.FgvStrPutOut(ConPutFgvStrAct::NeedEndl);//输出字符串[并换行]

	FgvString FgvStr3 = u8"被插入的字符 ==> ";
	FgvStr3.FgvStrIns(u8"我是在后面被插入的字符" , InsStrPosition::InLast);//在末尾插入字符串
	FgvStr3.FgvStrPutOut(ConPutFgvStrAct::NeedEndl);

	FgvString FgvStr4 = u8" <== 被插入的字符";
	FgvStr4.FgvStrIns(u8"我是在前面被插入的字符" , InsStrPosition::InFirst);//在首端插入字符串
	FgvStr4.FgvStrPutOut(ConPutFgvStrAct::NeedEndl);

	//FgvStrInsAndCopy方法 会产生一个返回值,因此 可以直接赋值给其他的FgvString类型的对象
	//使用被实例化过的FgvStr-在首端插入字符串-然后赋值给FgvStr5
	FgvString FgvStr5 = FgvStr.FgvStrInsAndCopy(u8"For-Super-Earths!!!" , InsStrPosition::InFirst);

	FgvStr5.FgvStrPutOut(ConPutFgvStrAct::NeedEndl);
	FgvStr5.FgvStrPutOutOther(u8"其他字符");//可以用于输出其他非自身持有的字符串

	FgvString FgvStr6 = FgvStr.FgvStrInsAndCopy(u8"AWA" , InsStrPosition::InFirst);//插入并拷贝[这是深拷贝]
	FgvStr6.FgvStrPutOut(ConPutFgvStrAct::NeedEndl);
	FgvStr = u8"重载";//FgvStr清空自身拥有的字符串并获得新字符串 重载
	FgvString FgvStr7 = FgvStr;
	FgvStr7.FgvStrPutOut(ConPutFgvStrAct::NeedEndl);
	FgvStr = FgvStr5;//FgvStr清空自身拥有的字符串并获得FgvStr5拥有的字符串
	FgvStr.FgvStrPutOut(ConPutFgvStrAct::NeedEndl);//输出字符串[并换行]
	FgvStr7 + FgvStr;//FgvStr7 = FgvStr7 + FgvStr的结果
	FgvStr7.FgvStrPutOut( );
	FgvStr7.FgvStrObjOwnToMove(FgvStr2).FgvStrPutOut_Obj(ConPutFgvStrAct::NeedEndl);
	//转移FgvStr2对象的资源所有权给FgvStr7然后输出,并销毁FgvStr2
	/*
	try//侦测异常
	{
		FgvStr2.FgvStrPutOut( );//需要侦测异常的代码
	}
	catch (const std::exception& e)//捕获异常
	{
		std::cerr << reinterpret_cast<const char *>(u8"异常! FgvStr2对象已被销毁!无法访问!") << e.what( ) << std::endl;//输出异常消息
		throw;//抛出异常 用于终止程序
	}*/
	FgvString FgvStr8 = u8"i like you";
	FgvStr8.FgvStrIns(u8" SMG for" , 6);
	FgvStr8.FgvStrPutOut(ConPutFgvStrAct::NeedEndl);

	FgvString FgvStr10 = u8"为了!";
	FgvStr10.FgvStrIns(u8"生化斯坦" , 6);
	FgvStr10.FgvStrPutOut(ConPutFgvStrAct::NeedEndl);

	FgvString FgvStr9 = u8"For-!";
	FgvStr9.FgvStrIns(u8"sad" , 4);
	FgvStr9.FgvStrPutOut(ConPutFgvStrAct::NeedEndl);


	return 0;
}