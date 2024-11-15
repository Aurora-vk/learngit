//五子棋
 
#include<iostream>
#include<time.h>
 
#include<stdlib.h>
 
using namespace std;
 
const int N = 15;//棋盘大小
const char ChessBoardFlag = ' ';
const char flag1 = 'O';
const char flag2 = 'X';
 
typedef struct Coordinate
{
    int x;
    int y;
}ChessCoordi;
 
class FiveChess
{
public:
    FiveChess()
    {
        InitChessBoard();
    }
 
    void Play()
    {
        ChessCoordi Pos1;
        ChessCoordi Pos2;
        while (1){
            int mode = ChoseMode();
            while (1){
                if (mode == 1){//玩家VS电脑
                    static size_t count = 1;
                    PalyerGo(Pos1, 1, flag1);
                    if (count++ >= 9 && GetWiner(Pos1, 1, flag1))
                        break;
                    ComputerGo(Pos2, flag2);
                    if (count++ >= 10 && GetWiner(Pos2, 0, flag2))
                       break;
                }
                else if (mode == 2){//玩家VS玩家
                    static size_t count = 1;
                    PalyerGo(Pos1, 1, flag1);
                    if (count++ >= 9 && GetWiner(Pos1,1, flag1))
                        break;
                    PalyerGo(Pos2,2 ,flag2);
                    if (count++ >= 10 && GetWiner(Pos2,2, flag2))
                        break;
                }
            }
            cout << "再来一局 y or no" << endl;
            char chose = 'y';
            cin >> chose;
            if (chose == 'n')
                break;
        }
    }
 
    void PrintChessBoard()
    {
        system("cls");
        for (size_t i = 0; i < N + 1; ++i)
        {
            for (size_t j = 0; j < N + 1; ++j)
            {
                if (i == 0){
                    if (j != 0)
                        printf("%d   ", j);
                    else if (j == 0)
                        printf("  ");
                }
                else if (j == 0){
                    if (i != 0)
                        printf("%2d", i);
                }
                else{
                    printf("%c  |", ChessBoard[i][j]);
                }
 
            }
            cout << endl;
            cout << "  ";
            for (size_t i = 1; i < N + 1; ++i){
                cout << "---+";
            }
            cout << endl;
        }
    }
 
    void InitChessBoard()
    {
        for (size_t i = 0; i < N + 1; ++i){
            for (size_t j = 0; j < N + 1; ++j){
                ChessBoard[i][j] = ChessBoardFlag;
            }
        }
    }
 
protected:
 
    int ChoseMode()
    {
        system("cls");
        InitChessBoard();
        cout << "请选择 1.玩家VS电脑 2.玩家VS玩家 3.退出" << endl;
        int chose = 0;
        cin >> chose;
        while (1){
            if (chose == 1)
                return chose;
            else if (chose == 2)
                return chose;
            else if (chose == 3)
                exit(1);
            else
                cout << "对不起 您的输入有误。。" << endl;
        }
    }
 
    void PalyerGo(ChessCoordi& Pos, int player, char flag)
    {
        PrintChessBoard();
        int x = 0;
        int y = 0;
        while (1){
            cout << "请玩家" << player << "下一步棋" << endl;
            cin >> Pos.x >> Pos.y;
            if (JudgePos(Pos))
                break;
            else
                cout << "玩家输入错误 ! 请重新输入" << endl;
        }
        ChessBoard[Pos.x][Pos.y] = flag;
    }
 
    void ComputerGo(ChessCoordi& Pos, char flag)
    {
        PrintChessBoard();
        int x = 0;
        int y = 0;
        while (1){
            x = rand() % N + 1;
            srand((unsigned int)time(NULL));
            y = rand() % N + 1;
            srand((unsigned int)time(NULL));//这种方式下生成的x，y一定在棋盘上
            if (ChessBoard[x][y] == ChessBoardFlag)
                break;
        }
        Pos.x = x;
        Pos.y = y;
        ChessBoard[Pos.x][Pos.y] = flag;
    }
 
