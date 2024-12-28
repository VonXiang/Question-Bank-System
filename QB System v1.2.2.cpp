#include <iostream>
#include <conio.h> //包含 getch 函数
#include <sstream>
#include <Windows.h>

using namespace std;

struct Tiku //题库的结构体
{
    string timu; //题目
    string biaoda; //标答
    string options1; //选项1
    string options2; //选项2
    string options3; //选项3
    string options4; //选项4
};

struct Mode //主页菜单模式按钮的位置
{
    int x;
    int y;
};

char a3 = 0; //判断是否退出系统a3
int check; //主菜单上一次键盘监测选定的模式
int let = 0; //记录设置选项的选定编号
int scolor = 0; //记录系统的颜色

Tiku ti[100010]; //题目的数组
Mode mode[10]; //记录6个按钮的位置

int n = 0; //随机题库的题目数量
int m = 0; //化学题库中的题目数量
int p = 0; //选择题库中的题目数量
int z[30]; //用于记录选择模式和化学模式中的题号，防止重复

string ent[] = { "退出时不进行询问", "退出时进行询问" }; //设置选项的内容：退出选项
string color[] = { "黄色", "白色", "绿色" }; //设置选项的内容：系统颜色

int entk = 1; //用来记录退出是否询问的状态
bool Quit = false; //判断程序是否结束运行

void SetMode() //设置主页菜单选项的位置
{
    mode[1].x = 14, mode[1].y = 5;
    mode[2].x = 34, mode[2].y = 5;
    mode[3].x = 54, mode[3].y = 5;
    mode[4].x = 14, mode[4].y = 9;
    mode[5].x = 34, mode[5].y = 9;
    mode[6].x = 54, mode[6].y = 9;
}

void ExitCursor() //关闭快速编辑模式和插入模式
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;  //移除快速编辑模式
    mode &= ~ENABLE_INSERT_MODE;      //移除插入模式
    mode &= ~ENABLE_MOUSE_INPUT;
    SetConsoleMode(hStdin, mode);
}

void SizeGoAway() //取消最大化，最小化
{
    SetWindowLongPtrA(
        GetConsoleWindow(),
        GWL_STYLE,
        GetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
}

void DeleteGoAway() //取消关闭
{
    DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE),
        SC_CLOSE, MF_DISABLED);
    DrawMenuBar(GetConsoleWindow());
}

void ShowCursor(bool visible) //显示或隐藏光标
{
    CONSOLE_CURSOR_INFO cursor_info = { 20, visible };
    //CONSOLE_CURSOR_INFO结构体包含控制台光标信息，成员分别表示光标百分比厚度和是否可见
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    //SetConsoleCursorInfo设定控制台窗口的光标大小和是否可见
}

void SetColor(int ForgC, int BackC)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((BackC << 4) | ForgC));
}

void ColorChange(string a) //设置选项字体的颜色
{
    // 保存默认颜色
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int defForgC = csbi.wAttributes & 0x0F;
    int defBackC = (csbi.wAttributes & 0xF0) >> 4;

    // 设置为白底黑字
    SetColor(0, 15);

    cout << a;

    // 恢复默认颜色
    SetColor(defForgC, defBackC);
}

void gotoxy(int x, int y) //控制光标的跳转
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void space() //清空中间区域
{
    for (int i = 3; i <= 11; i++)
    {
        gotoxy(1, i);
        for (int j = 2; j <= 78; j++)
        {
            cout << " ";
        }
        cout << endl;
    }
}

void Title(string a) //主标题
{
    gotoxy(18, 1);
    cout << a;
    for (int i = 1; i <= 2; i++)
    {
        cout << " ";
    }
}

void title(string a) //副标题
{
    gotoxy(28, 1);
    cout << a;
    for (int i = 1; i <= 20; i++)
    {
        cout << " ";
    }
}

void sigh(string a) //下标题
{
    gotoxy(10, 13);
    cout << "                                                         " << endl;
    gotoxy(39 - a.length() / 2, 13);
    cout << a;
    cout << "       ";
}

void form1(string a) //第一行标题
{
    gotoxy(2, 3);
    cout << "                                                         " << endl;
    gotoxy(39 - a.length() / 2, 3);
    cout << a;
    cout << "       ";
}

void form2(string a) //第二行标题
{
    gotoxy(2, 4);
    cout << "                                                         " << endl;
    gotoxy(39 - a.length() / 2, 4);
    cout << a;
    cout << "       ";
}

void form3(string a) //第三行标题
{
    gotoxy(2, 5);
    cout << "                                                         " << endl;
    gotoxy(39 - a.length() / 2, 5);
    cout << a;
    cout << "       ";
}

void form4(string a) //第四行标题
{
    gotoxy(2, 6);
    cout << "                                                         " << endl;
    gotoxy(39 - a.length() / 2, 6);
    cout << a;
    cout << "       ";
}

void form5(string a) //第五行标题
{
    gotoxy(2, 7);
    cout << "                                                         " << endl;
    gotoxy(39 - a.length() / 2, 7);
    cout << a;
    cout << "       ";
}

void form6(string a) //第六行标题
{
    gotoxy(2, 8);
    cout << "                                                         " << endl;
    gotoxy(39 - a.length() / 2, 8);
    cout << a;
    cout << "       ";
}

string Bottom5(string a) //按钮5
{
    gotoxy(2, 13);
    if (a.length() <= 2)
    {
        cout << "      ";
        gotoxy(2, 13);
    }
    return a;
}

string Bottom6(string a) //按钮6
{
    gotoxy(72, 13);
    if (a.length() <= 2)
    {
        cout << "      ";
        gotoxy(72, 13);
    }
    return a;
}

void GetTable() //生成表格
{
    gotoxy(0, 0);
    cout << "╔═══════════════╦═════════════════════════════════════════════════════════════╗" << endl;
    cout << "║";
    gotoxy(16, 1);
    cout << "║";
    gotoxy(78, 1);
    cout << "║";
    gotoxy(78, 2);
    cout << "╣";
    gotoxy(0, 2);
    cout << "╠" << endl;
    gotoxy(1, 2);
    cout << "═══════════════╩═════════════════════════════════════════════════════════════" << endl;
    for (int i = 3; i <= 11; i++)
    {
        cout << "║";
        gotoxy(78, i);
        cout << "║ " << endl;
    }
    cout << "╠═════════════════════════════════════════════════════════════════════════════╣" << endl;
    gotoxy(2, 1);
    cout << "题库系统v1.2.2";
    gotoxy(0, 13);
    cout << "║";
    gotoxy(78, 13);
    cout << "║";
    gotoxy(0, 14);
    cout << "╚═════════════════════════════════════════════════════════════════════════════╝" << endl;
}

string int_to_string(int a, string b) //整型转换成字符串
{
    stringstream stream;
    stream << a;
    stream >> b;
    return b;
}

bool ExitOrNot() //判断是否退出
{
    int an = 2; //判断是否退出的状态

    cout << Bottom5("5.退出");
    ColorChange(Bottom6("6.继续"));

    char cn = 0;
    while (cn != 13)
    {
        cn = _getch();
        if (cn == '5')
        {
            ColorChange(Bottom5("5.退出"));
            cout << Bottom6("6.继续");
            an = 1;
        }
        if (cn == '6')
        {
            cout << Bottom5("5.退出");
            ColorChange(Bottom6("6.继续"));
            an = 2;
        }
        if (cn == 13)
        {
            if (an == 1)
            {
                Bottom5("");
                Bottom6("");
                return true;
            }
            else
            {
                Bottom5("");
                Bottom6("");
                return false;
            }
        }
    }
}

