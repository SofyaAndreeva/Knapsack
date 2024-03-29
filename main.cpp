#include "ReadWriter.h"
//vector, string, iostream included in "ReadWriter.h"

using namespace std;

//Можно добавлять любые вспомогательные методы и классы для решения задачи.

void PushResult(int i, int j, int** A, pair<int, int>* items, vector<pair<int, int>>& res)
{
    if (A[i][j] == 0)
        return;
    else if (A[i - 1][j] == A[i][j])
        PushResult(i - 1, j, A, items, res);
    else
    {
        PushResult(i - 1, j - items[i - 1].first, A, items, res);
        res.push_back(items[i - 1]);
    }
}

//Задача реализовать этот метод
//param N - количество предметов
//param W - ограничения на вес рюкзака
//param items - массив размера N, с предметами - first = вес, second = стоимость
//param res - вектор результатов (предметы, которые надо взять)
void solve(int N, int W, pair<int, int>* items, vector<pair<int, int>>& res)
{
    int** A = new int*[N + 1];
    for (int i = 0; i <= N; i++)
        A[i] = new int[W + 1];

    for(int i = 0;i <= W; i++)
        A[0][i] = 0;

    for(int i = 1; i <= N; i++)
    {
        for(int j = 0; j <= W; j++)
        {
            A[i][j] = A[i - 1][j];
            if (j >= items[i - 1].first && ( A[i - 1][j - items[i - 1].first] + items[i - 1].second > A[i][j]))
                A[i][j] = A[i - 1][j - items[i - 1].first] + items[i - 1].second;
        }
    }

    PushResult(N, W, A, items, res);

    for (int i = 0; i <= N; i++)
        delete[] A[i];
    delete[] A;

}

int main(int argc, const char * argv[])
{
    ReadWriter rw;
    int N = rw.readInt(); //количество предметов
    int W = rw.readInt(); //ограничения на вес рюкзака

    //структура массив pair выбрана, так как известно количество и у объекта всего 2 характеристики
    //first = вес(weight), second = стоимость (cost)
    //Можно переложить данные в любую другую удобную струтуру
    //Внимание(!) данные не упорядочены, но можно это сделать если вам требуется
    pair<int, int>* arr = new pair<int, int>[N];
    rw.readArr(arr, N);

    //структура вектор pair выбрана, так как неизвестно количество элементов, и у объекта всего 2 характеристики
    //результат, также first = вес(weight), second = стоимость (cost)
    vector<pair<int, int>> res;
    solve(N, W, arr, res);

    int sumCost = 0, sumWeight = 0;
    for (int i = 0; i < res.size(); i++)
    {
        sumWeight += res[i].first;
        sumCost += res[i].second;
    }
    //записываем ответ в файл
    rw.writeInt(sumCost);
    rw.writeInt(sumWeight);
    rw.writeInt(res.size());
    rw.writeVector(res);

    delete[] arr;
    return 0;
}