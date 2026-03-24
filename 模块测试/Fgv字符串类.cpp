module FgvBase;//实现模块

using namespace FgvStringGroup;

#pragma region FgvString类型对象的构造函数和高危险性操作
//默认构造函数行为
FgvString::FgvString( )
{
    //分配一个UTF-8空字符
    FgvStrValue = new char8_t[1];
    FgvStr_PutFlag = NotEndl;
    FgvStrValue[0] = u8'\0';
    isValid = true;
}

//默认析构函数行为
FgvString::~FgvString( )
{
    if (FgvStrValue)//检测UTF-8字符指针是否存在
    {
        delete[ ] FgvStrValue;//存在则清除UTF-8字符指针指向的数据
        FgvStrValue = nullptr;//销毁UTF-8字符指针
    }


    if (InsFgvStrValue)//检测UTF-8字符指针是否存在
    {
        delete[ ] InsFgvStrValue;//存在则清除UTF-8字符指针指向的数据
        InsFgvStrValue = nullptr;
    }

    if (FinalFgvStrValue)//检测UTF-8字符指针是否存在
    {
        delete[ ] FinalFgvStrValue;//存在则清除UTF-8字符指针指向的数据
        FinalFgvStrValue = nullptr;
    }
    DefLength = 0;
    isValid = false;
}

//拷贝构造函数
FgvString::FgvString(const FgvString &copy)
{
    this->DefLength = 0;//设置默认值
    while (copy.FgvStrValue[this->DefLength] != u8'\0')//检测UTF-8字符指针指向的数据是否为UTF-8空字符,如果不是则默认长度自增
        ++this->DefLength;
    this->FgvStrValue = new char8_t[this->DefLength + 1];//动态分配UTF-8字符数组,长度+1[因为也得把空字符包含进去 不然会阻塞缓冲区]
    for (size_t i = 0; i <= this->DefLength; ++i)//将UTF-8字符指针指向的数据全部复制到UTF-8字符数组里(包括空字符\0[也叫终止符])
    {
        this->FgvStrValue[i] = copy.FgvStrValue[i];
    }
    this->FgvStrValue[DefLength] = u8'\0';
    isValid = true;
}

//含有const char8_t*类型参数时执行的构造函数
FgvString::FgvString(const char8_t *u8cp)
{
    if (!u8cp)//检测传输进来的是否为空指针 如果是 则新建空UTF-8字符数组
    {
        DefLength = 0;//设置默认值
        FgvStrValue = new char8_t[1];//动态分配UTF-8字符数组
        FgvStrValue[0] = u8'\0';//分配一个UTF-8空字符
        return;
    }
    DefLength = 0;//设置默认值
    while (u8cp[DefLength] != u8'\0')//检测UTF-8字符指针指向的数据是否为UTF-8空字符,如果不是则默认长度自增
    {
        ++DefLength;
    }
    FgvStrValue = new char8_t[DefLength + 1];//动态分配UTF-8字符数组,长度+1[因为也得把空字符包含进去 不然会阻塞缓冲区]
    for (size_t i = 0; i <= DefLength; ++i)//将UTF-8字符指针指向的数据全部复制到UTF-8字符数组里(包括空字符\0[也叫终止符])
    {
        FgvStrValue[i] = u8cp[i];
    }
    FgvStrValue[DefLength] = u8'\0';
    isValid = true;
}

//定义类方法 用于转移对象所有权[注: 转移后源对象会被立即销毁,不能再进行访问]
FgvString& FgvString::FgvStrObjOwnToMove(FgvString &NeedMovefgvStr)
{
    if (this != &NeedMovefgvStr)
    {
        delete[ ] this->FgvStrValue; //释放当前对象资源,清除自身对象的持有的字符串
        // 转移资源
        this->FgvStrValue = NeedMovefgvStr.FgvStrValue;//接管传入的对象的字符串
        this->DefLength = NeedMovefgvStr.DefLength;//接管传入的对象的字符串长度

        // 将源对象置于有效但为空的状态
        NeedMovefgvStr.FgvStrValue = nullptr;
        NeedMovefgvStr.DefLength = 0;
        NeedMovefgvStr.isValid = false;
    }
    return *this;//返回自身
}

//检测对象是否存在
void FgvString::checkValid( ) const
{
    if (!isValid)//如果不存在则抛出异常
    {
        throw std::exception( );
    }
}
#pragma endregion