void Exit() //模式结束退出
{
    Bottom6("");
    ColorChange(Bottom5("5.退出"));
    while (true)
    {
        char ch = _getch();
        if (ch == 13)
        {
            break;
        }
    }
    Bottom5("");
}

bool judgment(string a, string b) //a为输入的答案，b为标答
{
    int num = 0; //num用来计算输入内容和标答一致的文字数量
    int sum = b.length(); //sum变量为标答的长度

    for (int i = 1; i <= a.length(); i++) //逐字判断
    {
        const char c = a[i - 1];
        for (int j = 1; j <= b.length(); j++)
        {
            const char d = b[j - 1];
            if (c == d)
            {
                num++;
                break;
            }
        }
    }
    double num1 = num / 1.0, sum1 = sum / 1.0; //将整型变量转换为浮点型变量

    double n = (num1 / sum1) / 1.0; //计算重合率n
    if (n >= 0.5) //判断作答正误
    {
        return true; //正确
    }
    else
    {
        return false; //错误
    }
}

void n_num() //计算随机题库的题目数量n
{
    for (int i = 1; i <= 100000; i++)
    {
        if (ti[i].timu != "")
        {
            n++;
        }
        else
        {
            break;
        }
    }
}

void m_num() //计算化学题库的题目数量m
{
    for (int i = 5001; i <= 100000; i++)
    {
        if (ti[i].timu != "")
        {
            m++;
        }
        else
        {
            break;
        }
    }
}

void p_num() //计算选择题库的题目数量p
{
    for (int i = 10001; i <= 100000; i++)
    {
        if (ti[i].timu != "")
        {
            p++;
        }
        else
        {
            break;
        }
    }
}

/*-----------------------------题库部分-------------------------------------------------*/

void tik1() //随机题库
{
    ti[1].timu = "太阳系中哪颗行星离太阳最近?";
    ti[1].biaoda = "水星";

    ti[2].timu = "光的传播速度在真空中是多少?";
    ti[2].biaoda = "光在真空中的传播速度是299,792,458米/秒";

    ti[3].timu = "人类最早使用的金属是什么?";
    ti[3].biaoda = "铜";

    ti[4].timu = "中国历史上著名的四大发明是什么?";
    ti[4].biaoda = "造纸术、印刷术、火药、指南针";

    ti[5].timu = "在生物学中，DNA的全称是什么?";
    ti[5].biaoda = "脱氧核糖核酸";

    ti[6].timu = "地球上有多少块大陆?";
    ti[6].biaoda = "地球上有7块大陆";

    ti[7].timu = "世界上最长的河流是哪一条?";
    ti[7].biaoda = "尼罗河";

    ti[8].timu = "人类首次登上月球是在哪一年?";
    ti[8].biaoda = "1969年";

    ti[9].timu = "C语言是在哪一年被发明的?";
    ti[9].biaoda = "1972年";

    ti[10].timu = "一个圆的周长公式是什么?";
    ti[10].biaoda = "C = 2πr，其中C是周长，r是半径，π是圆周率";

    ti[11].timu = "世界上最深的海洋是哪一个?";
    ti[11].biaoda = "太平洋";

    ti[12].timu = "大熊猫主要以什么为食?";
    ti[12].biaoda = "竹子";

    ti[13].timu = "人体的哪个器官负责呼吸?";
    ti[13].biaoda = "肺";

    ti[14].timu = "联合国是在哪一年成立的?";
    ti[14].biaoda = "1945年";

    ti[15].timu = "世界上最快的陆生动物是什么?";
    ti[15].biaoda = "猎豹";

    ti[16].timu = "元素周期表中的第一个元素是什么?";
    ti[16].biaoda = "氢";

    ti[17].timu = "《蒙娜丽莎》的作者是谁?";
    ti[17].biaoda = "达·芬奇";

    ti[18].timu = "一个标准足球比赛中每个队有多少名球员?";
    ti[18].biaoda = "11名";

    ti[19].timu = "光年是什么的单位?";
    ti[19].biaoda = "长度单位，用于测量天体间的距离";

    ti[20].timu = "世界上最小的鸟是什么?";
    ti[20].biaoda = "蜂鸟";

    ti[21].timu = "请简述量子力学中的测不准原理。";
    ti[21].biaoda = "测不准原理是由海森堡提出，它表明在微观尺度上，粒子的位置和动量无法同时被精确测量";

    ti[22].timu = "请解释广义相对论中的时空弯曲概念。";
    ti[22].biaoda = "时空弯曲是爱因斯坦广义相对论的核心概念，它认为物质和能量能够影响时空的几何结构，导致时空弯曲，进而影响物体的运动轨迹";

    ti[23].timu = "什么是遗传算法？请简述其基本原理。";
    ti[23].biaoda = "遗传算法是一种启发式搜索算法，受生物进化理论的启发，通过模拟自然选择和遗传机制来优化问题求解,基本原理包括选择、交叉和变异操作，以生成新的解，并通过适应度函数评估解的质量";

    ti[24].timu = "请简述区块链技术的基本原理和特点。";
    ti[24].biaoda = "区块链技术是一种去中心化的分布式数据库技术，其基本原理是通过网络中的多个节点共同维护一个不断增长的交易记录列表,特点是数据一旦写入就难以篡改，具有高安全性、透明度和不可篡改性";

    ti[25].timu = "什么是人工智能中的深度学习？请简述其基本原理。";
    ti[25].biaoda = "深度学习是一种机器学习技术，通过构建多层的神经网络模型来学习数据的深层表示,基本原理是通过大量的训练数据和反向传播算法，自动学习特征表示和模型参数，以实现对复杂数据的建模和预测";

    ti[26].timu = "MC里有BUG吗";
    ti[26].biaoda = "没有。";

    ti[27].timu = "Minecraft中白天的时间是多久？";
    ti[27].biaoda = "15分钟。";

    ti[28].timu = "Minecraft中最坚硬的方块是什么？";
    ti[28].biaoda = "基岩";

    ti[29].timu = "在Minecraft中，如何快速穿越地图？";
    ti[29].biaoda = "使用末影珍珠。";

    ti[30].timu = "Minecraft中哪个生物会主动攻击玩家？";
    ti[30].biaoda = "僵尸。";

    ti[31].timu = "在Minecraft中，如何进入下界？";
    ti[31].biaoda = "制作并激活下界传送门。";

    ti[32].timu = "Minecraft中哪个方块可以用来制作附魔台？";
    ti[32].biaoda = "书、钻石和黑曜石。";

    ti[33].timu = "Minecraft中哪种生物会掉落煤炭？";
    ti[33].biaoda = "僵尸猪人。";

    ti[34].timu = "在Minecraft中，如何获得经验值？";
    ti[34].biaoda = "杀死怪物、挖掘矿物或交易。";

    ti[35].timu = "Minecraft中的末影龙有多少生命值？";
    ti[35].biaoda = "200点生命值。";

    ti[36].timu = "在Minecraft中，哪个物品可以用来修复工具？";
    ti[36].biaoda = "经验修补。";

    ti[37].timu = "Minecraft中哪个方块可以用来制作TNT？";
    ti[37].biaoda = "沙子和火药。";

    ti[38].timu = "在Minecraft中，如何获得青金石？";
    ti[38].biaoda = "挖掘青金石矿石。";

    ti[39].timu = "Minecraft中哪个生物是游戏中的主角？";
    ti[39].biaoda = "史蒂夫。";

    ti[40].timu = "在Minecraft中，如何获得金块？";
    ti[40].biaoda = "将9个金锭放入合成栏。";

    ti[41].timu = "Minecraft中的狼可以被驯服吗？";
    ti[41].biaoda = "可以，使用骨头。";

    ti[42].timu = "在Minecraft中，哪个方块可以用来制作熔炉？";
    ti[42].biaoda = "圆石。";

    ti[43].timu = "Minecraft中哪个生物会掉落音乐唱片？";
    ti[43].biaoda = "骷髅。";

    ti[44].timu = "在Minecraft中，如何获得附魔书？";
    ti[44].biaoda = "在附魔台使用书和青金石。";

    ti[45].timu = "Minecraft中的末影人可以被水淹没吗？";
    ti[45].biaoda = "不可以。";

    ti[46].timu = "在Minecraft中，如何获得绿宝石？";
    ti[46].biaoda = "挖掘绿宝石矿石。";

    ti[47].timu = "Minecraft中哪个生物会掉落铁锭？";
    ti[47].biaoda = "铁傀儡。";

    ti[48].timu = "在Minecraft中，如何进入末地？";
    ti[48].biaoda = "通过末地传送门。";

    ti[49].timu = "Minecraft中的仙人掌可以在哪种方块上生长？";
    ti[49].biaoda = "沙子或红沙。";

    ti[50].timu = "在Minecraft中，如何获得烈焰棒？";
    ti[50].biaoda = "击败烈焰人。";

    ti[51].timu = "Minecraft中哪个方块可以用来制作活塞？";
    ti[51].biaoda = "粘土、圆石和铁锭。";

    ti[52].timu = "在Minecraft中，如何获得龙息？";
    ti[52].biaoda = "用玻璃瓶收集末影龙吐息。";

    ti[53].timu = "Minecraft中的兔子有几种类型？";
    ti[53].biaoda = "六种。";

    ti[54].timu = "在Minecraft中，如何获得兔子皮？";
    ti[54].biaoda = "杀死兔子。";

    ti[55].timu = "Minecraft中的末影珍珠可以用来做什么？";
    ti[55].biaoda = "制作末影之眼或末影箱。";

    ti[56].timu = "在Minecraft中，如何获得甜菜根？";
    ti[56].biaoda = "收获甜菜作物。";

    ti[57].timu = "Minecraft中哪个生物会掉落蜘蛛眼？";
    ti[57].biaoda = "蜘蛛。";

    ti[58].timu = "在Minecraft中，如何获得兔子脚？";
    ti[58].biaoda = "杀死兔子。";

    ti[59].timu = "Minecraft中的村民可以被僵尸感染吗？";
    ti[59].biaoda = "可以，变成僵尸村民。";

    ti[60].timu = "在Minecraft中，如何获得南瓜？";
    ti[60].biaoda = "收获南瓜作物。";
}

