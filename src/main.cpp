#include <vector>
#include <string>
#include <iostream>
#include <chrono>

// 値返し (RVOに頼る)
std::vector<std::string> return_value()
{
    return std::vector<std::string>(10'000, "test");
}

// 出力引数 (参照)
void output_argument(std::vector<std::string> &v)
{
    v = std::vector<std::string>(10'000, "test");
}

// move
std::vector<std::string> return_move()
{
    std::vector<std::string> v(10'000, "test");
    return std::move(v);
}

int main()
{
    using namespace std::chrono;

    {
        high_resolution_clock::time_point begin = high_resolution_clock::now();
        for (int i = 0; i < 100'000; ++i)
        {
            std::vector<std::string> v = return_value();
        }
        high_resolution_clock::time_point end = high_resolution_clock::now();
        milliseconds elapsed_time = duration_cast<milliseconds>(end - begin);
        std::cout << "RVO: " << elapsed_time.count() << "ms" << std::endl;
    }

    {
        high_resolution_clock::time_point begin = high_resolution_clock::now();
        for (int i = 0; i < 100'000; ++i)
        {
            std::vector<std::string> v;
            output_argument(v);
        }
        high_resolution_clock::time_point end = high_resolution_clock::now();
        milliseconds elapsed_time = duration_cast<milliseconds>(end - begin);
        std::cout << "Output Argument: " << elapsed_time.count() << "ms" << std::endl;
    }

    {
        high_resolution_clock::time_point begin = high_resolution_clock::now();
        for (int i = 0; i < 100'000; ++i)
        {
            std::vector<std::string> v = return_move();
        }
        high_resolution_clock::time_point end = high_resolution_clock::now();
        milliseconds elapsed_time = duration_cast<milliseconds>(end - begin);
        std::cout << "Move: " << elapsed_time.count() << "ms" << std::endl;
    }

    return 0;
}