/*|||||||||||||||||||||||||||||||||||分割线||||||||||||||||||||||||||||||||||||||||*/

#pragma region FgvStrPutOut方法及其重载版本
//输出自身持有的UTF-8字符方法
void FgvString::FgvStrPutOut(ConPutFgvStrAct fgvStr_PutFlag)
{
    checkValid( );
    FgvStrPutOut_GeneralFunc(fgvStr_PutFlag);//调用私有方法 该方法实现通用输出自身持有字符串的操作
}

//专用于链式调用的类成员方法,用于输出自身拥有的UTF-8字符,同时给予控制是否换行选项
FgvString& FgvString::FgvStrPutOut_Obj(ConPutFgvStrAct fgvStr_PutFlag)
{
    checkValid( );
    FgvStrPutOut_GeneralFunc(fgvStr_PutFlag);
    return *this;
}
#pragma endregion

/*|||||||||||||||||||||||||||||||||||分割线||||||||||||||||||||||||||||||||||||||||*/

#pragma region FgvStrPutOutOther方法及其重载版本
//输出其他非自身持有的UTF-8字符串的方法
void FgvString::FgvStrPutOutOther(const char8_t *NputOurStr , ConPutFgvStrAct fgvStrPut_Flag)
{
    checkValid( );
    FgvStrPutOut_OtherGeneralFunc(NputOurStr , fgvStrPut_Flag);//调用私有方法 该方法实现通用输出其他非自身持有字符串的操作
}

//专用于链式调用的类成员方法,用于输出其他的UTF-8字符
FgvString& FgvString::FgvStrPutOutOther_Obj(const char8_t *NputOurStr , ConPutFgvStrAct fgvStr_PutFlag)
{
    checkValid( );
    FgvStrPutOut_OtherGeneralFunc(NputOurStr , fgvStr_PutFlag);
    return *this;
}
#pragma endregion

/*|||||||||||||||||||||||||||||||||||分割线||||||||||||||||||||||||||||||||||||||||*/

#pragma region FgvString类型对象的私有通用方法
//私有方法 定义通用输出自身持有字符串的操作
void FgvString::FgvStrPutOut_GeneralFunc(ConPutFgvStrAct fgvStr_PutFlag)
{
    FgvStr_PutFlag = fgvStr_PutFlag;
    std::cout << reinterpret_cast<const char *>(FgvStrValue);//由于C++没有提供处理UTF-8字符的标准库,所以将UTF-8字符转换为char字符
    if (FgvStr_PutFlag == NeedEndl)//检测枚举类型 如果为NeedEndl则进行换行操作
        std::cout << '\n';
}

//私有方法 定义通用输出其他非自身持有字符串的操作
void FgvString::FgvStrPutOut_OtherGeneralFunc(const char8_t *NputOurStr , ConPutFgvStrAct fgvStr_PutFlag)
{
    FgvStr_PutFlag = fgvStr_PutFlag;
    std::cout << reinterpret_cast<const char *>(NputOurStr);//由于C++没有提供处理UTF-8字符的标准库,所以将UTF-8字符转换为char字符
    if (FgvStr_PutFlag == NeedEndl)//检测枚举类型 如果为NeedEndl则进行换行操作
        std::cout << '\n';
}

