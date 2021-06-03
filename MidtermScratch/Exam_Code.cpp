#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <functional>
#include <chrono>


using std::vector;

template <typename T> class Matrix
{
public:
    Matrix(int x, int y) : _x(x), _y(y) 
    {
        //initialize contents to default value
        for (int i = 0; i < _x; i++)
        {
            //generate a column
            vector<T> column;
            for (int j = 0; j < _y; j++)
            {
                column.push_back(T());
            }

            //add it to the matrix
            _matrixContents.push_back(column);
        }
    }
    Matrix(Matrix &inpMatrix)
    {
        _x = inpMatrix.GetXDim();
        _y = inpMatrix.GetYDim();

        //initialize contents to given matrix's value
        for (int i = 0; i < _x; i++)
        {
            //generate a column
            vector<T> column;
            for (int j = 0; j < _y; j++)
            {
                column.push_back(inpMatrix.GetEntry(i,j));
            }

            //add it to the matrix
            _matrixContents.push_back(column);
        }
    }
    T GetEntry(int x, int y)
    {
        //validate coordinates are within matrix
        if (x >= 0 && y >= 0 && x < _x && y < _y)
        {
            return _matrixContents[x][y];
        }
        else
        {
            //I choose to return the default T to fail silently
            return T();
        }
    }
    void SetEntry(int x, int y, T value)
    {
        //validate coordinates are within matrix
        if (x < _x && y < _y)
        {
            _matrixContents[x][y] = value;
        }
    }
    int GetXDim()
    {
        return _x;
    }
    int GetYDim()
    {
        return _y;
    }
private:
    int _x, _y;
    vector<vector<T>> _matrixContents;
};

class NonTemplatedClassWithTemplatedFunction
{
public:
    template <typename T> T Func(T data)
    {
        return data;
    }
};

template <typename T> class TemplatedWithPureVirtual
{
public:
    virtual void Func(T data) = 0;
};

//void ThreadFunction(int id, std::condition_variable cv, std::mutex mutex, std::mutex finishMutex)
//{
//    //assuming N threads have been made starting with id = N
//    std::unique_lock<std::mutex> lock(mutex);
//    //int nextThreadToExecute is set to the first index 
//    //and stored on the containing class
//    EnterFoo(id, cv, lock);
//    //Foo();
//    ExitFoo(cv, lock, finishMutex);
//}
//
//void EnterFoo(int id, std::condition_variable cv, std::unique_lock<std::mutex> lock)
//{
//    cv.wait(lock, [id] {return id == nextThreadToExecute});
//}
//
//void ExitFoo(std::condition_variable cv, std::unique_lock<std::mutex> lock, std::mutex finishMutex)
//{
//    //get next thread or trigger exit
//    nextThreadToExecute++;
//
//    if (nextThreadToExecute > N)
//    {
//        //all threads have completed
//        //bool allThreadsDone defined on containing class
//        allThreadsDone = true;
//        lock.unlock();
//        cv.notify_all();
//    }
//    else
//    {
//        //wait until all threads are done
//        std::unique_lock<std::mutex> finishLock(finishMutex);
//        cv.wait(finishLock, [] { return allThreadsDone; });
//    }
//}

class Adder
{
public:
    Adder(int x)
    {
        x_ = x;
    }
    int Add(int y)
    {
        return x_ + y;
    }
private:
    int x_;
};

std::function<int(int)> Function(int x)
{
    Adder adder(x);
    return  [&](int x) { return adder.Add(x); };
}


int main()
{
    auto test = Function(5);
    int t = test(10);
}