    int GetVictory(ChessCoordi Pos, char flag)//判断是否有赢家
    {
        int begin = 0;//在检查对角线时 作为行坐标的开始 结束
        int end = 0;
        //检查行是否连续5个子
        int beginl = 0;//在检查对角线时 作为列坐标的开始 结束
        int endl = 0;
        (Pos.y - 4) > 0 ? begin = Pos.y - 4 : begin = 1;
        (Pos.y + 4) < N ? end = Pos.y + 4 : end = N;
        for (size_t i = Pos.x, j = begin; j + 4 <= end; ++j)
        {
            if (flag == ChessBoard[i][j] && flag == ChessBoard[i][j + 1] && \
                flag == ChessBoard[i][j + 2] && flag == ChessBoard[i][j + 3] && \
                flag == ChessBoard[i][j + 4])
                return 1;
        }
        //检查列是否连续5个子
        (Pos.x - 4) > 0 ? begin = Pos.x - 4 : begin = 1;
        (Pos.x + 4) > N ? end = Pos.x + 4 : end = N;
        for (size_t j = Pos.y, i = begin; i + 4 <= end; ++i)
        {
            if (flag == ChessBoard[i][j] && flag == ChessBoard[i + 1][j] && \
                flag == ChessBoard[i + 2][j] && flag == ChessBoard[i + 3][j] && \
                flag == ChessBoard[i + 4][j])
                return 1;
        }
 
        int len = 0;
        //检查主对角线是否满五个子
        (Pos.x > Pos.y) ? len = Pos.y - 1 : len = Pos.x - 1;
        if (len > 4)//找落子点到上 左两边的垂直距离较短的地方 如果其大于4 取4 不大于4 取其本身
            len = 4;
        begin = Pos.x - len;//向上 左移动适当距离找可能的五连子的起始位置
        beginl = Pos.y - len;
        (Pos.x > Pos.y) ? len = N - Pos.x : len = N - Pos.y;
        if (len > 4)
            len = 4;
        end = Pos.x + len;//向下 右移动适当距离找可能的五连子的终止位置
        endl = Pos.y + len;
        for (size_t i = begin, j = beginl; i + 4 <= end && j + 4 <= endl; ++i, ++j)
        {
            if (flag == ChessBoard[i][j] && flag == ChessBoard[i + 1][j + 1] && \
                flag == ChessBoard[i + 2][j + 2] && flag == ChessBoard[i + 3][j + 3] && \
                flag == ChessBoard[i + 4][j + 4])
                return 1;
        }
        //检查副对角线是否满五个子
        (Pos.x - 1 > N - Pos.y) ? len = N - Pos.y : Pos.x - 1;
        if (len > 4)//找落子点到右 下两边的垂直距离较短的地方 如果其大于4 取4 不大于4 取其本身
            len = 4;
        begin = Pos.x - len;//向上 右移动适当距离找可能的五连子的起始位置
        beginl = Pos.y + len;
        (N - Pos.x > Pos.y - 1) ? len = Pos.y - 1 : len = N - Pos.x;
        end = Pos.x + len;//向下 左移动适当距离找可能的五连子的最终位置
        endl = Pos.y - len;
        for (size_t i = begin, j = beginl; i + 4 <= end && j - 4 >= endl; ++i, ++j)
        {
            if (flag == ChessBoard[i][j] && flag == ChessBoard[i + 1][j - 1] && \
                flag == ChessBoard[i + 2][j - 2] && flag == ChessBoard[i + 3][j - 3] && \
                flag == ChessBoard[i + 4][j - 4])
                return 1;
        }
        //检查棋盘是否已满
        for (size_t i = 1; i < N + 1; ++i){
            for (size_t j = 1; j < N + 1; ++j){
                if (ChessBoard[i][j] == ChessBoardFlag)
                    return 0;//表示棋盘没满
            }
        }
        //和棋
        return -1;
    }
 
    bool GetWiner(ChessCoordi& Pos, int player, char flag)//判断是谁赢了
    {
        int n = 0;
        n = GetVictory(Pos, flag);
        PrintChessBoard();
        if (1 == n){
            if (0 == player)
                cout << "玩家1获胜" << endl;
            else if (1 == player)
                cout << "玩家1获胜" << endl;
            else
                cout << "电脑获胜"<<endl;
            return true;
        }
        else if (-1 == n){
            cout << "和棋" << endl;
            return true;
        }
        else{
            //还未分出胜负
            return false;
        }
 
    }
 
    bool JudgePos(const ChessCoordi& Pos)
    {
        if (Pos.x < N + 1 && Pos.x > 0 && Pos.y < N + 1 && Pos.x > 0\
            && ChessBoard[Pos.x][Pos.y] == ChessBoardFlag)
            return true;
 
        return false;
    }
 
private:
    char ChessBoard[N + 1][N + 1];
};
 
//#include"FiveChess.cpp"
int main()
{
    //char a[] = "exit";
    //for (size_t i = 0; i < sizeof(a) / sizeof(char);++i)
    //printf(":%d", a[i]);
    FiveChess a;
    a.InitChessBoard();
    a.PrintChessBoard();
    a.Play();
    system("pause");
    return 0;
}