//私有方法 定义通用字符串操作函数精简代码并提升复用性
void FgvString::FgvStrInsGeneralFunc(const char8_t *u8cpIns , InsStrPosition fgvStr_InsFlag)
{
    FgvStr_InsFlag = fgvStr_InsFlag;
    if (!u8cpIns)//检测传输进来的是否为空指针 如果是 则新建空UTF-8字符数组
    {
        InsStrLength = 0;//设置默认值
        InsFgvStrValue = new char8_t[1];//动态分配UTF-8字符数组
        InsFgvStrValue[0] = u8'\0';//分配一个UTF-8空字符
        return;
    }
    InsStrLength = 0;//设置默认值
    while (u8cpIns[InsStrLength] != u8'\0')//检测UTF-8字符指针指向的数据是否为UTF-8空字符,如果不是则默认长度自增
    {
        ++InsStrLength;
    }
    InsFgvStrValue = new char8_t[InsStrLength + 1];//动态分配UTF-8字符数组,长度+1[因为也得把空字符包含进去 不然会阻塞缓冲区]
    for (size_t i = 0; i <= InsStrLength; ++i)//将UTF-8字符指针指向的数据全部复制到UTF-8字符数组里(包括空字符\0[也叫终止符])
    {
        InsFgvStrValue[i] = u8cpIns[i];//将传入的字符串逐序赋值给InsFgvStrValue
    }

    FinalStrLength = DefLength + InsStrLength;//总长度 = 默认长度[原自身持有的] + 需要插入的字符串的长度; 注意这两的长度都不计入终止符 也就是空字符\0
    FinalFgvStrValue = new char8_t[FinalStrLength + 1];//动态分配内存,总长度+1是为了包含终止符

    if (FgvStr_InsFlag == InLast)//如果是 声明在末尾插入
    {
        for (size_t i = 0; i < DefLength; ++i)//DefLength - 1是因为DefLength也会自带一个空字符 所以需要减去它
        {
            FinalFgvStrValue[i] = FgvStrValue[i];
            //将FgvStrValue里的字符串逐序赋值给FinalFgvStrValue
        }

        for (size_t i = 0; i < InsStrLength; ++i)
        {
            FinalFgvStrValue[i + DefLength] = InsFgvStrValue[i];
            //将InsFgvStrValue里的字符串逐序赋值给FgvStrValue
            //i + 默认长度 是因为InsStrLength是独立的数据 如果不这样做 ,那么会将我们之前赋值的字符给覆盖掉 而不是在其后继续插入
        }
    }
    else if (FgvStr_InsFlag == InFirst)//如果是 声明在首端插入
    {
        for (size_t i = 0; i < InsStrLength; ++i)//InsStrLength - 1是因为DefLength也会自带一个空字符 所以需要减去它
        {
            FinalFgvStrValue[i] = InsFgvStrValue[i];
            //将InsFgvStrValue里的字符串逐序赋值给FgvStrValue,但是 先将InsFgvStrValue里的字符赋值给FinalFgvStrValue
        }

        for (size_t i = 0; i < DefLength; ++i)
        {
            FinalFgvStrValue[i + InsStrLength] = FgvStrValue[i];
            //将FgvStrValue里的字符串逐序赋值给FinalFgvStrValue
        }
    }
    else//如果 没有声明任何情况 则执行默认操作 在末尾插入字符串
    {
        for (size_t i = 0; i < DefLength; ++i)//DefLength - 1是因为DefLength也会自带一个空字符 所以需要减去它
        {
            FinalFgvStrValue[i] = FgvStrValue[i];
            //将FgvStrValue里的字符串逐序赋值给FinalFgvStrValue
        }

        for (size_t i = 0; i < InsStrLength; ++i)
        {
            FinalFgvStrValue[i + DefLength] = InsFgvStrValue[i];
            //将InsFgvStrValue里的字符串逐序赋值给FgvStrValue
            //i + 默认长度 是因为InsStrLength是独立的数据 如果不这样做 ,那么会将我们之前赋值的字符给覆盖掉 而不是在其后继续插入
        }
    }
    if (FgvStrValue)//检测UTF-8字符指针是否存在
    {
        delete[ ] FgvStrValue;//存在则清除UTF-8字符指针指向的数据
        FgvStrValue = nullptr;//设置FgvStrValue为空指针
    }
    FgvStrValue = new char8_t[FinalStrLength + 1];//动态分配内存
    //温馨提示 如果这边 不 + 1但是程序仍然会在看起来正常运行 但是 你会发现程序执行完所有语句后 不会自行终止并退出
    /*这就是C++的坑 出现这种看起来正常运行的情况 纯属狗运 要么恰好分配到了空闲内存[不重要的 , 无数据的]
      要么是调试器开启了内存保护模式给你修正了,要么是现代堆管理器太宽容了 出于各种目的给你多分配了内存
      [比如说 你申请了10字节内存 堆管理器给你分配了16字节 因为编译器会出于性能需求执行8字节或16字节对齐
      [在64位系统上,大多数编译器默认为16字节对齐] 堆管理器为了对齐或保护内存 给你分配了16字节内存],虽然目前能正常执行,但是迟早要爆炸  */
    DefLength = 0;
    for (size_t i = 0; i <= FinalStrLength; ++i)
    {
        FgvStrValue[i] = FinalFgvStrValue[i];
        ++DefLength;
        //将FinalFgvStrValue里的字符串逐序赋值给FgvStrValue,因为FinalFgvStrValue严格意义上只是个临时的,在该方法结束前会被销毁
    }

    FgvStrValue[FinalStrLength] = u8'\0';

    if (FinalFgvStrValue)//检测UTF-8字符指针是否存在
    {
        delete[ ] FinalFgvStrValue;//存在则清除UTF-8字符指针指向的数据
        FinalFgvStrValue = nullptr;//设置FgvStrValue为空指针
    }
}
#pragma endregion