void tik2() //化学题库
{
    ti[5001].timu = "请简述原子和离子的主要区别。";
    ti[5001].biaoda = "原子是电中性的，而离子是带电的原子或原子团";

    ti[5002].timu = "什么是摩尔？";
    ti[5002].biaoda = "摩尔是物质的量的单位，表示含有Avogadro常数个粒子的物质的数量";

    ti[5003].timu = "浓硫酸是否具有氧化性";
    ti[5003].biaoda = "是";

    ti[5004].timu = "什么是酸碱中和反应？";
    ti[5004].biaoda = "酸碱中和反应是酸和碱反应生成盐和水的化学反应";

    ti[5005].timu = "请简述氧化还原反应的定义。";
    ti[5005].biaoda = "氧化还原反应是指物质中的原子氧化态发生变化的化学反应";

    ti[5006].timu = "什么是催化剂？";
    ti[5006].biaoda = "催化剂是能够加速化学反应速率而自身不被消耗的物质";

    ti[5007].timu = "请写出氧气和氢气反应的的产物";
    ti[5007].biaoda = "水";

    ti[5008].timu = "什么是元素周期表？";
    ti[5008].biaoda = "元素周期表是按照原子序数排列所有已知元素的一种表格形式";

    ti[5009].timu = "请简述电解质和非电解质的主要区别。";
    ti[5009].biaoda = "电解质在水溶液中能够导电，而非电解质在水溶液中不能导电";

    ti[5010].timu = "什么是pH值？";
    ti[5010].biaoda = "pH值是衡量溶液酸碱程度的数值，表示溶液中氢离子浓度的负对数";

    ti[5011].timu = "请简述饱和溶液和不饱和溶液的区别。";
    ti[5011].biaoda = "在一定温度下，溶质已经溶解到最大限度，不能再溶解更多的溶质；而不饱和溶液则可以继续溶解更多的溶质";

    ti[5012].timu = "什么是同位素？";
    ti[5012].biaoda = "具有相同原子序数但质量数不同的元素，因此它们的原子核中的中子数不同";

    ti[5013].timu = "请写出氧化铜的化学式。";
    ti[5013].biaoda = "CuO";

    ti[5014].timu = "什么是化学反应的平衡常数？";
    ti[5014].biaoda = "在平衡状态下，反应物和生成物浓度的比值的乘积，与反应物初始浓度无关";

    ti[5015].timu = "请简述离子键和共价键的区别。";
    ti[5015].biaoda = "离子键是通过正负电荷吸引形成的键，通常发生在金属和非金属之间；而共价键是通过电子对共享形成的键，通常发生在非金属原子之间";

    ti[5016].timu = "什么是活化能？";
    ti[5016].biaoda = "活化学反应开始前必须克服的能量障碍";

    ti[5017].timu = "请写出氢氧化钠的化学式。";
    ti[5017].biaoda = "NaOH";

    ti[5018].timu = "什么是放射性衰变？";
    ti[5018].biaoda = "不稳定原子核自发地转变为更稳定状态的过程，伴随着粒子的发射";

    ti[5019].timu = "请简述酸的定义。";
    ti[5019].biaoda = "酸是能够提供氢离子的化合物";

    ti[5020].timu = "什么是分子量？";
    ti[5020].biaoda = "分子中所有原子相对原子质量的总和";

    ti[5021].timu = "请写出水的相对分子质量";
    ti[5021].biaoda = "18";

    ti[5022].timu = "什么是沉淀反应？";
    ti[5022].biaoda = "两种溶液混合后，生成不溶于溶液的沉淀物的化学反应";

    ti[5023].timu = "化学反应中的能量变化是如何体现的？";
    ti[5023].biaoda = "化学反应中的能量变化主要通过热效应体现，即反应放热或吸热";

    ti[5024].timu = "什么是氧化剂？";
    ti[5024].biaoda = "在化学反应中能够接受电子，使其他物质氧化的物质";

    ti[5025].timu = "请写出燃烧反应的通式。";
    ti[5025].biaoda = "燃烧反应的通式通常表示为：燃料 + 氧气 → 二氧化碳 + 水 + 能量";

    ti[5026].timu = "什么是化学键？";
    ti[5026].biaoda = "化学键是连接原子或离子的力，它决定了分子的结构和性质";

    ti[5027].timu = "请简述有机化学和无机化学的区别。";
    ti[5027].biaoda = "有机化学研究含有碳的化合物，而无机化学研究不含碳的化合物，以及一些简单的碳化合物";

    ti[5028].timu = "什么是晶体？";
    ti[5028].biaoda = "晶体是具有规则排列的粒子（如原子、离子或分子）形成的固体结构";

    ti[5029].timu = "仲钨酸铵经煅烧可得黄钨，同时也会生成蓝钨和紫钨的原因";
    ti[5029].biaoda = "黄钨被还原";

    ti[5030].timu = "什么是化学平衡？";
    ti[5030].biaoda = "化学平衡是指在封闭系统中，正反应速率相等，反应物和生成物的浓度不再发生变化的状态";

    ti[5031].timu = "请简述酸碱指示剂的原理。";
    ti[5031].biaoda = "酸碱指示剂是根据其分子结构在不同pH值下颜色变化的性质来指示溶液酸碱性的物质";

    ti[5032].timu = "什么是同素异形体？";
    ti[5032].biaoda = "同素异形体是指由相同元素组成，但结构不同，因而性质不同的化合物";

    ti[5033].timu = "氮气可以与氧气反应吗";
    ti[5033].biaoda = "可以";

    ti[5034].timu = "什么是极性分子和非极性分子？";
    ti[5034].biaoda = "极性分子是指分子中正负电荷中心不重合，存在部分电荷分离的分子；非极性分子是指分子中正负电荷中心重合，电荷分布均匀的分子";

    ti[5035].timu = "请简述配位化合物的定义。";
    ti[5035].biaoda = "配位化合物是由一个或多个中心金属离子和围绕其的配体通过配位键结合形成的化合物";

    ti[5036].timu = "什么是分散系？";
    ti[5036].biaoda = "分散系是由两种或多种物质组成的混合体系，其中一种物质以微粒形式分散在另一种物质中";

    ti[5037].timu = "请写出氢气的化学式。";
    ti[5037].biaoda = "H2";

    ti[5038].timu = "什么是活化分析？";
    ti[5038].biaoda = "活化分析是一种利用放射性同位素对物质进行化学成分分析的方法";

    ti[5039].timu = "请简述金属和非金属的主要区别。";
    ti[5039].biaoda = "金属通常具有良好的导电性和热导性，而非金属通常不良导电和不具有良好的热导性。此外，金属在固态时具有金属光泽，而非金属则不具有";

    ti[5040].timu = "什么是分子间力？";
    ti[5040].biaoda = "分子间力是分子之间的相互作用力，包括范德华力、氢键等，它们决定了物质的物理性质";

    ti[5041].timu = "请写出氯化钠的化学式。";
    ti[5041].biaoda = "NaCl";

    ti[5042].timu = "什么是多相催化？";
    ti[5042].biaoda = "多相催化是指催化剂和反应物处于不同相的催化过程";

    ti[5043].timu = "请简述光谱分析的原理。";
    ti[5043].biaoda = "光谱分析是利用物质对不同波长光的吸收或发射特性来分析其组成和性质的方法";
}

