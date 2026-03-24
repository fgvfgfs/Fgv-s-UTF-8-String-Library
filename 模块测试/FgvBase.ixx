export module FgvBase;//定义模块
import std;//导入标准库模块,因为标准库模块只导入不导出,所以要在这里导入标准库模块,不然实现该模块的代码会报错

export namespace FgvStringGroup//显式导出命名空间
{
	enum ConPutFgvStrAct//控制台字符输出时行动/操作
	{
		NotEndl , NeedEndl //不需要换行,需要换行
	};
	enum InsStrPosition//控制插入字符操作
	{
		InLast , InFirst //在末尾(插入),在首端(插入)
	};
	class FgvString//定义FgvString类 用于处理UTF-8字符
	{
	public://定义访问修饰符为公共的
		FgvString( );//定义默认构造函数
		~FgvString( );//定义默认析构函数
		FgvString(const FgvString &copy);//定义拷贝构造函数
		FgvString(const char8_t *u8cp);//定义参数为const char8_t*时的构造函数重载
		void FgvStrPutOut(ConPutFgvStrAct fgvStr_PutFlag = NeedEndl);//定义类方法,用于输出自身拥有的UTF-8字符,同时给予控制是否换行选项
		void FgvStrPutOutOther(const char8_t *NputOurStr , ConPutFgvStrAct fgvStr_PutFlag = NeedEndl);//定义类方法,用于输出其他的UTF-8字符
		FgvString& FgvStrPutOut_Obj(ConPutFgvStrAct fgvStr_PutFlag = NeedEndl);//专用于链式调用的类成员方法,用于输出自身拥有的UTF-8字符,同时给予控制是否换行选项
		FgvString& FgvStrPutOutOther_Obj(const char8_t *NputOurStr , ConPutFgvStrAct fgvStr_PutFlag = NeedEndl);//专用于链式调用的类成员方法,用于输出其他的UTF-8字符
		void FgvStrSetConsoleToUTF8( );//定义类方法,用于设置控制台为UTF-8,设置本地化为zh_CN.UTF-8并清空重置缓冲区[该效果是全局的,只用使用一次]
		//其实C/C++应该叫做函数,但是咱C#写习惯了 所以就习惯叫成为 方法 了
		char8_t* FgvStrIns(const char8_t *u8cpIns , InsStrPosition fgvStr_InsFlag = InLast);//定义类方法,用于插入字符串 同时给予控制选项
		FgvString& FgvStrInsAndCopy(const char8_t *u8cpIns , InsStrPosition fgvStr_InsFlag = InLast);//插入并复制字符串对象[不会修改源字符串,这是深拷贝]
		void operator=(const char8_t *u8cp);//赋值运算符重载 适用于 FgvStr = "我是新字符串"; 的情况
		void operator+(const FgvString &fgvStr);//加法运算符重载 适用于 FgvStr + FgvStr2; 的情况
		void operator=(const FgvString &fgvStr);//赋值运算符重载 适用于 FgvStr = FgvStr2; 的情况
		FgvString& FgvStrObjOwnToMove(FgvString &NeedMovefgvStr);//定义类方法 用于转移对象所有权[注: 转移后源对象会被立即销毁,不能再进行访问]

		//TODO FgvStrIns定义还未实现
		char8_t* FgvStrIns(const char8_t *u8cpIns , size_t InsPosition);//定义类方法,用于插入字符串 限定在指定索引位置插入
	private://定义访问修饰符为私有的
		ConPutFgvStrAct FgvStr_PutFlag = NotEndl;//默认为不需要换行
		size_t DefLength;//定义默认长度,未初始化 确切值在运行时才能确定 用于动态内存分配
		char8_t *FgvStrValue;//动态UTF-8字符数组分配,长度是在运行时确定的,本质上是个指向动态UTF-8字符数组的UTF-8字符指针
		size_t InsStrLength;//定义需要插入的字符串的默认长度,未初始化 确切值在运行时才能确定 用于动态内存分配
		char8_t *InsFgvStrValue;//动态UTF-8字符数组分配,用于初始化并指向需要插入的字符串
		size_t FinalStrLength;//定义自身持有的字符串 + 需要插入的字符串的默认长度,未初始化 确切值在运行时才能确定 用于动态内存分配
		char8_t *FinalFgvStrValue;//动态UTF-8字符数组分配,用于初始化并指向(自身持有的字符串 + 需要插入的字符串)
		size_t TempStrLength;//定义临时储存的字符串长度
		char8_t *TempStrValue;//动态UTF-8字符数组分配,用于初始化并指向(自身持有的字符串 + 需要插入的字符串)[专用于索引插入]
		size_t TempTwoStrLength;//定义临时储存的字符串长度
		char8_t *TempTwoStrValue;//动态UTF-8字符数组分配,用于初始化并指向(自身持有的字符串 + 需要插入的字符串)[专用于索引插入]
		InsStrPosition FgvStr_InsFlag = InLast;//默认为在末尾插入
		size_t FgvStr_InsPositionFlag = 0;//默认索引位置
		void FgvStrPutOut_GeneralFunc(ConPutFgvStrAct fgvStr_PutFlag = NeedEndl);//私有方法 定义通用输出自身持有字符串的操作
		void FgvStrPutOut_OtherGeneralFunc(const char8_t *NputOurStr , ConPutFgvStrAct fgvStr_PutFlag = NeedEndl);//私有方法 定义通用输出其他非自身持有字符串的操作
		void FgvStrInsGeneralFunc(const char8_t *u8cpIns , InsStrPosition fgvStr_InsFlag = InLast);//私有方法 定义通用字符串操作函数精简代码并提升复用性
		bool isValid; //表示该对象是否有效/存在
		void checkValid( ) const;//检查该对象是否有效/存在
	};
}