/*|||||||||||||||||||||||||||||||||||分割线||||||||||||||||||||||||||||||||||||||||*/

#pragma region FgvString类型对象的特殊全局操作
//实现类方法,用于设置控制台为UTF-8,设置本地化为zh_CN.UTF-8并清空重置缓冲区[该效果是全局的,只用使用一次]
void FgvString::FgvStrSetConsoleToUTF8( )
{
    //实现类方法,用于设置控制台为UTF-8,设置本地化为zh_CN.UTF-8并清空重置缓冲区[该效果是全局的,只用使用一次]
    system("chcp 65001 > nul");//设置控制台为UTF-8	
    std::locale::global(std::locale("zh_CN.UTF-8"));//设置本地化	
    std::cout.clear( );//重置流的错误状态(恢复错误后的流,例如一个函数期望输入数字而用户输入了字符 这个时候流就会有错误状态)
    std::cout.flush( );//强制刷新缓冲区
    //清除缓冲区并同步
}
#pragma endregion

#pragma region FgvStrIns方法及其重载版本
//定义类方法,用于插入字符串 同时给予控制选项
char8_t* FgvString::FgvStrIns(const char8_t *u8cpIns , InsStrPosition fgvStr_InsFlag)//实现类方法,用于插入字符串 同时给予控制选项
{
    checkValid( );
    FgvStrInsGeneralFunc(u8cpIns , fgvStr_InsFlag);
    return FgvStrValue;
}

//插入并复制字符串对象[不会修改源字符串,这是深拷贝]
FgvString& FgvString::FgvStrInsAndCopy(const char8_t *u8cpIns , InsStrPosition fgvStr_InsFlag)//插入并复制
{
    checkValid( );
    FgvStrInsGeneralFunc(u8cpIns , fgvStr_InsFlag);
    return *this;
}