void tik3() //选择题库
{
    ti[10001].timu = "以下哪位科学家提出了相对论？";
    ti[10001].options1 = "1.牛顿";
    ti[10001].options2 = "2.爱因斯坦";
    ti[10001].options3 = "3.伽利略";
    ti[10001].options4 = "4.波尔";
    ti[10001].biaoda = "2";

    ti[10002].timu = "太阳系中距离太阳最近的行星是哪颗？";
    ti[10002].options1 = "1.水星";
    ti[10002].options2 = "2.金星";
    ti[10002].options3 = "3.地球";
    ti[10002].options4 = "4.火星";
    ti[10002].biaoda = "1";

    ti[10003].timu = "以下哪种元素在周期表中符号为'Fe'？";
    ti[10003].options1 = "1.铜";
    ti[10003].options2 = "2.铁";
    ti[10003].options3 = "3.铝";
    ti[10003].options4 = "4.锡";
    ti[10003].biaoda = "2";

    ti[10004].timu = "世界上面积最大的国家是哪个？";
    ti[10004].options1 = "1.中国";
    ti[10004].options2 = "2.俄罗斯";
    ti[10004].options3 = "3.加拿大";
    ti[10004].options4 = "4.美国";
    ti[10004].biaoda = "2";

    ti[10005].timu = "下列哪位是中国古代著名的教育家？";
    ti[10005].options1 = "1.孔子";
    ti[10005].options2 = "2.孟子";
    ti[10005].options3 = "3.庄子";
    ti[10005].options4 = "4.以上都是";
    ti[10005].biaoda = "4";

    ti[10006].timu = "下列哪个城市被称为'世界水城'？";
    ti[10006].options1 = "1.威尼斯";
    ti[10006].options2 = "2.阿姆斯特丹";
    ti[10006].options3 = "3.巴黎";
    ti[10006].options4 = "4.布拉格";
    ti[10006].biaoda = "1";

    ti[10007].timu = "下列哪种动物被称为'森林之王'？";
    ti[10007].options1 = "1.老虎";
    ti[10007].options2 = "2.狮子";
    ti[10007].options3 = "3.熊";
    ti[10007].options4 = "4.狼";
    ti[10007].biaoda = "2";

    ti[10008].timu = "下列哪位是《红楼梦》的作者？";
    ti[10008].options1 = "1.曹雪芹";
    ti[10008].options2 = "2.施耐庵";
    ti[10008].options3 = "3.罗贯中";
    ti[10008].options4 = "4.吴承恩";
    ti[10008].biaoda = "1";

    ti[10009].timu = "下列哪个行星拥有最多的卫星？";
    ti[10009].options1 = "1.木星";
    ti[10009].options2 = "2.土星";
    ti[10009].options3 = "3.地球";
    ti[10009].options4 = "4.火星";
    ti[10009].biaoda = "1";

    ti[10010].timu = "下列哪种物质不是植物进行光合作用的必需品？";
    ti[10010].options1 = "1.氧气";
    ti[10010].options2 = "2.二氧化碳";
    ti[10010].options3 = "3.水";
    ti[10010].options4 = "4.叶绿体";
    ti[10010].biaoda = "1";

    ti[10011].timu = "下列哪个国家是联合国安全理事会的常任理事国？";
    ti[10011].options1 = "1.法国";
    ti[10011].options2 = "2.德国";
    ti[10011].options3 = "3.日本";
    ti[10011].options4 = "4.巴西";
    ti[10011].biaoda = "1";

    ti[10012].timu = "下列哪位科学家提出了量子力学的基本原理？";
    ti[10012].options1 = "1.普朗克";
    ti[10012].options2 = "2.海森堡";
    ti[10012].options3 = "3.薛定谔";
    ti[10012].options4 = "4.爱因斯坦";
    ti[10012].biaoda = "2";

    ti[10013].timu = "下列哪个是世界上最深的海洋？";
    ti[10013].options1 = "1.大西洋";
    ti[10013].options2 = "2.印度洋";
    ti[10013].options3 = "3.北冰洋";
    ti[10013].options4 = "4.太平洋";
    ti[10013].biaoda = "4";

    ti[10014].timu = "下列哪个国家是世界上人口最多的？";
    ti[10014].options1 = "1.印度";
    ti[10014].options2 = "2.美国";
    ti[10014].options3 = "3.印度尼西亚";
    ti[10014].options4 = "4.中国";
    ti[10014].biaoda = "1";

    ti[10015].timu = "下列哪座山是世界上最高的山峰？";
    ti[10015].options1 = "1.珠穆朗玛峰";
    ti[10015].options2 = "2.乔戈里峰";
    ti[10015].options3 = "3.喀喇昆仑山";
    ti[10015].options4 = "4.喜马拉雅山";
    ti[10015].biaoda = "1";

    ti[10016].timu = "下列哪种动物是现存最大的陆地哺乳动物？";
    ti[10016].options1 = "1.犀牛";
    ti[10016].options2 = "2.大象";
    ti[10016].options3 = "3.河马";
    ti[10016].options4 = "4.长颈鹿";
    ti[10016].biaoda = "2";

    ti[10017].timu = "下列哪个城市被称为'世界设计之都'？";
    ti[10017].options1 = "1.纽约";
    ti[10017].options2 = "2.东京";
    ti[10017].options3 = "3.米兰";
    ti[10017].options4 = "4.伦敦";
    ti[10017].biaoda = "3";

    ti[10018].timu = "下列哪个是太阳系中最大的行星？";
    ti[10018].options1 = "1.木星";
    ti[10018].options2 = "2.土星";
    ti[10018].options3 = "3.天王星";
    ti[10018].options4 = "4.海王星";
    ti[10018].biaoda = "1";

    ti[10019].timu = "下列哪位科学家发现了电和磁之间的关系？";
    ti[10019].options1 = "1.法拉第";
    ti[10019].options2 = "2.牛顿";
    ti[10019].options3 = "3.安培";
    ti[10019].options4 = "4.欧姆";
    ti[10019].biaoda = "1";

    ti[10020].timu = "下列哪个是世界上最长的河流？";
    ti[10020].options1 = "1.尼罗河";
    ti[10020].options2 = "2.亚马逊河";
    ti[10020].options3 = "3.长江";
    ti[10020].options4 = "4.密西西比河";
    ti[10020].biaoda = "2";

    ti[10021].timu = "下列哪个是地球上的最大洲？";
    ti[10021].options1 = "1.亚洲";
    ti[10021].options2 = "2.非洲";
    ti[10021].options3 = "3.北美洲";
    ti[10021].options4 = "4.欧洲";
    ti[10021].biaoda = "1";

    ti[10022].timu = "下列哪种元素是生命体中最多的元素？";
    ti[10022].options1 = "1.氧";
    ti[10022].options2 = "2.碳";
    ti[10022].options3 = "3.氢";
    ti[10022].options4 = "4.氮";
    ti[10022].biaoda = "2";

    ti[10023].timu = "下列哪位科学家提出了进化论？";
    ti[10023].options1 = "1.达尔文";
    ti[10023].options2 = "2.牛顿";
    ti[10023].options3 = "3.法布尔";
    ti[10023].options4 = "4.林奈";
    ti[10023].biaoda = "1";

    ti[10024].timu = "下列哪个国家是著名的咖啡生产国？";
    ti[10024].options1 = "1.巴西";
    ti[10024].options2 = "2.中国";
    ti[10024].options3 = "3.俄罗斯";
    ti[10024].options4 = "4.加拿大";
    ti[10024].biaoda = "1";

    ti[10025].timu = "下列哪个城市被称为'世界雾都'？";
    ti[10025].options1 = "1.伦敦";
    ti[10025].options2 = "2.巴黎";
    ti[10025].options3 = "3.纽约";
    ti[10025].options4 = "4.东京";
    ti[10025].biaoda = "1";

    ti[10026].timu = "下列哪种昆虫具有最强的力量？";
    ti[10026].options1 = "1.蚂蚁";
    ti[10026].options2 = "2.甲虫";
    ti[10026].options3 = "3.蜜蜂";
    ti[10026].options4 = "4.蝴蝶";
    ti[10026].biaoda = "2";

    ti[10027].timu = "下列哪个是世界上最小的鸟？";
    ti[10027].options1 = "1.蜂鸟";
    ti[10027].options2 = "2.啄木鸟";
    ti[10027].options3 = "3.鹦鹉";
    ti[10027].options4 = "4.猫头鹰";
    ti[10027].biaoda = "1";

    ti[10028].timu = "下列哪个是世界上最快的陆地动物？";
    ti[10028].options1 = "1.猎豹";
    ti[10028].options2 = "2.狮子";
    ti[10028].options3 = "3.老虎";
    ti[10028].options4 = "4.马";
    ti[10028].biaoda = "1";

    ti[10029].timu = "下列哪个国家是世界上最大的石油生产国？";
    ti[10029].options1 = "1.沙特阿拉伯";
    ti[10029].options2 = "2.俄罗斯";
    ti[10029].options3 = "3.美国";
    ti[10029].options4 = "4.中国";
    ti[10029].biaoda = "1";

    ti[10030].timu = "下列哪个是世界上最深的湖泊？";
    ti[10030].options1 = "1.贝加尔湖";
    ti[10030].options2 = "2.里海";
    ti[10030].options3 = "3.青海湖";
    ti[10030].options4 = "4.五大湖";
    ti[10030].biaoda = "1";

    ti[10031].timu = "下列哪个是世界上最古老的城市？";
    ti[10031].options1 = "1.耶路撒冷";
    ti[10031].options2 = "2.雅典";
    ti[10031].options3 = "3.罗马";
    ti[10031].options4 = "4.开罗";
    ti[10031].biaoda = "2";

    ti[10032].timu = "下列哪个是世界上最长的城墙？";
    ti[10032].options1 = "1.中国长城";
    ti[10032].options2 = "2.哈德良长城";
    ti[10032].options3 = "3.柏林墙";
    ti[10032].options4 = "4.大马士革城墙";
    ti[10032].biaoda = "1";

    ti[10033].timu = "下列哪个是世界上最古老的语言之一？";
    ti[10033].options1 = "1.汉语";
    ti[10033].options2 = "2.梵语";
    ti[10033].options3 = "3.阿拉伯语";
    ti[10033].options4 = "4.英语";
    ti[10033].biaoda = "2";

    ti[10034].timu = "下列哪个是世界上最小的国家？";
    ti[10034].options1 = "1.梵蒂冈";
    ti[10034].options2 = "2.摩纳哥";
    ti[10034].options3 = "3.瑙鲁";
    ti[10034].options4 = "4.列支敦士登";
    ti[10034].biaoda = "1";

    ti[10035].timu = "下列哪个是世界上最著名的画作之一？";
    ti[10035].options1 = "1.《蒙娜丽莎》";
    ti[10035].options2 = "2.《星夜》";
    ti[10035].options3 = "3.《最后的晚餐》";
    ti[10035].options4 = "4.以上都是";
    ti[10035].biaoda = "4";

    ti[10036].timu = "下列哪个是世界上最著名的雕塑之一？";
    ti[10036].options1 = "1.《大卫》";
    ti[10036].options2 = "2.《思想者》";
    ti[10036].options3 = "3.《自由女神像》";
    ti[10036].options4 = "4.以上都是";
    ti[10036].biaoda = "4";

    ti[10037].timu = "下列哪个是世界上最著名的歌剧之一？";
    ti[10037].options1 = "1.《卡门》";
    ti[10037].options2 = "2.《图兰朵》";
    ti[10037].options3 = "3.《蝴蝶夫人》";
    ti[10037].options4 = "4.以上都是";
    ti[10037].biaoda = "4";

    ti[10038].timu = "下列哪个是世界上最著名的交响曲之一？";
    ti[10038].options1 = "1.贝多芬的《第九交响曲》";
    ti[10038].options2 = "2.莫扎特的《安魂曲》";
    ti[10038].options3 = "3.巴赫的《马太受难曲》";
    ti[10038].options4 = "4.以上都是";
    ti[10038].biaoda = "4";

    ti[10039].timu = "下列哪个是世界上最著名的小说之一？";
    ti[10039].options1 = "1.《战争与和平》";
    ti[10039].options2 = "2.《百年孤独》";
    ti[10039].options3 = "3.《悲惨世界》";
    ti[10039].options4 = "4.以上都是";
    ti[10039].biaoda = "4";

    ti[10040].timu = "下列哪个是世界上最著名的古代建筑之一？";
    ti[10040].options1 = "1.古埃及金字塔";
    ti[10040].options2 = "2.希腊帕台农神庙";
    ti[10040].options3 = "3.罗马斗兽场";
    ti[10040].options4 = "4.以上都是";
    ti[10040].biaoda = "4";

    ti[10041].timu = "下列哪位科学家提出了关于黑洞的'事件视界'概念？";
    ti[10041].options1 = "1.爱因斯坦";
    ti[10041].options2 = "2.霍金";
    ti[10041].options3 = "3.卡尔·施瓦西";
    ti[10041].options4 = "4.特斯拉";
    ti[10041].biaoda = "3";

    ti[10042].timu = "下列哪个物理常数是描述电磁相互作用强度的？";
    ti[10042].options1 = "1.普朗克常数";
    ti[10042].options2 = "2.精细结构常数";
    ti[10042].options3 = "3.阿伏伽德罗常数";
    ti[10042].options4 = "4.引力常数";
    ti[10042].biaoda = "2";

    ti[10043].timu = "下列哪个是量子力学中的基本方程之一？";
    ti[10043].options1 = "1.薛定谔方程";
    ti[10043].options2 = "2.牛顿第二定律";
    ti[10043].options3 = "3.麦克斯韦方程组";
    ti[10043].options4 = "4.热力学第一定律";
    ti[10043].biaoda = "1";

    ti[10044].timu = "下列哪个是描述宇宙早期状态的宇宙学理论？";
    ti[10044].options1 = "1.大爆炸理论";
    ti[10044].options2 = "2.稳态宇宙理论";
    ti[10044].options3 = "3.弦理论";
    ti[10044].options4 = "4.量子场论";
    ti[10044].biaoda = "1";

    ti[10045].timu = "下列哪个是生物分类学中的基本单位？";
    ti[10045].options1 = "1.种群";
    ti[10045].options2 = "2.物种";
    ti[10045].options3 = "3.属";
    ti[10045].options4 = "4.科";
    ti[10045].biaoda = "2";

    ti[10046].timu = "下列哪个是化学中描述原子结构的模型？";
    ti[10046].options1 = "1.波尔模型";
    ti[10046].options2 = "2.道尔顿原子理论";
    ti[10046].options3 = "3.电子云模型";
    ti[10046].options4 = "4.阿伏伽德罗假说";
    ti[10046].biaoda = "1";

    ti[10047].timu = "下列哪个是经济学中的'无形的手'理论的提出者？";
    ti[10047].options1 = "1.马克思";
    ti[10047].options2 = "2.凯恩斯";
    ti[10047].options3 = "3.斯密";
    ti[10047].options4 = "4.李嘉图";
    ti[10047].biaoda = "3";

    ti[10048].timu = "下列哪个是计算机科学中的图灵测试的提出者？";
    ti[10048].options1 = "1.艾伦·图灵";
    ti[10048].options2 = "2.冯·诺伊曼";
    ti[10048].options3 = "3.史蒂夫·乔布斯";
    ti[10048].options4 = "4.比尔·盖茨";
    ti[10048].biaoda = "1";

    ti[10049].timu = "下列哪个是数学中的费马大定理的证明者？";
    ti[10049].options1 = "1.欧拉";
    ti[10049].options2 = "2.高斯";
    ti[10049].options3 = "3.希尔伯特";
    ti[10049].options4 = "4.安德鲁·怀尔斯";
    ti[10049].biaoda = "4";

    ti[10050].timu = "下列哪个是医学中首次成功应用抗生素的案例？";
    ti[10050].options1 = "1.青霉素";
    ti[10050].options2 = "2.链霉素";
    ti[10050].options3 = "3.磺胺类药物";
    ti[10050].options4 = "4.疫苗";
    ti[10050].biaoda = "1";

    ti[10051].timu = "哪位科学家提出了量子力学的矩阵力学表述？";
    ti[10051].options1 = "1.海森堡";
    ti[10051].options2 = "2.薛定谔";
    ti[10051].options3 = "3.玻尔";
    ti[10051].options4 = "4.爱因斯坦";
    ti[10051].biaoda = "1";

    ti[10052].timu = "下列哪项是化学元素周期律的发现者？";
    ti[10052].options1 = "1.门捷列夫";
    ti[10052].options2 = "2.道尔顿";
    ti[10052].options3 = "3.拉瓦锡";
    ti[10052].options4 = "4.阿伏伽德罗";
    ti[10052].biaoda = "1";

    ti[10053].timu = "哪位数学家提出了欧几里得几何的平行公设？";
    ti[10053].options1 = "1.欧几里得";
    ti[10053].options2 = "2.毕达哥拉斯";
    ti[10053].options3 = "3.笛卡尔";
    ti[10053].options4 = "4.高斯";
    ti[10053].biaoda = "1";

    ti[10054].timu = "下列哪项是太阳系中最大的小行星？";
    ti[10054].options1 = "1.谷神星";
    ti[10054].options2 = "2.智神星";
    ti[10054].options3 = "3.婚神星";
    ti[10054].options4 = "4.灶神星";
    ti[10054].biaoda = "1";

    ti[10055].timu = "哪位天文学家提出了日心说？";
    ti[10055].options1 = "1.哥白尼";
    ti[10055].options2 = "2.托勒密";
    ti[10055].options3 = "3.开普勒";
    ti[10055].options4 = "4.牛顿";
    ti[10055].biaoda = "1";

    ti[10056].timu = "下列哪项是生物进化论的基础概念？";
    ti[10056].options1 = "1.自然选择";
    ti[10056].options2 = "2.物种不变论";
    ti[10056].options3 = "3.用进废退";
    ti[10056].options4 = "4.获得性遗传";
    ti[10056].biaoda = "1";

    ti[10057].timu = "哪位物理学家提出了光量子假说？";
    ti[10057].options1 = "1.普朗克";
    ti[10057].options2 = "2.爱因斯坦";
    ti[10057].options3 = "3.玻尔";
    ti[10057].options4 = "4.海森堡";
    ti[10057].biaoda = "2";

    ti[10058].timu = "下列哪项是地球最外层的岩石圈的主要组成部分？";
    ti[10058].options1 = "1.地壳";
    ti[10058].options2 = "2.地幔";
    ti[10058].options3 = "3.外核";
    ti[10058].options4 = "4.内核";
    ti[10058].biaoda = "1";

    ti[10059].timu = "哪位哲学家提出了'我思故我在'的命题？";
    ti[10059].options1 = "1.笛卡尔";
    ti[10059].options2 = "2.康德";
    ti[10059].options3 = "3.黑格尔";
    ti[10059].options4 = "4.尼采";
    ti[10059].biaoda = "1";

    ti[10060].timu = "下列哪项是宇宙微波背景辐射的发现者？";
    ti[10060].options1 = "1.彭齐亚斯和威尔逊";
    ti[10060].options2 = "2.哈勃";
    ti[10060].options3 = "3.钱德拉塞卡";
    ti[10060].options4 = "4.霍金";
    ti[10060].biaoda = "1";
}

/*-------------------------------------------------------*/

void mode1() //选择模式
{
    space();
    ShowCursor(false);
    char ca = 0;
    int num = 0;
    srand(time(NULL));
    int d = rand() % 5 + 5; //题目数量
    Title("选择模式");
    title("题目说明");
    string number;

    form5("本轮共" + int_to_string(d, number) + "题");
    sigh("模式界面");

    if (ExitOrNot() == true) //判断是否退出
    {
        return;
    }
    space();

    for (int h = 1; h <= 25; h++) //初始数组
    {
        z[h] = 0;
    }

    for (int i = 1; i <= d; i++)
    {
        int a = rand() % p + 10001;
        bool tu = false;
        while (tu == false) //判断题目是否重复
        {
            int su = 0;
            for (int j = 1; j <= 25; j++)
            {
                if (a == z[j]) //1.2修改的bug
                {
                    su++;
                }
            }
            if (su == 0)
            {
                tu = true;
                z[i] = a;
            }
            else
            {
                tu = false;
                int a1 = rand() % p + 10001;
                a = a1;
            }
        }

        title("第" + int_to_string(i, number) + "题");

        form2(ti[a].timu);
        form3(ti[a].options1);
        form4(ti[a].options2);
        form5(ti[a].options3);
        form6(ti[a].options4);

        string ba = "";

        while (true)
        {
            ca = _getch();
            if (ca == '1')
            {
                ba = "1";
                break;
            }
            if (ca == '2')
            {
                ba = "2";
                break;
            }
            if (ca == '3')
            {
                ba = "3";
                break;
            }
            if (ca == '4')
            {
                ba = "4";
                break;
            }
            else
            {
                continue;
            }
        }

        if (ba == ti[a].biaoda)
        {
            sigh("回答正确");
            num++;
        }
        else
        {
            sigh("回答错误");
        }

        if (ExitOrNot() == true) //判断是否退出
        {
            return;
        }

        space();
        sigh("模式界面");
    }
    space();
    title("本轮结算");

    form5("本次共" + int_to_string(d, number) + "道题, 答对" + int_to_string(num, number) + "道题");

    ShowCursor(false);
    Exit();
}