//TODO FgvStrIns实现还未实现;定义类方法,用于插入字符串 限定在指定索引位置插入
char8_t* FgvString::FgvStrIns(const char8_t *u8cpIns , size_t InsPosition)//实现类方法,用于插入字符串 限定在指定索引位置插入
{
    checkValid( );
    FgvStr_InsPositionFlag = InsPosition;
    if (!u8cpIns)//检测传输进来的是否为空指针 如果是 则新建空UTF-8字符数组
    {
        InsStrLength = 0;//设置默认值
        InsFgvStrValue = new char8_t[1];//动态分配UTF-8字符数组
        InsFgvStrValue[0] = u8'\0';//分配一个UTF-8空字符
        return 0;
    }
    InsStrLength = 0;//设置默认值
    while (u8cpIns[InsStrLength] != u8'\0')//检测UTF-8字符指针指向的数据是否为UTF-8空字符,如果不是则默认长度自增
    {
        ++InsStrLength;
    }
    InsFgvStrValue = new char8_t[InsStrLength + 1];//动态分配UTF-8字符数组,长度+1[因为也得把空字符包含进去 不然会阻塞缓冲区]
    for (size_t i = 0; i <= InsStrLength; ++i)//将UTF-8字符指针指向的数据全部复制到UTF-8字符数组里(包括空字符\0[也叫终止符])
    {
        InsFgvStrValue[i] = u8cpIns[i];//将传入的字符串逐序赋值给InsFgvStrValue
    }

    if (FgvStr_InsPositionFlag != 0 && (FgvStrValue[FgvStr_InsPositionFlag] != u8'\0' && FgvStr_InsPositionFlag <= DefLength))
    {//FgvStr_InsPositionFlag不能为0,FgvStrValue[FgvStr_InsPositionFlag]不能为空字符且FgvStr_InsPositionFlag 必须 <= DefLength
        TempStrValue = new char8_t[FgvStr_InsPositionFlag + 1];
        int ls = 0;
        TempStrLength = 0;
        for (size_t i = 0; i <= FgvStr_InsPositionFlag - 1; ++i)
        {
            TempStrValue[i] = FgvStrValue[i];
            ++TempStrLength;
        }
        TempStrValue[TempStrLength] = u8'\0';
        size_t charsToCopy = DefLength - TempStrLength;
        TempTwoStrValue = new char8_t[charsToCopy + 1];
        TempTwoStrLength = 0;

        int b = 0;
        for (size_t i = TempStrLength; i <= DefLength - 1; ++i)
        {
            TempTwoStrValue[b] = FgvStrValue[i];
            ++TempTwoStrLength;
            ++b;
        }
        TempTwoStrValue[TempTwoStrLength] = u8'\0';
        FinalStrLength = TempStrLength + InsStrLength + TempTwoStrLength;
        FinalFgvStrValue = new char8_t[FinalStrLength + 1];//动态分配内存,总长度+1是为了包含终止符

        for (size_t j = 0; j <= TempStrLength && TempStrValue[j] != '\0'; ++j)
        {
            FinalFgvStrValue[ls] = TempStrValue[j];
            ++ls;
        }
        for (size_t j = 0; j <= InsStrLength && InsFgvStrValue[j] != '\0'; ++j)
        {
            FinalFgvStrValue[ls] = InsFgvStrValue[j];
            ++ls;
        }
        for (size_t j = 0; j <= TempTwoStrLength && TempTwoStrValue[j] != '\0'; ++j)
        {
            FinalFgvStrValue[ls] = TempTwoStrValue[j];
            ++ls;
        }
        FinalFgvStrValue[FinalStrLength] = u8'\0';

        if (FgvStrValue)//检测UTF-8字符指针是否存在
        {
            delete[ ] FgvStrValue;//存在则清除UTF-8字符指针指向的数据
            FgvStrValue = nullptr;//设置FgvStrValue为空指针
        }
        FgvStrValue = new char8_t[FinalStrLength + 1];//动态分配内存
        for (size_t i = 0; i <= FinalStrLength; ++i)
        {
            FgvStrValue[i] = FinalFgvStrValue[i];
            ++DefLength;
            //将FinalFgvStrValue里的字符串逐序赋值给FgvStrValue,因为FinalFgvStrValue严格意义上只是个临时的,在该方法结束前会被销毁
        }
        FgvStrValue[FinalStrLength] = u8'\0';
        if (FinalFgvStrValue)//检测UTF-8字符指针是否存在
        {
            delete[ ] FinalFgvStrValue;//存在则清除UTF-8字符指针指向的数据
            FinalFgvStrValue = nullptr;//设置FgvStrValue为空指针
        }
    }
    else if (FgvStr_InsPositionFlag == 0)
    {
        FgvStrInsGeneralFunc(u8cpIns , FgvStr_InsFlag = InFirst);
    }
    else if (FgvStr_InsPositionFlag == DefLength)
    {
        FgvStrInsGeneralFunc(u8cpIns , FgvStr_InsFlag = InLast);
    }
    else
    {
        FgvStrInsGeneralFunc(u8cpIns , FgvStr_InsFlag = InLast);
    }
    return FgvStrValue;
}
#pragma endregion

/*|||||||||||||||||||||||||||||||||||分割线||||||||||||||||||||||||||||||||||||||||*/

#pragma region 适用于FgvString类型对象的运算符重载
//赋值运算符重载 适用于 FgvStr = "我是新字符串"; 的情况
void FgvString::operator=(const char8_t *u8cp)
{
    checkValid( );
    if (!u8cp)//检测传输进来的是否为空指针 如果是 则新建空UTF-8字符数组
    {
        this->DefLength = 0;//设置默认值
        this->FgvStrValue = new char8_t[1];//动态分配UTF-8字符数组
        this->FgvStrValue[0] = u8'\0';//分配一个UTF-8空字符
        return;
    }
    if (FgvStrValue)//检测UTF-8字符指针是否存在
    {
        delete[ ] this->FgvStrValue;//存在则清除UTF-8字符指针指向的数据
        this->FgvStrValue = nullptr;//设置FgvStrValue为空指针
        this->DefLength = 0;//设置默认值
    }
    this->DefLength = 0;//设置默认值
    while (u8cp[this->DefLength] != u8'\0')//检测UTF-8字符指针指向的数据是否为UTF-8空字符,如果不是则默认长度自增
    {
        ++this->DefLength;
    }
    FgvStrValue = new char8_t[this->DefLength + 1];//动态分配UTF-8字符数组,长度+1[因为也得把空字符包含进去 不然会阻塞缓冲区]
    for (size_t i = 0; i <= this->DefLength; ++i)//将UTF-8字符指针指向的数据全部复制到UTF-8字符数组里(包括空字符\0[也叫终止符])
    {
        this->FgvStrValue[i] = u8cp[i];
    }
    this->FgvStrValue[this->DefLength] = u8'\0';
}