void mode2() //随机模式
{
    Title("随机模式");
    title("简答题");
    sigh("模式界面");
    space();
    ShowCursor(true);
    gotoxy(2, 3);
    cout << "题目：";
    srand(time(NULL));
    int a = rand() % n + 1;
    cout << ti[a].timu << endl; //输出题目
    gotoxy(2, 4);
    string b;
    char c = 0;
    cin.get(c);
    b += c;

    while (c != '\n') //输入答案
    {
        cin.get(c);
        b += c;
    }

    ShowCursor(false);
    if (judgment(b, ti[a].biaoda) == 1)
    {
        sigh("回答正确");
    }
    else
    {
        sigh("回答错误");
    }
    GetTable();
    Exit();
}

void mode3() //化学模式
{
    Title("化学模式");
    title("题目说明");
    sigh("模式界面");
    space();
    ShowCursor(false);
    int num = 0;
    srand(time(NULL));
    int d = rand() % 5 + 5; //题目数量

    string number;
    form5("本轮共" + int_to_string(d, number) + "题");

    if (ExitOrNot() == true) //判断是否退出
    {
        return;
    }
    space();

    for (int h = 1; h <= 25; h++) //初始数组
    {
        z[h] = 0;
    }

    ShowCursor(true);
    for (int i = 1; i <= d; i++)
    {
        int a = rand() % m + 5001;
        bool tu = false;
        while (tu == false) //判断题目是否重复
        {
            int su = 0;
            for (int j = 1; j <= 25; j++)
            {
                if (a == z[j])
                {
                    su++;
                }
            }
            if (su == 0)
            {
                tu = true;
                z[i] = a;
            }
            else
            {
                tu = false;
                int a1 = rand() % m + 5001;
                a = a1;
            }
        }
        title("第" + int_to_string(i, number) + "题");
        ShowCursor(true);
        gotoxy(2, 3);
        cout << ti[a].timu << endl; //输出题目
        gotoxy(2, 4);
        string b;
        char c = 0;
        cin.get(c);
        b += c;

        while (c != '\n') //输入答案
        {
            cin.get(c);
            b += c;
        }

        ShowCursor(false);
        if (judgment(b, ti[a].biaoda) == 1)
        {
            sigh("回答正确");
            num++;
        }
        else
        {
            sigh("回答错误");
        }
        GetTable();

        if (ExitOrNot() == true) //判断是否退出
        {
            return;
        }

        space();
        sigh("模式界面");
    }
    space();
    title("本轮结算");

    form5("本次共" + int_to_string(d, number) + "道题, 答对" + int_to_string(num, number) + "道题");

    ShowCursor(false);
    Exit();
}

void mode4() //设置选项
{
    let = 1;
    //进入设置选项后显示的内容
    Title("设置选项");
    title("");
    sigh("模式界面");
    space();
    gotoxy(2, 3);
    cout << "1.退出选项 ";
    cout << Bottom5("5.退出");
    gotoxy(2, 4);
    cout << "2.系统颜色 ";
    gotoxy(14, 3);
    ColorChange(ent[entk]);
    gotoxy(14, 4);
    cout << color[scolor];

    ShowCursor(false);

    //循环部分，重复检测键盘活动
    while (true)
    {
        char cn = _getch();
        //通过键盘录入改变显示内容
        if (cn == '1')
        {
            let = 1;
            cout << Bottom5("5.退出");
            gotoxy(14, 4);
            cout << color[scolor];
            cout << "     ";
            gotoxy(14, 3);
            ColorChange(ent[entk]);
            cout << "     ";
        }
        else if (cn == '2')
        {
            let = 2;
            cout << Bottom5("5.退出");
            gotoxy(14, 3);
            cout << ent[entk];
            cout << "     ";
            gotoxy(14, 4);
            ColorChange(color[scolor]);
            cout << "     ";
        }
        else if (cn == '5')
        {
            let = 5;
            gotoxy(14, 3);
            cout << ent[entk];
            gotoxy(14, 4);
            cout << color[scolor];
            ColorChange(Bottom5("5.退出"));
        }
        else if (cn == 13) //按下回车键
        {
            if (let == 1)
            {
                if (entk == 1)
                {
                    gotoxy(14, 3);
                    ColorChange(ent[0]);
                    cout << "     ";
                    entk = 0;
                }
                else
                {
                    gotoxy(14, 3);
                    ColorChange(ent[1]);
                    cout << "     ";
                    entk = 1;
                }
            }
            else if (let == 2)
            {
                scolor++;
                if (scolor >= 3)
                {
                    scolor -= 3;
                }
                if (scolor == 0)
                {
                    system("color E");
                }
                else if (scolor == 1)
                {
                    system("color 7");
                }
                else
                {
                    system("color A");
                }
                gotoxy(14, 4);
                ColorChange(color[scolor]);
                cout << "     ";
            }
            else if (let == 5)
            {
                break;
            }
        }
    }
    Bottom5("");
    ShowCursor(false);
}