//加法运算符重载 适用于 FgvStr + FgvStr2; 的情况
void FgvString::operator+(const FgvString &fgvStr)
{
    checkValid( );
    InsStrLength = 0;//设置默认值
    while (fgvStr.FgvStrValue[InsStrLength] != u8'\0')//检测UTF-8字符指针指向的数据是否为UTF-8空字符,如果不是则默认长度自增
    {
        ++InsStrLength;
    }
    InsFgvStrValue = new char8_t[InsStrLength + 1];//动态分配UTF-8字符数组,长度+1[因为也得把空字符包含进去 不然会阻塞缓冲区]
    for (size_t i = 0; i <= InsStrLength; ++i)//将UTF-8字符指针指向的数据全部复制到UTF-8字符数组里(包括空字符\0[也叫终止符])
    {
        InsFgvStrValue[i] = fgvStr.FgvStrValue[i];//将传入的字符串逐序赋值给InsFgvStrValue
    }

    FinalStrLength = DefLength + InsStrLength;//总长度 = 默认长度[原自身持有的] + 需要插入的字符串的长度; 注意这两的长度都不计入终止符 也就是空字符\0
    FinalFgvStrValue = new char8_t[FinalStrLength + 1];//动态分配内存,总长度+1是为了包含终止符

    for (size_t i = 0; i <= DefLength; ++i)
    {
        FinalFgvStrValue[i] = FgvStrValue[i];
        //将FgvStrValue里的字符串逐序赋值给FinalFgvStrValue
    }

    for (size_t i = 0; i <= InsStrLength; ++i)
    {
        FinalFgvStrValue[i + DefLength] = InsFgvStrValue[i];
        //将InsFgvStrValue里的字符串逐序赋值给FgvStrValue
        //i + 默认长度 是因为InsStrLength是独立的数据 如果不这样做 ,那么会将我们之前赋值的字符给覆盖掉 而不是在其后继续插入
    }
    if (FgvStrValue)//检测UTF-8字符指针是否存在
    {
        delete[ ] FgvStrValue;//存在则清除UTF-8字符指针指向的数据
        FgvStrValue = nullptr;//设置FgvStrValue为空指针
    }
    FgvStrValue = new char8_t[FinalStrLength + 1];//动态分配内存

    for (size_t i = 0; i <= FinalStrLength; ++i)
    {
        FgvStrValue[i] = FinalFgvStrValue[i];
        ++DefLength;
        //将FinalFgvStrValue里的字符串逐序赋值给FgvStrValue,因为FinalFgvStrValue严格意义上只是个临时的,在该方法结束前会被销毁
    }

    FgvStrValue[FinalStrLength] = u8'\0';

    if (FinalFgvStrValue)//检测UTF-8字符指针是否存在
    {
        delete[ ] FinalFgvStrValue;//存在则清除UTF-8字符指针指向的数据
        FinalFgvStrValue = nullptr;//设置FgvStrValue为空指针
    }
}

//赋值运算符重载 适用于 FgvStr = FgvStr2; 的情况
void FgvString::operator=(const FgvString &fgvStr)
{
    checkValid( );
    if (FgvStrValue)//检测UTF-8字符指针是否存在
    {
        delete[ ] this->FgvStrValue;//存在则清除UTF-8字符指针指向的数据
        this->FgvStrValue = nullptr;//设置FgvStrValue为空指针
        this->DefLength = 0;//设置默认值
    }
    this->DefLength = 0;//设置默认值
    while (fgvStr.FgvStrValue[this->DefLength] != u8'\0')//检测UTF-8字符指针指向的数据是否为UTF-8空字符,如果不是则默认长度自增
    {
        ++this->DefLength;
    }
    FgvStrValue = new char8_t[this->DefLength + 1];//动态分配UTF-8字符数组,长度+1[因为也得把空字符包含进去 不然会阻塞缓冲区]
    for (size_t i = 0; i <= this->DefLength; ++i)//将UTF-8字符指针指向的数据全部复制到UTF-8字符数组里(包括空字符\0[也叫终止符])
    {
        this->FgvStrValue[i] = fgvStr.FgvStrValue[i];
    }
    this->FgvStrValue[this->DefLength] = u8'\0';
}
#pragma endregion

/*|||||||||||||||||||||||||||||||||||分割线||||||||||||||||||||||||||||||||||||||||*/