void mode5() //使用说明
{
    //显示的内容
    Title("使用说明");
    title("");
    sigh("模式界面");
    space();
    ShowCursor(false);
    gotoxy(2, 3);
    cout << "欢迎使用题库系统v1.2.2，以下是相关使用说明：";
    gotoxy(2, 4);
    cout << "1.主菜单页面按键盘1~6数字进行选择，按Enter键确认.";
    gotoxy(2, 5);
    cout << "2.进入模式后，按照要求进行操作，结束后按任意键退出";

    gotoxy(2, 7);
    cout << "-系统日志";
    gotoxy(2, 8);
    cout << "-修改底层代码，优化类图形化体验。";
    gotoxy(2, 9);
    cout << "-优化了部分代码，以及程序运行效率。";
    gotoxy(2, 10);
    cout << "-优化了部分题库内容。" << endl;
    gotoxy(2, 11);
    ColorChange(Bottom5("5.退出"));

    while (true) //重复判断是否按下回车键，按下后退出使用说明
    {
        char ch = _getch();
        if (ch == 13)
        {
            break;
        }
    }
    Bottom5("");
    ShowCursor(false);
}

void mode6() //退出系统
{
    Title("退出系统");
    title("");
    sigh("模式界面");
    space();
    ShowCursor(false);
    int zt = 2;
    if (entk == 1)
    {
        form3("您正在尝试退出系统，退出后将清空所有用户数据，是否继续？");
        while (true)
        {
            if (zt == 1)
            {
                gotoxy(20, 8);
                ColorChange("1.是");
                cout << " ";
                cout << "                         ";
                cout << "2.否";
            }
            else
            {
                gotoxy(20, 8);
                cout << "1.是" << " ";
                cout << "                         ";
                ColorChange("2.否");
            }
            char cx = _getch();

            if (cx == '1')
            {
                zt = 1;
            }
            if (cx == '2')
            {
                zt = 2;
            }
            if (cx == 13)
            {
                if (zt == 1)
                {
                    a3 = zt;
                    Quit = true;
                    return;
                }
                if (zt == 2)
                {
                    a3 = zt;
                    break;
                }
            }
        }
    }
    else
    {
        Quit = true;
        return;
    }
}

void Menu() //主菜单
{
    //进入菜单后显示的内容
    check = 0;
    ShowCursor(false);
    space();
    Title("主页菜单");
    title("");
    gotoxy(mode[1].x, mode[1].y);
    cout << "1.选择模式";
    gotoxy(mode[2].x, mode[2].y);
    cout << "2.随机模式";
    gotoxy(mode[3].x, mode[3].y);
    cout << "3.化学模式";
    gotoxy(mode[4].x, mode[4].y);
    cout << "4.设置选项";
    gotoxy(mode[5].x, mode[5].y);
    cout << "5.使用说明";
    gotoxy(mode[6].x, mode[6].y);
    cout << "6.退出系统";
    sigh("请按数字键选择模式，按Enter确认");

    while (true) //重复监测键盘输入
    {
        char ch = 0;
        ch = _getch(); //获取键盘输入

        //删除原先选中模式
        if (check == 1 && ch != '1')
        {
            gotoxy(mode[1].x, mode[1].y);
            cout << "1.选择模式";
        }
        if (check == 2 && ch != '2')
        {
            gotoxy(mode[2].x, mode[2].y);
            cout << "2.随机模式";
        }
        if (check == 3 && ch != '3')
        {
            gotoxy(mode[3].x, mode[3].y);
            cout << "3.化学模式";
        }
        if (check == 4 && ch != '4')
        {
            gotoxy(mode[4].x, mode[4].y);
            cout << "4.设置选项";
        }
        if (check == 5 && ch != '5')
        {
            gotoxy(mode[5].x, mode[5].y);
            cout << "5.使用说明";
        }
        if (check == 6 && ch != '6')
        {
            gotoxy(mode[6].x, mode[6].y);
            cout << "6.退出系统";
        }

        //显示此时的选中模式
        if (ch == '1')
        {
            gotoxy(mode[1].x, mode[1].y);
            ColorChange("1.选择模式");
            title("选择模式确认");
            check = 1;
            sigh("单项选择的选择题题库，每轮题目5~10道");
        }
        else if (ch == '2')
        {
            gotoxy(mode[2].x, mode[2].y);
            ColorChange("2.随机模式");
            title("随机模式确认");
            check = 2;
            sigh("随机简答题，每轮题目1道");
        }
        else if (ch == '3')
        {
            gotoxy(mode[3].x, mode[3].y);
            ColorChange("3.化学模式");
            title("化学模式确认");
            check = 3;
            sigh("化学学科的简答题，每轮题目5~10道");
        }
        else if (ch == '4')
        {
            gotoxy(mode[4].x, mode[4].y);
            ColorChange("4.设置选项");
            title("设置选项确认");
            check = 4;
            sigh("设置相关内容以改善用户体验");
        }
        else if (ch == '5')
        {
            gotoxy(mode[5].x, mode[5].y);
            ColorChange("5.使用说明");
            title("使用说明确认");
            check = 5;
            sigh("题库系统的使用说明及注意事项");
        }
        else if (ch == '6')
        {
            gotoxy(mode[6].x, mode[6].y);
            ColorChange("6.退出系统");
            title("退出系统确认");
            check = 6;
            sigh("退出系统，并清空所有用户数据");
        }
        else
        {
            title("");
            sigh("请按数字键选择模式，按Enter确认");
        }

        if (ch == 13) //按下回车键确认，并进入模式
        {
            if (check == 1)
            {
                mode1();
                break;
            }
            if (check == 2)
            {
                mode2();
                break;
            }
            if (check == 3)
            {
                mode3();
                break;
            }
            if (check == 4)
            {
                mode4();
                break;
            }
            if (check == 5)
            {
                mode5();
                break;
            }
            if (check == 6)
            {
                mode6();
                break;
            }
        }
    }
}

int main()
{
    system("mode con cols=80 lines=16"); //设置窗口大小
    system("title 题库系统"); //系统名字
    system("color E"); //系统文字颜色
    SetMode();
    ExitCursor();
    SizeGoAway();
    DeleteGoAway();
    GetTable();
    ShowCursor(false);
    tik1();
    tik2();
    tik3();
    n_num();
    m_num();
    p_num();
    while (Quit == false)
    {
        Menu();
    }
    gotoxy(1, 12);
    return 0;
}